#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>
#include<GL/glew.h>
#include<GL/gl.h>		// for opengl api's 
#include<GL/glx.h>		// for glx apis
#include"vmath.h"


using namespace std;
using namespace vmath;

bool bFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColormap;
Window gWindow;

GLXContext gglxContext;						// similar to HGLRC of windows (handle to rc)

int giWindowWidth = 800;
int giWindowHeight = 600;
static XFontStruct *grpXFontStruct = NULL;
XGCValues grgcValues;						// similar to PAINTSTRUCT ps
XColor grgreenColor;
int grstringLength;
int grstringWidth;
int grfontHeight;


// project specific global variables declaration
GLfloat grfangle;
typedef GLXContext(* glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int *);
glXCreateContextAttribsARBProc gglxCreateContextAttribsARB = NULL;
GLXFBConfig gglXFBConfig;

GLuint grgVertexShaderObject;
GLuint grgFragmentShadeerObject;
GLuint grgShaderProgramObject;

enum
{
	GR_ATTRIBUTE_POSITION = 0,
	GR_ATTRIBUTE_COLOR,
	GR_ATTRIBUTE_TEXCOORD,
	GR_ATTRIBUTE_NORMAL
};

GLuint grgVao;
GLuint grgVbo_position;
GLuint grgMvpMatrixUniform;
mat4 grgPerspectiveProjectionMatrix;

GLfloat grVerticalLineVerts1[80];
GLfloat grVerticalLineVerts2[80];
GLfloat grVerticalCenterLineVerts[4] =
{
	0.0f, -2.0f,
	0.0f, 2.0f
};
GLfloat grHorizontalLineVerts1[80];
GLfloat grHorizontalLineVerts2[80];
GLfloat grHorizontalCenterLineVerts[4] =
{
	-3.0f, 0.0f,
	3.0f, 0.0f
};
GLuint grgVaoCircle;
GLuint grgVbo_position_circle;

int main()
{
	void CreateWindow();
	void ToggleFullscreen();
	void Uninitialize();
	void Initialize(void);
	void Resize(int, int);
	void Draw(void);

	int winWidth = giWindowWidth;
	int winHeight = giWindowHeight;
	bool bDone = false;
	
	CreateWindow();
	Initialize();
	
	XEvent event;
	KeySym keysym;
	
	while(bDone == false)
	{
		while(XPending(gpDisplay))
		{
			XNextEvent(gpDisplay, &event);
			switch(event.type)
			{
				case MapNotify:
					grpXFontStruct = XLoadQueryFont(gpDisplay, "Fixed");
					break;
				
				case KeyPress:
					keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
					switch(keysym)
					{
						case XK_Escape :
							XUnloadFont(gpDisplay, grpXFontStruct->fid);
							bDone = true;
							break;
						
						case XK_F :
						case XK_f :
							if(bFullscreen == false)
							{
								ToggleFullscreen();
								bFullscreen = true;
							}
							else
							{
								ToggleFullscreen();
								bFullscreen = false;
								
							}
							break;

						
						default :
							break;
					}
					break;
				
				case ButtonPress :
					switch(event.xbutton.button)
					{
						case 1:
							break;
						case 2 :
							break;
						case 3 :
							break;
						default :
							break;
					}
					break;
				
				case MotionNotify:
					break;
				
				case ConfigureNotify:								// similar to WM_SIZE
					winWidth = event.xconfigure.width;
					winHeight = event.xconfigure.height;
					Resize(winWidth, winHeight);
					break;
				
				case Expose:										// similar to WM_PAINT
					break;
				
				case DestroyNotify:
					break;
				
				case 33:
					XUnloadFont(gpDisplay, grpXFontStruct->fid);
					bDone = true;

				default :
					break;
			}
		}
		Draw();
	}
	
	Uninitialize();
	return(0);
}


