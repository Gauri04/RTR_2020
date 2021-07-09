var grvertexShaderObject;
var grfragmentShaderObject;
var grshaderProgramObject;

var grgVaoSquare;
var grgVboSquarePosition;
var grgVboSquareTexCoord;
var grgVboSquareNormal;

var grmvpUniform;
var grtextureSamplerUniform;


// bloom vars
var render_fbo;
var grgOne = 1.0;
var tex_scene;
var tex_brightpass;
var tex_depth;
var filter_fbo1;
var filter_fbo2;
var tex_filter1;
var tex_filter2;
var grgBloomThreshMin = 0.0;
var grgBloomThreshMax = 0.0;
var grgExposure = 0.9;

// bloom uniforms
var grgLightPositionUniform;
var grgProjMatrixUniform;
var grgViewMatrixUniform;
var grgModelMatrixUniform;
var grgBloomThreshMinUniform, grgBloomThreshMaxUniform;
var grgMatDiffuseUniform, grgMatAmbientUniform, grgMatSpecularPowerUniform, grgMatSpecularUniform;
var grgHdrImageUniform1, grgHdrImageUniform2;
var grgBloomImageUniform, grgExposureUniform;
var grgBloomFactorUniform, grgSceneFactorUniform;
var grgShowPrefilter = 0;
var grgShowBloom;
var grgShowScene;
var grgBloomFactor = 1.0;
var grgSceneFactor = 1.0;
var MAX_SCENE_WIDTH = 2048;
var MAX_SCENE_HEIGHT = 2048;
var hdrbloom_scene, hdrbloom_filter, hdrbloom_resolve;

var grvertexShaderObject1, grfragmentShaderObject1;
var grvertexShaderObject2, grfragmentShaderObject2;
var grvertexShaderObject3, grfragmentShaderObject3;

