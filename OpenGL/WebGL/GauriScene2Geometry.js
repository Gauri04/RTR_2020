
var grgVertexShaderObjectStage;
var grgFragmentShadeerObjectStage;
var grgShaderProgramObjectStage;


var grgVaoStage;
var grgVboStagePosition;
var grgVboStageTexture;

var grgVaoStageWall;
var grgVboStageWallPosition;
var grgVboStageWallTexture;

var grfangleX = 0.0;
var grfangleY = 0.0;
var grtransStageX = 0.0;
var grtransStageY = 0.0;
var grtransStageZ = -10.0;


// texture
var grgtextureStageFloor;
var grgtextureStageWall;
var grgtextureWings;
var grgtextureSamplerUniform;

var grgModelMatrixUniform;
var grgViewMatrixUniform;
var grgProjectionMatrixUniform;

var grstackMatrix = [];
var grmatrixPosition = -1;

function GRInitScene2()
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
     if(gl.getShaderParameter(grvertexShaderObject, gl.COMPILE_STATUS) == false)
     {
         var error = gl.getShaderInfoLog(grvertexShaderObject);
         if(error.length > 0)
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
     if(gl.getShaderParameter(grfragmentShaderObject, gl.COMPILE_STATUS) == false)
     {
         var error = gl.getShaderInfoLog(grfragmentShaderObject);
         if(error.length > 0)
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
     if(!gl.getProgramParameter(grshaderProgramObject, gl.LINK_STATUS))
     {
         var err = gl.getProgramInfoLog(grshaderProgramObject);
         if(err.length > 0)
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
 
   
 
     var grstageTexcoords = new Float32Array(
         [
            0.3, 0.0,
            0.3, 1.0,
            0.1, 1.0,
            0.1, 0.0,

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
             2.0, 0.0,
             2.0, 1.0,
     
             1.0, 0.0,
             0.0, 0.0,
             0.0, 1.0,
             1.0, 1.0
         ]
     );

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
 
     // stage
     grgVaoStage = gl.createVertexArray();
     gl.bindVertexArray(grgVaoStage);
 
     grgVboStagePosition = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboStagePosition);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
     gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
 
     grgVboStageTexture = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboStageTexture);
     gl.bufferData(gl.ARRAY_BUFFER, grstageTexcoords, gl.STATIC_DRAW);
     gl.vertexAttribPointer(macros.AMC_ATTRIB_TEXCOORD, 2, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(macros.AMC_ATTRIB_TEXCOORD);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
     
     gl.bindVertexArray(null);

     
     // stage wall
     grgVaoStageWall = gl.createVertexArray();
     gl.bindVertexArray(grgVaoStageWall);
 
     grgVboStagePositionWall = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboStagePositionWall);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
     gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
 
     grgVboStageTextureWall = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboStageTextureWall);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeTexcoords, gl.STATIC_DRAW);
     gl.vertexAttribPointer(macros.AMC_ATTRIB_TEXCOORD, 2, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(macros.AMC_ATTRIB_TEXCOORD);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
     
     gl.bindVertexArray(null);


     // texture for bench
     grgtextureStageFloor = gl.createTexture();
     grgtextureStageFloor.image = new Image();
     grgtextureStageFloor.image.src = "GauriResources/stage_floor.jpg";
     grgtextureStageFloor.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grgtextureStageFloor);
         //gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.pixelStorei(gl.UNPACK_ALIGNMENT, 2);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
         //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
         //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, grgtextureStageFloor.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };
     // texture for radio
     grgtextureWings = gl.createTexture();
     grgtextureWings.image = new Image();
     grgtextureWings.image.src = "GauriResources/wing_cloth.jpg";
     grgtextureWings.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
         //gl.pixelStorei(gl.UNPACK_ALIGNMENT, 4);
         gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureWings.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };

     grgtextureStageWall = gl.createTexture();
     grgtextureStageWall.image = new Image();
     grgtextureStageWall.image.src = "GauriResources/wall.jpg";
     grgtextureStageWall.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grgtextureStageWall);
         gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grgtextureStageWall.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };

     
     
}


