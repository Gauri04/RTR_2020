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
            //console.log("Add key exposure" +grgExposure);
            break;

        case 109 :  // VK_SUBTRACT
            grgExposure = grgExposure / 1.1; 
            //console.log("Sub key exposure" +grgExposure);
            break;

        case 83 :       // S
        case 115 :      // s
            grgBloomThreshMin = grgBloomThreshMin + 1.0;
            //console.log("S key bloomthreshmin" +grgBloomThreshMin);
            break;

        case 88 : //x
        case 120 :
			grgBloomThreshMin = grgBloomThreshMin - 1.0;
            //console.log("X key bloomthreshmin" +grgBloomThreshMin);
			break;

		case 68 :   //d
        case 100 :
			grgBloomThreshMax = grgBloomThreshMax + 1.0;
            //console.log("D key bloomthreshmax" +grgBloomThreshMax);
			break;

		case 67 : // C
        case 99 :
			grgBloomThreshMax = grgBloomThreshMax - 1.0;
            //console.log("C key bloomthreshmax" +grgBloomThreshMax);
			break;

		case 78 :
        case 110 :  //n
           
			if(grgShowPrefilter == 0)
            {
                grgShowPrefilter = 1;
            }
            else
            {
                grgShowPrefilter = 0;
            }
            alert("n key pressed, showpreflter : " + grgShowPrefilter);
			break;

		case 66 :   // b
        case 98 :
			grgBloomFactor = grgBloomFactor + 1.0;
            //console.log("B key bloomfactor" +grgBloomFactor);
			break;

		case 86 :       //v
        case 118 :
			grgSceneFactor = grgSceneFactor + 1.0;
            //console.log("V key bloomfactor" +grgSceneFactor);
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
    GRInitBloom();
    
    gl.enable(gl.DEPTH_TEST);
    gl.depthFunc(gl.LEQUAL);
    grperspectiveMatrix = mat4.create();
   
    // blue color
    gl.clearColor(0.0, 0.0, 1.0, 1.0);
     
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
    //gl.canvas.width = canvas.width;
   // gl.canvas.height = canvas.height;
   // gl.viewportWidth = canvas.width
   // gl.viewportHeight = canvas.height;
    gl.viewport(0, 0, canvas.width, canvas.height);

    mat4.perspective(grperspectiveMatrix, 45.0, parseFloat(canvas.width) / parseFloat(canvas.height), 0.1, 100.0);

}

function draw()
{
  
   GRDisplayBloom();
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
   GRUninitializeBloom();

}