function GRInitBloom()
{


    // extensions
    
    if(!gl.getExtension('EXT_color_buffer_float'))
    {
        return alert("need color buffer float");
    }
    if(!gl.getExtension('OES_texture_float_linear'))
    {
        return alert("Need OES float linear structure");
    }   


    //****************************************************** SHADERS- BLOOM********************************************************************
    //*****************************************************************************************************************************************

     // vertex shader
    var grvertexShaderSourceCode1 =				
    "#version 300 es" +
    "\n" +
    "in vec4 vPosition;" +
    "in vec3 vNormal;" +
    "uniform highp mat4 transform_mat_proj;" +
    "uniform highp mat4 transform_mat_view;" +
    "uniform highp mat4 transform_mat_model;" +
    "out vec3 out_n;" +
    "out vec3 out_l;" +
    "out vec3 out_v;" +
    "vec3 light_position = vec3(100.0, 100.0, 100.0);" +
    "void main(void)" +
    "{" +
    "mat4 mat_mv = transform_mat_view * transform_mat_model;" +
    "vec4 P = mat_mv * vPosition;" +
    "out_n = mat3(mat_mv) * vNormal;" +
    "out_l = light_position - P.xyz;" +
    "out_v = -P.xyz;" +
    "gl_Position = transform_mat_proj * P;" +
    "}";


    grvertexShaderObject1 = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(grvertexShaderObject1, grvertexShaderSourceCode1);
    gl.compileShader(grvertexShaderObject1);
    if(gl.getShaderParameter(grvertexShaderObject1, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grvertexShaderObject1);
        if(error.length > 0)
        {
            alert(error);
            console.log(error);
            uninitialize();
        }
        alert("in compile vertex shader 1 error");

    }

    var grfragmentShaderSourceCode1 =
        "#version 300 es" +
        "\n" +
        "precision highp float;" +
		"in vec3 out_n;" +
		"in vec3 out_l;" +
		"in vec3 out_v;" +
		"layout (location = 0) out vec4 color0;" +
		"layout (location = 1) out vec4 color1;" +
		"uniform highp float bloom_thresh_min;" +
		"uniform highp  float bloom_thresh_max;" +
		"uniform highp  vec3 material_diffuse_color;" +
		"uniform highp  vec3 material_specular_color;" +
		"uniform highp  float material_specular_power;" +
		"uniform highp  vec3 material_ambient_color;" +
		"void main(void)" +
		"{" +
		"vec3 N = normalize(out_n);" +
		"vec3 L = normalize(out_l);" +
		"vec3 V = normalize(out_v);" +
		"vec3 R = reflect(-L, N);" +
		"vec3 diffuse = max(dot(N, L), 0.0) * material_diffuse_color;" +
		"vec3 specular = pow(max(dot(R, V), 0.0), material_specular_power) * material_specular_color;" +
		"vec3 ambient = material_ambient_color;" +
		"vec3 color = ambient + diffuse + specular;" +
		"color0 = vec4(color, 1.0);" +
		"float Y = dot(color, vec3(0.299, 0.587, 0.144));" +
		"color = color * 4.0 * smoothstep(bloom_thresh_min, bloom_thresh_max, Y);" +
		"color1 = vec4(color, 1.0);" +
		"}";

 

    grfragmentShaderObject1 = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(grfragmentShaderObject1, grfragmentShaderSourceCode1);
    gl.compileShader(grfragmentShaderObject1);
    if(gl.getShaderParameter(grfragmentShaderObject1, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grfragmentShaderObject1);
        if(error.length > 0)
        {
            alert(error);
            uninitialize(); 
        }
        alert("in compile fragment shader1 error");
        
    }

    // shader program
    hdrbloom_scene = gl.createProgram();
    //attach shader object
    gl.attachShader(hdrbloom_scene, grvertexShaderObject1);
    gl.attachShader(hdrbloom_scene, grfragmentShaderObject1);
    // pre-linking
    gl.bindAttribLocation(hdrbloom_scene, WebGLMacros.GR_ATTRIBUTE_POSITION, "vPosition");
    gl.bindAttribLocation(hdrbloom_scene, WebGLMacros.GR_ATTRIBUTE_NORMAL, "vNormal");
    // linking
    gl.linkProgram(hdrbloom_scene);
    if(!gl.getProgramParameter(hdrbloom_scene, gl.LINK_STATUS))
    {
        var err = gl.getProgramInfoLog(hdrbloom_scene);
        if(err.length > 0)
        {
            alert(err);
            uninitialize(); 
        }
        
        alert("in shader program object error");
        alert(err);
       // uninitialize(); 
    }

    // mvp uniform binding
    //grgLightPositionUniform = gl.getUniformLocation(hdrbloom_scene, "light_position");
	grgProjMatrixUniform = gl.getUniformLocation(hdrbloom_scene, "transform_mat_proj");
	grgViewMatrixUniform = gl.getUniformLocation(hdrbloom_scene, "transform_mat_view");
	grgModelMatrixUniform = gl.getUniformLocation(hdrbloom_scene, "transform_mat_model");
	grgBloomThreshMinUniform = gl.getUniformLocation(hdrbloom_scene, "bloom_thresh_min");
	grgBloomThreshMaxUniform = gl.getUniformLocation(hdrbloom_scene, "bloom_thresh_max");
	grgMatDiffuseUniform = gl.getUniformLocation(hdrbloom_scene, "material_diffuse_color");
	grgMatSpecularUniform = gl.getUniformLocation(hdrbloom_scene, "material_specular_color");
	grgMatSpecularPowerUniform = gl.getUniformLocation(hdrbloom_scene, "material_specular_power");
	grgMatAmbientUniform = gl.getUniformLocation(hdrbloom_scene, "material_ambient_color");

    //************************************************************************************** Shader 2 *************************************************************************
    //*************************************************************************************************************************************************************************
    // vertex shader
    var grvertexShaderSourceCode2 =				
    "#version 300 es" +
	"\n" +
    "void main(void)" +
    "{" +
    "const vec4 vertices[] = vec4[](vec4(-1.0, -1.0, 0.5, 1.0)," +
    "vec4(1.0, -1.0, 0.5, 1.0)," +
    "vec4(1.0, 1.0, 0.5, 1.0)," +
    "vec4(-1.0, 1.0, 0.5, 1.0));" +
    "gl_Position = vertices[gl_VertexID];" +
    "}";
 
 
    grvertexShaderObject2 = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(grvertexShaderObject2, grvertexShaderSourceCode2);
    gl.compileShader(grvertexShaderObject2);
    if(gl.getShaderParameter(grvertexShaderObject2, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grvertexShaderObject2);
        if(error.length > 0)
        {
            alert(error);
            uninitialize();
        }
        alert("in compile vertex shader2 error");
 
    }
 
    var grfragmentShaderSourceCode2 =
    "#version 300 es" +
	"\n" +
	"precision highp float;" +
    "uniform sampler2D hdr_image;" +
    "out vec4 color;" +
    "const float weights[] = float[] (0.0024499299678342," +
    "0.0043538453346397," +
    "0.0073599963704157," +
    "0.0118349786570722," +
    "0.0181026699707781," +
    "0.0263392293891488," +
    "0.0364543006660986," +
    "0.0479932050577658," +
    "0.0601029809166942," +
    "0.0715974486241365," +
    "0.0811305381519717," +
    "0.0874493212267511," +
    "0.0896631113333857," +
    "0.0874493212267511," +
    "0.0811305381519717," +
    "0.0715974486241365," +
    "0.0601029809166942," +
    "0.0479932050577658," +
    "0.0364543006660986," +
    "0.0263392293891488," +
    "0.0181026699707781," +
    "0.0118349786570722," +
    "0.0073599963704157," +
    "0.0043538453346397," +
    "0.0024499299678342" +
    ");" +
    "void main(void)" +
    "{" +
    "vec4 c = vec4(0.0, 0.0, 0.0, 0.0);" +
    "ivec2 P = ivec2(gl_FragCoord.xy) - ivec2(0, weights.length() >> 1);" +
    "int i;" +
    "for(i = 0; i < weights.length(); i++)" +
    "{" +
    "c+= texelFetch(hdr_image, P + ivec2(0, i), 0) * weights[i];" +
    "}" +
    "color = c;" +
    "}";
  
 
    grfragmentShaderObject2 = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(grfragmentShaderObject2, grfragmentShaderSourceCode2);
    gl.compileShader(grfragmentShaderObject2);
    if(gl.getShaderParameter(grfragmentShaderObject2, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grfragmentShaderObject2);
        if(error.length > 0)
        {
        
            alert(error);
            uninitialize(); 
        }
        alert("in compile fragment shader2 error");
         
    }
 
    // shader program
    hdrbloom_filter = gl.createProgram();
    //attach shader object
    gl.attachShader(hdrbloom_filter, grvertexShaderObject2);
    gl.attachShader(hdrbloom_filter, grfragmentShaderObject2);
     // pre-linking

    // linking
    gl.linkProgram(hdrbloom_filter);
    if(!gl.getProgramParameter(hdrbloom_filter, gl.LINK_STATUS))
    {
        var err = gl.getProgramInfoLog(hdrbloom_filter);
        if(err.length > 0)
        {
            alert(err);
            uninitialize(); 
        }
         
        alert("in shader program object error");
        alert(err);
        // uninitialize(); 
    }

    grgHdrImageUniform1 = gl.getUniformLocation(hdrbloom_filter, "hdr_image");
    
    

    //**************************************************************************** Shader 3 ********************************************************************
    //**********************************************************************************************************************************************************
       // vertex shader
    var grvertexShaderSourceCode3 =				
    "#version 300 es" +
	"\n" +
    "void main(void)" +
    "{" +
    "const vec4 vertices[] = vec4[](vec4(-1.0, -1.0, 0.5, 1.0)," +
    "vec4(1.0, -1.0, 0.5, 1.0)," +
    "vec4(1.0, 1.0, 0.5, 1.0)," +
    "vec4(-1.0, 1.0, 0.5, 1.0));" +
    "gl_Position = vertices[gl_VertexID];" +
    "}";
 
 
    grvertexShaderObject3 = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(grvertexShaderObject3, grvertexShaderSourceCode3);
    gl.compileShader(grvertexShaderObject3);
    if(gl.getShaderParameter(grvertexShaderObject3, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grvertexShaderObject3);
        if(error.length > 0)
        {
            alert(error);
            uninitialize();
        }
        alert("in compile vertex shader3 error");
 
    }
 
    var grfragmentShaderSourceCode3 =
    "#version 300 es" +
	"\n" +
	"precision highp float;" +
    "uniform sampler2D hdr_image;" +
    "uniform sampler2D bloom_image;" +
    "uniform float exposure;" +
    "uniform float bloom_factor;" +
    "uniform float scene_factor;" +
    "out vec4 color;" +
    "void main(void)" +
    "{" +
    "vec4 c = vec4(0.0, 0.0, 0.0, 0.0);" +
    "c += texelFetch(hdr_image, ivec2(gl_FragCoord.xy), 0) * scene_factor;" +
    "c += texelFetch(bloom_image, ivec2(gl_FragCoord.xy), 0) * bloom_factor;" +
    "c.rgb = vec3(1.0, 1.0, 1.0) - exp(-c.rgb * exposure);" +
    "color = c;" +
    "}";
  
 
    grfragmentShaderObject3 = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(grfragmentShaderObject3, grfragmentShaderSourceCode3);
    gl.compileShader(grfragmentShaderObject3);
    if(gl.getShaderParameter(grfragmentShaderObject3, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grfragmentShaderObject3);
        if(error.length > 0)
        {
            alert(error);
            console.log(error)
            uninitialize(); 
        }
        alert("in compile fragment shader3 error");
         
    }
 
    // shader program
    hdrbloom_resolve = gl.createProgram();
    //attach shader object
    gl.attachShader(hdrbloom_resolve, grvertexShaderObject3);
    gl.attachShader(hdrbloom_resolve, grfragmentShaderObject3);
     // pre-linking

    // linking
    gl.linkProgram(hdrbloom_resolve);
    if(!gl.getProgramParameter(hdrbloom_resolve, gl.LINK_STATUS))
    {
        var err = gl.getProgramInfoLog(hdrbloom_resolve);
        if(err.length > 0)
        {
            alert(err);
            uninitialize(); 
        }
         
        alert("in shader program object error");
        alert(err);
        // uninitialize(); 
    }

    grgHdrImageUniform2 = gl.getUniformLocation(hdrbloom_resolve, "hdr_image");
	grgBloomImageUniform = gl.getUniformLocation(hdrbloom_resolve, "bloom_image");
	grgExposureUniform = gl.getUniformLocation(hdrbloom_resolve, "exposure");
	grgBloomFactorUniform = gl.getUniformLocation(hdrbloom_resolve, "bloom_factor");
	grgSceneFactorUniform = gl.getUniformLocation(hdrbloom_resolve, "scene_factor");
    

    var grsquareVertices = new Float32Array(
        [
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0
            
        ]
    );
    
    var grsquareNormals = new Float32Array(
        [    
		0.0, 0.0, 1.0,				
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0
        ]
    );


    // cube
    grgVaoSquare = gl.createVertexArray();
    gl.bindVertexArray(grgVaoSquare);

    grgVboSquarePosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboSquarePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grsquareVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    //normals
    grgVboSquareNormal = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVboSquareNormal);
    gl.bufferData(gl.ARRAY_BUFFER, grsquareNormals, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_NORMAL, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_NORMAL);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    gl.bindVertexArray(null);

    
    // ******************************************************** FBO *****************************************************************8
    //********************************************************************************************************************************
    var buffers = [gl.COLOR_ATTACHMENT0, gl.COLOR_ATTACHMENT1];

    render_fbo = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, render_fbo);

    tex_scene = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, tex_scene);
    gl.texStorage2D(gl.TEXTURE_2D, 1, gl.RGBA16F, MAX_SCENE_WIDTH, MAX_SCENE_HEIGHT);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, tex_scene, 0);
    //gl.framebufferTextureLayer(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, tex_scene, 0, 2);

    tex_brightpass = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, tex_brightpass);
    gl.texStorage2D(gl.TEXTURE_2D, 1, gl.RGBA16F, MAX_SCENE_WIDTH, MAX_SCENE_HEIGHT);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT1, gl.TEXTURE_2D, tex_brightpass, 0);
    //gl.framebufferTextureLayer(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT1, tex_brightpass, 0, 2);
    
    tex_depth = gl.createRenderbuffer();
    gl.bindRenderbuffer(gl.RENDERBUFFER, tex_depth);
    gl.renderbufferStorage(gl.RENDERBUFFER, gl.DEPTH_COMPONENT32F, MAX_SCENE_WIDTH, MAX_SCENE_HEIGHT);
    gl.framebufferRenderbuffer(gl.FRAMEBUFFER, gl.DEPTH_ATTACHMENT, gl.RENDERBUFFER, tex_depth);
    //gl.renderbufferStorage(gl.RENDERBUFFER, gl.DEPTH_COMPONENT16, targetTextureWidth, targetTextureHeight);
    //gl.framebufferRenderbuffer(gl.FRAMEBUFFER, gl.DEPTH_ATTACHMENT, gl.RENDERBUFFER, depthBuffer);
    gl.drawBuffers([gl.COLOR_ATTACHMENT0, gl.COLOR_ATTACHMENT1]);

    var err = gl.checkFramebufferStatus(gl.FRAMEBUFFER);
    if(err !== gl.FRAMEBUFFER_COMPLETE)
    {
        console.log("in fbo, error, framebuffer not complete, error code : " + err);
    }

    filter_fbo1 = gl.createFramebuffer();
    filter_fbo2 = gl.createFramebuffer();
    tex_filter1 = gl.createTexture();
    tex_filter2 = gl.createTexture();
  
        gl.bindFramebuffer(gl.FRAMEBUFFER, filter_fbo1);
        gl.bindTexture(gl.TEXTURE_2D, tex_filter1);
        gl.texStorage2D(gl.TEXTURE_2D, 1, gl.RGBA16F, MAX_SCENE_WIDTH, MAX_SCENE_HEIGHT);
        gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, tex_filter1, 0);
        gl.drawBuffers([gl.COLOR_ATTACHMENT0]);
       
        gl.bindFramebuffer(gl.FRAMEBUFFER, filter_fbo2);
        gl.bindTexture(gl.TEXTURE_2D, tex_filter2);
        gl.texStorage2D(gl.TEXTURE_2D, 1, gl.RGBA16F, MAX_SCENE_HEIGHT, MAX_SCENE_WIDTH);
        gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, tex_filter2, 0);
        gl.drawBuffers([gl.COLOR_ATTACHMENT0]);
    
    
    if(err !== gl.FRAMEBUFFER_COMPLETE)
    {
        console.log("in filter fbo, error, framebuffer not complete");
    }
    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
}