void CreateWindow()
{
	// function declaration
	void Uninitialize();
	
	XSetWindowAttributes winAttribs;
	int defaultScreen;
	int defaultDepth;
	int styleMask;
	static int framebufferAttributes[] = 				// similar to PixelFormatAttributes of windows (static declaration is conventional not compulsary)
	{
		GLX_X_RENDERABLE, True,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, 24,								// v4l recommentds bitsize of depth to be ketp around 24 or below (v4l = video for linux)
		GLX_STENCIL_SIZE, 8,
		GLX_DOUBLEBUFFER, True,
		None												// to indicate unix systems to set next attributes to default, insert 0 / None at end 
	};
	GLXFBConfig *pGLXFBConfig = NULL;
	GLXFBConfig bestGLXFBConfig;
	XVisualInfo *pTempXVisualInfo = NULL;
	int numFBConfigs = 0;
	int i;

	// code
	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL)
	{
		printf("\n Unable to open XDisplay.. Exiting now...");
		Uninitialize();
		exit(1);
	}
	
	defaultScreen = XDefaultScreen(gpDisplay);

	pGLXFBConfig = glXChooseFBConfig(gpDisplay, defaultScreen, framebufferAttributes, &numFBConfigs);
	printf("\n Total Framebuffer Configs : %d", numFBConfigs);

	int bestFramebufferConfig = -1;
	int worstFramebufferConfig = -1;
	int bestNumberOfSamples = -1;
	int worstNumberOfSamples = 999;

	for(i = 0; i < numFBConfigs; i++)
	{
		pTempXVisualInfo = glXGetVisualFromFBConfig(gpDisplay, pGLXFBConfig[i]);
		if(pTempXVisualInfo != NULL)
		{
			int sampleBuffers, samples;
			glXGetFBConfigAttrib(gpDisplay, pGLXFBConfig[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
			glXGetFBConfigAttrib(gpDisplay, pGLXFBConfig[i], GLX_SAMPLES, &samples);

			if(bestFramebufferConfig < 0 || sampleBuffers && samples > bestNumberOfSamples)
			{
				bestFramebufferConfig = i;
				bestNumberOfSamples = samples;
			}
			if(worstFramebufferConfig < 0 || !sampleBuffers || samples < worstNumberOfSamples)
			{
				worstFramebufferConfig = i;
				worstNumberOfSamples = samples;
			}
			printf("\n When i : %d, sampleBuffers : %d, samples : %d", i, sampleBuffers, samples);
		}
		XFree(pTempXVisualInfo);

	}

	bestGLXFBConfig = pGLXFBConfig[bestFramebufferConfig];
	gglXFBConfig = bestGLXFBConfig;
	XFree(pGLXFBConfig);

	gpXVisualInfo = glXGetVisualFromFBConfig(gpDisplay, bestGLXFBConfig);

	if(gpXVisualInfo == NULL)
	{
		printf("\n Unable to allocate mamory for visual info.. Exiting now..");
		Uninitialize();
		exit(1);
	}
	
	XMatchVisualInfo(gpDisplay, defaultScreen, defaultDepth, TrueColor, gpXVisualInfo);
	
	if(gpXVisualInfo == NULL)
	{
		printf("\n Unable to get a visual.. Exiting now..");
		Uninitialize();
		exit(1);
	}
	
	
	winAttribs.border_pixel = 0;
	winAttribs.background_pixmap = 0;
	winAttribs.colormap = XCreateColormap(gpDisplay, 
					RootWindow(gpDisplay, gpXVisualInfo->screen),
					gpXVisualInfo->visual,
					AllocNone);
	gColormap = winAttribs.colormap;
	winAttribs.background_pixel = BlackPixel(gpDisplay, defaultScreen);
	
	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | ButtonPressMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;
	
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
		printf("\n Error : Failed to create Main Window. Exiting Now ...");
		Uninitialize();
		exit(1);	
	}
	
	XStoreName(gpDisplay, gWindow, "OGL Blue Window");

	Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(gpDisplay, gWindow, &windowManagerDelete, 1);
	XMapWindow(gpDisplay, gWindow);
	
}


