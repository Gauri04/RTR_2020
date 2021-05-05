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

enum
{
	GR_ATTRIBUTE_POSITION = 0,
	GR_ATTRIBUTE_COLOR,
		GR_ATTRIBUTE_NORMAL,
	GR_ATTRIBUTE_TEXCOORD
};

// project specific global variables declaration
GLuint grgVaoSphere;
GLuint grgVboSpherePosition;
GLuint grgVboSphereNormal;
GLuint grgVboSphereElements;
mat4 grgPerspectiveProjectionMatrix;

// per vertex
// uniforms
GLuint grgModelMarixUniformPV;
GLuint grgViewMatrixUniformPV;
GLuint grgProjectionMatrixUniformPV;
GLuint grgLaUniformPV[3];				// light ambient
GLuint grgLdUniformPV[3];				// light diffuse
GLuint grgLsUniformPV[3];				// light specular
GLuint grgLightPositionUniformPV[3];
GLuint grgKdUniformPV;
GLuint grgKaUniformPV;
GLuint grgKsUniformPV;
GLuint grgMaterialShinynessUniformPV;
GLuint grgLKeyPressedUniformPV;

GLuint grgVertexShaderObjectPV;
GLuint grgFragmentShaderObjectPV;
GLuint grgShaderProgramObjectPV;


// per fragment
// uniforms
GLuint grgModelMatrixUniformPF;
GLuint grgViewMatrixUniformPF;
GLuint grgProjectionMatrixUniformPF;
GLuint grgLaUniformPF[3];
GLuint grgLdUniformPF[3];
GLuint grgLsUniformPF[3];
GLuint grgLightPositionUniformPF[3];
GLuint grgKdUniformPF;					// material diffuse
GLuint grgKaUniformPF;					// material ambient
GLuint grgKsUniformPF;					// material specular
GLuint grgMaterialShinynessUniformPF;
GLuint grgLKeyPressedUniformPF;

GLuint grgVertexShaderObjectPF;
GLuint grgFragmentShaderObjectPF;
GLuint grgShaderProgramObjectPF;

bool grgbLight;
GLfloat grgSphereVertices[1146];
GLfloat grgSphereNormals[1146];
GLfloat grgSphereTextures[764];
unsigned short grgSphereElements[2280];
GLint grgNumVertices;
GLint grgNumElements;

struct Light
{
	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;
	vec4 lightPosition;
};
struct Light grlight[3];

vec4 grgKa = { 0.0, 0.0, 0.0, 1.0 };	// material ambient
vec4 grgKd = { 1.0, 1.0, 1.0, 1.0 };	// material diffuse
vec4 grgKs = { 1.0, 1.0, 1.0, 1.0 };	// material specular
GLfloat grgMaterialShinyness = 128;

