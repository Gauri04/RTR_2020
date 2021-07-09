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

var grvertexShaderObject;
var grfragmentShaderObject;
var grshaderProgramObject;


var grvaoCube;
var grvboCubePosition;
var grvboCubeNormal;
var grvboCubeColor;

var grmodelViewMatrixUniform;
var grprojectionMatrixUniform;
var grlKeyPressedUniform;
var grldUniform;
var grkdUniform;
var grlightPositionUniform;
var grperspectiveMatrix;
var grblight = false;
var grbanimate = false;
var grangle = 0.0;

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

        case 27 :       // escape
            uninitialize();
            window.close();
            break;

        case 108:       // 'l' or 'L'
        case 76:
            grblight = !grblight;
            break;

        case 97: // a
        case 65:
            grbanimate = !grbanimate;
            break;
        
   }
   console.log(event.keyCode);
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

    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;

    // vertex shader
    var grvertexShaderSourceCode = 
    "#version 300 es" +
    "\n" +
    "in vec4 vPosition;" +
    "in vec3 vNormal;" +
    "uniform highp mat4 u_model_view_matrix;" +
    "uniform highp mat4 u_projection_matrix;" +
    "uniform highp int u_l_key_pressed;" +
    "uniform highp vec3 u_ld;" +
    "uniform highp vec3 u_kd;" +
    "uniform highp vec4 u_light_position;" +
    "out vec3 diffuse_light;" +
    "void main(void)" +
    "{" +
        "if(u_l_key_pressed == 1)" +
        "{" +
        "vec4 eye_coordinates = u_model_view_matrix * vPosition;" +
        "mat3 normal_matrix = mat3(transpose(inverse(u_model_view_matrix)));" +
        "vec3 t_norm = normalize(normal_matrix * vNormal);" +
        "vec3 s = normalize(vec3(u_light_position - eye_coordinates));" +
        "diffuse_light = u_ld * u_kd * max(dot(s, t_norm), 0.0);" +
        "}" +
    "gl_Position = u_projection_matrix * u_model_view_matrix * vPosition;" +
    "}";

    grvertexShaderObject = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(grvertexShaderObject, grvertexShaderSourceCode);
    gl.compileShader(grvertexShaderObject);
    if(gl.getShaderParameter(grvertexShaderObject, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grvertexShaderObject);
        if(error.length > 0)
        {
            alert("Vertex shader log : " + error);
            uninitialize();
        }

    }

    var grfragmentShaderSourceCode = 
    "#version 300 es" +
    "\n" +
    "precision highp float;" +
    "vec4 color;" +
    "in vec3 diffuse_light;" +
    "uniform highp int u_l_key_pressed;" +
    "out vec4 FragColor;" +
    "void main(void)" +
    "{" +
    "if(u_l_key_pressed == 1)" +
    "{" +
        "color = vec4(diffuse_light, 1.0);" +
    "}" +
    "else" +
    "{" +
        "color = vec4(1.0, 1.0, 1.0, 1.0);"	+
    "}" +
    "FragColor = color;" +
    "}";

    grfragmentShaderObject = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(grfragmentShaderObject, grfragmentShaderSourceCode);
    gl.compileShader(grfragmentShaderObject);
    if(gl.getShaderParameter(grfragmentShaderObject, gl.COMPILE_STATUS) == false)
    {
        var error = gl.getShaderInfoLog(grfragmentShaderObject);
        if(error.length > 0)
        {
            alert("fragment shader : " + error);
            uninitialize(); 
        }
        
    }

    // shader program
    grshaderProgramObject = gl.createProgram();
    //attach shader object
    gl.attachShader(grshaderProgramObject, grvertexShaderObject);
    gl.attachShader(grshaderProgramObject, grfragmentShaderObject);
    // pre-linking
    gl.bindAttribLocation(grshaderProgramObject, WebGLMacros.GR_ATTRIBUTE_POSITION, "vPosition");
    gl.bindAttribLocation(grshaderProgramObject, WebGLMacros.GR_ATTRIBUTE_NORMAL, "vNormal");

    // linking
    gl.linkProgram(grshaderProgramObject);
    if(!gl.getProgramParameter(grshaderProgramObject, gl.LINK_STATUS))
    {
        var err = gl.getProgramInfoLog(grshaderProgramObject);
        if(err.length > 0)
        {
            alert("Shader Program : " + err);
            uninitialize(); 
        }
       
    }

    // mvp uniform binding
    grmodelViewMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_model_view_matrix");
    grprojectionMatrixUniform = gl.getUniformLocation(grshaderProgramObject, "u_projection_matrix");
    grlKeyPressedUniform = gl.getUniformLocation(grshaderProgramObject, "u_l_key_pressed");
    grldUniform = gl.getUniformLocation(grshaderProgramObject, "u_ld");
    grkdUniform = gl.getUniformLocation(grshaderProgramObject, "u_kd");
    grlightPositionUniform = gl.getUniformLocation(grshaderProgramObject, "u_light_position");


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

    var grcubeNormals = new Float32Array(
        [
            0.0, 0.0, 1.0,					// one normal for single surface 
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
    
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
    
            0.0, 0.0, -1.0,
            0.0, 0.0, -1.0,
            0.0, 0.0, -1.0,
            0.0, 0.0, -1.0,
    
            -1.0, 0.0, 0.0,
            -1.0, 0.0, 0.0,
            -1.0, 0.0, 0.0,
            -1.0, 0.0, 0.0,
    
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
    
            0.0, -1.0, 0.0,
            0.0, -1.0, 0.0,
            0.0, -1.0, 0.0,
            0.0, -1.0, 0.0,
        ]
    );

    // square
    grvaoCube = gl.createVertexArray();
    gl.bindVertexArray(grvaoCube);

    grvboCubePosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboCubePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    grvboCubeNormal = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboCubeNormal);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeNormals, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_NORMAL, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_NORMAL);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    
    gl.bindVertexArray(null);


    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    grperspectiveMatrix = mat4.create();
    // blue color
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
     
}

