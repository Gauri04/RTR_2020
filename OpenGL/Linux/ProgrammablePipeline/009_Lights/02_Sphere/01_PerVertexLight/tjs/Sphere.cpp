#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <GL/glew.h>
#include "vmath.h"
#include "Sphere.h"

using namespace vmath;
#include <X11/Xlib.h> //
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <GL/glx.h> //openGL for xwindows //for glx api
#include <GL/gl.h>

#include <SOIL/SOIL.h> // texture change

//namespace
using namespace std;

//global vars declaration
bool bFullScreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColorMap;
Window gWindow;
/*******************************/

typedef GLXContext (*glxCreateContextAttribsArbProc)(Display *, GLXFBConfig, GLXContext, Bool, const int *);
glxCreateContextAttribsArbProc glxCreateContextAttribsArb = NULL;
GLXFBConfig gGLXFBConfig;
GLXContext gGLXContext;

/******************************/

int giWindowWidth= 800;
int giWindowHeight= 600;

/**************************/
int winWidth;
int winHeight;

enum 
{
	tvn_attribute_position = 0,
	tvn_attribute_color,
	tvn_attribute_textccord,
	tvn_attribute_normal,
	tvn_attribute_element
};



GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLint shaderProgramLinkStatus;

GLuint gShaderProgramObject;
GLint shaderCompiledStatus;

mat4 perspectiveProjectionMatrix;

GLint glInfoLogLength;
GLuint mvpMatrixUniform;
GLuint modelViewMatrix;
GLuint projectionMatrixUniform ;
GLuint lkeyPressedUniform;
GLuint ldUniform;
GLuint kdUniform;
GLuint lightPositionUniform;


GLfloat sphere_vertices[1146];
GLfloat sphere_normals[1146];
GLfloat sphere_textures[764];

unsigned short sphere_elements[2280];
GLuint gNumVertices;
GLuint gNumElements;

GLuint vao_sphere;
GLuint vbo_sphere_normal;
GLuint vbo_sphere_vertex;
GLuint vbo_sphere_element;



GLchar *szBuffer = NULL;
GLsizei written;

GLfloat tangle = 0.0f;
GLfloat sangle = 0.0f;


FILE *gpFile = NULL;
bool bLight = false;


//entry point function
int main(void)
{
	//func prototype
	void CreateWindow(void);
	void ToggleFullScreen(void);
	void unintialize();
/***************************************/
	void initialize();
	void resize(int, int);
	void Draw();
	bool bDone = false;

	gpFile =fopen("logfile.txt","w+" );
	if(gpFile == NULL)
	{
		printf("Failed to Open A Log File\n");
		fprintf(gpFile,"Succesfully Create Strat of Program\n");
		exit(0);
	}
	else 
	{
		fprintf(gpFile,"Succesfully Create Strat of Program\n");
		
	}		
	


	//code
	CreateWindow();
	/***********************/
	initialize();

	//Message loop
	XEvent event;
	KeySym keysym;


	while(bDone == false) /********************change*******game loop********/
	{
		while(XPending(gpDisplay)) //in network it creates queue, xpending keeps in the queue 
		{
		XNextEvent(gpDisplay, &event); // give next from pending
		switch(event.type)
		{
			case MapNotify:
				break;
			case KeyPress:
				keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
				switch(keysym)
				{
					case XK_Escape:

						bDone = true;
					//	unintialize();
					//	exit(0);
					case XK_F:
					case XK_f:
						if(bFullScreen == false)
						{
							ToggleFullScreen();
							bFullScreen = true;
						}
						else
						{
							ToggleFullScreen();
							bFullScreen = false;
						}
						break;
					case XK_l:
						bLight = !bLight;
						break;
					default: 
						break;


				}
				break;
			case ButtonPress:
				switch(event.xbutton.button)
				{
					case 1:
						break;
					case 2:
						break;
					case 3: 
						break;
					default :
						break;
				}
				break;
			case MotionNotify:
				break;
			case ConfigureNotify:
				winWidth = event.xconfigure.width;
				winHeight = event.xconfigure.height;
				resize(winWidth, winHeight);
				break;
			case Expose :
				break;
			case DestroyNotify:
				break;
			case 33:
				bDone = true;
//				unintialize();
//				exit(0);
			default: 
				break;
		}
	   }
		Draw();//render only when there is no pending message
	}
	unintialize();
	return (0);
}


