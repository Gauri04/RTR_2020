
var grvertexShaderObject;
var grfragmentShadeerObject;
var grshaderProgramObject;

var grgPerspectiveProjectionMatrix;

var grgVaoCylinder;
var grgVboCylinderPosition;
var grgVboCylinderTexture;
var grglightSphere;
var grgVaoCube;
var grgVboCubePosition;
var grgVboCubeTexture;

var grfangleX = 0.0;
var grfangleY = 0.0;
var grfangleXHandle = 0.0;
var grtransStageLightX = 0.0;
var grtransStageLightY = 0.0;
var grtransStageLightZ = -10.0;



// texture
var grgtextureLightGlass;
var grgtextureLightMaterial;
var grgtextureSamplerUniform;

var grgModelMatrixUniform;
var grgViewMatrixUniform;
var grgProjectionMatrixUniform;

var grstackMatrix = [];
var grmatrixPosition = -1;
var grcircleCount = 0, i;
var grmodelMatrix;
var grviewMatrix;
var grprojectionMatrix; 
var grscaleMatrix;
var grtranslateMatrix;
var grrotateMatrix;


function GRInitStageLights() 
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
        var error = gl.getShaderInfoLog(grfragmentShaderObject);
        if (error.length > 0) 
        {
            alert(error);
            uninitialize();
        }
        alert("in compile fragment shader error");

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
        // uninitialize(); 
    }

    // mvp uniform binding
    grgModelMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_model_matrix");
    grgViewMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_view_matrix");
    grgProjectionMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_projection_matrix");
    grtextureSamplerUniform = gl.getUniformLocation(grshaderProgramObject, "u_texture_sampler");



    var grcubeTexcoords = new Float32Array(
        [
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,

            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            1.0, 0.0,
            0.0, 0.0,
            0.0, 1.0,
            1.0, 1.0
        ]
    );

    var grcubeVertices = new Float32Array(
        [
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
            // right face
            1.0, 1.0, -1.0,
            1.0, 1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, -1.0, -1.0,
            // back face
            -1.0, 1.0, -1.0,
            1.0, 1.0, -1.0,
            1.0, -1.0, -1.0,
            -1.0, -1.0, -1.0,
            // left face
            -1.0, 1.0, 1.0,
            -1.0, 1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0, 1.0,
            // top face
            1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0,
            -1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            // bottom face
            1.0, -1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0
        ]
    );
    
    var circleVerts = new Float32Array(37704);

    var index = 0;
    for(i = 0.0; i < 2 * 3.142; i = i + 0.001)
    {
        circleVerts[index] = Math.cos(i);
        circleVerts[index + 1] = Math.sin(i);
        circleVerts[index + 2] = 0.0;

        circleVerts[index + 3] = Math.cos(i);
        circleVerts[index + 4] = Math.sin(i);
        circleVerts[index + 5] = 1.0;
        index = index + 6;

    }
    console.log("index : " + index);

    // cube
    grgVaoCube = gl.createVertexArray();
    gl.bindVertexArray(grgVaoCube);

    grgVboCubePosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCubePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    grgVboCubeTexture = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCubeTexture);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeTexcoords, gl.STATIC_DRAW);
    gl.vertexAttribPointer(macros.AMC_ATTRIB_TEXCOORD, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(macros.AMC_ATTRIB_TEXCOORD);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    gl.bindVertexArray(null);

    // lights (cylinder)
    grgVaoCylinder = gl.createVertexArray();
    gl.bindVertexArray(grgVaoCylinder);

    grgVboCylinderPosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboCylinderPosition);
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
    grgtextureLightMaterial = gl.createTexture();
    grgtextureLightMaterial.image = new Image();
    grgtextureLightMaterial.image.src = "GauriResources/light_material2.jpg";
    grgtextureLightMaterial.image.onload = function () 
    {
        gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
        //gl.pixelStorei(gl.UNPACK_ALIGNMENT, 4);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureLightMaterial.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };

    grgtextureLightGlass = gl.createTexture();
    grgtextureLightGlass.image = new Image();
    grgtextureLightGlass.image.src = "GauriResources/light_glass2.jpg";
    grgtextureLightGlass.image.onload = function () 
    {
        gl.bindTexture(gl.TEXTURE_2D, grgtextureLightGlass);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureLightGlass.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };
    
    grglightSphere = new Mesh();
    makeSphere(grglightSphere, 2.0, 30, 30);
}