function GRDisplayBloom()
{
    var grmodelMatrix = mat4.create();
    var grviewMatrix = mat4.create();
    var grprojectionMatrix = mat4.create();
    var grtranslateMatrix = mat4.create();
    var grrotateMatrix = mat4.create();
    var grscaleMatrix = mat4.create();
    var perspectiveMatrix1 = mat4.create();

    gl.clear(gl.COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);

    
    gl.bindFramebuffer(gl.FRAMEBUFFER, render_fbo);
    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.clearBufferfv(gl.COLOR, 0, new Float32Array([0.0, 0.0, 0.0, 1.0]));          // black
    gl.clearBufferfv(gl.COLOR, 1, new Float32Array([0.0, 0.0, 0.0, 1.0]));          // black
    gl.clearBufferfv(gl.DEPTH, 0, new Float32Array([1.0]));

    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LESS);

    gl.useProgram(hdrbloom_scene);
    gl.uniform1f(grgBloomThreshMinUniform, grgBloomThreshMin);
    gl.uniform1f(grgBloomThreshMaxUniform, grgBloomThreshMax);

    gl.uniform3f(grgMatDiffuseUniform, Math.sin(3.142 / 8) * 0.5 + 0.5, Math.sin((3.142 / 8) + 1.345) * 0.5 + 0.5, Math.sin((3.412 / 8) + 2.567) * 0.5 + 0.5);
    gl.uniform3f(grgMatSpecularUniform, 2.8, 2.8, 2.8);
    gl.uniform3f(grgMatAmbientUniform,  0.002 * 0.025, 0.002 * 0.025, 0.002 * 0.025);
    gl.uniform1f(grgMatSpecularPowerUniform, 30.0);
   
    mat4.perspective(perspectiveMatrix1, 45.0, 1.0, 0.1, 100.0);
   //\ mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, -6.0]);
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, -0.0, -3.0]);
    mat4.multiply(grmodelMatrix, grmodelMatrix, grtranslateMatrix);
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grperspectiveMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjMatrixUniform, false, grprojectionMatrix);

    gl.bindVertexArray(grgVaoSquare);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);
    
    
    //***************** filter program 
    gl.useProgram(hdrbloom_filter);
    gl.bindFramebuffer(gl.FRAMEBUFFER, filter_fbo2);
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, tex_filter1);
    gl.uniform1i(grgHdrImageUniform1, 0);
    gl.viewport(0, 0, canvas.width, canvas.height);

    
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);

    gl.bindFramebuffer(gl.FRAMEBUFFER, filter_fbo1);
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, tex_brightpass);
    gl.uniform1i(grgHdrImageUniform1, 0);
    gl.viewport(0, 0, canvas.width, canvas.height);

    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
   
    
   
    
    //******************************* resolve program
    gl.useProgram(hdrbloom_resolve);
    gl.uniform1f(grgExposureUniform, grgExposure);
    if(grgShowPrefilter == 1)
    {
        gl.uniform1f(grgBloomFactorUniform, 0.0);
        gl.uniform1f(grgSceneFactorUniform, 1.0);
    }
    else
    {
        gl.uniform1f(grgBloomFactorUniform, grgBloomFactor);
        gl.uniform1f(grgSceneFactorUniform, grgSceneFactor);
    }
    

    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.activeTexture(gl.TEXTURE1);
    gl.bindTexture(gl.TEXTURE_2D, tex_filter1);
    gl.activeTexture(gl.TEXTURE0);
    if(grgShowPrefilter == 0)
    {
        gl.bindTexture(gl.TEXTURE_2D, tex_scene);
    }
    else
    {
        gl.bindTexture(gl.TEXTURE_2D, tex_brightpass);
    }
    gl.uniform1i(grgHdrImageUniform2, 1);
    gl.uniform1i(grgBloomImageUniform, 0);
   // gl.bindTexture(gl.TEXTURE_2D, grgShowPrefilter ? tex_brightpass : tex_scene);

    
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    
    gl.bindTexture(gl.TEXTURE_2D, null);
    
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


