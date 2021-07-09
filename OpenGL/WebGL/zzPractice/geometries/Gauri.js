const WebGLMacros = 
{
    GR_ATTRIBUTE_POSITION:0,
    GR_ATTRIBUTE_COLOR:1,
    GR_ATTRIBUTE_TEXTURE:2,
    GR_ATTRIBUTE_NORMAL:3
};

var grgVertexShaderObject;
var grgFragmentShadeerObject;
var grgShaderProgramObject;

var grvaoTriangle;
var grvboTrianglePosition;
var grvboTriangleTexCoord;
var grgPerspectiveProjectionMatrix;

var grgVaoRadio;
var grgVboPositionRadio;
var grgVboTextureRadio;
// bench
// bench
var grgVaoBenchTable;
var grgVboPositionBenchTable;
var grgVboTextureBenchTable;
var grgVaoBenchLegs;
var grgVboPositionBenchLegs;
var grgVboTextureBenchLegs;

var grfangleX = 0.0;
var grfangleY = 0.0;


// texture
var grtextureBench;
var grtextureRadio;
var grtextureBenchLegs;
var grtextureAntenna;
var grtextureRoad;
var grtextureFootpath;
var grgtextureSamplerUniform;

var grgModelMatrixUniform;
var grgViewMatrixUniform;
var grgProjectionMatrixUniform;
var grperspectiveMatrix;

var grstackMatrix = [];
var grmatrixPosition = -1;

function GRInit()
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
     gl.bindAttribLocation(grshaderProgramObject, WebGLMacros.GR_ATTRIBUTE_POSITION, "vPosition");
     gl.bindAttribLocation(grshaderProgramObject, WebGLMacros.GR_ATTRIBUTE_TEXTURE, "vTexCoord");
 
     // linking
     gl.linkProgram(grshaderProgramObject);
     if(!gl.getProgramParameter(grshaderProgramObject, gl.LINK_STATUS));
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
 
     // radio 
     var grradioVertices = new Float32Array(
         [
             1.0, 0.5, 0.2,
             -1.0, 0.5, 0.2,
             -1.0, -0.5, 0.2,
             1.0, -0.5, 0.2,
                                                 // right face
             1.0, 0.5, -0.2,
             1.0, 0.5, 0.2,
             1.0, -0.5, 0.2,
             1.0, -0.5, -0.2,
                                                 // back face
             -1.0, 0.5, -0.2,
             1.0, 0.5, -0.2,
             1.0, -0.5, -0.2,
             -1.0, -0.5, -0.2,
                                                 // left face
             -1.0, 0.5, 0.2,
             -1.0, 0.5, -0.2,
             -1.0, -0.5, -0.2,
             -1.0, -0.5, 0.2,
                                                 // top face
             1.0, 0.5, -0.2,
             -1.0, 0.5, -0.2,
             -1.0, 0.5, 0.2,
             1.0, 0.5, 0.2,
                                                 // bottom face
             1.0, -0.5, -0.2,
             -1.0, -0.5, -0.2,
             -1.0, -0.5, 0.2,
             1.0, -0.5, 0.2
         ]
     ); 
 
     var grradioTexCoords = new Float32Array(
         [
             0.98, 0.92,						// left bottom	rt
             0.015, 0.92,						// left top     lt
             0.015, 0.08,						// right top	lb
             0.98, 0.08,						// right bottom	rb
 
             0.13, 0.08,							// right
             0.1, 0.08,
             0.1, 0.067,
             0.13, 0.067,
 
             0.13, 0.08,							// back rt
             0.1, 0.08,								// lt
             0.1, 0.069,							// lb
             0.13, 0.069,								// rb
 
             0.13, 0.08,							// left
             0.1, 0.08,
             0.1, 0.07,
             0.13, 0.07,
 
             0.13, 0.08,							// right
             0.1, 0.08,
             0.1, 0.067,
             0.13, 0.067,
 
             0.13, 0.08,							// right
             0.1, 0.08,
             0.1, 0.067,
             0.13, 0.067,
         ]
     );
 
     var grcubeTexcoords = new Float32Array(
         [
             0.0, 0.0,				
             1.0, 0.0,
             1.0, 1.0,
             0.0, 1.0,
     
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
 
     // radio
     grgVaoRadio = gl.createVertexArray();
     gl.bindVertexArray(grgVaoRadio);
 
     grgVboPositionRadio = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboPositionRadio);
     gl.bufferData(gl.ARRAY_BUFFER, grradioVertices, gl.STATIC_DRAW);
     gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
 
     grgVboTextureRadio = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboTextureRadio);
     gl.bufferData(gl.ARRAY_BUFFER, grradioTexCoords, gl.STATIC_DRAW);
     gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_TEXTURE, 2, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_TEXTURE);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
     
     gl.bindVertexArray(null);
 
 
     // table
     grgVaoBenchTable = gl.createVertexArray();
     gl.bindVertexArray(grgVaoBenchTable);
 
     grgVboPositionBenchTable = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboPositionBenchTable);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
     gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
 
     grgVboTextureBenchTable = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboTextureBenchTable);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeTexcoords, gl.STATIC_DRAW);
     gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_TEXTURE, 2, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_TEXTURE);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
     
     gl.bindVertexArray(null);
     
     // bench legs
     grgVaoBenchLegs = gl.createVertexArray();
     gl.bindVertexArray(grgVaoBenchLegs);
 
     grgVboPositionBenchLegs = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboPositionBenchLegs);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
     gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
 
     grgVboTextureBenchLegs = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboTextureBenchLegs);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeTexcoords, gl.STATIC_DRAW);
     gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_TEXTURE, 2, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_TEXTURE);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
     
     gl.bindVertexArray(null);
 
     // texture for bench
     grtextureBench = gl.createTexture();
     grtextureBench.image = new Image();
     grtextureBench.image.src = "bench.jpg";
     grtextureBench.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grtextureBench);
         //gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.pixelStorei(gl.UNPACK_ALIGNMENT, 2);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
         //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
         //gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, grtextureBench.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };
     // texture for radio
     grtextureRadio = gl.createTexture();
     grtextureRadio.image = new Image();
     grtextureRadio.image.src = "bush.png";
     grtextureRadio.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grtextureRadio);
         //gl.pixelStorei(gl.UNPACK_ALIGNMENT, 4);
         gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grtextureRadio.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };
     // texture for bench legs and table
     grtextureBenchLegs = gl.createTexture();
     grtextureBenchLegs.image = new Image();
     grtextureBenchLegs.image.src = "wood.png";
     grtextureBenchLegs.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
         gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, grtextureBenchLegs.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };
     // texture for antenna
     grtextureAntenna = gl.createTexture();
     grtextureAntenna.image = new Image();
     grtextureAntenna.image.src = "antenna.png";
     grtextureAntenna.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grtextureAntenna);
         gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, grtextureAntenna.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };
     
}