function GRDisplayStageLights() 
{
    // vars
    var grmodel = mat4.create();
    var grview = mat4.create();
    var grtranslate = mat4.create();
    var grrotate = mat4.create();
    var scale = mat4.create(); 


    gl.useProgram(grshaderProgramObject);

    // stage and stage-wing
    mat4.translate(grtranslate, grtranslate, [grtransStageLightX - 6.0, grtransStageLightY, grtransStageLightZ]);
    mat4.multiply(grmodel, grmodel, grtranslate);
    GRPushToStack(grmodel);
    GRLightHolderScrew();
    GRStageLights();
    GRPopFromStack();

    grmodel = mat4.create();
    grtranslate = mat4.create();
    mat4.translate(grtranslate, grtranslate, [grtransStageLightX - 4.0, grtransStageLightY, grtransStageLightZ]);
    mat4.multiply(grmodel, grmodel, grtranslate);
    GRPushToStack(grmodel);
    GRLightHolderScrew();
    GRStageLights();
    GRPopFromStack();

    grmodel = mat4.create();
    grtranslate = mat4.create();
    mat4.translate(grtranslate, grtranslate, [grtransStageLightX - 2.0, grtransStageLightY, grtransStageLightZ]);
    mat4.multiply(grmodel, grmodel, grtranslate);
    GRPushToStack(grmodel);
    GRLightHolderScrew();
    GRStageLights();
    GRPopFromStack();

    grmodel = mat4.create();
    grtranslate = mat4.create();
    mat4.translate(grtranslate, grtranslate, [grtransStageLightX, grtransStageLightY, grtransStageLightZ]);
    mat4.multiply(grmodel, grmodel, grtranslate);
    GRPushToStack(grmodel);
    GRLightHolderScrew();
    GRStageLights();
    GRPopFromStack();

    grmodel = mat4.create();
    grtranslate = mat4.create();
    mat4.translate(grtranslate, grtranslate, [grtransStageLightX + 2.0, grtransStageLightY, grtransStageLightZ]);
    mat4.multiply(grmodel, grmodel, grtranslate);
    GRPushToStack(grmodel);
    GRLightHolderScrew();
    GRStageLights();
    GRPopFromStack();

    grmodel = mat4.create();
    grtranslate = mat4.create();
    mat4.translate(grtranslate, grtranslate, [grtransStageLightX + 4.0, grtransStageLightY, grtransStageLightZ]);
    mat4.multiply(grmodel, grmodel, grtranslate);
    GRPushToStack(grmodel);
    GRLightHolderScrew();
    GRStageLights();
    GRPopFromStack();

    grmodel = mat4.create();
    grtranslate = mat4.create();
    mat4.translate(grtranslate, grtranslate, [grtransStageLightX + 6.0, grtransStageLightY, grtransStageLightZ]);
    mat4.multiply(grmodel, grmodel, grtranslate);
    GRPushToStack(grmodel);
    GRLightHolderScrew();
    GRStageLights();
    GRPopFromStack();


    // light holder pipe
    GRLightHolderPipe();

    gl.useProgram(null);

}

function GRLightHolderPipe()
{
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [grtransStageLightX, grtransStageLightY, grtransStageLightZ]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);
    GRPushToStack(grmodelMatrix);

    grmodelMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    grscaleMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, - 0.8, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [7.0, 0.1, 0.1]);
   // mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);

    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    GRPopFromStack();

}

function GRLightHolderScrew()
{
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, 0.0]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grmodelMatrix, grtranslateMatrix);
    GRPushToStack(grmodelMatrix);

    grmodelMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -0.48, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.1, 0.2, 0.1]);
   // mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
   // mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(-grfangleY));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);

    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    GRPopFromStack();
}

function GRStageLights() 
{

    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    // push matrix for stage - light geometry
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, 0.0]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(180 + grfangleX));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleY));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);
    GRPushToStack(grmodelMatrix);


    //********************************************* light - outer ****************************************
    //********************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.5, 0.5, 0.8]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    //mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleY));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCylinder);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 12568);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
    //********************************************* light - handle ****************************************
    //********************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.5, 0.5, 0.8]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    //mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleY));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // light handle - 1 left
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-0.5, -0.4, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.07, 0.05, 0.05]);
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // light handle 1 - right
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.5, -0.4, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.07, 0.05, 0.05]);
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);


    // stack for handle
    grmodelMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    grtranslateMatrix = mat4.create();

    //mat4.translate(grtranslateMatrix, grtranslateMatrix, [-0.5, 0.3,  0.0]); 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-0.0, -0.4,  0.0]); 
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleXHandle));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);
    GRPushToStack(grmodelMatrix);

    grmodelMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    grtranslateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.18,  0.0]); 
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grtranslateMatrix);

    GRPushToStack(grmodelMatrix);
    

    // light - handle - 2 - left
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-0.55, 0.0,  0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.02, 0.4, 0.12]);
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // light - handle - 2 - right
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.55, 0.0,  0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.02, 0.4, 0.12]);
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // light handle - middle
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.4,  0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.02, 0.56, 0.12]);
    mat4.rotateZ(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightMaterial);
    gl.uniform1i(grtextureSamplerUniform, 0);
    
    gl.bindVertexArray(grgVaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    GRPopFromStack();
    GRPopFromStack();

    //********************************************* light - sphere ****************************************
    //********************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -0.75, 0.0]);
    //mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -0.21, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.23, 0.15, 0.21]);
    //mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
    
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureLightGlass);
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


function GRUninitializeStageLights() 
{
    if (grgVaoCylinder) 
    {
        gl.deleteVertexArray(grgVaoCylinder);
        grgVaoCylinder = null;
    }
    if (grgVboCylinderPosition) 
    {
        gl.deleteBuffer(grgVboCylinderPosition);
        grgVboCylinderPosition = null;
    }
    if (grgVboCylinderTexture) 
    {
        gl.deleteBuffer(grgVboCylinderTexture);
        grgVboCylinderTexture = null;
    }
    if (grgVaoCube) 
    {
        gl.deleteVertexArray(grgVaoCube);
        grgVaoCube = null;
    }
    if (grgVboCubePosition) 
    {
        gl.deleteBuffer(grgVboCubePosition);
        grgVboCubePosition = null;
    }
    if (grgVboCubeTexture) 
    {
        gl.deleteBuffer(grgVboCubeTexture);
        grgVboCubeTexture = null;
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
    if (grgtextureLightGlass) 
    {
        gl.deleteTexture(grgtextureLightGlass);
        grgtextureLightGlass = null;
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












