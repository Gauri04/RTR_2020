var canvas = null;
var gl = null;
var canvas_original_width;
var canvas_original_height;
var bFullscreen = false;
var requestAnimationFrame = window.requestAnimationFrame || 
                            window.webkitRequestAnimationFrame ||
                            window.mozRequestAnimationFrame ||
                            window.oRequestAnimationFrame ||
                            window.msRequestAnimationFrame;
const WebGLMacros = 
{
    GR_ATTRIBUTE_POSITION:0,
    GR_ATTRIBUTE_COLOR:1,
    GR_ATTRIBUTE_TEXTURE:2,
    GR_ATTRIBUTE_NORMAL:3
};


var grgVao;
var grgVao_cube;
var grgVbo_position_cube;
var grgperspecticeMatrix;
// bloom
var render_fbo;
var grgOne = 1.0;
var tex_scene;
var grgWidth, grgHeight;
var tex_brightpass;
var tex_depth;
var filter_fbo = [2];
var tex_filter = [2];
var i;
var tex_lut;
var grgBloomThreshMin;
var grgBloomThreshMax;
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
var grgShowPrefilter = false;
var grgShowBloom;
var grgShowScene;
var grgBloomFactor;
var grgSceneFactor;
var MAX_SCENE_WIDTH = 2048;
var MAX_SCENE_HEIGHT = 2048;
var hdrbloom_scene, hdrbloom_filter, hdrbloom_resolve;

var grvertexShaderObject1, grfragmentShaderObject1;
var grvertexShaderObject2, grfragmentShaderObject2;
var grvertexShaderObject3, grfragmentShaderObject3;

var cancelAnimationFrame = window.cancelAnimationFrame || 
                        window.webkitCancelRequestAnimationFrame || window.webkitCancelAnimationFrame ||
                        window.mozCancelRequestAnimationFrame || window.mozCancelAnimationFrame ||
                        window.onCancelRequestAnimationFrame || window.onCancelAnimationFrame ||
                        window.msCancelRequestAnimationFrame || window.msCancelAnimationFrame;

function main()
{
   
    // get  canvas from DOM
    canvas = document.getElementById("GR");
    if(!canvas)
        console.log("\n ontaining canvas failed");
    else
        console.log("\n ontaining canvas succeeded");

    canvas_original_width = canvas.width;
    canvas_original_height = canvas.height;

    // "keydown" and "click" are in-built events. keyDown and mouseDown are user defined functions
    // param false states that events are bubble events, not captured events 
    window.addEventListener("keydown", keyDown, false);         // window is in-build variable, just like document. window is inherited from document, its a DOM object.
    window.addEventListener("click", mouseDown, false);
    window.addEventListener("resize", resize, false);

    init();

    resize();                                   
    // till now in window, linux and android we did not have to call display() / draw() as it internally calls repaint. But here we have to call it as it doesnt do it 
    // internally
    // warm up call
    draw();
}




function toggleFullscreen()
{
    var fullscreen_element = document.fullscreenElement || 
                            document.webkitFullscreenElement ||         // apple - safari fullscreen
                            document.mozFullScreenElement ||            // fullscreen for mozilla
                            document.msFullscreenElement ||             // fullscreen for internet explorer / edge
                            null;                                       // fullscreen for browsers other than the above three

    if(fullscreen_element == null)
    {
         // set fullscreen
        if(canvas.requestFullscreen)                                        // check whether function pointer is not null
        {
            canvas.requestFullscreen();
        }
        else if(canvas.webkitRequestFullscreen)
        {
            canvas.webkitRequestFullscreen();
        }
        else if(canvas.mozRequestFullScreen)
        {
            canvas.mozRequestFullScreen();
        }
        else if(canvas.msRequestFullscreen)
        {
          canvas.msRequestFullscreen();
        }
        bFullscreen = true;   
    }
    else
    {
        if(document.exitFullscreen)
        {
            document.exitFullscreen();
        }
        else if(document.webkitExitFullscreen)
        {
            document.webkitExitFullscreen();
        }
        else if(document.mozCancelFullScreen)
        {
            document.mozCancelFullScreen();
        }
        else if(document.msExitFullscreen)
        {
            document.msExitFullscreen();
        }
        bFullscreen = false;
    }
}