function GRDisplay()
{
    // variables
    var grmodelMatrix = mat4.create();
    var grviewMatrix = mat4.create();
    var grprojectionMatrix = mat4.create();
    var grscaleMatrix = mat4.create();
    var grtranslateMatrix = mat4.create();
    var grrotateMatrix = mat4.create();

   

    gl.useProgram(grshaderProgramObject);

    //************************************************************************************************ radio ********************************************************
    //***************************************************************************************************************************************************************
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, -6.0]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleY));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);

    GRPushToStack(grmodelMatrix);

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
    
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureRadio);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoRadio);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
    gl.bindTexture(gl.TEXTURE_2D, null);


    //***************** antenna - 1
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-0.9, 0.9, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.015, 1.0, 0.08]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureAntenna);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoRadio);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
    gl.bindTexture(gl.TEXTURE_2D, null);

    //***************** antenna - 2
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-0.9, 1.4, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.008, 0.1, 0.06]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureAntenna);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoRadio);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    //********************** Antenna - 3
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-0.9, 1.45, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.017, 0.03, 0.08]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();

    //console.log("antenna model matrix : " + grmodelMatrix);
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureAntenna);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoRadio);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);
    GRPopFromStack();

    //*************************************************************************************** bench ************************************************************** 
    //************************************************************************************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-4.0, -0.7, -18.4]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleY));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);
    // push matrix for whole bench
    GRPushToStack(grmodelMatrix);

    //*********************** bench desk
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [3.8, 0.1, 1.2]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBench);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoBenchTable);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    //********************** Bench legs 
    // right leg bench
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [2.2, -1.2, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [1.2, 0.1, 1.0]);
    mat4.rotateZ(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    // left leg bench
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-2.2, -1.2, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [1.2, 0.1, 1.0]);
    mat4.rotateZ(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
    
    GRPopFromStack();

    //************************************************************************ Chai Table **********************************************************************
    //**********************************************************************************************************************************************************
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [4.0, -0.7, -18.4]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grfangleY));
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grrotateMatrix);
    // push matrix for whole bench
    GRPushToStack(grmodelMatrix);

    //*********************** table surface
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [4.0, 0.1, 1.5]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    //*********************** table holder - front
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -0.25, 1.2]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [3.0, 0.14, 0.1]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
    
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.bindTexture(gl.TEXTURE_2D, null);

    //*********************** table holder - back
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -0.25, -1.2]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [3.2, 0.14, 0.1]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
     
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
 
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
 
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);
 
    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
 
    gl.bindTexture(gl.TEXTURE_2D, null);
    
    //******************************** table holder - right
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [3.1, -0.25, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.1, 0.14, 1.12]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
     
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
 
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
 
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);
 
    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
 
    gl.bindTexture(gl.TEXTURE_2D, null);

    //******************************* table holder - left
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-3.1, -0.3, 0.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.1, 0.2, 1.12]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
     
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
 
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
 
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);
 
    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
 
    gl.bindTexture(gl.TEXTURE_2D, null);
    
    //********************** table legs - front left 
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-3.15, -1.8, 1.2]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.15, 1.7, 0.12]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
     
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
 
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
 
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);
 
    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
 
    gl.bindTexture(gl.TEXTURE_2D, null);
    
    //********************** table legs - front right 
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [3.15, -1.8, 1.2]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.15, 1.7, 0.12]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
     
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
 
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
 
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);
 
    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
 
    gl.bindTexture(gl.TEXTURE_2D, null);

    //********************** table legs - back left 
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-3.15, -1.8, -1.2]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.15, 1.7, 0.12]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
     
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
 
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
 
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);
 
    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
 
    gl.bindTexture(gl.TEXTURE_2D, null);

    //*********************** table legs - back right
    grmodelMatrix = mat4.create();
    grviewMatrix = mat4.create();
    grprojectionMatrix = mat4.create();
    grscaleMatrix = mat4.create();
    grtranslateMatrix = mat4.create();
    grrotateMatrix = mat4.create();
 
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [3.15, -1.8, -1.2]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.15, 1.7, 0.12]);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);
    grmodelMatrix = GRPushToStack(grmodelMatrix);
    GRPopFromStack();
     
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgPerspectiveProjectionMatrix);
 
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);
 
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureBenchLegs);
    gl.uniform1i(grtextureSamplerUniform, 0);
 
    gl.bindVertexArray(grgVaoBenchLegs);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);
 
    gl.bindTexture(gl.TEXTURE_2D, null);
    GRPopFromStack();

    gl.useProgram(null);

}

function GRPushToStack(matrix)
{
    if(grmatrixPosition == -1)
    {
        grstackMatrix.push(matrix);
        //console.log("in push, matrixposition 0 : " +grstackMatrix[0]);
        grmatrixPosition++;
        return matrix;
    }
    else
    {
        var topMatrix = grstackMatrix[grmatrixPosition];
        //console.log("in GRPushToStack, top matrix : " + topMatrix);
        mat4.multiply(matrix, topMatrix, matrix);
        grstackMatrix.push(matrix);
        grmatrixPosition++;
        //sconsole.log("return pushed matrix : position : " + grmatrixPosition + " matrix : " + grstackMatrix);
        return grstackMatrix[grmatrixPosition];
    }
  
}

function GRPopFromStack()
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


function GRUninitialize()
{
    if(grgVaoRadio)
    {
        gl.deleteVertexArray(grgVaoRadio);
        grgVaoRadio = null;
    }
    if(grgVboPositionRadio)
    {
        gl.deleteBuffer(grgVboPositionRadio);
        grgVboPositionRadio = null;
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












