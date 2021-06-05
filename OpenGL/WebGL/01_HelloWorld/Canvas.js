function main()
{
    // get  canvas from DOM
    var canvas = document.getElementById("GR");
    if(!canvas)
        console.log("ontaining canvas failed");
    else
        console.log("ontaining canvas succeeded");

    // retrieve width and height of canvas just for info
    console.log("\n canvas width : " + canvas.clientWidth + " canvas height : " + canvas.height );

    // get drawing context from canvas
    var context = canvas.getContext("2d");

    if(!context)
        console.log("obtaining context failed");
    else
        console.log("obtaining context succeeded");

    context.fillStyle = "black";
    context.fillRect(0, 0, canvas.width, canvas.height);

    // center the text
    context.textAlign = "center";   // horizontal center
    context.textBaseline = "middle"; // vertical center
    context.font = "48px sans-serif";

    // declare string to be displayed
    var str = "Hello World..!!!";

    // color the text
    context.fillStyle = "white";

    // display the text
    context.fillText(str, canvas.width/2, canvas.height/2);
}