// because of type inference, we dont need to write data type of any variable
function keyDown(event)
{
   switch(event.keyCode)
   {
       case 70 :
            toggleFullscreen();
            // as there is no repaint event in javascript
            break;

        case 107 : // VK_ADD
            grgExposure = grgExposure * 1.1;
            break;

        case 109 :  // VK_SUBTRACT
            grgExposure = grgExposure / 1.1; 
            break;

        case 83 :       // S
        case 115 :      // s
            grgBloomThreshMin = grgBloomThreshMin + 1.0;
            break;

        case 88 : //x
        case 120 :
			grgBloomThreshMin = grgBloomThreshMin - 1.0;
			break;

		case 68 :
        case 100 :
			grgBloomThreshMax = grgBloomThreshMax + 1.0;
			break;

		case 67 : 
        case 99 :
			grgBloomThreshMax = grgBloomThreshMax - 1.0;
			break;

		case 78 :
        case 110 :
            alert("n key pressed, showpreflter : " + grgShowPrefilter);
			grgShowPrefilter = !grgShowPrefilter;
			break;

		case 66 :
        case 98 :
			grgBloomFactor = grgBloomFactor + 1.0;
			break;

		case 86 :
        case 118 :
			grgSceneFactor = grgSceneFactor + 1.0;
			break;
   }
}

function mouseDown()
{
    // code
   
}