void ToggleFullscreen()
{
	Atom wm_state;
	Atom fullscreen;
	XEvent xev = {0};
	
	wm_state = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
	memset(&xev, 0, sizeof(xev));
	
	xev.type = ClientMessage;
	xev.xclient.window = gWindow;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = bFullscreen ? 0 : 1;
	
	fullscreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);
	xev.xclient.data.l[1] = fullscreen;
	
	XSendEvent(gpDisplay, 
			RootWindow(gpDisplay, gpXVisualInfo->screen),
			False,
			StructureNotifyMask,
			&xev);
}

void Initialize()
{
	// function declaration
	void Resize(int, int);
	void Uninitialize();

	gglxCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB((GLubyte *) "glXCreateContextAttribsARB");

	const int attribs[] = 
	{
		GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
		GLX_CONTEXT_MINOR_VERSION_ARB, 5,
		GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		None
	};

	gglxContext = gglxCreateContextAttribsARB(gpDisplay, gglXFBConfig, 0, True, attribs);
	if(!gglxContext)
	{
		int attribsLow[] = 
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB, 1,
			GLX_CONTEXT_MINOR_VERSION_ARB, 0,
			None
		};
		gglxContext = gglxCreateContextAttribsARB(gpDisplay, gglXFBConfig, 0, True, attribs);
		printf("\n Context for version 4.5 not found");
	}

	Bool bIsDirectContext = glXIsDirect(gpDisplay, gglxContext);
	if(bIsDirectContext == true)
	{
		printf("\n Context is direct hardware rendering context");
	}
	else
	{
		printf("\n Context is software rendering context");
	}

	glXMakeCurrent(gpDisplay, gWindow, gglxContext);		// similar to wglMakeColor()

	GLenum grglew_error = glewInit();
	if (grglew_error != GLEW_OK)
	{ 
		Uninitialize();
	}