bool grgbPerFragmentLighting;
bool grgbPerVertexLighting;
bool grgbLKeyPressed = false;
bool grgbXKeyPressed;
bool grgbYKeyPressed;
bool grgbZKeyPressed;
GLfloat grflightAngleX;
GLfloat grflightAngleY;
GLfloat grflightAngleZ;
int i;

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
						case XK_Q :
						case XK_q :
							XUnloadFont(gpDisplay, grpXFontStruct->fid);
							bDone = true;
							break;

						case XK_Escape :
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
						
						case XK_F :
						case XK_f :
							grgbPerFragmentLighting = !grgbPerFragmentLighting;
							if(grgbPerFragmentLighting == true)
							{
								grgbPerVertexLighting = false;
							}
							break;

						case XK_V:
						case XK_v:
							grgbPerVertexLighting = !grgbPerVertexLighting;
							if(grgbPerVertexLighting == true)
							{
								grgbPerFragmentLighting = false;
							}
							break;

						case XK_L :
						case XK_l :
							grgbLight = !grgbLight; 
							break;
						
						case XK_x :
						case XK_X:
							grgbXKeyPressed = true;
							break;

						case XK_Y:
						case XK_y:
							grgbYKeyPressed = true;
							break;

						case XK_Z:
						case XK_z:
							grgbZKeyPressed = true;
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

	/********* Shader Code  - Per Vertex *********/

	grgVertexShaderObjectPV = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* grvertexShaderSourceCodePV =				
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_l_key_pressed;" \
		"uniform vec3 u_la[3];" \
		"uniform vec3 u_ld[3];" \
		"uniform vec3 u_ls[3];" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_material_shinyness;" \
		"uniform vec4 u_light_position[3];" \
		"out vec3 phong_ads_light;" \
		"int i;" \
		"void main(void)" \
		"{" \
		"if(u_l_key_pressed == 1)" \
		"{" \
			"vec4 eye_coordinates =  u_view_matrix * u_model_matrix * vPosition;" \
			"vec3 transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
			"vec3 view_vector = normalize(-eye_coordinates.xyz);" \
			"vec3 light_direction[3];" \
			"vec3 reflection_vector[3];" \
			"vec3 ambient[3];" \
			"vec3 diffuse[3];" \
			"vec3 specular[3];" \
			"for(i = 0; i < 3; i++)" \
			"{" \
				"light_direction[i] = normalize(vec3(u_light_position[i] - eye_coordinates));" \
				"reflection_vector[i] = reflect(-light_direction[i], transformed_normal);" \
				"ambient[i] = u_la[i] * u_ka;" \
				"diffuse[i] = u_ld[i] * u_kd * max(dot(light_direction[i], transformed_normal), 0.0);" \
				"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], view_vector), 0.0), u_material_shinyness);" \
				"phong_ads_light = phong_ads_light + ambient[i] + diffuse[i] + specular[i];" \
			"}" \
		"}" \
		"else" \
		"{" \
			"phong_ads_light = vec3(1.0, 1.0, 1.0);" \
		"}" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"}";
	
	glShaderSource(grgVertexShaderObjectPV, 1, (const GLchar**)&grvertexShaderSourceCodePV, NULL);

	// compile shader
	glCompileShader(grgVertexShaderObjectPV);
	// error check for compilation
	GLint griInfoLength = 0;
	GLint griShaderCompileStatus = 0;
	char* grszInfoLog = NULL;

	glGetShaderiv(grgVertexShaderObjectPV, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgVertexShaderObjectPV, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgVertexShaderObjectPV, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Vertex Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	////// Fragment Shader
	grgFragmentShaderObjectPV = glCreateShader(GL_FRAGMENT_SHADER);

	// source code of shader
	const GLchar* grfragmentShaderSourceCodePV =
		"#version 450 core" \
		"\n" \
		"in vec3 phong_ads_light;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = vec4(phong_ads_light, 1.0);" \
		"}";

	glShaderSource(grgFragmentShaderObjectPV, 1, (const GLchar **) &grfragmentShaderSourceCodePV, NULL);

	// compile shader
	glCompileShader(grgFragmentShaderObjectPV);
	// error check for compiation
	glGetShaderiv(grgFragmentShaderObjectPV, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgFragmentShaderObjectPV, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgFragmentShaderObjectPV, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Fragment Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	//****** Shader Program *****//
	// create
	grgShaderProgramObjectPV = glCreateProgram();

	// attach vertex shader to shader program
	glAttachShader(grgShaderProgramObjectPV, grgVertexShaderObjectPV);

	// attach fragment shader to shader program
	glAttachShader(grgShaderProgramObjectPV, grgFragmentShaderObjectPV);

	// pre-link our attribute enum with shader's attributes
	glBindAttribLocation(grgShaderProgramObjectPV, GR_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(grgShaderProgramObjectPV, GR_ATTRIBUTE_NORMAL, "vNormal");
	
	// link shader
	glLinkProgram(grgShaderProgramObjectPV);
	// error check for linking
	GLint griShaderProgramLinkStatus = 0;
	glGetProgramiv(grgShaderProgramObjectPV, GL_LINK_STATUS, &griShaderProgramLinkStatus);
	if (griShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(grgShaderProgramObjectPV, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(griInfoLength) * sizeof(char));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetProgramInfoLog(grgShaderProgramObjectPV, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Shader Program Link Log : %s", grszInfoLog);
			}
		}
		Uninitialize();
	}

	grgModelMarixUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_model_matrix");
	grgViewMatrixUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_view_matrix");
	grgProjectionMatrixUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_projection_matrix");

	grgLdUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ld[0]");
	grgLaUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_la[0]");
	grgLsUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ls[0]");
	grgLdUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ld[1]");
	grgLaUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_la[1]");
	grgLsUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ls[1]");
	grgLdUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ld[2]");
	grgLaUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_la[2]");
	grgLsUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ls[2]");
	grgLightPositionUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_light_position[0]");
	grgLightPositionUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_light_position[1]");
	grgLightPositionUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_light_position[2]");

	grgKaUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_ka");
	grgKdUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_kd");
	grgKsUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_ks");

	grgLKeyPressedUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_l_key_pressed");
	grgMaterialShinynessUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_material_shinyness");

	// initialize colors
	grlight[0].lightAmbientColor = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[0].lightDiffuseColor = vec4(1.0, 0.0, 0.0, 1.0);
	grlight[0].lightSpecularColor = vec4(1.0, 0.0, 0.0, 1.0);

	grlight[1].lightAmbientColor = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[1].lightDiffuseColor = vec4(0.0, 1.0, 0.0, 1.0);
	grlight[1].lightSpecularColor = vec4(0.0, 1.0, 0.0, 1.0);

	grlight[2].lightAmbientColor = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[2].lightDiffuseColor = vec4(0.0, 0.0, 1.0, 1.0);
	grlight[2].lightSpecularColor = vec4(0.0, 0.0, 1.0, 1.0);

	grlight[0].lightPosition = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[1].lightPosition = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[2].lightPosition = vec4(0.0, 0.0, 0.0, 1.0);

	/********** sHADER cODE FOR PER FRAGMENT ***********************/
	// create shader
	grgVertexShaderObjectPF = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* grvertexShaderSourceCodePF =
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_l_key_pressed;" \
		"uniform vec4 u_light_position[3];" \
		"out vec3 transformed_normal;" \
		"out vec3 light_direction[3];" \
		"out vec3 view_vector;" \
		"int i;" \
		"void main(void)" \
		"{" \
		"if(u_l_key_pressed == 1)" \
		"{" \
		"vec4 eye_coordinates = u_view_matrix * u_model_matrix * vPosition;" \
		"transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
		"view_vector = normalize(-eye_coordinates.xyz);" \
		"for(i = 0; i < 3; i++)" \
		"{" \
		"light_direction[i] = normalize(vec3(u_light_position[i] - eye_coordinates));" \
		"}" \
		"}" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"}";

	glShaderSource(grgVertexShaderObjectPF, 1, (const GLchar**)&grvertexShaderSourceCodePF, NULL);

	// compile shader
	glCompileShader(grgVertexShaderObjectPF);
	// error check for compilation
	griInfoLength = 0;
	griShaderCompileStatus = 0;
	grszInfoLog = NULL;

	glGetShaderiv(grgVertexShaderObjectPF, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgVertexShaderObjectPF, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgVertexShaderObjectPF, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Vertex Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	////// fragment shader 
	grgFragmentShaderObjectPF = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* grfragmentShaderSourceCodePF =
		"#version 450 core" \
		"\n" \
		"in vec3 transformed_normal;" \
		"in vec3 light_direction[3];" \
		"in vec3 view_vector;" \
		"uniform vec3 u_la[3];" \
		"uniform vec3 u_ld[3];" \
		"uniform vec3 u_ls[3];" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_material_shinyness;" \
		"uniform int u_l_key_pressed;" \
		"vec3 fong_ads_light;" \
		"out vec4 FragColor;" \
		"int i;" \
		"void main(void)" \
		"{" \
		"if(u_l_key_pressed == 1)" \
		"{" \
		"vec3 reflection_vector[3];" \
		"vec3 ambient[3];" \
		"vec3 diffuse[3];" \
		"vec3 specular[3];" \
		"for(i = 0; i < 3; i++)" \
		"{" \
		"reflection_vector[i] = reflect(-light_direction[i], transformed_normal);" \
		"ambient[i] = u_la[i] *u_ka;" \
		"diffuse[i] = u_ld[i] * u_kd * max(dot(light_direction[i], transformed_normal), 0.0);" \
		"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], view_vector), 0.0), u_material_shinyness);" \
		"fong_ads_light = fong_ads_light + ambient[i] + diffuse[i] + specular[i];" \
		"}" \
		"}" \
		"else" \
		"{" \
		"fong_ads_light = vec3(1.0, 1.0, 1.0);" \
		"}" \
		"FragColor = vec4(fong_ads_light, 1.0);" \
		"}";

	glShaderSource(grgFragmentShaderObjectPF, 1, (const GLchar**)&grfragmentShaderSourceCodePF, NULL);

	// compile shader
	glCompileShader(grgFragmentShaderObjectPF);

	// error check for compiation
	glGetShaderiv(grgFragmentShaderObjectPF, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgFragmentShaderObjectPF, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgFragmentShaderObjectPF, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Fragment Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	//****** Shader Program for Per fragment *****//
	// create
	grgShaderProgramObjectPF = glCreateProgram();

	// attach vertex shader to shader program
	glAttachShader(grgShaderProgramObjectPF, grgVertexShaderObjectPF);

	// attach fragment shader to shader program
	glAttachShader(grgShaderProgramObjectPF, grgFragmentShaderObjectPF);

	// pre-link our attribute enum with shader's attributes
	glBindAttribLocation(grgShaderProgramObjectPF, GR_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(grgShaderProgramObjectPF, GR_ATTRIBUTE_NORMAL, "vNormal");

	// link shader
	glLinkProgram(grgShaderProgramObjectPF);

	// error check for linking
	griShaderProgramLinkStatus = 0;
	glGetProgramiv(grgShaderProgramObjectPF, GL_LINK_STATUS, &griShaderProgramLinkStatus);
	if (griShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(grgShaderProgramObjectPF, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(griInfoLength) * sizeof(char));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetProgramInfoLog(grgShaderProgramObjectPF, griInfoLength, &grwritten, grszInfoLog);
				printf("\n Shader Program Link Log : %s", grszInfoLog);
			}
		}
		Uninitialize();
	}

	// uniforms for per fragment lighting
	grgModelMatrixUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_model_matrix");
	grgViewMatrixUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_view_matrix");
	grgProjectionMatrixUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_projection_matrix");

	grgLdUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ld[0]");
	grgLaUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_la[0]");
	grgLsUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ls[0]");
	grgLdUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ld[1]");
	grgLaUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_la[1]");
	grgLsUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ls[1]");
	grgLdUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ld[2]");
	grgLaUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_la[2]");
	grgLsUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ls[2]");
	grgLightPositionUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_light_position[0]");
	grgLightPositionUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_light_position[1]");
	grgLightPositionUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_light_position[2]");

	grgKaUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ka");
	grgKdUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_kd");
	grgKsUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ks");

	grgLKeyPressedUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_l_key_pressed");
	grgMaterialShinynessUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_material_shinyness");


	//***** sphere *****/
	glGenVertexArrays(1, &grgVaoSphere);
	glBindVertexArray(grgVaoSphere);

	// position
	glGenBuffers(1, &grgVboSpherePosition);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grgSphereVertices), grgSphereVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// elements
	glGenBuffers(1, &grgVboSphereElements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grgSphereElements), grgSphereElements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// normals
	glGenBuffers(1, &grgVboSphereNormal);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grgSphereNormals), grgSphereNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

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