function resize()
{
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

    mat4.perspective(grperspectiveMatrix, 45.0, parseFloat(canvas.width) / parseFloat(canvas.height), 0.1, 100.0);

}

function draw()
{
    // variables
    var grmodelViewMatrix = mat4.create();
    var grscaleMatrix = mat4.create();
    var grprojectionMatrix = mat4.create();
    var grtranslateMatrix = mat4.create();
    var grrotateMatrix = mat4.create();
    var grlightPosition = new Float32Array([0.0, 0.0, 2.0, 1.0]);

    gl.clear(gl.COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);

    gl.useProgram(grshaderProgramObject);

    //*** cube ******
    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, -6.0]);
    mat4.scale(grscaleMatrix, grscaleMatrix, [0.75, 0.75, 0.75]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grangle));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grangle));
    mat4.rotateZ(grrotateMatrix, grrotateMatrix, deg2rad(grangle));
  
    mat4.multiply(grmodelViewMatrix, grtranslateMatrix, grscaleMatrix);
    mat4.multiply(grmodelViewMatrix, grmodelViewMatrix, grrotateMatrix);
    mat4.multiply(grprojectionMatrix, grprojectionMatrix, grperspectiveMatrix);

    if(grblight == true)
    {
        gl.uniform1i(grlKeyPressedUniform, 1);
        gl.uniform3f(grldUniform, 1.0, 1.0, 1.0);
        gl.uniform3f(grkdUniform, 0.5, 0.5, 0.5);
        gl.uniform4f(grlightPositionUniform, 0.0, 0.0, 100.0, 0.0);
    }
    else
    {
        gl.uniform1i(grlKeyPressedUniform, 0);
    }

    gl.uniformMatrix4fv(grmodelViewMatrixUniform, false, grmodelViewMatrix);
    gl.uniformMatrix4fv(grprojectionMatrixUniform, false, grprojectionMatrix);
    
    gl.bindVertexArray(grvaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.useProgram(null);
    if(grbanimate == true)
    {
        update();
    }
    requestAnimationFrame(draw, canvas);
}

function update()
{
    if(grangle >= 360.0)
    {
        grangle = 0.0;
    }
    grangle = grangle + 0.1;

}

function deg2rad(degrees)
{
    var rad = degrees * Math.PI / 180.0;
    return rad;
}

function uninitialize()
{
    
    if(grvaoCube)
    {
        gl.deleteVertexArray(grvaoCube);
        grvaoCube = null;
    }
    if(grvboCubePosition)
    {
        gl.deleteBuffer(grvboCubePosition);
        grvboCubePosition = null;
    }
    if(grvboCubeNormal)
    {
        gl.deleteBuffer(grvboCubeNormal);
        grvboCubeNormal = null;
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