function init()
{
    // get drawing context from canvas
    // to maintain consistency, we will get context in init() instead of in main()
    gl = canvas.getContext("webgl2");

    if(!gl)
        console.log("webgl2 context failed");
    else
        console.log("webgl2 context succeeded");

    if(!gl.getExtension('EXT_color_buffer_float'))
    {
        return alert("need color buffer float");
    }
    if(!gl.getExtension('OES_texture_float_linear'))
    {
        return alert("Need OES structure");
    }
    if(!gl.getExtension('WEBGL_color_buffer_float'))
    {
       
        return alert("Need render buffer extension");
    }
    if(!gl.getExtension('WEBGL_color_buffer_float'))
    {
       
        return alert("Need render buffer extension");
    }
    

    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;

    // vertex shader
    var grvertexShaderSourceCode1 =				
    "#version 300 es" +
    "\n" +
    //"precision mediump uniform;" +
    "in vec4 vPosition;" +
    "in vec3 vNormal;" +
    "uniform mat4 transform_mat_proj;" +
    "uniform mat4 transform_mat_view;" +
    "uniform mat4 transform_mat_model;" +
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
		"uniform float bloom_thresh_min;" +
		"uniform float bloom_thresh_max;" +
		"uniform vec3 material_diffuse_color;" +
		"uniform vec3 material_specular_color;" +
		"uniform float material_specular_power;" +
		"uniform vec3 material_ambient_color;" +
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
    "vec4(-1.0, 1.0, 0.5, 1.0)," +
    "vec4(1.0, 1.0, 0.5, 1.0));" +
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
    "vec4 c = vec4(0.0);" +
    "ivec2 P = ivec2(gl_FragCoord.yx) - ivec2(0, weights.length() >> 1);" +
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
    "vec4(-1.0, 1.0, 0.5, 1.0)," +
    "vec4(1.0, 1.0, 0.5, 1.0));" +
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
    "vec4 c = vec4(0.0);" +
    "c += texelFetch(hdr_image, ivec2(gl_FragCoord.xy), 0) * scene_factor;" +
    "c += texelFetch(bloom_image, ivec2(gl_FragCoord.xy), 0) * bloom_factor;" +
    "c.rgb = vec3(1.0) - exp(-c.rgb * exposure);" +
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
    

    var grcubeVertices = new Float32Array(
        [
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0
        ]
    );

    var grcubeNormals = new Float32Array(
        [
            0.0, 0.0, 1.0,					// one normal for single surface 
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0
        ]
    );

    // cube
    grgVao_cube = gl.createVertexArray();
    gl.bindVertexArray(grgVao_cube);

    grgVbo_position_cube = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVbo_position_cube);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    // normals
    grgVbo_normal_cube = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grgVbo_normal_cube);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeNormals, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_NORMAL, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_NORMAL);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    
    gl.bindVertexArray(null);

    // ******************************************************** FBO *****************************************************************8
    //********************************************************************************************************************************
    
    var exposureLUT = new Float32Array([11.0, 6.0, 3.2, 2.8, 2.2, 1.90, 1.80, 1.80, 1.70, 1.70,
		1.60, 1.60, 1.50, 1.50, 1.40, 1.40, 1.30, 1.20, 1.10, 1.00]);

    var buffers = [gl.COLOR_ATTACHMENT0, gl.COLOR_ATTACHMENT1];

    render_fbo = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, render_fbo);

    tex_scene = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, tex_scene);
    gl.texStorage2D(gl.TEXTURE_2D, 1, gl.RGBA16F, MAX_SCENE_WIDTH, MAX_SCENE_HEIGHT);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, tex_scene, 0);
    
    tex_brightpass = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, tex_brightpass);
    gl.texStorage2D(gl.TEXTURE_2D, 1, gl.RGBA16F, MAX_SCENE_WIDTH, MAX_SCENE_HEIGHT);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT1, gl.TEXTURE_2D, tex_brightpass, 0);
    
    tex_depth = gl.createRenderbuffer();
    gl.bindRenderbuffer(gl.RENDERBUFFER, tex_depth);
    gl.renderbufferStorage(gl.RENDERBUFFER, gl.DEPTH_COMPONENT32F, gl.TEXTURE_2D, tex_depth, 0);
    gl.framebufferRenderbuffer(gl.FRAMEBUFFER, gl.DEPTH_ATTACHMENT, gl.RENDERBUFFER, tex_depth);
    gl.drawBuffers(buffers);

    var err = gl.checkFramebufferStatus(gl.FRAMEBUFFER);
    if(err !== gl.FRAMEBUFFER_COMPLETE)
    {
        console.log("in fbo, error, framebuffer not complete, error code : " + err);
    }

    filter_fbo[0] = gl.createFramebuffer();
    filter_fbo[1] = gl.createFramebuffer();
    tex_filter[0] = gl.createTexture();
    tex_filter[1] = gl.createTexture();
    for(i = 0; i < 2; i++)
    {
        gl.bindFramebuffer(gl.FRAMEBUFFER, filter_fbo[i]);
        gl.bindTexture(gl.TEXTURE_2D, tex_filter[i]);
        gl.texStorage2D(gl.TEXTURE_2D, 1, gl.R32F, 20, i ? MAX_SCENE_HEIGHT : MAX_SCENE_WIDTH);
        gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, tex_filter[i], 0);
        gl.drawBuffers([gl.COLOR_ATTACHMENT0, gl.COLOR_ATTACHMENT1]);
       
       
    }

    if(err !== gl.FRAMEBUFFER_COMPLETE)
    {
        console.log("in filter fbo, error, framebuffer not complete");
    }
    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
    
    tex_lut = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, tex_lut);
    gl.texStorage2D(gl.TEXTURE_2D, 1, gl.RGBA16F, 20, 20);
    gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 20, 0, 20, gl.RED, gl.FLOAT, exposureLUT, 0);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);

    grgperspecticeMatrix = mat4.create();

    gl.enable(gl.DEPTH_TEST);
    //gl.clearDepth(1.0);

    // blue color
    gl.clearColor(0.0, 0.0, 1.0, 1.0);
     
}

function resize()
{
    grgperspecticeMatrix = mat4.create();
    if(bFullscreen == true)
    {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
    }
    else
    {
        canvas.width = canvas_original_width;
        canvas.height = canvas_original_height;
    }

    gl.viewport(0, 0, canvas.width, canvas.height);

    mat4.perspective(grgperspecticeMatrix, 45.0, parseFloat(canvas.width) / parseFloat(canvas.height), 0.1, 100.0);
    

}

