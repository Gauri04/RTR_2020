
var grvertexShaderObjectCoffee;
var grfragmentShadeerObjectCoffee;
var grshaderProgramObjectCoffee;


var grgVaoCoffee;
var grgVboCoffeePosition;

var grfangleCoffeeX = 0.0;
var grfangleCoffeeY = 0.0;
var grtransCoffeeX = 4.5;
var grtransCoffeeY = -0.9;
var grtransCoffeeZ =  4.2;


// texture
var grgtextureCoffee;
var grgtextureCoffeeCover;
var grgtextureSamplerUniformCoffee;

var grgModelMatrixUniformCoffee;
var grgViewMatrixUniformCoffee;
var grgProjectionMatrixUniformCoffee;
var grgIsCoffeeCoverUniform;

var grstackMatrixCoffee = [];
var grmatrixPositionCoffee = -1;
var grcircleCountCoffee = 0;
var grmodelMatrixCoffee;
var grviewMatrixCoffee;
var grprojectionMatrixCoffee; 
var grscaleMatrixCoffee;
var grtranslateMatrixCoffee;
var grrotateMatrixCoffee;
var grgCircleVertsCoffee;
var grgCylinderVertsCoffee;
var grgCylinderVertsCoffeeCover;

function GRInitCoffee() 
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
        "out_texcoord = vec2(vPosition.x + 1.5, vPosition.z* 0.8);" +     
        "}";

    // working 
    //"out_texcoord = vec2(vPosition.x + 1.4, vPosition.z* 0.8);" +
    grvertexShaderObjectCoffee = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(grvertexShaderObjectCoffee, grvertexShaderSourceCode);
    gl.compileShader(grvertexShaderObjectCoffee);
    if (gl.getShaderParameter(grvertexShaderObjectCoffee, gl.COMPILE_STATUS) == false) 
    {
        var error = gl.getShaderInfoLog(grvertexShaderObjectCoffee);
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
        "if(u_is_sphere == 1)" +
        "{" +
        "FragColor = texture(u_texture_sampler, out_texcoord);" +
        "}" +
        "else" +
        "{" +
        "FragColor = vec4(0.85, 0.85, 0.85, 1.0);" +
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
    // shader program
    grshaderProgramObjectCoffee = gl.createProgram();
    //attach shader object
    gl.attachShader(grshaderProgramObjectCoffee, grvertexShaderObjectCoffee);
    gl.attachShader(grshaderProgramObjectCoffee, grfragmentShaderObject);
    // pre-linking
    gl.bindAttribLocation(grshaderProgramObjectCoffee, macros.AMC_ATTRIB_POSITION, "vPosition");
    gl.bindAttribLocation(grshaderProgramObjectCoffee, macros.AMC_ATTRIB_TEXCOORD, "vTexCoord");

    // linking
    gl.linkProgram(grshaderProgramObjectCoffee);
    if (!gl.getProgramParameter(grshaderProgramObjectCoffee, gl.LINK_STATUS)) 
    {
        var err = gl.getProgramInfoLog(grshaderProgramObjectCoffee);
        if (err.length > 0) 
        {
            alert(err);

        }

        alert("in shader program object error");
        alert(err);
        uninitialize(); 
    }

    // mvp uniform binding
    grgModelMatrixUniformCoffee = gl.getUniformLocation(grshaderProgramObjectCoffee, "u_model_matrix");
    grgViewMatrixUniformCoffee = gl.getUniformLocation(grshaderProgramObjectCoffee, "u_view_matrix");
    grgProjectionMatrixUniformCoffee = gl.getUniformLocation(grshaderProgramObjectCoffee, "u_projection_matrix");
    grtextureSamplerUniform = gl.getUniformLocation(grshaderProgramObjectCoffee, "u_texture_sampler");
    grgIsCoffeeCoverUniform = gl.getUniformLocation(grshaderProgramObjectCoffee, "u_is_sphere");

    /*
    var grgCircleVertsCoffee;
var grgCylinderVertsCoffee;
    */
    grgCircleVertsCoffee = new Float32Array(37704);
    var index = 0;
    var i;
    for(i = 0.0; i < 2 * 3.142; i = i + 0.001)
    {
      
        grgCircleVertsCoffee[index] = 0.3 * Math.cos(i);
        grgCircleVertsCoffee[index + 1] = 0.3 * Math.sin(i);
        grgCircleVertsCoffee[index + 2] = 0.0;

        grgCircleVertsCoffee[index + 3] = 0.53 * Math.cos(i);
        grgCircleVertsCoffee[index + 4] = 0.53 * Math.sin(i);
        grgCircleVertsCoffee[index + 5] = 1.4;
        index = index + 6;

    }

    index = 0;
    grgCylinderVertsCoffee = new Float32Array(37704);
    for(i = 0.0; i < 2 * 3.142; i = i + 0.001)
    {
      
        grgCylinderVertsCoffee[index] = 0.53 * Math.cos(i);
        grgCylinderVertsCoffee[index + 1] = 0.53 * Math.sin(i);
        grgCylinderVertsCoffee[index + 2] = 0.0;

        grgCylinderVertsCoffee[index + 3] = 0.53 * Math.cos(i);
        grgCylinderVertsCoffee[index + 4] = 0.53 * Math.sin(i);
        grgCylinderVertsCoffee[index + 5] = 1.4;
        index = index + 6;

    }
    
    index = 0;
    grgCylinderVertsCoffeeCover = new Float32Array(37704);
    for(i = 0.0; i < 2 * 3.142; i = i + 0.001)
    {
      
        grgCylinderVertsCoffeeCover[index] = 0.54 * Math.cos(i);
        grgCylinderVertsCoffeeCover[index + 1] = 0.54 * Math.sin(i);
        grgCylinderVertsCoffeeCover[index + 2] = 0.0;

        grgCylinderVertsCoffeeCover[index + 3] = 0.46 * Math.cos(i);
        grgCylinderVertsCoffeeCover[index + 4] = 0.46 * Math.sin(i);
        grgCylinderVertsCoffeeCover[index + 5] = 1.4;
        index = index + 6;

    }

    // lights (cylinder)
    grgVaoCoffee = gl.createVertexArray();
    gl.bindVertexArray(grgVaoCoffee);

    grgVboCoffeePosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCoffeePosition);
    gl.bufferData(gl.ARRAY_BUFFER, null, gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    gl.bindVertexArray(null);

    
    // texture
    grgtextureCoffee = gl.createTexture();
    grgtextureCoffee.image = new Image();
    grgtextureCoffee.image.src = "GauriResources/star.jpg";
    grgtextureCoffee.image.onload = function () 
    {
        gl.bindTexture(gl.TEXTURE_2D, grgtextureCoffee);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureCoffee.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };

    grgtextureCoffeeCover = gl.createTexture();
    grgtextureCoffeeCover.image = new Image();
    grgtextureCoffeeCover.image.src = "GauriResources/grey.jpg";
    grgtextureCoffeeCover.image.onload = function () 
    {
        gl.bindTexture(gl.TEXTURE_2D, grgtextureCoffeeCover);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.MIRRORED_REPEAT);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureCoffeeCover.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };
    
}


