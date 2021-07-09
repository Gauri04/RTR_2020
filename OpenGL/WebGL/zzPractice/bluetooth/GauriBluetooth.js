
var grvertexShaderObject;
var grfragmentShadeerObject;
var grshaderProgramObject;

var grgPerspectiveProjectionMatrix;

var grgVaoBluetooth;
var grgVboBluetoothPosition;

var grfangleBluetoothX = 0.0;
var grfangleBluetoothY = 0.0;
var grtransBluetoothX = 0.0;
var grtransBluetoothY = 0.0;
var grtransBluetoothZ = -10.0;


// texture
var grgtextureBluetooth;
var grgtextureButtons;
var grgtextureSamplerUniformBluetooth;

var grgModelMatrixUniformBluetooth;
var grgViewMatrixUniformBluetooth;
var grgProjectionMatrixUniformBluetooth;
var grgIsButtonUniform;

var grstackMatrixBluetooth = [];
var grmatrixPositionBluetooth = -1;
var grcircleCountBluetooth = 0;
var grmodelMatrixBluetooth;
var grviewMatrixBluetooth;
var grprojectionMatrixBluetooth; 
var grscaleMatrixBluetooth;
var grtranslateMatrixBluetooth;
var grrotateMatrixBluetooth;
var circleVerticesBluetooth;


function GRInitBluetooth() 
{   
   
    // vertex shader
    var grvertexShaderSourceCode =
        "#version 300 es" +
        "\n" +
        "in vec4 vPosition;" +
        "in vec2 vTexCoord;" +
        "uniform mat4 u_model_matrix;" +
        "uniform mat4 u_view_matrix;" +
        "uniform mat4 u_projection_matrix;" +
        "out vec2 out_texcoord;" +
        "uniform mediump int u_is_sphere;" +
        "void main(void)" +
        "{" +
        "gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" +
        "if(u_is_sphere == 1)" +
        "{" +
        "out_texcoord = vec2(vPosition.x + 1.5, vPosition.z* 0.8);" +
        "}" +
        "else" +
        "{" +
        "out_texcoord = vec2(vPosition.x + 0.47, vPosition.y + 0.44 * 1.22);" +
        "}" +
        "}";

    // working 
    //"out_texcoord = vec2(vPosition.x + 1.4, vPosition.z* 0.8);" +
    grvertexShaderObject = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(grvertexShaderObject, grvertexShaderSourceCode);
    gl.compileShader(grvertexShaderObject);
    if (gl.getShaderParameter(grvertexShaderObject, gl.COMPILE_STATUS) == false) 
    {
        var error = gl.getShaderInfoLog(grvertexShaderObject);
        if (error.length > 0) 
        {
            alert(error);
            uninitialize();
        }
        alert("in compile vertex shader error");

    }
    

    var grfragmentShaderSourceCode =
        "#version 300 es" +
        "\n" +
        "precision highp float;" +
        "in vec2 out_texcoord;" +
        "uniform highp sampler2D u_texture_sampler;" +
        "uniform mediump int u_is_sphere;" +
        "out vec4 FragColor;" +
        "void main(void)" +
        "{" +
        "FragColor = texture(u_texture_sampler, out_texcoord);" +
        "}";
       
    grfragmentShaderObject = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(grfragmentShaderObject, grfragmentShaderSourceCode);
  
    gl.compileShader(grfragmentShaderObject);
    if (gl.getShaderParameter(grfragmentShaderObject, gl.COMPILE_STATUS) == false) 
    {
        alert("in compile fragment shader error");
        var error = gl.getShaderInfoLog(grfragmentShaderObject);
        if (error.length > 0) 
        {
            alert(error);
            uninitialize();
        }
       

    }
    // shader program
    grshaderProgramObject = gl.createProgram();
    //attach shader object
    gl.attachShader(grshaderProgramObject, grvertexShaderObject);
    gl.attachShader(grshaderProgramObject, grfragmentShaderObject);
    // pre-linking
    gl.bindAttribLocation(grshaderProgramObject, macros.AMC_ATTRIB_POSITION, "vPosition");
    gl.bindAttribLocation(grshaderProgramObject, macros.AMC_ATTRIB_TEXCOORD, "vTexCoord");

    // linking
    gl.linkProgram(grshaderProgramObject);
    if (!gl.getProgramParameter(grshaderProgramObject, gl.LINK_STATUS)) 
    {
        var err = gl.getProgramInfoLog(grshaderProgramObject);
        if (err.length > 0) 
        {
            alert(err);

        }

        alert("in shader program object error");
        alert(err);
        uninitialize(); 
    }

    // mvp uniform binding
    grgModelMatrixUniformBluetooth = gl.getUniformLocation(grshaderProgramObject, "u_model_matrix");
    grgViewMatrixUniformBluetooth = gl.getUniformLocation(grshaderProgramObject, "u_view_matrix");
    grgProjectionMatrixUniformBluetooth = gl.getUniformLocation(grshaderProgramObject, "u_projection_matrix");
    grtextureSamplerUniform = gl.getUniformLocation(grshaderProgramObject, "u_texture_sampler");
    grgIsButtonUniform = gl.getUniformLocation(grshaderProgramObject, "u_is_sphere");

    var circleVerts = new Float32Array(37704);
    var index = 0;
    var i;
    for(i = 0.0; i < 2 * 3.142; i = i + 0.001)
    {
      
        circleVerts[index] = 0.53 * Math.cos(i);
        circleVerts[index + 1] = 0.3 * Math.sin(i);
        circleVerts[index + 2] = 0.0;

        circleVerts[index + 3] = 0.53 * Math.cos(i);
        circleVerts[index + 4] = 0.3 * Math.sin(i);
        circleVerts[index + 5] = 1.2;
        index = index + 6;

    }



    // lights (cylinder)
    grgVaoBluetooth = gl.createVertexArray();
    gl.bindVertexArray(grgVaoBluetooth);

    grgVboBluetoothPosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboBluetoothPosition);
    gl.bufferData(gl.ARRAY_BUFFER, circleVerts, gl.STATIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    gl.bindVertexArray(null);

    
    // texture
    grgtextureBluetooth = gl.createTexture();
    grgtextureBluetooth.image = new Image();
    grgtextureBluetooth.image.src = "GauriResources/bose.jpg";
    grgtextureBluetooth.image.onload = function () 
    {
        gl.bindTexture(gl.TEXTURE_2D, grgtextureBluetooth);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.MIRRORED_REPEAT);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureBluetooth.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };

    grgtextureButtons = gl.createTexture();
    grgtextureButtons.image = new Image();
    grgtextureButtons.image.src = "GauriResources/buttons.jpg";
    grgtextureButtons.image.onload = function () 
    {
        gl.bindTexture(gl.TEXTURE_2D, grgtextureButtons);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.MIRRORED_REPEAT);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureButtons.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };
    
}