void CreateWindow(void)
{
	//func prototype
	void unintialize(void);


	//var declaration
	XSetWindowAttributes winAttribs;

	/***********pp change*************/

	GLXFBConfig *pGLXFBConfig = NULL;
	GLXFBConfig bestGLXFBConfig;
	XVisualInfo *ptempXVisualInfo = NULL;
	int numFBConfig = 0;


	/************************************/

	int defaultScreen;
	int defaultDepth;
	int styleMask;

	/**********************pp changes added 4 embers****/
        static int frameBufferAttributes[] = {
		
					      GLX_DOUBLEBUFFER, True,
					      GLX_X_RENDERABLE , True,
					      GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
					      GLX_RENDER_TYPE, GLX_RGBA_BIT,
					      GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
	                                      GLX_RED_SIZE, 8,
	                                      GLX_GREEN_SIZE, 8, 
	                                      GLX_BLUE_SIZE,8,
	                                      GLX_ALPHA_SIZE, 8, 
					      GLX_DEPTH_SIZE, 24, 
					      GLX_STENCIL_SIZE, 8,
					      None                          //end of array we can say 0 as well

					     };

	////////////////change for doubleBuffer from 1 to 8	

	/**********************************/

	//code
	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL)
	{
		printf("Error: UNable to open X Display \n Exitting NOw...\n");
		unintialize();
		exit(1);

	}

	defaultScreen= XDefaultScreen(gpDisplay);
	//defaultDepth= DefaultDepth(gpDisplay, defaultScreen);
	

	gpXVisualInfo = (XVisualInfo*)malloc(sizeof(XVisualInfo));
	//not required for pp
//	gpXVisualInfo = glXChooseVisual(gpDisplay, defaultScreen, frameBufferAttributes); // bridging api 
	
       //openGl visual	 - not immediate mode renderiing
	if(gpXVisualInfo== NULL)
	{
		printf("Error : Unable to allocate memory for visual info\n Exitting now .. \n");
		unintialize();
		exit(1);

	}

//	XMatchVisualInfo(gpDisplay, defaultScreen, defaultDepth, TrueColor, gpXVisualInfo);
	pGLXFBConfig = 	glXChooseFBConfig(gpDisplay, XDefaultScreen(gpDisplay),frameBufferAttributes, &numFBConfig); //pp
	printf("Found Number of FBConfig : numFBConfig %d",numFBConfig);

	int bestFrameBufferConfig = -1,worstFrameBufferConfig = -1, bestNuberOfSamples = -1, worstNumberOfSamples = 99; //imagination -sdk
	int i;
	
	for(i = 0 ; i < numFBConfig; i++)
	{
		ptempXVisualInfo = glXGetVisualFromFBConfig(gpDisplay, pGLXFBConfig[i]);
		if(ptempXVisualInfo != NULL)
		{
			int sampleBuffers, samples;
			glXGetFBConfigAttrib(gpDisplay, pGLXFBConfig[i],GLX_SAMPLE_BUFFERS,&sampleBuffers);
			glXGetFBConfigAttrib(gpDisplay,pGLXFBConfig[i],GLX_SAMPLES,&samples);
			
			if(bestFrameBufferConfig < 0 || sampleBuffers && samples > bestNuberOfSamples )
			{
				bestFrameBufferConfig = i;
				bestNuberOfSamples = samples;	
			}
			if(worstFrameBufferConfig < 0 || !sampleBuffers ||  samples < worstNumberOfSamples)
			{
				worstFrameBufferConfig = i;
				worstNumberOfSamples= samples;	
			}
			printf("When i %d , When samples %d , when sampleBuffer %d , when ptempXVisualInfo->VisualID : %lu \n",i , samples, sampleBuffers, ptempXVisualInfo->visualid);
		}
		XFree(ptempXVisualInfo);
	} 

	printf(" bestNuberOfSamples %d ,bestFrameBufferConfig %d \n",bestNuberOfSamples, bestFrameBufferConfig);
	
	bestGLXFBConfig = pGLXFBConfig[bestFrameBufferConfig];
	gGLXFBConfig 	= bestGLXFBConfig;
	
	XFree(pGLXFBConfig);
	
	gpXVisualInfo = glXGetVisualFromFBConfig(gpDisplay,bestGLXFBConfig);	
	


	winAttribs.border_pixel=0;
	winAttribs.background_pixmap=0;
	winAttribs.colormap=XCreateColormap(gpDisplay, 
			RootWindow(gpDisplay, gpXVisualInfo->screen),
			gpXVisualInfo->visual,
			AllocNone
			);

	gColorMap = winAttribs.colormap;

	winAttribs.background_pixel = BlackPixel(gpDisplay, defaultScreen);
	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | ButtonPressMask
				| KeyPressMask | PointerMotionMask | StructureNotifyMask;

	styleMask = CWBorderPixel | CWBackPixel | CWEventMask | CWColormap;

	gWindow = XCreateWindow(gpDisplay,
			RootWindow(gpDisplay, gpXVisualInfo->screen),
			0,
			0,
			giWindowWidth,
			giWindowHeight,
			0,
			gpXVisualInfo->depth,
			InputOutput,
			gpXVisualInfo->visual,
			styleMask,
			&winAttribs);


	if(!gWindow)
	{
		printf("Error: Failed to create Main Window..exiting\n");
		unintialize();
		exit(1);
	}


	XStoreName(gpDisplay, gWindow, "First XWIndow");

	Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);

	XMapWindow(gpDisplay, gWindow);

}