void Resize(int width, int height)
{
	if(height ==0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	grgPerspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
}

void Draw(void)
{
	// function declaration
	void Update(void);

	// code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// OpenGL drawing code will start here
	mat4 grmodelMatrix = mat4::identity();
	mat4 grviewMatrix = mat4::identity();
	mat4 grprojectionMatrix = mat4::identity();
	mat4 grtranslateMatrix = mat4::identity();

	if (grgbPerVertexLighting == true)
	{
		// start use of shader program
		glUseProgram(grgShaderProgramObjectPV);

		grmodelMatrix = mat4::identity();
		grviewMatrix = mat4::identity();
		grprojectionMatrix = mat4::identity();
		grtranslateMatrix = mat4::identity();

		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -4.0f);
		grmodelMatrix = grtranslateMatrix;

		// multiply modelview and orthographic matrix to get modelviewprojectionmatrix
		grprojectionMatrix = grgPerspectiveProjectionMatrix;

		if (grgbLight == true)
		{
			glUniform1i(grgLKeyPressedUniformPV, 1);
			glUniform3fv(grgKdUniformPV, 1, grgKd);
			glUniform3fv(grgKaUniformPV, 1, grgKa);
			glUniform3fv(grgKsUniformPV, 1, grgKs);
			glUniform1f(grgMaterialShinynessUniformPV, grgMaterialShinyness);

			if (grgbXKeyPressed == true)
			{
				grlight[0].lightPosition[0] = 0.0;
				grlight[0].lightPosition[1] = (GLfloat)5.5 * sin(grflightAngleX);
				grlight[0].lightPosition[2] = (GLfloat)5.5 * cos(grflightAngleX);
				grlight[0].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}
			if (grgbYKeyPressed == true)
			{
				grlight[1].lightPosition[0] = (GLfloat)4.5 * sin(grflightAngleX);;
				grlight[1].lightPosition[1] = 0.0;
				grlight[1].lightPosition[2] = (GLfloat)4.5 * cos(grflightAngleX);
				grlight[1].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			if (grgbZKeyPressed == true)
			{
				grlight[2].lightPosition[0] = (GLfloat)6.5 * sin(grflightAngleX);;
				grlight[2].lightPosition[1] = (GLfloat)6.5 * cos(grflightAngleX);
				grlight[2].lightPosition[2] = 0.0f;
				grlight[2].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			for (i = 0; i < 3; i++)
			{
				glUniform3fv(grgLdUniformPV[i], 1, grlight[i].lightDiffuseColor);
				glUniform3fv(grgLaUniformPV[i], 1, grlight[i].lightAmbientColor);
				glUniform3fv(grgLsUniformPV[i], 1, grlight[i].lightSpecularColor);
				glUniform4fv(grgLightPositionUniformPV[i], 1, grlight[i].lightPosition);
			}

		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPV, 0);
		}

		glUniformMatrix4fv(grgModelMarixUniformPV, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPV, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPV, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVaoSphere);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElements);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		Update();
		// stop use of shader program
		glUseProgram(0);
	}
	else if (grgbPerFragmentLighting == true)
	{
		// start use of shader program
		glUseProgram(grgShaderProgramObjectPF);

		grmodelMatrix = mat4::identity();
		grviewMatrix = mat4::identity();
		grprojectionMatrix = mat4::identity();
		grtranslateMatrix = mat4::identity();

		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -4.0f);
		grmodelMatrix = grtranslateMatrix;

		// multiply modelview and orthographic matrix to get modelviewprojectionmatrix
		grprojectionMatrix = grgPerspectiveProjectionMatrix;

		if (grgbLight == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd);
			glUniform3fv(grgKaUniformPF, 1, grgKa);
			glUniform3fv(grgKsUniformPF, 1, grgKs);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness);

			if (grgbXKeyPressed == true)
			{
				grlight[0].lightPosition[0] = 0.0;
				grlight[0].lightPosition[1] = (GLfloat)5.5 * sin(grflightAngleX);
				grlight[0].lightPosition[2] = (GLfloat)5.5 * cos(grflightAngleX);
				grlight[0].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}
			if (grgbYKeyPressed == true)
			{
				grlight[1].lightPosition[0] = (GLfloat)4.5 * sin(grflightAngleX);;
				grlight[1].lightPosition[1] = 0.0;
				grlight[1].lightPosition[2] = (GLfloat)4.5 * cos(grflightAngleX);
				grlight[1].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			if (grgbZKeyPressed == true)
			{
				grlight[2].lightPosition[0] = (GLfloat)6.5 * sin(grflightAngleX);;
				grlight[2].lightPosition[1] = (GLfloat)6.5 * cos(grflightAngleX);
				grlight[2].lightPosition[2] = 0.0f;
				grlight[2].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			for (i = 0; i < 3; i++)
			{
				glUniform3fv(grgLdUniformPF[i], 1, grlight[i].lightDiffuseColor);
				glUniform3fv(grgLaUniformPF[i], 1, grlight[i].lightAmbientColor);
				glUniform3fv(grgLsUniformPF[i], 1, grlight[i].lightSpecularColor);
				glUniform4fv(grgLightPositionUniformPF[i], 1, grlight[i].lightPosition);
			}

		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}

		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);

		// bind vao
		glBindVertexArray(grgVaoSphere);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElements);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		Update();
		// stop use of shader program
		glUseProgram(0);
	}
	glXSwapBuffers(gpDisplay, gWindow);

}

