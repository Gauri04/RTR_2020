#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>
#include<GL/gl.h>		// for opengl api's 
#include<GL/glx.h>		// for glx apis
#include<GL/glu.h>

#include<SOIL/SOIL.h>
#include"teapot.h"

using namespace std;

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
GLuint grteapotTexture;
bool grgbLight = false;
bool btexture = false;
bool gbAnimate = false;

GLfloat grlightAmbient[] =			// gray
{
	0.1f, 0.1f, 0.1f, 1.0f
};
GLfloat grlightDiffuse[] =
{
	1.0f, 1.0f, 1.0f, 1.0f
};
GLfloat grlightSpecular[] =
{
	1.0f, 1.0f, 1.0f, 1.0f
};
GLfloat grlightPosition[] =			// light comes from z axis
{
	100.0f, 100.0f, 100.0f, 1.0f
};

GLfloat grmaterialAmbient[] =
{
	0.0f, 0.0f, 0.0f, 1.0f
};
GLfloat grmaterialDiffuse[] =
{
	1.0f, 1.0f, 1.0f, 1.0f
};
GLfloat grmaterialSpecular[] =
{
	1.0f, 1.0f, 1.0f, 1.0f
};
GLfloat grmaterialShinyness = 128.0f;

GLUquadric* grquadric = NULL;



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

						case XK_l:
							grgbLight = !grgbLight;
							if (grgbLight == false)
							{
								glEnable(GL_LIGHTING);
							}
							else
							{
								glDisable(GL_LIGHTING);
							}
							break;


						case XK_t :
							btexture = !btexture;
							if (btexture == false)
							{
								glEnable(GL_TEXTURE_2D);
							}
							else
							{
								glDisable(GL_TEXTURE_2D);
							}
							break;
							

						case XK_a :
							gbAnimate = !gbAnimate;
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
		GLX_DOUBLEBUFFER, True,
		GLX_RGBA,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, 24,								// v4l recommentds bitsize of depth to be ketp around 24 or below (v4l = video for linux)
		None												// to indicate unix systems to set next attributes to default, insert 0 / None at end 
	};
	
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

	gpXVisualInfo = glXChooseVisual(gpDisplay, defaultScreen, framebufferAttributes);	//opengl bridging api similar to wgl* from windows
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
	GLuint LoadBitmapAsTexture(const char *);

	gglxContext = glXCreateContext(gpDisplay,				// similar wglCreateContext()
								gpXVisualInfo,
								NULL,
								GL_TRUE
								);
	glXMakeCurrent(gpDisplay, gWindow, gglxContext);		// similar to wglMakeColor()

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	grteapotTexture = LoadBitmapAsTexture("marble.bmp");

	// light
	glLightfv(GL_LIGHT0, GL_AMBIENT, grlightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, grlightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, grlightSpecular);


	// material
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, grmaterialShinyness);
	glEnable(GL_LIGHT0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// warm - up call to resize
	Resize(giWindowWidth, giWindowHeight);

}

GLuint LoadBitmapAsTexture(const char * path)
{
	// variable declarations
	int width, height;						// it will get image's width and heoght
	unsigned char *imageData = NULL;
	GLuint textureId;

	// CODE
	imageData = SOIL_load_image(path, 
		&width, 
		&height,
		NULL,									// how many channels (R,G,B,A) your image has 
		SOIL_LOAD_RGB);							// Load 3 channels - RGB as our bmp is 24 color bitmap (24 means RGB 2^3)
												// if it was png file then would have written SOIL_LOAD_RGBA
	// from here starts OpenGL actual code
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// MAG - Magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);				// MIN - Minification
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData); // 3 is GL_RGBA 

	// free memory used by soil
	SOIL_free_image_data(imageData);
	return textureId;

}

void Resize(int width, int height)
{
	if(height ==0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	
}

void Draw(void)
{
	// function declaration
	void Update(void);

	// code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_MODELVIEW);

	////////////// Pyramid ///////////////////////
	glLoadIdentity();
	glLightfv(GL_LIGHT1, GL_POSITION, grlightPosition);
	glTranslatef(0.0f, 0.0f, -1.0f);
	glRotatef(grfangle, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, grteapotTexture);

	glBegin(GL_TRIANGLES);
		for (int i = 0; i < sizeof(face_indicies) / sizeof(face_indicies[0]); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int vi = face_indicies[i][j];
				int ni = face_indicies[i][j + 3];
				int ti = face_indicies[i][j + 6];

				glNormal3f(normals[ni][0], normals[ni][1], normals[ni][2]);
				glTexCoord2f(textures[ti][0], textures[ti][1]);
				glVertex3f(vertices[vi][0], vertices[vi][1], vertices[vi][2]);

			}
		}
	glEnd();


	Update();

	glXSwapBuffers(gpDisplay, gWindow);

}

void Update(void)
{
	if (gbAnimate)
	{
		if (grfangle >= 360.0f)
		{
			grfangle = 0.0f;
		}
		grfangle = grfangle + 0.05f;
	}
}

void Uninitialize()
{
	// variable declaration
	GLXContext currentGLXContext;

	// code
	currentGLXContext = glXGetCurrentContext();			// in unix we can have multiple monitors, multiple screens hence check if we are uninitializing current context only
	if(currentGLXContext == gglxContext)
	{
		glXMakeCurrent(gpDisplay, 0, 0);
		if(gglxContext)
		{
			glXDestroyContext(gpDisplay, gglxContext);
		}

	}

	glDeleteTextures(1, &grteapotTexture);

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


/*
compile, link command : 
g++ -o OGL  OGL.cpp -lX11 -lGL -lGLU
./OGL
*/








































