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


var grvaoSquare;
var grvboSquarePosition;
var grvboSquareTexCoord;

var grmvpUniform;
var grtextureSamplerUniform;
var grperspectiveMatrix;
var grtextureSmiley;
var grkeyPress = 1;

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

        case 27 :
            uninitialize();
            window.close();
            break;

        case 49 :           // numpad1
            grkeyPress = 1;
            break;

        case 50 :           // numpad2
            grkeyPress = 2;
            break;

        case 51 :           // numpad 3
            grkeyPress = 3; 
            break;

        case 52 :           // numpad4
            grkeyPress = 4;
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
    "in vec2 vTexCoord;" +
    "out vec2 out_texcoord;" +
    "uniform mat4 u_mvp_matrix;" +
    "void main(void)" +
    "{" +
    "out_texcoord = vTexCoord;" +
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
    grtextureSamplerUniform = gl.getUniformLocation(grshaderProgramObject, "u_texture_sampler");


    var grsquareVertices = new Float32Array(
        [
            1.0, 1.0, 0.0,
            -1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0
        ]
    );

    // square
    grvaoSquare = gl.createVertexArray();
    gl.bindVertexArray(grvaoSquare);

    grvboSquarePosition = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboSquarePosition);
    gl.bufferData(gl.ARRAY_BUFFER, grsquareVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    grvboSquareTexCoord = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboSquareTexCoord);
    gl.bufferData(gl.ARRAY_BUFFER, null, gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_TEXTURE, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_TEXTURE);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    
    gl.bindVertexArray(null);

    // texture
    grtextureSmiley = gl.createTexture();
	grtextureSmiley.image = new Image();
	grtextureSmiley.image.src = "smiley.jpg";
	grtextureSmiley.image.onload = function()
	{
		gl.bindTexture(gl.TEXTURE_2D, grtextureSmiley);
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, grtextureSmiley.image);
        gl.bindTexture(gl.TEXTURE_2D, null);
	};


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
    var grmodelViewProjectionMatrix = mat4.create();
    var grtranslateMatrix = mat4.create();
    var grrotateMatrix = mat4.create();
    var grtexCoord = new Float32Array(8);

    gl.clear(gl.COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT);

    gl.useProgram(grshaderProgramObject);

    //*** Square ******
    switch(grkeyPress)
    {
        case 1:
            grtexCoord[0] = 1;
		    grtexCoord[1] = 1;
		    grtexCoord[2] = 0;
		    grtexCoord[3] = 1;
		    grtexCoord[4] = 0;
		    grtexCoord[5] = 0;
		    grtexCoord[6] = 1;
		    grtexCoord[7] = 0;
            break;

        case 2:
            grtexCoord[0] = 0.5;
            grtexCoord[1] = 0.5;
            grtexCoord[2] = 0;
            grtexCoord[3] = 0.5;
            grtexCoord[4] = 0;
            grtexCoord[5] = 0;
            grtexCoord[6] = 0.5;
            grtexCoord[7] = 0;
            break;

        case 3:
            grtexCoord[0] = 2;
            grtexCoord[1] = 2;
            grtexCoord[2] = 0;
            grtexCoord[3] = 2;
            grtexCoord[4] = 0;
            grtexCoord[5] = 0;
            grtexCoord[6] = 2;
            grtexCoord[7] = 0;
            break;

        case 4:
            grtexCoord[0] = 0.5;
            grtexCoord[1] = 0.5;
            grtexCoord[2] = 0.5;
            grtexCoord[3] = 0.5;
            grtexCoord[4] = 0.5;
            grtexCoord[5] = 0.5;
            grtexCoord[6] = 0.5;
            grtexCoord[7] = 0.5;
            break;

    }
    grtranslateMatrix = mat4.create();
    grmodelViewMatrix = mat4.create();
    grrotateMatrix - mat4.create();
    grmodelViewProjectionMatrix = mat4.create();

    mat4.translate(grtranslateMatrix, grtranslateMatrix, [0.0, 0.0, -6.0]);
    mat4.multiply(grmodelViewMatrix, grmodelViewMatrix, grtranslateMatrix);
    mat4.multiply(grmodelViewProjectionMatrix, grperspectiveMatrix, grmodelViewMatrix);

    gl.uniformMatrix4fv(grmvpUniform, false, grmodelViewProjectionMatrix);

    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, grtextureSmiley);
    gl.uniform1i(grtextureSamplerUniform, 0);

    gl.bindVertexArray(grvaoSquare);
    gl.bindBuffer(gl.ARRAY_BUFFER, grvboSquareTexCoord);
    gl.bufferData(gl.ARRAY_BUFFER, grtexCoord, gl.DYNAMIC_DRAW);
    gl.vertexAttribPointer(WebGLMacros.GR_ATTRIBUTE_TEXTURE, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(WebGLMacros.GR_ATTRIBUTE_TEXTURE);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
    gl.bindVertexArray(null);

    gl.useProgram(null);
    update();
    requestAnimationFrame(draw, canvas);
}

function update()
{
   // code
}

function deg2rad(degrees)
{
    var rad = degrees * Math.PI / 180.0;
    return rad;
}

function uninitialize()
{

    if(grvaoSquare)
    {
        gl.deleteVertexArray(grvaoSquare);
        grvaoSquare = null;
    }
    if(grvboSquarePosition)
    {
        gl.deleteBuffer(grvboSquarePosition);
        grvboSquarePosition = null;
    }
    if(grvboSquareTexCoord)
    {
        gl.deleteBuffer(grvboSquareTexCoord);
        grvboSquareTexCoord = null;
    }
    // textures
    if(grtextureSmiley)
    {
        gl.deleteTexture(grtextureSmiley);
        grtextureSmiley = null;
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