function GRDisplayBluetooth() 
{
  
    gl.useProgram(grshaderProgramObject);
    GRBluetooth();
    gl.useProgram(null);

}




function GRBluetooth() 
{

    grmodelMatrixBluetooth = mat4.create();
    grviewMatrixBluetooth = mat4.create();
    grprojectionMatrixBluetooth = mat4.create();
    grscaleMatrixBluetooth = mat4.create();
    grtranslateMatrixBluetooth = mat4.create();
    grrotateMatrixBluetooth = mat4.create();

    // push matrix for stage - light geometry
    mat4.translate(grtranslateMatrixBluetooth, grtranslateMatrixBluetooth, [grtransBluetoothX, grtransBluetoothY, grtransBluetoothZ]);
    //mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(180 + grfangleXMic));
    mat4.rotateY(grrotateMatrixBluetooth, grrotateMatrixBluetooth, deg2rad(grfangleBluetoothY));
    mat4.rotateX(grrotateMatrixBluetooth, grrotateMatrixBluetooth, deg2rad(180 + grfangleBluetoothX));
    mat4.scale(grscaleMatrixBluetooth, grscaleMatrixBluetooth, [2.5, 2.5, 2.5]);
    mat4.multiply(grtranslateMatrixBluetooth, grtranslateMatrixBluetooth, grrotateMatrixBluetooth);
    mat4.multiply(grmodelMatrixBluetooth, grtranslateMatrixBluetooth, grscaleMatrixBluetooth);
    GRPushToStackBluetooth(grmodelMatrixBluetooth);


    //********************************************* mic - handle ****************************************
    //********************************************************************************************
    grmodelMatrixBluetooth = mat4.create();
    grviewMatrixBluetooth = mat4.create();
    grprojectionMatrixBluetooth = mat4.create();
    grscaleMatrixBluetooth = mat4.create();
    grtranslateMatrixBluetooth = mat4.create();
    grrotateMatrixBluetooth = mat4.create();

    mat4.translate(grtranslateMatrixBluetooth, grtranslateMatrixBluetooth, [0.0, 0.0, 0.0]);
    mat4.rotateX(grrotateMatrixBluetooth, grrotateMatrixBluetooth, deg2rad(90.0));
    mat4.multiply(grtranslateMatrixBluetooth, grtranslateMatrixBluetooth, grrotateMatrixBluetooth);
    mat4.multiply(grmodelMatrixBluetooth, grtranslateMatrixBluetooth, grscaleMatrixBluetooth);
    grmodelMatrixBluetooth = GRPushToStackBluetooth(grmodelMatrixBluetooth);
    GRPopFromStackBluetooth();

    mat4.multiply(grprojectionMatrixBluetooth, grprojectionMatrixBluetooth, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniformBluetooth, false, grmodelMatrixBluetooth);
    gl.uniformMatrix4fv(grgViewMatrixUniformBluetooth, false, grviewMatrixBluetooth);
    gl.uniformMatrix4fv(grgProjectionMatrixUniformBluetooth, false, grprojectionMatrixBluetooth);
    

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureBluetooth);
    gl.uniform1i(grgIsButtonUniform, 1);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoBluetooth);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 12568);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
    // buttons
    grmodelMatrixBluetooth = mat4.create();
    grviewMatrixBluetooth = mat4.create();
    grprojectionMatrixBluetooth = mat4.create();
    grscaleMatrixBluetooth = mat4.create();
    grtranslateMatrixBluetooth = mat4.create();
    grrotateMatrixBluetooth = mat4.create();

    mat4.translate(grtranslateMatrixBluetooth, grtranslateMatrixBluetooth, [0.0, -1.2, 0.0]);
    mat4.rotateX(grrotateMatrixBluetooth, grrotateMatrixBluetooth, deg2rad(90.0));
    mat4.scale(grscaleMatrixBluetooth, grscaleMatrixBluetooth, [1.0, 1.0, 0.03]);
    mat4.multiply(grtranslateMatrixBluetooth, grtranslateMatrixBluetooth, grrotateMatrixBluetooth);
    mat4.multiply(grmodelMatrixBluetooth, grtranslateMatrixBluetooth, grscaleMatrixBluetooth);
    grmodelMatrixBluetooth = GRPushToStackBluetooth(grmodelMatrixBluetooth);
    GRPopFromStackBluetooth();

    mat4.multiply(grprojectionMatrixBluetooth, grprojectionMatrixBluetooth, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniformBluetooth, false, grmodelMatrixBluetooth);
    gl.uniformMatrix4fv(grgViewMatrixUniformBluetooth, false, grviewMatrixBluetooth);
    gl.uniformMatrix4fv(grgProjectionMatrixUniformBluetooth, false, grprojectionMatrixBluetooth);
    

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureButtons);
    gl.uniform1i(grgIsButtonUniform, 0);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoBluetooth);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 12568);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    

    GRPopFromStackBluetooth();

}