/********* Shader Code *********/

	// create shader
	grgVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	///// Vertex Shader
	const GLchar* grvertexShaderSourceCode =					// also called as "pass-through shader" as it does not have any code (main is empty, no code is there in main)
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec4 vColor;" \
		"out vec4 out_color;" \
		"uniform mat4 u_mvpMatrix;" \
		"void main(void)" \
		"{" \
		"out_color = vColor;" \
		"gl_Position = u_mvpMatrix * vPosition;" \
		"}";
	
	glShaderSource(grgVertexShaderObject, 1, (const GLchar **) &grvertexShaderSourceCode, NULL);

	// compile shader
	glCompileShader(grgVertexShaderObject);
	// error check for compilation
	GLint griInfoLength = 0;
	GLint griShaderCompileStatus = 0;
	char* grszInfoLog = NULL;

	glGetShaderiv(grgVertexShaderObject, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgVertexShaderObject, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgVertexShaderObject, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Vertex Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
				Uninitialize();
			}
		}
	}

	////// Fragment Shader
	grgFragmentShadeerObject = glCreateShader(GL_FRAGMENT_SHADER);

	// source code of shader
	const GLchar* grfragmentShaderSourceCode =
		"#version 450 core" \
		"\n" \
		"in vec4 out_color;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = out_color;" \
		"}";

	glShaderSource(grgFragmentShadeerObject, 1, (const GLchar **) &grfragmentShaderSourceCode, NULL);

	// compile shader
	glCompileShader(grgFragmentShadeerObject);
	// error check for compiation
	glGetShaderiv(grgFragmentShadeerObject, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgFragmentShadeerObject, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgFragmentShadeerObject, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Fragment Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
				Uninitialize();
			}
		}
	}

	//****** Shader Program *****//
	// create
	grgShaderProgramObject = glCreateProgram();

	// attach vertex shader to shader program
	glAttachShader(grgShaderProgramObject, grgVertexShaderObject);

	// attach fragment shader to shader program
	glAttachShader(grgShaderProgramObject, grgFragmentShadeerObject);

	// pre-link our attribute enum with shader's attributes
	glBindAttribLocation(grgShaderProgramObject, GR_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(grgShaderProgramObject, GR_ATTRIBUTE_COLOR, "vColor");
	// link shader
	glLinkProgram(grgShaderProgramObject);
	// error check for linking
	GLint griShaderProgramLinkStatus = 0;
	glGetProgramiv(grgShaderProgramObject, GL_LINK_STATUS, &griShaderProgramLinkStatus);
	if (griShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(grgShaderProgramObject, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(griInfoLength) * sizeof(char));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetProgramInfoLog(grgShaderProgramObject, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Shader Program Link Log : %s", grszInfoLog);
				Uninitialize();
			}
		}
	}

	grgMvpMatrixUniform = glGetUniformLocation(grgShaderProgramObject, "u_mvpMatrix");
	
	GLfloat i;
	GLint index = 0;

	i = 0.11f;
	for (index = 0; index < 80; index = index + 4)
	{
		grVerticalLineVerts1[index] = i;
		grVerticalLineVerts1[index + 1] = -2.0f;
		grVerticalLineVerts1[index + 2] = i;
		grVerticalLineVerts1[index + 3] = 2.0f;
		i = i + 0.11f;
		
	}

	i = 0.11f;
	for (index = 0; index < 80; index = index + 4)
	{
		grVerticalLineVerts2[index] = -i;
		grVerticalLineVerts2[index + 1] = -2.0f;
		grVerticalLineVerts2[index + 2] = -i;
		grVerticalLineVerts2[index + 3] = 2.0f;
		i = i + 0.11f;

	}

	// horizontal lines
	i = 0.060f;
	for (index = 0; index < 80; index = index + 4)
	{
		grHorizontalLineVerts1[index] = -3.0f;
		grHorizontalLineVerts1[index + 1] = i;
		grHorizontalLineVerts1[index + 2] = 3.0f;
		grHorizontalLineVerts1[index + 3] = i;
		i = i + 0.060f;
	}
	i = 0.060f;
	for (index = 0; index < 80; index = index + 4)
	{
		grHorizontalLineVerts2[index] = -3.0f;
		grHorizontalLineVerts2[index + 1] = -i;
		grHorizontalLineVerts2[index + 2] = 3.0f;
		grHorizontalLineVerts2[index + 3] = -i;
		i = i + 0.060f;
	}

	GLfloat grcircleVerts[1258];
	index = 0;
	for (i = 0.0f; i < 3.142f * 2.0f; i = i + 0.01f)
	{
		grcircleVerts[index] = cos(i);
		grcircleVerts[index + 1] = sin(i);
		index = index + 2;
	}

	glGenVertexArrays(1, &grgVao);
	glBindVertexArray(grgVao);

	glGenBuffers(1, &grgVbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position);
	glBufferData(GL_ARRAY_BUFFER, 40 * 2 * sizeof(int), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 1.0f, 0.0f, 0.0f);

	glBindVertexArray(0);

	// Square Vao and Vbo
	glGenVertexArrays(1, &grgVaoCircle);
	glBindVertexArray(grgVaoCircle);

	glGenBuffers(1, &grgVbo_position_circle);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position_circle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grcircleVerts), grcircleVerts, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 1.0f, 1.0f, 0.0f);

	glBindVertexArray(0);

	// Depth
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	grgPerspectiveProjectionMatrix = mat4::identity();	
	// warm - up call to resize
	Resize(giWindowWidth, giWindowHeight);

}