void ToggleFullScreen(void)
{

	//var decl
	Atom wm_state;
	Atom fullScreen;
	XEvent 	xev= {0};

	//code
	wm_state = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
	memset(&xev, 0, sizeof(xev));

	xev.type = ClientMessage;
	xev.xclient.window = gWindow;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = bFullScreen ? 0:1; 


	fullScreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN",False);
	xev.xclient.data.l[1] = fullScreen;

	XSendEvent(gpDisplay, 
			RootWindow(gpDisplay, gpXVisualInfo->screen),
			False,
			StructureNotifyMask,
			&xev
		  );

		
}

void initialize()
{
   	//func declaration 
	void resize(int, int);
	void unintialize(void);

	glxCreateContextAttribsArb = (glxCreateContextAttribsArbProc)glXGetProcAddressARB((GLubyte *)"glXCreateContextAttribsARB");
	if(glxCreateContextAttribsArb == NULL)
	{
		printf("Failed to Locate ""glXCreateContextAttribsARB""\n");
	}


	const int attribs[]  = {GLX_CONTEXT_MAJOR_VERSION_ARB,4,GLX_CONTEXT_MINOR_VERSION_ARB,5, GLX_CONTEXT_PROFILE_MASK_ARB,GLX_CONTEXT_CORE_PROFILE_BIT_ARB,None};

	gGLXContext = glxCreateContextAttribsArb(gpDisplay, gGLXFBConfig, 0, True, attribs);
	if(!gGLXContext)
	{
		const int attribs1[] = {GLX_CONTEXT_MAJOR_VERSION_ARB,1,GLX_CONTEXT_MINOR_VERSION_ARB,0,None};
		gGLXContext = glxCreateContextAttribsArb(gpDisplay, gGLXFBConfig, 0, True, attribs1);
		if(!gGLXContext)
		{
			printf("gGLXContext Failed  \n");
			exit(-1);
		}
	}

	Bool isDirectContext = glXIsDirect(gpDisplay, gGLXContext);
	if(isDirectContext == True)
	{
		printf("HardWareRendering Context\n");
	}
	else
	{
		printf("SoftWareRendering Context\n");
	}
		

	glXMakeCurrent(gpDisplay,gWindow,gGLXContext);


	GLenum glew_error = glewInit();
	if(glew_error != GLEW_OK)
	{
		unintialize();
		exit(1);
	}	


	fprintf(gpFile, "OpenGL Vender : %s\n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(gpFile, "OpenGL GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION)); //gRAPHICS Library shadinng language

	
	//OpenGL Enable Extensions 
	GLint  numExtension;
	
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtension);
	printf("NumExtension %d\n",numExtension);
	for (unsigned int i = 0; i < numExtension; i++)
	{	
		fprintf(gpFile,"%s\n", glGetStringi(GL_EXTENSIONS,i));
	}
	
	//**VERTEX SHADER***
	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexShaderSourceCode =
			"#version 440 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec4 vColor;"\
		"uniform mat4 u_mvpMatrix;"\
		"out vec4 out_color;"\
		"void main(void)" \
		"{" \
		"gl_Position = u_mvpMatrix * vPosition;" \
		"out_color = vColor;"\
		"}";



	glShaderSource(gVertexShaderObject, 1, (const GLchar**)&vertexShaderSourceCode, NULL);

	//compile shader 
	glCompileShader(gVertexShaderObject);


	glGetShaderiv(gVertexShaderObject, GL_COMPILE_STATUS, &shaderCompiledStatus);
	if (shaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gVertexShaderObject, GL_INFO_LOG_LENGTH, &glInfoLogLength);

		if (glInfoLogLength > 0)
		{
			szBuffer = (GLchar*)malloc(glInfoLogLength );
			if (szBuffer != NULL)
			{
				glGetShaderInfoLog(gVertexShaderObject, glInfoLogLength, &written, szBuffer); //1.47
				fprintf(gpFile, "shader compilation log %s \n", szBuffer);
				free(szBuffer);
				//XDestroyWindow(gpDisplay,gWindow);
			}
		}
	}


	//**FRAGMENT SHADER**
	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentShaderSourceCode = 


		"#version 440 core" \
		"\n" \
		"in vec4 color;" \
		"out vec4 fragColor;" \
		"void main(void)" \
		"{" \
		"color = fragColor;" \
		"}";



	glShaderSource(gFragmentShaderObject, 1, (const GLchar**)&fragmentShaderSourceCode,NULL);
	//compile shader
	glCompileShader(gFragmentShaderObject);


	glInfoLogLength = 0;
	szBuffer = NULL;
	shaderCompiledStatus = 0;
	written = 0;


	glGetShaderiv(gFragmentShaderObject, GL_COMPILE_STATUS, &shaderCompiledStatus);
	if (shaderCompiledStatus == GL_FALSE)
	{
		glGetShaderiv(gFragmentShaderObject, GL_INFO_LOG_LENGTH, &glInfoLogLength);
		if (glInfoLogLength > 0)
		{
			szBuffer = (GLchar*)malloc(glInfoLogLength);
			if (szBuffer != NULL)
			{
				glGetShaderInfoLog(gFragmentShaderObject, glInfoLogLength, &written, szBuffer); //1.47
				fprintf(gpFile, "fragment shader compilation log %s \n", szBuffer);
				free(szBuffer);
				//XDestroyWindow(gpDisplay, gWindow);

			}
		}

	}




	//**SHADER PROGRAM**
	//Create 
	gShaderProgramObject = glCreateProgram();

	glAttachShader(gShaderProgramObject, gVertexShaderObject);
	glAttachShader(gShaderProgramObject, gFragmentShaderObject);

	glBindAttribLocation(gShaderProgramObject, tvn_attribute_position, "vPosition");// dont do mistake
	glBindAttribLocation(gShaderProgramObject, tvn_attribute_normal, "vNormal");// dont do mistake

	glLinkProgram(gShaderProgramObject);	

	glInfoLogLength = 0;
	szBuffer = NULL;
	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &shaderProgramLinkStatus);
	if (shaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &glInfoLogLength);
		if (glInfoLogLength > 0)
		{
			szBuffer = (GLchar*)malloc(sizeof(char) * glInfoLogLength + 1);
			if (szBuffer != NULL)
			{
				glGetProgramInfoLog(gShaderProgramObject, glInfoLogLength, &written, szBuffer); //1.47
				fprintf(gpFile, "gShaderrogramObject link log %s \n", szBuffer);
				free(szBuffer);
				//XDestroyWindow(gpDisplay, gWindow);
			}
		}

	}

	mvpMatrixUniform = glGetUniformLocation(gShaderProgramObject, "u_mvpMatrix");
	//modelViewMatrix = glGetUniformLocation(gShaderProgramObject, "model_view_matrix");
	//projectionMatrixUniform = glGetUniformLocation(gShaderProgramObject, "projection_matrix");
	//lkeyPressedUniform  = glGetUniformLocation(gShaderProgramObject, "u_lkeypressed");
