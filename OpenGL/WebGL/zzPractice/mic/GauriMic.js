
var grvertexShaderObject;
var grfragmentShadeerObject;
var grshaderProgramObject;

var grgPerspectiveProjectionMatrix;

var grgVaoMic;
var grgVboMicPosition;
var grglightSphere;

var grfangleXMic = 0.0;
var grfangleYMic = 0.0;
var grfangleXHandle = 0.0;
var grtransMicX = 0.0;
var grtransMicY = 0.0;
var grtransMicZ = -10.0;


// texture
var grgtextureMicSphere;
var grgtextureSamplerUniform;

var grgModelMatrixUniform;
var grgViewMatrixUniform;
var grgProjectionMatrixUniform;
var grgIsMicSphereUniform;
var grgIsMicSphere = 0;

var grstackMatrix = [];
var grmatrixPosition = -1;
var grcircleCount = 0, i;
var grmodelMatrix;
var grviewMatrix;
var grprojectionMatrix; 
var grscaleMatrix;
var grtranslateMatrix;
var grrotateMatrix;


function GRInitMic() 
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
        "void main(void)" +
        "{" +
        "gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" +
        "out_texcoord = vTexCoord;" +
        "}";

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
        "uniform highp int u_is_sphere;" +
        "out vec4 FragColor;" +
        "void main(void)" +
        "{" +
        "if(u_is_sphere == 1)" +
        "{" +
        "FragColor = texture(u_texture_sampler, out_texcoord);" +
        "}" +
        "else" +
        "{" +
        "FragColor = vec4(0.2, 0.2, 0.2, 1.0);" +
        "}" +
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
    alert("in init");
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
    grgModelMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_model_matrix");
    grgViewMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_view_matrix");
    grgProjectionMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_projection_matrix");
    grtextureSamplerUniform = gl.getUniformLocation(grshaderProgramObject, "u_texture_sampler");
    grgIsMicSphereUniform = gl.getUniformLocation(grshaderProgramObject, "u_is_sphere");

    var circleVerts = new Float32Array(37704);

    var index = 0;
    for(i = 0.0; i < 2 * 3.142; i = i + 0.001)
    {
        circleVerts[index] = 0.3 * Math.cos(i);
        circleVerts[index + 1] = 0.3 * Math.sin(i);
        circleVerts[index + 2] = 0.0;

        circleVerts[index + 3] = 0.1 * Math.cos(i);
        circleVerts[index + 4] = 0.1 * Math.sin(i);
        circleVerts[index + 5] = 1.2;
        index = index + 6;

    }
    console.log("index : " + index);


    // lights (cylinder)
    grgVaoMic = gl.createVertexArray();
    gl.bindVertexArray(grgVaoMic);

    grgVboMicPosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboMicPosition);
    gl.bufferData(gl.ARRAY_BUFFER, circleVerts, gl.STATIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    grgVboCylinderTexture = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCylinderTexture);
    gl.bufferData(gl.ARRAY_BUFFER, circleVerts, gl.STATIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_TEXCOORD, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_TEXCOORD);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    gl.bindVertexArray(null);

    
    // texture
    grgtextureMicSphere = gl.createTexture();
    grgtextureMicSphere.image = new Image();
    grgtextureMicSphere.image.src = "GauriResources/mic_cloth.jpg";
    grgtextureMicSphere.image.onload = function () 
    {
        gl.bindTexture(gl.TEXTURE_2D, grgtextureMicSphere);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureMicSphere.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };
    
    grglightSphere = new Mesh();
    makeSphere(grglightSphere, 2.0, 30, 30);
}


function GRDisplayMic() 
{
  
    gl.useProgram(grshaderProgramObject);
    GRMic();
    gl.useProgram(null);

}




function GRMic() 
{

    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    // push matrix for stage - light geometry
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [grtransMicX, grtransMicY, grtransMicZ]);
    //mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(180 + grfangleXMic));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleYMic));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);
    GRPushToStack(grmodelMatrix);


    //********************************************* mic - handle ****************************************
    //********************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, 0.0]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    

    gl.uniform1i(grgIsMicSphereUniform, 0);
    
    gl.bindVertexArray(grgVaoMic);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 12568);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
   
    //********************************************* mic - sphere ****************************************
    //********************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.12, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.18, 0.18, 0.18]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureMicSphere);
    gl.uniform1i(grgIsMicSphereUniform, 1);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    grglightSphere.draw();

    gl.bindTexture(gl.TEXTURE_2D, null);
    

    GRPopFromStack();

}


function GRPushToStack(matrix) 
{
    if (grmatrixPosition == -1) 
    {
        grstackMatrix.push(matrix);
        grmatrixPosition++;
        return matrix;
    }
    else 
    {
        var topMatrix = grstackMatrix[grmatrixPosition];
        mat4.multiply(matrix, topMatrix, matrix);
        grstackMatrix.push(matrix);
        grmatrixPosition++;
        return grstackMatrix[grmatrixPosition];
    }

}

function GRPopFromStack() 
{
    if (!grstackMatrix[0]) 
    {
        grstackMatrix[0] = mat4.create();
        return grstackMatrix[0];
    }
    else 
    {
        grstackMatrix.pop();
        grmatrixPosition--;
        return grstackMatrix[grmatrixPosition];
    }

}


function GRUninitializeMic() 
{
    if (grgVaoMic) 
    {
        gl.deleteVertexArray(grgVaoMic);
        grgVaoMic = null;
    }
    if (grgVboMicPosition) 
    {
        gl.deleteBuffer(grgVboMicPosition);
        grgVboMicPosition = null;
    }
    if(grgVboCylinderTexture)
    {
        gl.deleteBuffer(grgVboMicPosition);
        grgVboMicPosition = null;
    }
   
    if(grglightSphere)
    {
        grglightSphere.deallocate();
    }
    
    
    // delete textures
    if (grgtextureLightMaterial) 
    {
        gl.deleteTexture(grgtextureLightMaterial);
        grgtextureLightMaterial = null;
    }
    if (grgtextureMicSphere) 
    {
        gl.deleteTexture(grgtextureMicSphere);
        grgtextureMicSphere = null;
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












