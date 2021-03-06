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

var grvaoPyramid;
var grvboPyramidPosition;
var grvboPyramidColors;

var grvaoCube;
var grvboCubePosition;
var grvboCubeColor;

var grmvpUniform;
var grperspectiveMatrix;
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

    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;

    // vertex shader
    var grvertexShaderSourceCode = 
    "#version 300 es" +
    "\n" +
    "in vec4 vPosition;" +
    "in vec4 vColor;" +
    "out vec4 out_color;" +
    "uniform mat4 u_mvp_matrix;" +
    "void main(void)" +
    "{" +
    "out_color = vColor;" +
    "gl_Position = u_mvp_matrix * vPosition;" +
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
    "in vec4 out_color;" +
    "out vec4 FragColor;" +
    "void main(void)" +
    "{" +
    "FragColor = out_color;" +
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
    gl.bindAttribLocation(grshaderProgramObject, WebGLMacros.GR_ATTRIBUTE_COLOR, "vColor");

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
    grmvpUniform = gl.getUniformLocation(grshaderProgramObject, "u_mvp_matrix");


    var grpyramidVertices = new Float32Array(
        [
            0.0, 1.0, 0.0,
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
                                    //right face
            0.0, 1.0, 0.0,
            1.0, -1.0, -1.0,
            1.0, -1.0, 1.0,
                                    // back face
            0.0, 1.0, 0.0,
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
                                    // left face
            0.0, 1.0, 0.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0, 1.0
        ]
    );
    var grpyramidColors = new Float32Array(
        [
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
    
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
    
            0.0, 0.0, 0.0,
            0.0, 0.0, 1.0,
            0.0, 1.0, 0.0,
    
            1.0, 0.0, 0.0,
            0.0, 0.0, 1.0,
            0.0, 1.0, 0.0
        ]
    );

    var grcubeColors = new Float32Array(
        [
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
    
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
    
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
    
            0.0, 1.0, 1.0,
            0.0, 1.0, 1.0,
            0.0, 1.0, 1.0,
            0.0, 1.0, 1.0,
    
            1.0, 0.0, 1.0,
            1.0, 0.0, 1.0,
            1.0, 0.0, 1.0,
            1.0, 0.0, 1.0,
    
            1.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            1.0, 1.0, 0.0,
            1.0, 1.0, 0.0
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

    // triangle
    grvaoPyramid = gl.createVertexArray();
    gl.bindVertexArray(grvaoPyramid);

    grvboPyramidPosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboPyramidPosition);
    gl.bufferData(gl.ARRAY_BUFFER, grpyramidVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    grvboPyramidColors = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboPyramidColors);
    gl.bufferData(gl.ARRAY_BUFFER, grpyramidColors, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_COLOR, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_COLOR);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    
    gl.bindVertexArray(null);


    // square
    grvaoCube = gl.createVertexArray();
    gl.bindVertexArray(grvaoCube);

    grvboCubePosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboCubePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    grvboCubeColor = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboCubeColor);
    gl.bufferData(gl.ARRAY_BUFFER, grcubeColors, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_COLOR, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_COLOR);
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
    var grmodelViewMatrix;
    var grmodelViewProjectionMatrix;
    var grtranslateMatrix;
    var grrotateMatrix = mat4.create();

    gl.clear(gl.COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);

    gl.useProgram(grshaderProgramObject);
    grmodelViewMatrix = mat4.create();
    grmodelViewProjectionMatrix = mat4.create();
    grtranslateMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [-2.0, 0.0, -6.0]);
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grangle));
    mat4.multiply(grmodelViewMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelViewProjectionMatrix, grperspectiveMatrix, grmodelViewMatrix);

    gl.uniformMatrix4fv(grmvpUniform, false, grmodelViewProjectionMatrix);


    gl.bindVertexArray(grvaoPyramid);
    gl.drawArrays(gl.TRIANGLES, 0, 12);
    gl.bindVertexArray(null);

    //*** Square ******
    grtranslateMatrix = mat4.create();
    grmodelViewMatrix = mat4.create();
    grrotateMatrix - mat4.create();
    grmodelViewProjectionMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [2.0, 0.0, -6.0]);
    mat4.rotateX(grrotateMatrix, grrotateMatrix, deg2rad(grangle));
    mat4.rotateY(grrotateMatrix, grrotateMatrix, deg2rad(grangle));
    mat4.rotateZ(grrotateMatrix, grrotateMatrix, deg2rad(grangle));
    mat4.multiply(grmodelViewMatrix, grtranslateMatrix, grrotateMatrix);
    mat4.multiply(grmodelViewProjectionMatrix, grperspectiveMatrix, grmodelViewMatrix);

    gl.uniformMatrix4fv(grmvpUniform, false, grmodelViewProjectionMatrix);

    gl.bindVertexArray(grvaoCube);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 4, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 8, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 12, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 16, 4);
    gl.drawArrays(gl.TRIANGLE_FAN, 20, 4);
    gl.bindVertexArray(null);

    gl.useProgram(null);
    update();
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
    if(grvaoPyramid)
    {
        gl.deleteVertexArray(grvaoPyramid);
        grvaoPyramid = null;
    }
    if(grvboPyramidPosition)
    {
        gl.deleteBuffer(grvboPyramidPosition);
        grvboPyramidPosition = null;
    }
    if(grvboPyramidColors)
    {
        gl.deleteBuffer(grvboPyramidColors);
        grvboPyramidColors = null;
    }
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
    if(grvboCubeColor)
    {
        gl.deleteBuffer(grvboCubeColor);
        grvboCubeColor = null;
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