function GRDisplayCoffee() 
{
  
    gl.useProgram(grshaderProgramObjectCoffee);
    GRCoffee();
    gl.useProgram(null);

}




function GRCoffee() 
{

    grmodelMatrixCoffee = mat4.create();
    grviewMatrixCoffee = mat4.create();
    grprojectionMatrixCoffee = mat4.create();
    grscaleMatrixCoffee = mat4.create();
    grtranslateMatrixCoffee = mat4.create();
    grrotateMatrixCoffee = mat4.create();

    // push matrix for stage - light geometry
    mat4.translate(grtranslateMatrixCoffee, grtranslateMatrixCoffee, [grtransCoffeeX, grtransCoffeeY, grtransCoffeeZ]);
    //mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(180 + grfangleXMic));
    mat4.rotateY(grrotateMatrixCoffee, grrotateMatrixCoffee, deg2rad(40));
    mat4.rotateX(grrotateMatrixCoffee, grrotateMatrixCoffee, deg2rad(180 + grfangleCoffeeX));
    mat4.scale(grscaleMatrixCoffee, grscaleMatrixCoffee, [0.11, 0.15, 0.15]);
    mat4.multiply(grtranslateMatrixCoffee, grtranslateMatrixCoffee, grrotateMatrixCoffee);
    mat4.multiply(grmodelMatrixCoffee, grtranslateMatrixCoffee, grscaleMatrixCoffee);
    GRPushToStackCoffee(grmodelMatrixCoffee);


    //********************************************* cup ****************************************
    //********************************************************************************************
    grmodelMatrixCoffee = mat4.create();
    grviewMatrixCoffee = mat4.create();
    grprojectionMatrixCoffee = mat4.create();
    grscaleMatrixCoffee = mat4.create();
    grtranslateMatrixCoffee = mat4.create();
    grrotateMatrixCoffee = mat4.create();

    mat4.translate(grtranslateMatrixCoffee, grtranslateMatrixCoffee, [0.0, 0.0, 0.0]);
    mat4.rotateX(grrotateMatrixCoffee, grrotateMatrixCoffee, deg2rad(90.0));
    mat4.multiply(grtranslateMatrixCoffee, grtranslateMatrixCoffee, grrotateMatrixCoffee);
    mat4.multiply(grmodelMatrixCoffee, grtranslateMatrixCoffee, grscaleMatrixCoffee);
    grmodelMatrixCoffee = GRPushToStackCoffee(grmodelMatrixCoffee);
    GRPopFromStackCoffee();

    mat4.multiply(grprojectionMatrixCoffee, grprojectionMatrixCoffee, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniformCoffee, false, grmodelMatrixCoffee);
    gl.uniformMatrix4fv(grgViewMatrixUniformCoffee, false, DM_View_Matrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniformCoffee, false, grprojectionMatrixCoffee);
    

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureCoffee);
    gl.uniform1i(grgIsCoffeeCoverUniform, 1);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCoffee);
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCoffeePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grgCircleVertsCoffee, gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 12568);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
    // cup line - middle
    grmodelMatrixCoffee = mat4.create();
    grviewMatrixCoffee = mat4.create();
    grprojectionMatrixCoffee = mat4.create();
    grscaleMatrixCoffee = mat4.create();
    grtranslateMatrixCoffee = mat4.create();
    grrotateMatrixCoffee = mat4.create();

    mat4.translate(grtranslateMatrixCoffee, grtranslateMatrixCoffee, [0.0, -1.37, 0.0]);
    mat4.rotateX(grrotateMatrixCoffee, grrotateMatrixCoffee, deg2rad(90.0));
    mat4.scale(grscaleMatrixCoffee, grscaleMatrixCoffee, [1.01, 1.0, 0.015]);
    mat4.multiply(grtranslateMatrixCoffee, grtranslateMatrixCoffee, grrotateMatrixCoffee);
    mat4.multiply(grmodelMatrixCoffee, grtranslateMatrixCoffee, grscaleMatrixCoffee);
    grmodelMatrixCoffee = GRPushToStackCoffee(grmodelMatrixCoffee);
    GRPopFromStackCoffee();

    mat4.multiply(grprojectionMatrixCoffee, grprojectionMatrixCoffee, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniformCoffee, false, grmodelMatrixCoffee);
    gl.uniformMatrix4fv(grgViewMatrixUniformCoffee, false, DM_View_Matrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniformCoffee, false, grprojectionMatrixCoffee);
    

  
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureCoffeeCover);
    gl.uniform1i(grgIsCoffeeCoverUniform, 1);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    
    gl.bindVertexArray(grgVaoCoffee);
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCoffeePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grgCylinderVertsCoffee, gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, grgCylinderVertsCoffee.length / 3);
    gl.bindVertexArray(null);
    
    // cup cover 
    grmodelMatrixCoffee = mat4.create();
    grviewMatrixCoffee = mat4.create();
    grprojectionMatrixCoffee = mat4.create();
    grscaleMatrixCoffee = mat4.create();
    grtranslateMatrixCoffee = mat4.create();
    grrotateMatrixCoffee = mat4.create();

    mat4.translate(grtranslateMatrixCoffee, grtranslateMatrixCoffee, [0.0, -1.33, 0.0]);
    mat4.rotateX(grrotateMatrixCoffee, grrotateMatrixCoffee, deg2rad(90.0));
    mat4.scale(grscaleMatrixCoffee, grscaleMatrixCoffee, [1.01, 1.0, 0.14]);
    mat4.multiply(grtranslateMatrixCoffee, grtranslateMatrixCoffee, grrotateMatrixCoffee);
    mat4.multiply(grmodelMatrixCoffee, grtranslateMatrixCoffee, grscaleMatrixCoffee);
    grmodelMatrixCoffee = GRPushToStackCoffee(grmodelMatrixCoffee);
    GRPopFromStackCoffee();

    mat4.multiply(grprojectionMatrixCoffee, grprojectionMatrixCoffee, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniformCoffee, false, grmodelMatrixCoffee);
    gl.uniformMatrix4fv(grgViewMatrixUniformCoffee, false, DM_View_Matrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniformCoffee, false, grprojectionMatrixCoffee);
    

    gl.uniform1i(grgIsCoffeeCoverUniform, 0);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCoffee);
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCoffeePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grgCylinderVertsCoffeeCover, gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, grgCylinderVertsCoffeeCover.length / 3);
    gl.bindVertexArray(null);
    
    GRPopFromStackCoffee();

}