void Update(void)
{
	if (grgbXKeyPressed)
	{
		grflightAngleX = grflightAngleX + 0.003f;
		if (grflightAngleX >= 360.0f)
			grflightAngleX = 0.0f;

	}
	if (grgbYKeyPressed)
	{
		grflightAngleY = grflightAngleY + 0.0035f;
		if (grflightAngleY >= 360.0f)
			grflightAngleY = 0.0f;
	}
	if (grgbZKeyPressed)
	{
		grflightAngleZ = grflightAngleZ + 0.0028f;
		if (grflightAngleZ >= 360.0f)
			grflightAngleZ = 0.0f;
	}

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
	if (grgVboSphereNormal)
	{
		glDeleteBuffers(1, &grgVboSphereNormal);
		grgVboSphereNormal = 0;
	}
	if (grgVboSphereElements)
	{
		glDeleteBuffers(1, &grgVboSphereElements);
		grgVboSphereElements = 0;
	}
	
	// free shaders (safe release)
	if(grgShaderProgramObjectPV)
	{
		glUseProgram(grgShaderProgramObjectPV);
		GLsizei grshaderCount;
		glGetProgramiv(grgShaderProgramObjectPV, GL_ATTACHED_SHADERS, &grshaderCount);
		GLuint *grpShaders = NULL;
		grpShaders = NULL;
		grpShaders = (GLuint *)malloc(sizeof(GLuint) * grshaderCount);
		glGetAttachedShaders(grgShaderProgramObjectPV, grshaderCount, &grshaderCount, grpShaders);
		for(i = 0; i < grshaderCount; i++)
		{
			glDetachShader(grgShaderProgramObjectPV, grpShaders[i]);
			glDeleteShader(grpShaders[i]);
			grpShaders[i] = 0;
		}
		// unlink shader program
		glUseProgram(0);
	}
	if(grgShaderProgramObjectPF)
	{
		glUseProgram(grgShaderProgramObjectPF);
		GLsizei grshaderCount;
		glGetProgramiv(grgShaderProgramObjectPF, GL_ATTACHED_SHADERS, &grshaderCount);
		GLuint *grpShaders = NULL;
		grpShaders = NULL;
		grpShaders = (GLuint *)malloc(sizeof(GLuint) * grshaderCount);
		glGetAttachedShaders(grgShaderProgramObjectPF, grshaderCount, &grshaderCount, grpShaders);
		for(i = 0; i < grshaderCount; i++)
		{
			glDetachShader(grgShaderProgramObjectPF, grpShaders[i]);
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
g++ -o OGL2 OGL2.cpp -L . -lGL -lX11 -lGLEW -lSphere
*/







































