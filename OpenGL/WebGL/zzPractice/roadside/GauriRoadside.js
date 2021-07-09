

var grgVertexShaderObject;
var grgFragmentShadeerObject;
var grgShaderProgramObject;

var grgVaoRoadside;
var grgVboPositionRoadside;
var grgVboTextureRoadside;

var grtransRoadsideX = 1.0;
var grtransRoadsideY = -0.5;
var grtransRoadsideZ = -6.0;


// texture
var grtextureRoadside;
var grgtextureSamplerUniform;

var grgModelMatrixUniform;
var grgViewMatrixUniform;
var grgProjectionMatrixUniform;

var grstackMatrix = [];
var grmatrixPosition = -1;

function GRInitRoadside()
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
 
   
 
     var grcubeTexcoords = new Float32Array(
         [
             0.0, 0.0,		// right		
             4.0, 0.0,
             4.0, 1.0,
             0.0, 1.0,

             0.9, 0.9,
             0.9, 0.9,
             0.9, 0.9,
             0.9, 0.9,
     
             4.0, 0.0,  // left
             0.0, 0.0,
             0.0, 1.0,
             4.0, 1.0,
     
             0.9, 0.9,
             0.9, 0.9,
             0.9, 0.9,
             0.9, 0.9,

             0.0, 0.0,
             4.0, 0.0,
             4.0, 1.0,
             0.0, 1.0,
     
             0.9, 0.9,
             0.9, 0.9,
             0.9, 0.9,
             0.9, 0.9
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
     grgVaoRoadside = gl.createVertexArray();
     gl.bindVertexArray(grgVaoRoadside);
 
     grgVboPositionRoadside = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboPositionRoadside);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
     gl.vertexAttribPointer(macros.AMC_ATTRIB_POSITION, 3, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(macros.AMC_ATTRIB_POSITION);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
 
     grgVboTextureRoadside = gl.createBuffer();
     gl.bindBuffer(gl.ARRAY_BUFFER, grgVboTextureRoadside);
     gl.bufferData(gl.ARRAY_BUFFER, grcubeTexcoords, gl.STATIC_DRAW);
     gl.vertexAttribPointer(macros.AMC_ATTRIB_TEXCOORD, 2, gl.FLOAT, false, 0, 0);
     gl.enableVertexAttribArray(macros.AMC_ATTRIB_TEXCOORD);
     gl.bindBuffer(gl.ARRAY_BUFFER, null);
     
     gl.bindVertexArray(null);
 

     // texture for radio
     grtextureRoadside = gl.createTexture();
     grtextureRoadside.image = new Image();
     grtextureRoadside.image.src = "GauriResources/road_pavement.jpg";
     grtextureRoadside.image.onload = function()
     {
         gl.bindTexture(gl.TEXTURE_2D, grtextureRoadside);
         gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
         gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
         gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, grtextureRoadside.image);
         gl.bindTexture(gl.TEXTURE_2D, null);
     };
}


function GRDisplayRoadside()
{
    // variables
    var grmodelMatrix = mat4.create();
    var grviewMatrix = mat4.create();
    var grprojectionMatrix = mat4.create();
    var grscaleMatrix = mat4.create();
    var grtranslateMatrix = mat4.create();
    var grrotateMatrix = mat4.create();

   

    gl.useProgram(grshaderProgramObject);

    //************************************************************************************************ roadside ********************************************************
    //***************************************************************************************************************************************************************
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [grtransRoadsideX, grtransRoadsideY, grtransRoadsideZ]);
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(90.0));
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grfangleX));
    mat4.scale(grscaleMatrix, grscaleMatrix, [4.0, 0.1, 0.1]);
    mat4.multiply(grtranslateMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelMatrix, grtranslateMatrix, grscaleMatrix);

    GRPushToStack(grmodelMatrix);

    mat4.multiply(grprojectionMatrix, grprojectionMatrix, perspectiveMatrix);
    
    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjectionMatrixUniform, false, grprojectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureRoadside);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grgVaoRoadside);
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


function GRUninitializeRoadside()
{
    if(grgVaoRoadside)
    {
        gl.deleteVertexArray(grgVaoRoadside);
        grgVaoRoadside = null;
    }
    if(grgVboPositionRoadside)
    {
        gl.deleteBuffer(grgVboPositionRoadside);
        grgVboPositionRoadside = null;
    }
    if(grtextureRoadside)
    {
        gl.deleteTexture(grtextureRoadside);
        grtextureRoadside = null;
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