function GRPushToStackCoffee(matrix) 
{
    if (grmatrixPositionCoffee == -1) 
    {
        grstackMatrixCoffee.push(matrix);
        grmatrixPositionCoffee++;
        return matrix;
    }
    else 
    {
        var topMatrix = grstackMatrixCoffee[grmatrixPositionCoffee];
        mat4.multiply(matrix, topMatrix, matrix);
        grstackMatrixCoffee.push(matrix);
        grmatrixPositionCoffee++;
        return grstackMatrixCoffee[grmatrixPositionCoffee];
    }

}

function GRPopFromStackCoffee() 
{
    if (!grstackMatrixCoffee[0]) 
    {
        grstackMatrixCoffee[0] = mat4.create();
        return grstackMatrixCoffee[0];
    }
    else 
    {
        grstackMatrixCoffee.pop();
        grmatrixPositionCoffee--;
        return grstackMatrixCoffee[grmatrixPositionCoffee];
    }

}


function GRUninitializeCoffee() 
{
    if (grgVaoCoffee) 
    {
        gl.deleteVertexArray(grgVaoCoffee);
        grgVaoCoffee = null;
    }
    if (grgVboCoffeePosition) 
    {
        gl.deleteBuffer(grgVboCoffeePosition);
        grgVboCoffeePosition = null;
    }  
    
    // delete textures
    if (grgtextureCoffeeCover) 
    {
        gl.deleteTexture(grgtextureCoffeeCover);
        grgtextureCoffeeCover = null;
    }
    if (grgtextureCoffee) 
    {
        gl.deleteTexture(grgtextureCoffee);
        grgtextureCoffee = null;
    }
    

    if (grshaderProgramObjectCoffee) 
    {
        if (grfragmentShaderObject) 
        {
            gl.detachShader(grshaderProgramObjectCoffee, grfragmentShaderObject);
            gl.deleteShader(grfragmentShaderObject);
            grfragmentShaderObject = null;
        }

        if (grfragmentShaderObject) 
        {
            gl.detachShader(grshaderProgramObjectCoffee, grvertexShaderObjectCoffee);
            gl.deleteShader(grvertexShaderObjectCoffee);
            grvertexShaderObjectCoffee = null;
        }

        gl.deleteProgram(grshaderProgramObjectCoffee);
        grshaderProgramObjectCoffee = null;
    }
}












