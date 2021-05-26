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
#include"Sphere.h"
#include"GRStack.h"

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


GLfloat grfangle;
typedef GLXContext(* glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int *);
glXCreateContextAttribsARBProc gglxCreateContextAttribsARB = NULL;
GLXFBConfig gglXFBConfig;

// project specific global variables declaration
GLuint grgVertexShaderObject;
GLuint grgFragmentShaderObject;
GLuint grgShaderProgramObject;

enum
{
	GR_ATTRIBUTE_POSITION = 0,
	GR_ATTRIBUTE_COLOR,
	GR_ATTRIBUTE_NORMAL,
	GR_ATTRIBUTE_TEXCOORD
};

GLuint grgVaoSphere;
GLuint grgVboSpherePosition;
GLuint grgVboSphereElements;
mat4 grgPerspectiveProjectionMatrix;

// uniforms
GLuint grgModelMatrixUniform;
GLuint grgViewMatrixUniform;
GLuint grgProjectionMatrixUniform;

bool grgbLight;
bool grgbAnimate;
GLfloat grgSphereVertices[1146];
GLfloat grgSphereNormals[1146];
GLfloat grgSphereTextures[764];
unsigned short grgSphereElements[2280];
GLint grgNumVertices;
GLint grgNumElements;

int grgShoulder = 0;
int grgElbow = 0;
static bool flag = false;
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

						case XK_s :
							if(flag == false)
								grgShoulder = (grgShoulder + 3) % 360;
							else
								grgShoulder = (grgShoulder - 3) % 360;
							break;


						case XK_e :
							if(flag == false)
								grgElbow = (grgElbow + 3) % 360;
							else
								grgElbow = (grgElbow - 3) % 360;
							break;

						case XK_g :
							flag = !flag;
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

	// get sphere data
	getSphereVertexData(grgSphereVertices, grgSphereNormals, grgSphereTextures, grgSphereElements);
	grgNumVertices = getNumberOfSphereVertices();
	grgNumElements = getNumberOfSphereElements();

	/********* Shader Code *********/

	// create shader
	grgVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	///// Vertex Shader
	const GLchar* grvertexShaderSourceCode =		
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vColor;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"out vec3 out_color;" \
		"void main(void)" \
		"{" \
		"out_color = vColor;" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
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
			}
		}
		Uninitialize();
	}

	////// Fragment Shader
	grgFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// source code of shader
	const GLchar* grfragmentShaderSourceCode =
		"#version 450 core" \
		"\n" \
		"in vec3 out_color;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = vec4(out_color, 1.0);" \
		"}";

	glShaderSource(grgFragmentShaderObject, 1, (const GLchar **) &grfragmentShaderSourceCode, NULL);

	// compile shader
	glCompileShader(grgFragmentShaderObject);
	// error check for compiation
	glGetShaderiv(grgFragmentShaderObject, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgFragmentShaderObject, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgFragmentShaderObject, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Fragment Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	//****** Shader Program *****//
	// create
	grgShaderProgramObject = glCreateProgram();

	// attach vertex shader to shader program
	glAttachShader(grgShaderProgramObject, grgVertexShaderObject);

	// attach fragment shader to shader program
	glAttachShader(grgShaderProgramObject, grgFragmentShaderObject);

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
			}
		}
		Uninitialize();
	}

	grgModelMatrixUniform = glGetUniformLocation(grgShaderProgramObject, "u_model_matrix");
	grgViewMatrixUniform = glGetUniformLocation(grgShaderProgramObject, "u_view_matrix");
	grgProjectionMatrixUniform = glGetUniformLocation(grgShaderProgramObject, "u_projection_matrix");	
	

	/*
	GLuint grgVaoSphere;
GLuint grgVboSpherePosition;
GLuint grgVboSphereElements;
	*/
	//***** Vao and Vbo *****/
	glGenVertexArrays(1, &grgVaoSphere);
	glBindVertexArray(grgVaoSphere);

	// position
	glGenBuffers(1, &grgVboSpherePosition);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grgSphereVertices), grgSphereVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.5f, 0.35f, 0.05f);

	// elements
	glGenBuffers(1, &grgVboSphereElements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grgSphereElements), grgSphereElements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	////////// Depth
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

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
	mat4 grmodelMatrix = mat4::identity();
	mat4 grviewMatrix = mat4::identity();
	mat4 grprojectionMatrix = mat4::identity();
	mat4 grtranslateMatrix = mat4::identity();
	mat4 grscaleMatrix = mat4::identity();
	mat4 grrotateMatrix = mat4::identity();

	// code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// start use of shader program
	glUseProgram(grgShaderProgramObject);	

	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -12.0f);
	grmodelMatrix = grtranslateMatrix;
	grprojectionMatrix = grgPerspectiveProjectionMatrix;

	//*** Arm ***

	// push matrix for whole geometry
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -12.0f);
	grrotateMatrix = vmath::rotate((GLfloat)grgShoulder, 0.0f, 0.0f, 1.0f);

	grmodelMatrix = grtranslateMatrix * grrotateMatrix;
	grprojectionMatrix = grgPerspectiveProjectionMatrix;

	PushToStack(grmodelMatrix);

	// shoulder
	grmodelMatrix = mat4::identity();
	grviewMatrix = mat4::identity();
	grprojectionMatrix = mat4::identity();
	grrotateMatrix = mat4::identity();
	grtranslateMatrix = mat4::identity();
	grscaleMatrix = mat4::identity();

	grtranslateMatrix = vmath::translate(1.0f, 0.0f, 0.0f);
	grmodelMatrix =  grtranslateMatrix;
	grprojectionMatrix = grgPerspectiveProjectionMatrix;

	grmodelMatrix = PushToStack(grmodelMatrix);
	PopFromStack();

	grscaleMatrix = vmath::scale(2.0f, 0.5f, 1.0f);
	grmodelMatrix = grmodelMatrix * grscaleMatrix;
	glUniformMatrix4fv(grgProjectionMatrixUniform, 1, GL_FALSE, grprojectionMatrix);
	glUniformMatrix4fv(grgViewMatrixUniform, 1, GL_FALSE, grviewMatrix);
	glUniformMatrix4fv(grgModelMatrixUniform, 1, GL_FALSE, grmodelMatrix);

	// bind vao of square
	glBindVertexArray(grgVaoSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElements);
	glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

	// unbind vao
	glBindVertexArray(0);

	
	// arm
	grmodelMatrix = mat4::identity();
	grviewMatrix = mat4::identity();
	grprojectionMatrix = mat4::identity();
	grrotateMatrix = mat4::identity();
	grtranslateMatrix = mat4::identity();
	grscaleMatrix = mat4::identity();


	grtranslateMatrix = vmath::translate(1.8f, 0.0f, 0.0f);
	grrotateMatrix = vmath::rotate((GLfloat)grgElbow, 0.0f, 0.0f, 1.0f);
	grmodelMatrix = grtranslateMatrix * grrotateMatrix;
	grtranslateMatrix = vmath::translate(1.0f, 0.0f, 0.0f);
	grmodelMatrix = grmodelMatrix * grtranslateMatrix;
	grprojectionMatrix = grgPerspectiveProjectionMatrix;

	grmodelMatrix = PushToStack(grmodelMatrix);
	PopFromStack();

	grscaleMatrix = vmath::scale(2.0f, 0.5f, 1.0f);
	grmodelMatrix = grmodelMatrix * grscaleMatrix;
	glUniformMatrix4fv(grgProjectionMatrixUniform, 1, GL_FALSE, grprojectionMatrix);
	glUniformMatrix4fv(grgViewMatrixUniform, 1, GL_FALSE, grviewMatrix);
	glUniformMatrix4fv(grgModelMatrixUniform, 1, GL_FALSE, grmodelMatrix);

	// bind vao of square
	glBindVertexArray(grgVaoSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElements);
	glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

	// unbind vao
	glBindVertexArray(0);
	

	PopFromStack();
	// stop use of shader program
	glUseProgram(0);
	glXSwapBuffers(gpDisplay, gWindow);

}


void Uninitialize()
{
	int i;

	if (grgVaoSphere)
	{
		glDeleteVertexArrays(1, &grgVaoSphere);
		grgVaoSphere = 0;
	}
	if (grgVboSpherePosition)
	{
		glDeleteBuffers(1, &grgVboSpherePosition);
		grgVboSpherePosition = 0;
	}
	
	if (grgVboSphereElements)
	{
		glDeleteBuffers(1, &grgVboSphereElements);
		grgVboSphereElements = 0;
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


/* compile and linking command //
g++ -o OGL2 OGL2.cpp -lGL -lX11 -lGLEW
*/







































