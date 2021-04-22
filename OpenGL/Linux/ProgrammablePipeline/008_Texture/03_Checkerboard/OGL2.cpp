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
#include<SOIL/SOIL.h>
#include"vmath.h"


using namespace std;
using namespace vmath;

// project specific
#define CHECK_IMAGE_WIDTH 64
#define CHECK_IMAGE_HEIGHT 64

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
	GR_ATTRIBUTE_TEXCOORD,
	GR_ATTRIBUTE_NORMAL
};

GLuint grgVaoSquare;
GLuint grgVboPositionSquare;
GLuint grgVboTextureSquare;
GLuint grgMvpMatrixUniform;
mat4 grgPerspectiveProjectionMatrix;
GLuint grgTextureSamplerUniform;

// texture variables
GLuint grgTextureCheckerboard;
GLubyte checkImage[CHECK_IMAGE_HEIGHT][CHECK_IMAGE_WIDTH][4];
GLfloat grSquarePositionOne[12];
GLfloat grSquarePositionTwo[12];
GLfloat grsquareOneVertices[12];
GLfloat grsquareTwoVertices[12];

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
	//defaultDepth =DefaultDepth(gpDisplay, defaultScreen);		// we will not be using defaultdepth of xVisual


	//gpXVisualInfo = (XVisualInfo *) malloc(sizeof(XVisualInfo));		// we will get visualInfo using opengl bridging api

	//gpXVisualInfo = glXChooseVisual(gpDisplay, defaultScreen, framebufferAttributes);	//opengl bridging api similar to wgl* from windows

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
	void LoadBitmapAsTexture(void);

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
	const GLchar* grvertexShaderSourceCode =		
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec2 vTexCoord;" \
		"out vec2 out_texcoord;" \
		"uniform mat4 u_mvpMatrix;" \
		"void main(void)" \
		"{" \
		"gl_Position = u_mvpMatrix * vPosition;" \
		"out_texcoord = vTexCoord;" \
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
		"in vec2 out_texcoord;" \
		"uniform sampler2D u_texture_sampler;"
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = texture(u_texture_sampler, out_texcoord);" \
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
	glBindAttribLocation(grgShaderProgramObject, GR_ATTRIBUTE_TEXCOORD, "vTexCoord");

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

	grgMvpMatrixUniform = glGetUniformLocation(grgShaderProgramObject, "u_mvpMatrix");
	grgTextureSamplerUniform = glGetUniformLocation(grgShaderProgramObject, "u_texture_sampler");

	GLfloat grsquareTexture[] = 
	{
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};
	

	// **** square ***** /
	// position
	glGenVertexArrays(1, &grgVaoSquare);
	glBindVertexArray(grgVaoSquare);

	glGenBuffers(1, &grgVboPositionSquare);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboPositionSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	// texture
	glGenBuffers(1, &grgVboTextureSquare);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboTextureSquare);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsquareTexture), grsquareTexture, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);				// 2nd param is 2 because 2D texture has two parameters (S and T)
	glEnableVertexAttribArray(GR_ATTRIBUTE_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
/*
	glGenBuffers(1, &grgVboTextureSquare);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboTextureSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
*/
	glBindVertexArray(0);

	LoadBitmapAsTexture();

	////////// Depth
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


void LoadBitmapAsTexture()
{
	// function declaration
	void MakeCheckImage(void);

	MakeCheckImage();

	// OGL specific code
	glGenTextures(1, &grgTextureCheckerboard);
	glBindTexture(GL_TEXTURE_2D, grgTextureCheckerboard);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECK_IMAGE_WIDTH, CHECK_IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

}

void MakeCheckImage(void)
{
	
	int i, j, c;
	for(i = 0; i < CHECK_IMAGE_HEIGHT; i++)
	{
		for(j = 0; j < CHECK_IMAGE_WIDTH; j++)
		{
			c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = 255;
		}
	}
	
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

	// code
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// start use of shader program
	glUseProgram(grgShaderProgramObject);

	// OpenGL drawing code will start here
	mat4 grmodelViewMatrix = mat4::identity();
	mat4 grmodelViewProjectionMatrix = mat4::identity();
	mat4 grtranslateMatrix = mat4::identity();

	//////////////////////// square 

	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	grmodelViewMatrix = grtranslateMatrix;
	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grgTextureCheckerboard);
	glUniform1i(grgTextureSamplerUniform, 0);

	// bind vao of square
	glBindVertexArray(grgVaoSquare);
	
	
	grSquarePositionOne[0] = 0.0f;
	grSquarePositionOne[1] = 1.0;
	grSquarePositionOne[2] = 0.0;
	grSquarePositionOne[3] = -2.0;
	grSquarePositionOne[4] = 1.0;
	grSquarePositionOne[5] = 0.0;
	grSquarePositionOne[6] = -2.0;
	grSquarePositionOne[7] = -1.0;
	grSquarePositionOne[8] = 0.0;
	grSquarePositionOne[9] = 0.0;
	grSquarePositionOne[10] = -1.0;
	grSquarePositionOne[11] = 0.0;

	glBindBuffer(GL_ARRAY_BUFFER, grgVboPositionSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), grSquarePositionOne, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);			
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);												// In Programmable pipeline, there's no GL_QUADS, hence we have used GL_TRIANGLE_FAN
	

	////////////////////2nd Square 
	grSquarePositionTwo[0] = 2.41421;
	grSquarePositionTwo[1] = 1.0;
	grSquarePositionTwo[2] = -1.41421;
	grSquarePositionTwo[3] = 1.0;
	grSquarePositionTwo[4] = 1.0;
	grSquarePositionTwo[5] = 0.0;
	grSquarePositionTwo[6] = 1.0;
	grSquarePositionTwo[7] = -1.0;
	grSquarePositionTwo[8] = 0.0;
	grSquarePositionTwo[9] = 2.41421;
	grSquarePositionTwo[10] = -1.0;
	grSquarePositionTwo[11] = -1.41421;

	glBindBuffer(GL_ARRAY_BUFFER, grgVboPositionSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), grSquarePositionTwo, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);			
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	
	glBindVertexArray(0);
	
	// stop use of shader program
	glUseProgram(0);
	glXSwapBuffers(gpDisplay, gWindow);

}