//	kdUniform = glGetUniformLocation(gShaderProgramObject, "u_kd");
//	ldUniform = glGetUniformLocation(gShaderProgramObject, "u_ld");
//	lightPositionUniform = glGetUniformLocation(gShaderProgramObject, "u_light_position");
	
	getSphereVertexData(sphere_vertices, sphere_normals, sphere_textures, sphere_elements);
	gNumVertices = getNumberOfSphereVertices();
	gNumElements = getNumberOfSphereElements();


	//vao
	glGenVertexArrays(1, &vao_sphere);
	glBindVertexArray(vao_sphere);

	glGenBuffers(1, &vbo_sphere_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere_vertex);//whenever we want to give postion, color, texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_vertices), sphere_vertices, GL_STATIC_DRAW); //data badalnar nahi - GL_STATIC_DRAW
	glVertexAttribPointer(tvn_attribute_position, 3, GL_FLOAT, GL_FALSE/*dont normalize*/, 0, NULL);
	glEnableVertexAttribArray(tvn_attribute_position);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//0 - unbind where binded on 515

	//normals
	
	glGenBuffers(1, &vbo_sphere_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere_normal);//whenever we want to give postion, color, texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_normals), sphere_normals, GL_STATIC_DRAW); //data badalnar nahi - GL_STATIC_DRAW
	glVertexAttribPointer(tvn_attribute_normal, 3, GL_FLOAT, GL_FALSE/*dont normalize*/, 0, NULL);
	glEnableVertexAttribArray(tvn_attribute_normal);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//0 - unbind where binded on 515
	glBindVertexArray(0);


	//elements
	
	glGenBuffers(1, &vbo_sphere_element);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere_element);//whenever we want to give postion, color, texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_elements), sphere_elements, GL_STATIC_DRAW); //data badalnar nahi - GL_STATIC_DRAW
	glVertexAttribPointer(tvn_attribute_element, 3, GL_FLOAT, GL_FALSE/*dont normalize*/, 0, NULL);
	glEnableVertexAttribArray(tvn_attribute_element);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//0 - unbind where binded on 515
	glBindVertexArray(0);


	glBindVertexArray(0);



	///******Depth function*************//
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	/*********************************************/


	perspectiveProjectionMatrix = vmath::mat4::identity();
	bLight = false;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	resize(winWidth, winHeight);



}

