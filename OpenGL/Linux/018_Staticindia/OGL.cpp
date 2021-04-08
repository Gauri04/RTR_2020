#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<math.h>

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>
#include<GL/gl.h>		// for opengl api's 
#include<GL/glx.h>		// for glx apis
#include<GL/glu.h>

const GLfloat PI = 3.142f;

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
GLfloat grangleStone = 0.0f;
GLfloat grangleWand = 0.0f;
GLfloat grangleCloak = 0.0f;
GLfloat grmoveStoneX = -3.0f;
GLfloat grmoveStoneY = -2.0f;
GLfloat grmoveCloakX = 3.0f;
GLfloat grmoveCloakY = 2.0f;
GLfloat grmoveWandY = 2.2f;
GLfloat i;

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
		GLX_RGBA,
		GLX_RED_SIZE, 1,
		GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE, 1,
		GLX_ALPHA_SIZE, 1,
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

	gglxContext = glXCreateContext(gpDisplay,				// similar wglCreateContext()
								gpXVisualInfo,
								NULL,
								GL_TRUE
								);
	glXMakeCurrent(gpDisplay, gWindow, gglxContext);		// similar to wglMakeColor()
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// warm - up call to resize
	Resize(giWindowWidth, giWindowHeight);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	//////////////////////////////////////////////////////////// I ////////////////////////////////////////////////////////////////
	glLoadIdentity();
	glTranslatef(-2.9f, 1.0f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
		glVertex3f(0.4f, 0.1f, 0.0f);
		glVertex3f(-0.4f, 0.1f, 0.0f);
		glVertex3f(-0.4f, -0.05f, 0.0f);
		glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// bottom _ of I
	glLoadIdentity();
	glTranslatef(-2.9f, -1.0f, -6.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glBegin(GL_QUADS);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, -0.05f, 0.0f);
	glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// | of I (top)
	glLoadIdentity();
	glTranslatef(-2.89f, 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of I (middle)
	glLoadIdentity();
	glTranslatef(-2.89f, 0.3f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.4f, 0.0f);
	glEnd();

	// | of I (bottom)
	glLoadIdentity();
	glTranslatef(-2.89f, -0.4f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(-0.1f, -0.6f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(0.1f, -0.6f, 0.0f);
	glEnd();
	
	///////////////////////////////////////// N ///////////////////////////////////////////////////////////////
	// N ( | of N) (top)
	glLoadIdentity();
	glTranslatef(-2.0f, 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of N (middle)
	glLoadIdentity();
	glTranslatef(-2.0f, 0.3f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.4f, 0.0f);
	glEnd();

	// | of N (bottom)
	glLoadIdentity();
	glTranslatef(-2.0f, -0.4f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(-0.1f, -0.645f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(0.1f, -0.645f, 0.0f);
	glEnd();

	// N ( \ of N)
	glLoadIdentity();
	glTranslatef(-1.875f, 0.7f, -6.0f);
	glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();

	// \ of N
	glLoadIdentity();
	glTranslatef(-1.79f, 0.3f, -6.0f);
	glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.5f, 0.0f);
	glEnd();

	// \ of N
	glLoadIdentity();
	glTranslatef(-1.645f, -0.4f, -6.0f);
	glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.25f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(-0.1f, -0.63f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(0.1f, -0.63f, 0.0f);
	glEnd();


	// | of N
	// N ( | of N)
	glLoadIdentity();
	glTranslatef(-1.49f, 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of N (middle)
	glLoadIdentity();
	glTranslatef(-1.49f, 0.3f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.4f, 0.0f);
	glEnd();

	// | of N (bottom)
	glLoadIdentity();
	glTranslatef(-1.49f, -0.4f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(-0.1f, -0.645f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(0.1f, -0.645f, 0.0f);
	glEnd();

	//////////////////////////////////////////////////// D ////////////////////////////////////////////////////////////////////
	// D ( | of D) (top)
	glLoadIdentity();
	glTranslatef(-0.9f, 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of D (middle)
	glLoadIdentity();
	glTranslatef(-0.9f, 0.3f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.4f, 0.0f);
	glEnd();

	// | of D (bottom)
	glLoadIdentity();
	glTranslatef(-0.9f, -0.4f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(-0.1f, -0.645f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(0.1f, -0.645f, 0.0f);
	glEnd();

	// top - of D
	glLoadIdentity();
	glTranslatef(-0.6f, 1.0f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);
	glBegin(GL_QUADS);
	glVertex3f(0.11f, 0.1f, 0.0f);				//top right
	glVertex3f(-0.2f, 0.1f, 0.0f);				// top left
	glVertex3f(-0.2f, -0.1f, 0.0f);				// bottom left
	glVertex3f(0.1f, -0.1f, 0.0f);				// bottom right
	glEnd();
	
	// D ( \ of D)
	glLoadIdentity();
	glTranslatef(-0.32f, 0.89f, -6.0f);
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();

	// | of D (top)
	glLoadIdentity();
	glTranslatef(-0.2f, 0.5f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.37f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.07f, 0.0f);
	glVertex3f(0.1f, -0.07f, 0.0f);
	glEnd();

	// | of D (middle)
	glLoadIdentity();
	glTranslatef(-0.2f, 0.4f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.5f, 0.0f);
	glEnd();

	// / of D
	glLoadIdentity();
	glTranslatef(-0.32f, -0.83f, -6.0f);
	glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.07f, 0.53f, 0.03f);
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();

	// | of D (bottom)
	glLoadIdentity();
	glTranslatef(-0.2f, -0.3f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.2f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.2f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(-0.1f, -0.5f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(0.1f, -0.5f, 0.0f);
	glEnd();

	// bottom - of D
	glLoadIdentity();
	glTranslatef(-0.6f, -0.946f, -6.0f);
	//glRotatef(83.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.07f, 0.53f, 0.03f);
	glBegin(GL_QUADS);
	glVertex3f(0.11f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, -0.1f, 0.0f);
	glVertex3f(0.11f, -0.1f, 0.0f);
	glEnd();
	
	///////////////////////////////////////////////////////////////// I ///////////////////////////////////////////////////////////////////
	
	// - of A (top)
	glLoadIdentity();
	glTranslatef(0.6f, 1.0f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, -0.05f, 0.0f);
	glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// bottom _ of I
	glLoadIdentity();
	glTranslatef(0.6f, -1.0f, -6.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glBegin(GL_QUADS);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, -0.05f, 0.0f);
	glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// | of I (top)
	glLoadIdentity();
	glTranslatef(0.623f, 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of I (middle)
	glLoadIdentity();
	glTranslatef(0.623f, 0.3f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.4f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.4f, 0.0f);
	glEnd();

	// | of I (bottom)
	
	glLoadIdentity();
	glTranslatef(0.623f, -0.38f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(-0.1f, -0.6f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glVertex3f(0.1f, -0.6f, 0.0f);
	glEnd();

	////////////////////////////////////////////////////////////// A //////////////////////////////////////////////////////////////////////

	// - of A (middle - white)
	
	glLoadIdentity();
	glTranslatef(2.0f, -0.12f, -6.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glBegin(GL_QUADS);
	glVertex3f(0.35f, 0.03f, 0.0f);
	glVertex3f(-0.35f, 0.03f, 0.0f);
	glVertex3f(-0.35f, -0.03f, 0.0f);
	glVertex3f(0.35f, -0.03f, 0.0f);
	glEnd();

	// - of A (top - saffron)
	glLoadIdentity();
	glTranslatef(2.0f, -0.07f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.3f, 0.03f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.3f, 0.03f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.3f, -0.03f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.3f, -0.03f, 0.0f);
	glEnd();

	// - of A (bottom - green)
	glLoadIdentity();
	glTranslatef(2.0f, -0.16f, -6.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.4f, 0.03f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.4f, 0.03f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			// green
	glVertex3f(-0.4f, -0.03f, 0.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			// green
	glVertex3f(0.4f, -0.03f, 0.0f);
	glEnd();


	// / of A (bottom)
	glLoadIdentity();
	glTranslatef(1.4f, -0.83f, -6.0f);
	glRotatef(165.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			// green
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// / of A (middle)
	glLoadIdentity();
	glTranslatef(1.4950f, -0.48f, -6.0f);
	glRotatef(165.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.53f, 0.03f);			// green
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(0.1f, 0.53f, 0.03f);			// green
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -0.3f, 0.0f);
	glEnd();

	// / of A (top)
	glLoadIdentity();
	glTranslatef(1.65f, 0.09f, -6.0f);
	glRotatef(165.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, -1.0f, 0.0f);
	glEnd();

	// - of A (top)
	glLoadIdentity();
	glTranslatef(1.93f, 1.0f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.12f, 0.13f, 0.0f);
	glVertex3f(-0.12f, 0.13f, 0.0f);
	glVertex3f(-0.12f, -0.01f, 0.0f);
	glVertex3f(0.14f, -0.01f, 0.0f);
	glEnd();


	// \ of A (top)
	glLoadIdentity();
	glTranslatef(2.05f, 0.8f, -6.0f);
	glRotatef(18.325f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, -1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, -1.0f, 0.0f);
	glEnd();

	// \ of A (middle)
	glLoadIdentity();
	glTranslatef(2.457f, -0.425f, -6.0f);
	glRotatef(18.325f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.1f, 0.53f, 0.03f);			// green
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(0.1f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);			//white
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glColor3f(0.1f, 0.53f, 0.03f);			// green
	glVertex3f(-0.1f, -0.3f, 0.0f);
	glColor3f(0.1f, 0.53f, 0.03f);			// green
	glVertex3f(0.1f, -0.3f, 0.0f);
	glEnd();

	// \ of A (bottom)
	glLoadIdentity();
	glTranslatef(2.645f, -0.99f, -6.0f);
	glRotatef(18.325f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			// green
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.14f, 0.0f);
	glEnd();

	glXSwapBuffers(gpDisplay, gWindow);

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









