function draw()
{
    var grmodelMatrix = mat4.create();
    var grviewMatrix = mat4.create();
    var grprojectionMatrix = mat4.create();
    var grtranslateMatrix = mat4.create();
    var grrotateMatrix = mat4.create();
    var grscaleMatrix = mat4.create();

    gl.clear(gl.COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);

    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.bindFramebuffer(gl.FRAMEBUFFER, render_fbo);
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

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, -6.0]);
    mat4.multiply(grmodelMatrix, grmodelMatrix, grtranslateMatrix);
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grgperspecticeMatrix);

    gl.uniformMatrix4fv(grgModelMatrixUniform, false, grmodelMatrix);
    gl.uniformMatrix4fv(grgViewMatrixUniform, false, grviewMatrix);
    gl.uniformMatrix4fv(grgProjMatrixUniform, false, grprojectionMatrix);

    gl.bindVertexArray(grgVao_cube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);
    
    // **** filter program *******
    gl.useProgram(hdrbloom_filter);
    gl.bindVertexArray(grgVao_cube);
    gl.bindFramebuffer(gl.FRAMEBUFFER, filter_fbo[0]);
    gl.bindTexture(gl.TEXTURE_2D, tex_brightpass);
    gl.viewport(0, 0, canvas.width, canvas.height);

    gl.bindVertexArray(grgVao_cube);
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    
    gl.bindFramebuffer(gl.FRAMEBUFFER, filter_fbo[1]);
    gl.bindTexture(gl.TEXTURE_2D, tex_filter[0]);
    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);

    // ***** resolve program ******
    gl.useProgram(hdrbloom_filter);
    gl.uniform1f(grgExposureUniform, grgExposure);
    if(grgShowPrefilter)
    {
        gl.uniform1f(grgBloomFactorUniform, 0.0);
        gl.uniform1f(grgSceneFactorUniform, 1.0);
    }
    else
    {
        gl.uniform1f(grgBloomFactorUniform, grgBloomFactor);
        gl.uniform1f(grgSceneFactorUniform, grgSceneFactor);
    }
    gl.uniform1i(grgHdrImageUniform2, 0);
    gl.uniform1i(grgBloomImageUniform, 1);

    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.activeTexture(gl.TEXTURE1);
    gl.bindTexture(gl.TEXTURE_2D, tex_filter[1]);
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grgShowPrefilter ? tex_brightpass : tex_scene);

    gl.bindVertexArray(grgVao_cube);
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    gl.bindVertexArray(null);
    
    gl.useProgram(null);


    /*
    // variables
    var grmodelViewMatrix;
    var grmodelViewProjectionMatrix;
    var grtranslateMatrix;

    gl.clear(gl.COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);

    gl.useProgram(grshaderProgramObject);
    grmodelViewMatrix = mat4.create();
    grmodelViewProjectionMatrix = mat4.create();
    grtranslateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, -6.0]);
    mat4.multiply(grmodelViewMatrix, grmodelViewMatrix, grtranslateMatrix);
    mat4.multiply(grmodelViewProjectionMatrix, grperspectiveMatrix, grmodelViewMatrix);

    gl.uniformMatrix4fv(grmvpUniform, false, grmodelViewProjectionMatrix);

    gl.bindVertexArray(grvao);
    gl.drawArrays(gl.TRIANGLES, 0, 3);
    gl.bindVertexArray(null);

    gl.useProgram(null);
    */
    requestAnimationFrame(draw, canvas);
}

function uninitialize()
{
    if(grgVao_cube)
    {
        gl.deleteVertexArray(grgVao_cube);
        grgVao_cube = null;
    }
    if(grgVbo_position_cube)
    {
        gl.deleteBuffer(grgVbo_position_cube);
        grgVbo_position_cube = null;
    }

   

}