function GRDisplayScene2()
{
  //  console.log("p matrix "+ perspectiveMatrix);
    gl.useProgram(grshaderProgramObject);

   // stage and stage-wing
    GRStage();

    


    gl.useProgram(null);

}

function GRStage()
{

    var grmodelMatrix = mat4.create();
    var grviewMatrix = mat4.create();
    var grprojectionMatrix = mat4.create();
    var grscaleMatrix = mat4.create();
    var grtranslateMatrix = mat4.create();
    var grrotateMatrix = mat4.create();
    // push matrix for stage geometry
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [grtransStageX, grtransStageY, grtransStageZ]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grtranslateMatrix);
    GRPushToStackScene2(grmodelMatrix);


    //********************************************* stage ***************************************
    //********************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -2.7, -18.4]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleY));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);
    // push matrix for whole stage
    GRPushToStackScene2(grmodelMatrix);

    //*********************** stage
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -1.0, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [24.0, 1.2, 12.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureStageFloor);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStage);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // Stage wall - right
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [25.0, 8.0, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [10.4, 0.5, 12.0]);
    mat4.rotateZ(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureStageWall);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // Stage wall left
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-25.0, 8.0, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [10.4, 0.5, 12.0]);
    mat4.rotateZ(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureStageWall);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // stage wall back
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 8.0, -10.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [24.0, 1.2, 10.0]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);


    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);


    //****************************************************** Wing - 1 Right
    // right - 1
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [23.0, 4.2, 10.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // right - 2
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [23.0, 4.2, 6.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
    // right - 3
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [23.0, 4.2, 2.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    //***  right - 4
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [23.0, 4.2, -4.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
   
    //********************** Wing - 1 Left
    // left - 1
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-23.0, 4.2, 10.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // left - 2
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-23.0, 4.2, 6.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
    // left - 3
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-23.0, 4.2, 2.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // left - 4
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
    
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-23.0, 4.2, -4.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [2.5, 6.3, 0.0]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStackScene2(grmodelMatrix);
    GRPopFromStackScene2();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgtextureWings);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoStageWall);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    
  
    
    GRPopFromStackScene2();
    GRPopFromStackScene2();

}


function GRPushToStackScene2(matrix)
{
    if(grmatrixPosition == -1)
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

function GRPopFromStackScene2()
{
    if(!grstackMatrix[0])
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


function GRUninitializeScene2()
{
    if(grgVaoStage)
    {
        gl.deleteVertexArray(grgVaoStage);
        grgVaoStage = null;
    }
    if(grgVboStagePosition)
    {
        gl.deleteBuffer(grgVboStagePosition);
        grgVboStagePosition = null;
    }
    if(grgVboStageTexture)
    {
        gl.deleteBuffer(grgVboStageTexture);
        grgVboStageTexture = null;
    }

    if(grgVaoStageWall)
    {
        gl.deleteVertexArray(grgVaoStageWall);
        grgVaoStageWall = null;
    }
    if(grgVboStageWallPosition)
    {
        gl.deleteBuffer(grgVboStageWallPosition);
        grgVboStageWallPosition = null;
    }
    if(grgVboStageWallTexture)
    {
        gl.deleteBuffer(grgVboStageWallTexture);
        grgVboStageWallTexture = null;
    }

    // delete textures
    if(grgtextureWings)
    {
        gl.deleteTexture(grgtextureWings);
    }
    if(grgtextureStageFloor)
    {
        gl.deleteTexture(grgtextureStageFloor);
    }
    if(grgtextureStageWall)
    {
        gl.deleteTexture(grgtextureStageWall);
    }

    if(grshaderProgramObject)
    {
        if(grfragmentShaderObject)
        {
            gl.detachShader(grshaderProgramObject, grfragmentShaderObject);
            gl.deleteShader(grfragmentShaderObject);
            grfragmentShaderObject = null;
        }

        if(grfragmentShaderObject)
        {
            gl.detachShader(grshaderProgramObject, grvertexShaderObject);
            gl.deleteShader(grvertexShaderObject);
            grvertexShaderObject = null;
        }

        gl.deleteProgram(grshaderProgramObject);
        grshaderProgramObject = null;
    }
}












