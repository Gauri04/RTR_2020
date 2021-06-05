var canvas = null;
var context = null;

function main()
{
    // get  canvas from DOM
    canvas = document.getElementById("GR");
    if(!canvas)
        console.log("ontaining canvas failed");
    else
        console.log("ontaining canvas succeeded");

    // retrieve width and height of canvas just for info
    console.log("\n canvas width : " + canvas.clientWidth + " canvas height : " + canvas.height );

    // get drawing context from canvas
    context = canvas.getContext("2d");

    if(!context)
        console.log("obtaining context failed");
    else
        console.log("obtaining context succeeded");

    context.fillStyle = "black";
    context.fillRect(0, 0, canvas.width, canvas.height);

    drawText("Hello World !!!");
    // "keydown" and "click" are in-built events. keyDown and mouseDown are user defined functions
    // param false states that events are bubble events, not captured events 
    window.addEventListener("keydown", keyDown, false);         // window is in-build variable, just like document. window is inherited from document, its a DOM object.
    window.addEventListener("click", mouseDown, false);
}

function drawText(text)
{
   // center the text
   context.textAlign = "center";   // horizontal center
   context.textBaseline = "middle"; // vertical center
   context.font = "48px sans-serif";

   // color the text
   context.fillStyle = "white";

   // display the text
   context.fillText(text, canvas.width/2, canvas.height/2);    
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
            drawText("Hello World !!!");
            break;
   }
}

function mouseDown()
{
    // code
   
}