function GRPushToStackBluetooth(matrix) 
{
    if (grmatrixPositionBluetooth == -1) 
    {
        grstackMatrixBluetooth.push(matrix);
        grmatrixPositionBluetooth++;
        return matrix;
    }
    else 
    {
        var topMatrix = grstackMatrixBluetooth[grmatrixPositionBluetooth];
        mat4.multiply(matrix, topMatrix, matrix);
        grstackMatrixBluetooth.push(matrix);
        grmatrixPositionBluetooth++;
        return grstackMatrixBluetooth[grmatrixPositionBluetooth];
    }

}

function GRPopFromStackBluetooth() 
{
    if (!grstackMatrixBluetooth[0]) 
    {
        grstackMatrixBluetooth[0] = mat4.create();
        return grstackMatrixBluetooth[0];
    }
    else 
    {
        grstackMatrixBluetooth.pop();
        grmatrixPositionBluetooth--;
        return grstackMatrixBluetooth[grmatrixPositionBluetooth];
    }

}


function GRUninitializeBluetooth() 
{
    if (grgVaoBluetooth) 
    {
        gl.deleteVertexArray(grgVaoBluetooth);
        grgVaoBluetooth = null;
    }
    if (grgVboBluetoothPosition) 
    {
        gl.deleteBuffer(grgVboBluetoothPosition);
        grgVboBluetoothPosition = null;
    }  
    
    // delete textures
    if (grgtextureButtons) 
    {
        gl.deleteTexture(grgtextureButtons);
        grgtextureButtons = null;
    }
    if (grgtextureBluetooth) 
    {
        gl.deleteTexture(grgtextureBluetooth);
        grgtextureBluetooth = null;
    }
    

    if (grshaderProgramObject) 
    {
        if (grfragmentShaderObject) 
        {
            gl.detachShader(grshaderProgramObject, grfragmentShaderObject);
            gl.deleteShader(grfragmentShaderObject);
            grfragmentShaderObject = null;
        }

        if (grfragmentShaderObject) 
        {
            gl.detachShader(grshaderProgramObject, grvertexShaderObject);
            gl.deleteShader(grvertexShaderObject);
            grvertexShaderObject = null;
        }

        gl.deleteProgram(grshaderProgramObject);
        grshaderProgramObject = null;
    }
}