void Resize(int width, int height)
{
	if(height ==0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	grgPerspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
}

void Draw(void)
{
	// variable declaration
	mat4 grmodelViewMatrix = mat4::identity();
	mat4 grmodelViewProjectionMatrix = mat4::identity();
	mat4 grtranslateMatrix = mat4::identity();

	// code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// start use of shader program
	glUseProgram(grgShaderProgramObject);

	//***************************************** VERTICAL LINES ******************************************
	//****************** Vertical Line - bottom ****************
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	grmodelViewMatrix = grtranslateMatrix;

	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	
	// bind vao
	glBindVertexArray(grgVao);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grVerticalLineVerts1), grVerticalLineVerts1, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_LINES, 0, 40);

	// unbind vao
	glBindVertexArray(0);

	//*************************** Vertical Line - center *****************
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	grmodelViewMatrix = grtranslateMatrix;

	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	// bind vao
	glBindVertexArray(grgVao);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grVerticalCenterLineVerts), grVerticalCenterLineVerts, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_LINES, 0, 2);

	// unbind vao
	glBindVertexArray(0);

	//********************* Vertical Line - top ********************
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	grmodelViewMatrix = grtranslateMatrix;

	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	// bind vao
	glBindVertexArray(grgVao);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grVerticalLineVerts2), grVerticalLineVerts2, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_LINES, 0, 40);

	// unbind vao
	glBindVertexArray(0);

	//***************************************************** HORIZONTAL LINES **********************************************************
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	grmodelViewMatrix = grtranslateMatrix;

	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	
	// bind vao
	glBindVertexArray(grgVao);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grHorizontalLineVerts1), grHorizontalLineVerts1, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_LINES, 0, 40);

	// unbind vao
	glBindVertexArray(0);

	//*************************** Vertical Line - center *****************
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	grmodelViewMatrix = grtranslateMatrix;

	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	// bind vao
	glBindVertexArray(grgVao);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grHorizontalCenterLineVerts), grHorizontalCenterLineVerts, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_LINES, 0, 2);

	// unbind vao
	glBindVertexArray(0);

	//********************* Vertical Line - top ********************
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	grmodelViewMatrix = grtranslateMatrix;

	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	// bind vao
	glBindVertexArray(grgVao);
	glBindBuffer(GL_ARRAY_BUFFER, grgVbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grHorizontalLineVerts2), grHorizontalLineVerts2, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_LINES, 0, 40);

	// unbind vao
	glBindVertexArray(0);

	//************************************************ TRIANGLE ***********************************************************
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -3.0f);
	grmodelViewMatrix = grtranslateMatrix;

	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	// bind vao
	glBindVertexArray(grgVaoCircle);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 1.0f, 1.0f, 0.0f);
	glDrawArrays(GL_LINE_LOOP, 0, 629);
	// unbind vao
	glBindVertexArray(0);


	// stop use of shader program
	glUseProgram(0);
	glXSwapBuffers(gpDisplay, gWindow);

}


void Uninitialize()
{
	int i;

	if (grgVao)
	{
		glDeleteVertexArrays(1, &grgVao);
		grgVao = 0;
	}

	if (grgVbo_position)
	{
		glDeleteBuffers(1, &grgVbo_position);
		grgVbo_position = 0;
	}
	
	// free shaders (safe release)
	if(grgShaderProgramObject)
	{
		glUseProgram(grgShaderProgramObject);
		GLsizei grshaderCount;
		glGetProgramiv(grgShaderProgramObject, GL_ATTACHED_SHADERS, &grshaderCount);
		GLuint *grpShaders = NULL;
		grpShaders = NULL;
		grpShaders = (GLuint *)malloc(sizeof(GLuint) * grshaderCount);
		glGetAttachedShaders(grgShaderProgramObject, grshaderCount, &grshaderCount, grpShaders);
		for(i = 0; i < grshaderCount; i++)
		{
			glDetachShader(grgShaderProgramObject, grpShaders[i]);
			glDeleteShader(grpShaders[i]);
			grpShaders[i] = 0;
		}
		// unlink shader program
		glUseProgram(0);
	}


	GLXContext currentGLXContext = glXGetCurrentContext();			// in unix we can have multiple monitors, multiple screens hence check if we are uninitializing current context only
	if(currentGLXContext == gglxContext)
	{
		glXMakeCurrent(gpDisplay, 0, 0);
		if(gglxContext)
		{
			glXDestroyContext(gpDisplay, gglxContext);
		}

	}



	if(gWindow)
	{
		XDestroyWindow(gpDisplay, gWindow);
	}
	
	if(gColormap)
	{
		XFreeColormap(gpDisplay, gColormap);	
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

/* Compile command 
g++ -o OGL2 OGL2.cpp -lX11 -lGL -lGLEW
*/









