/*
void Draw(void)
{
	// variable declaration
	GLfloat grtexCoord[8];


	// code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// start use of shader program
	glUseProgram(grgShaderProgramObject);

	// OpenGL drawing code will start here
	mat4 grmodelViewMatrix = mat4::identity();
	mat4 grmodelViewProjectionMatrix = mat4::identity();
	mat4 grtranslateMatrix = mat4::identity();
	mat4 grscaleMatrix = mat4::identity();

	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	grscaleMatrix = vmath::scale(0.75f, 0.75f, 0.75f);


	grmodelViewMatrix = grtranslateMatrix * grscaleMatrix;
	grmodelViewProjectionMatrix = grgPerspectiveProjectionMatrix * grmodelViewMatrix;

	glUniformMatrix4fv(grgMvpMatrixUniform, 1, GL_FALSE, grmodelViewProjectionMatrix);

	// apply texture to cube
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grgTextureCheckerboard);
	glUniform1i(grgTextureSamplerUniform, 0);

	// bind vao of square
	glBindVertexArray(grgVaoSquare);

	grsquareOneVertices[0] = 0.0f;
	grsquareOneVertices[1] = 1.0;
	grsquareOneVertices[2] = 0.0;
	grsquareOneVertices[3] = -2.0;
	grsquareOneVertices[4] = 1.0;
	grsquareOneVertices[5] = 0.0;
	grsquareOneVertices[6] = -2.0;
	grsquareOneVertices[7] = -1.0;
	grsquareOneVertices[8] = 0.0;
	grsquareOneVertices[9] = 0.0;
	grsquareOneVertices[10] = -1.0;
	grsquareOneVertices[11] = 0.0;

	grtexCoord[0] = 1;
	grtexCoord[1] = 1;
	grtexCoord[2] = 0;
	grtexCoord[3] = 1;
	grtexCoord[4] = 0;
	grtexCoord[5] = 0;
	grtexCoord[6] = 1;
	grtexCoord[7] = 0;

	
	glBindBuffer(GL_ARRAY_BUFFER, grgVboPositionSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GL_FLOAT), grsquareOneVertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, grgVboTextureSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GL_FLOAT), grtexCoord, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);												// In Programmable pipeline, there's no GL_QUADS, hence we have used GL_TRIANGLE_FAN

	////////////// 2nd square
	grsquareTwoVertices[0] = 2.41421;
	grsquareTwoVertices[1] = 1.0;
	grsquareTwoVertices[2] = -1.41421;
	grsquareTwoVertices[3] = 1.0;
	grsquareTwoVertices[4] = 1.0;
	grsquareTwoVertices[5] = 0.0;
	grsquareTwoVertices[6] = 1.0;
	grsquareTwoVertices[7] = -1.0;
	grsquareTwoVertices[8] = 0.0;
	grsquareTwoVertices[9] = 2.41421;
	grsquareTwoVertices[10] = -1.0;
	grsquareTwoVertices[11] = -1.41421;

	grtexCoord[0] = 1;
	grtexCoord[1] = 1;
	grtexCoord[2] = 0;
	grtexCoord[3] = 1;
	grtexCoord[4] = 0;
	grtexCoord[5] = 0;
	grtexCoord[6] = 1;
	grtexCoord[7] = 0;

	glBindBuffer(GL_ARRAY_BUFFER, grgVboPositionSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GL_FLOAT), grsquareTwoVertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, grgVboTextureSquare);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GL_FLOAT), grtexCoord, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_TEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// unbind vao
	glBindVertexArray(0);

	// stop use of shader program
	glUseProgram(0);

	glXSwapBuffers(gpDisplay, gWindow);
}
*/

void Uninitialize()
{
	int i;

	// free texture memory
	if(grgTextureCheckerboard)
	{
		glDeleteTextures(1, &grgTextureCheckerboard);
		grgTextureCheckerboard = 0;
	}

	if (grgVboPositionSquare)
	{
		glDeleteBuffers(1, &grgVboPositionSquare);
		grgVboPositionSquare = 0;
	}
	if (grgVboTextureSquare)
	{
		glDeleteBuffers(1, &grgVboTextureSquare);
		grgVboTextureSquare = 0;
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
g++ -o OGL2 OGL2.cpp -lGL -lX11 -lGLEW -lSOIL
*/







