function GRUninitializeBloom()
{
    if(grgVaoSquare)
    {
        gl.deleteVertexArray(grgVaoSquare);
        grgVaoSquare = null;
    }
    if(grgVboSquarePosition)
    {
        gl.deleteBuffer(grgVboSquarePosition);
        grgVboSquarePosition = null;
    }
    if(grgVboSquareNormal)
    {
        gl.deleteBuffer(grgVboSquareNormal);
        grgVboSquareNormal = null;
    }

    if(hdrbloom_scene)
    {
        if(grfragmentShaderObject1)
        {
            gl.detachShader(hdrbloom_scene, grfragmentShaderObject1);
            gl.deleteShader(grfragmentShaderObject1);
            grfragmentShaderObject1 = null;
        }

        if(grvertexShaderObject1)
        {
            gl.detachShader(hdrbloom_scene, grvertexShaderObject1);
            gl.deleteShader(grvertexShaderObject1);
            grvertexShaderObject1 = null;
        }

        gl.deleteProgram(hdrbloom_scene);
        hdrbloom_scene = null;
    }
    if(hdrbloom_filter)
    {
        if(grfragmentShaderObject2)
        {
            gl.detachShader(hdrbloom_filter, grfragmentShaderObject2);
            gl.deleteShader(grfragmentShaderObject2);
            grfragmentShaderObject2 = null;
        }

        if(grvertexShaderObject2)
        {
            gl.detachShader(hdrbloom_filter, grvertexShaderObject2);
            gl.deleteShader(grvertexShaderObject2);
            grvertexShaderObject2 = null;
        }

        gl.deleteProgram(hdrbloom_filter);
        hdrbloom_filter = null;
    }
    if(hdrbloom_resolve)
    {
        if(grfragmentShaderObject3)
        {
            gl.detachShader(hdrbloom_resolve, grfragmentShaderObject3);
            gl.deleteShader(grfragmentShaderObject3);
            grfragmentShaderObject3 = null;
        }

        if(grvertexShaderObject3)
        {
            gl.detachShader(hdrbloom_resolve, grvertexShaderObject3);
            gl.deleteShader(grvertexShaderObject3);
            grvertexShaderObject3 = null;
        }

        gl.deleteProgram(hdrbloom_resolve);
        hdrbloom_resolve = null;
    }
}