void resize(int width, int height)
{
	if(height == 0 )
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	/***********************perspective change********************/

	perspectiveProjectionMatrix = vmath::perspective(45.0f,   ((GLfloat)width / (GLfloat)height), 0.1f, 100.0f);

	/***********************perspective change********************/

}



void Draw()
{

	void update();
	//Code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat lightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};

	mat4 modelviewmatrix;
	mat4 modelviewprojectionmatrix;
	mat4 rotationMatrix;
	mat4 rotationMatrix_X = mat4::identity();
	mat4 rotationMatrix_Y = mat4::identity();
	mat4 rotationMatrix_Z = mat4::identity();

	glUseProgram(gShaderProgramObject); //whatever i have compiled and linked, use it

	modelviewmatrix = mat4::identity();
	modelviewprojectionmatrix = mat4::identity();
	

	mat4 translateMatrix = mat4::identity();
	translateMatrix = mat4::identity();

	translateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);

	modelviewmatrix = translateMatrix;

	modelviewprojectionmatrix = perspectiveProjectionMatrix * modelviewmatrix; //do only in shader
	
	glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, modelviewprojectionmatrix);




	glBindVertexArray(vao_sphere);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_sphere_element);
	glDrawElements(GL_TRIANGLES, gNumElements, GL_UNSIGNED_SHORT, 0);

	//quad two triangles
	glBindVertexArray(0);

	update();
	glUseProgram(0); //	stop using it now

	glXSwapBuffers(gpDisplay, gWindow);

}


void update()
{

	sangle = sangle + 0.7f;
	if(sangle > 360)
		sangle = 0.0f;

}

void unintialize(void)
{

	GLXContext currentGLXContext ;

	currentGLXContext = glXGetCurrentContext();

	if(currentGLXContext == gGLXContext)
	{
		glXMakeCurrent(gpDisplay, 0, 0);
	}

//destroy

	if(gWindow)
	{
		XDestroyWindow(gpDisplay, gWindow);
	}

	if(gColorMap)
	{
		XFreeColormap(gpDisplay, gColorMap);
	}

	if(gpXVisualInfo)
	{
		free(gpXVisualInfo);
		gpXVisualInfo = NULL;

	}


	if(gpDisplay)
	{
		XCloseDisplay(gpDisplay);
		gpDisplay = NULL;

	}



}



