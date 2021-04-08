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
GLfloat grMoveI = -2.5f;
GLfloat grMoveA = 3.3f;
GLfloat grMoveN = -4.2f;
GLfloat grMoveI2 = 4.2f;
GLfloat grColorDSaffronRed = 0.0f;
GLfloat grColorDSaffronGreen = 0.0f;
GLfloat grColorDSaffronBlue = 0.0f;
GLfloat grColorDWhite = 0.0f;
GLfloat grColorDWhiteGreen = 0.0f;
GLfloat grColorDWhiteBlue = 0.0f;
GLfloat grColorDGreenRed = 0.0f;
GLfloat grColorDGreenGreen = 0.0f;
GLfloat grColorDGreenBlue = 0.0f;


bool grbIMoved = false;
bool grbNMoved = false;
bool grbDColored = false;
bool grbI2Moved = false;
bool grbAMoved = false;

// Plane variables
GLfloat grMovePlaneInHorizontal = -4.8f;
//GLfloat grMovePlane1InHorizontal = -2.0f;
GLfloat grMoveGreenPlaneInHorizontal = -2.0f;	// green plane
GLfloat grMoveOrangePlaneInHorizontal = -0.22f;	// orange plane
GLfloat radius = 1.9f;
bool bStartAnimation = false;

const GLfloat PI = 3.142f;
GLfloat x = (GLfloat)(PI * radius) / 2;
GLdouble y = (GLfloat)(PI * radius) / 2;
GLfloat grangleOrangePlane = 270.0f;
GLfloat grangleGreenPlane = 90.0f;
bool grbRotateOrangePlane = false;
bool grbRotateGreenPlane = false;

bool bPlanesVisible = false;

int main()
{
	void CreateWindow();
	void ToggleFullscreen();
	void Uninitialize();
	void Initialize(void);
	void Resize(int, int);
	void Draw(void);
	void Update(void);

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

						case XK_a:
						case XK_A :
							bStartAnimation = true;
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
	// function declaration
	void Update(void);

	// code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//////////////////////////////////////////////////////////// I ////////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveI -2.9f, 1.0f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
		glVertex3f(0.4f, 0.1f, 0.0f);
		glVertex3f(-0.4f, 0.1f, 0.0f);
		glVertex3f(-0.4f, -0.05f, 0.0f);
		glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// bottom _ of I
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveI -2.9f, -1.0f, -6.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glBegin(GL_QUADS);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, -0.05f, 0.0f);
	glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// | of I (top)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveI -2.89f, 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of I (middle)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveI -2.89f, 0.3f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveI -2.89f, -0.4f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-2.0f, grMoveN + 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of N (middle)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-2.0f, grMoveN + 0.3f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-2.0f, grMoveN -0.4f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.875f, grMoveN + 0.7f, -6.0f);
	glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();

	// \ of N
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.79f, grMoveN + 0.3f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.645f, grMoveN -0.4f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.49f, grMoveN + 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of N (middle)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.49f, grMoveN + 0.3f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.49f, grMoveN + -0.4f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.9f, 0.7f, -6.0f);
	//glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of D (middle)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.9f, 0.3f, -6.0f);
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	//glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(-0.1f, -0.4f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(0.1f, -0.4f, 0.0f);
	glEnd();

	// | of D (bottom)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.9f, -0.4f, -6.0f);
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(0.1f, 0.3f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(-0.1f, 0.3f, 0.0f);
	//glColor3f(0.07f, 0.53f, 0.03f);			//green
	glColor3f(grColorDGreenRed, grColorDGreenGreen, grColorDGreenBlue);
	glVertex3f(-0.1f, -0.645f, 0.0f);
	//glColor3f(0.07f, 0.53f, 0.03f);			//green
	glColor3f(grColorDGreenRed, grColorDGreenGreen, grColorDGreenBlue);
	glVertex3f(0.1f, -0.645f, 0.0f);
	glEnd();

	// top - of D
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.6f, 1.0f, -6.0f);
	//glColor3f(1.0f, 0.5f, 0.10f);
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.11f, 0.1f, 0.0f);				//top right
	glVertex3f(-0.2f, 0.1f, 0.0f);				// top left
	glVertex3f(-0.2f, -0.1f, 0.0f);				// bottom left
	glVertex3f(0.1f, -0.1f, 0.0f);				// bottom right
	glEnd();
	
	// D ( \ of D)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.32f, 0.89f, -6.0f);
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
	//glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();

	// | of D (top)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.2f, 0.5f, -6.0f);
	//glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.37f, 0.0f);
	glVertex3f(-0.1f, 0.4f, 0.0f);
	glVertex3f(-0.1f, -0.07f, 0.0f);
	glVertex3f(0.1f, -0.07f, 0.0f);
	glEnd();

	// | of D (middle)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.2f, 0.4f, -6.0f);
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glVertex3f(0.1f, 0.3f, 0.0f);
	//glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glColor3f(grColorDSaffronRed, grColorDSaffronGreen, grColorDSaffronBlue);			//saffron
	glVertex3f(-0.1f, 0.3f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(-0.1f, -0.5f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(0.1f, -0.5f, 0.0f);
	glEnd();

	// / of D
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.32f, -0.83f, -6.0f);	
	glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
	//glColor3f(0.07f, 0.53f, 0.03f);			//green
	glColor3f(grColorDGreenRed, grColorDGreenGreen, grColorDGreenBlue);
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();

	// | of D (bottom)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.2f, -0.3f, -6.0f);
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(0.1f, 0.2f, 0.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);			//white
	glColor3f(grColorDWhite, grColorDWhite, grColorDWhite);
	glVertex3f(-0.1f, 0.2f, 0.0f);
	//glColor3f(0.07f, 0.53f, 0.03f);			//green
	glColor3f(grColorDGreenRed, grColorDGreenGreen, grColorDGreenBlue);
	glVertex3f(-0.1f, -0.5f, 0.0f);
	//glColor3f(0.07f, 0.53f, 0.03f);			//green
	glColor3f(grColorDGreenRed, grColorDGreenGreen, grColorDGreenBlue);
	glVertex3f(0.1f, -0.5f, 0.0f);
	glEnd();

	// bottom - of D
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-0.6f, -0.946f, -6.0f);
	//glRotatef(83.0f, 0.0f, 0.0f, 1.0f);
	//glColor3f(0.07f, 0.53f, 0.03f);			//green
	glColor3f(grColorDGreenRed, grColorDGreenGreen, grColorDGreenBlue);
	glBegin(GL_QUADS);
	glVertex3f(0.11f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, -0.1f, 0.0f);
	glVertex3f(0.11f, -0.1f, 0.0f);
	glEnd();
	
	///////////////////////////////////////////////////////////////// I ///////////////////////////////////////////////////////////////////
	
	// - of A (top)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.6f, grMoveI2 + 1.0f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, -0.05f, 0.0f);
	glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// bottom _ of I
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.6f, grMoveI2 -1.0f, -6.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			//green
	glBegin(GL_QUADS);
	glVertex3f(0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, 0.1f, 0.0f);
	glVertex3f(-0.4f, -0.05f, 0.0f);
	glVertex3f(0.4f, -0.05f, 0.0f);
	glEnd();

	// | of I (top)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.623f, grMoveI2 + 0.7f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// | of I (middle)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.623f, grMoveI2 + 0.3f, -6.0f);
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
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.623f, grMoveI2 -0.38f, -6.0f);
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
	////////////////////////////// middle - of A with colors

	if (grMoveOrangePlaneInHorizontal >= 4.5)
	{
		// - of A (top - saffron)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(grMoveA + 2.0f, -0.05f, -6.0f);
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
	}



	if (grMovePlaneInHorizontal >= 2.0f)
	{
		// - of A (middle - white)

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(grMoveA + 2.0f, -0.10f, -6.0f);
		glColor3f(1.0f, 1.0f, 1.0f);			//white
		glBegin(GL_QUADS);
		glVertex3f(0.35f, 0.03f, 0.0f);
		glVertex3f(-0.35f, 0.03f, 0.0f);
		glVertex3f(-0.35f, -0.03f, 0.0f);
		glVertex3f(0.35f, -0.03f, 0.0f);
		glEnd();

	}

	if (grMoveGreenPlaneInHorizontal >= 2.1f)
	{
		// - of A (bottom - green)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(grMoveA + 2.0f, -0.15f, -6.0f);
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
	}

	// / of A (bottom)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveA + 1.4f, -0.83f, -6.0f);
	glRotatef(165.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			// green
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glEnd();

	// / of A (middle)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveA + 1.4950f, -0.48f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveA + 1.65f, 0.09f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveA + 1.93f, 1.0f, -6.0f);
	glColor3f(1.0f, 0.5f, 0.10f);			//saffron
	glBegin(GL_QUADS);
	glVertex3f(0.12f, 0.13f, 0.0f);
	glVertex3f(-0.12f, 0.13f, 0.0f);
	glVertex3f(-0.12f, -0.01f, 0.0f);
	glVertex3f(0.14f, -0.01f, 0.0f);
	glEnd();


	// \ of A (top)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveA + 2.05f, 0.8f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveA + 2.457f, -0.425f, -6.0f);
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(grMoveA + 2.645f, -0.99f, -6.0f);
	glRotatef(18.325f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.07f, 0.53f, 0.03f);			// green
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, 0.3f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.14f, 0.0f);
	glEnd();

	
	
	


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////// PLANES //////////////////////////////////////////////////////////////
	if (bPlanesVisible == true)
	{
		///////////////////////////////////////////////////////// PLANE 1 (ORANGE - MIDDLE) /////////////////////////////////////////////

// | of plane (1)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)) + 0.0f, 2.0f + (radius * sin(x)) + 0.0f, -6.0f);
		glRotatef(grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.3f, 0.0f);
		glVertex3f(-0.05f, 0.3f, 0.0f);
		glVertex3f(-0.05f, -0.3f, 0.0f);
		glVertex3f(0.0f, -0.3f, 0.0f);
		glEnd();

		// small | of plane (2)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)) + 0.0f, -6.0f);
		glRotatef(grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.1f, 0.0f);		// right top
		glVertex3f(-0.12f, 0.1f, 0.0f);		// left top 
		glVertex3f(-0.12f, -0.1f, 0.0f);	// left bottom
		glVertex3f(0.0f, -0.1f, 0.0f);	// right bottom
		glEnd();

		// \ of plane (3)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)), -6.0f); // -0.10f
		glRotatef(40.0f + grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		//glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.30f, 0.0f);			// is right-top
		glVertex3f(-0.05f, 0.30f, 0.0f);		// left top
		glVertex3f(-0.05f, -0.05f, 0.0f);	// left bottom x,y
		glVertex3f(0.0f, -0.05f, 0.0f);
		glEnd();


		// \ of plane (4)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)), -6.0f);
		glRotatef(40.0f + grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		//glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.23f, 0.0f);
		glVertex3f(-0.08f, 0.23f, 0.0f);
		glVertex3f(-0.08f, -0.05f, 0.0f);
		glVertex3f(0.0f, -0.05f, 0.0f);
		glEnd();


		// small / of plane (5)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)), -6.0f);	// -2.0f, -0.088f
		glRotatef(135.0f + grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		//glRotatef(135.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.04f, 0.3f, 0.0f);
		glVertex3f(-0.015f, 0.3f, 0.0f);
		glVertex3f(-0.015f, -0.08f, 0.0f);
		glVertex3f(0.04f, -0.08f, 0.0f);
		glEnd();


		// / of plane (6)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)), -6.0f); // -0.15, -0.088
		glRotatef(135.0f + grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		//glRotatef(135.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.073f, 0.23f, 0.0f);
		glVertex3f(-0.015f, 0.23f, 0.0f);
		glVertex3f(-0.015f, -0.08f, 0.0f);
		glVertex3f(0.073f, -0.08f, 0.0f);
		glEnd();
		/*
		*/
		// ---------- Front side of plane
		// > of plane (7)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)), -6.0f);
		glRotatef(grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.3f, 0.0f, 0.0f);			//apex
		glVertex3f(-0.0f, 0.3f, 0.0f);
		glVertex3f(-0.0f, -0.3f, 0.0f);
		glEnd();

		// >  tip of plane (8) 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)), -6.0f);
		glRotatef(grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.5f, 0.0f, 0.0f);			//apex
		glVertex3f(-0.0f, 0.15f, 0.0f);
		glVertex3f(-0.0f, -0.15f, 0.0f);
		glEnd();

		// Window of plane (9)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)) + 0.0f, -6.0f);
		glRotatef(grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.8f, 0.8f, 0.8f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.4f, 0.0f, 0.0f);			//apex
		glVertex3f(0.17f, 0.05f, 0.0f);
		glVertex3f(0.17f, -0.05f, 0.0f);
		glEnd();

		
		// Smoke of plane (10)
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(-2.0f + grMoveOrangePlaneInHorizontal + (radius * cos(x)), 2.0f + (radius * sin(x)) + 0.0f, -6.0f);
		glRotatef(grangleOrangePlane, 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.5f, 0.10f);			//saffron
		glVertex3f(-0.10f, 0.05f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.35f, 0.05f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.35f, -0.05f, 0.0f);
		glColor3f(1.0f, 0.5f, 0.10f);			//saffron
		glVertex3f(-0.10f, -0.05f, 0.0f);
		glEnd();
	
		



		///////////////////////////////////////////////////////// PLANE 3 (GREEN - Bottom) /////////////////////////////////////////////

		// | of plane (1)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.3f, 0.0f);
		glVertex3f(-0.05f, 0.3f, 0.0f);
		glVertex3f(-0.05f, -0.3f, 0.0f);
		glVertex3f(0.0f, -0.3f, 0.0f);
		glEnd();

		// small | of plane (2)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.1f, 0.0f);		// right top
		glVertex3f(-0.12f, 0.1f, 0.0f);		// left top 
		glVertex3f(-0.12f, -0.1f, 0.0f);	// left bottom
		glVertex3f(0.0f, -0.1f, 0.0f);	// right bottom
		glEnd();

		// \ of plane (3)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(40.0f + grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		//glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.30f, 0.0f);			// is right-top
		glVertex3f(-0.05f, 0.30f, 0.0f);		// left top
		glVertex3f(-0.05f, -0.05f, 0.0f);	// left bottom x,y
		glVertex3f(0.0f, -0.05f, 0.0f);
		glEnd();

		// \ of plane (4)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(40.0f + grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		//glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.23f, 0.0f);
		glVertex3f(-0.08f, 0.23f, 0.0f);
		glVertex3f(-0.08f, -0.05f, 0.0f);
		glVertex3f(0.0f, -0.05f, 0.0f);
		glEnd();

		// small / of plane (5)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane + 140.0f, 0.0f, 0.0f, 1.0f);
		//glRotatef(140.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.04f, 0.3f, 0.0f);
		glVertex3f(-0.015f, 0.3f, 0.0f);
		glVertex3f(-0.015f, -0.08f, 0.0f);
		glVertex3f(0.04f, -0.08f, 0.0f);
		glEnd();

		// / of plane (6)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane + 140.0f, 0.0f, 0.0f, 1.0f);
		//glRotatef(140.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.073f, 0.23f, 0.0f);
		glVertex3f(-0.015f, 0.23f, 0.0f);
		glVertex3f(-0.015f, -0.08f, 0.0f);
		glVertex3f(0.073f, -0.08f, 0.0f);
		glEnd();

		// ---------- Front side of plane
		// > of plane (7) (middle)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.3f, 0.0f, 0.0f);			//apex
		glVertex3f(-0.0f, 0.3f, 0.0f);
		glVertex3f(-0.0f, -0.3f, 0.0f);
		glEnd();

		// >  tip of plane (8) 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.5f, 0.0f, 0.0f);			//apex
		glVertex3f(-0.0f, 0.15f, 0.0f);
		glVertex3f(-0.0f, -0.15f, 0.0f);
		glEnd();

		// Window of plane (9)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		glColor3f(0.8f, 0.8f, 0.8f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.4f, 0.0f, 0.0f);			//apex
		glVertex3f(0.17f, 0.05f, 0.0f);
		glVertex3f(0.17f, -0.05f, 0.0f);
		glEnd();


		// Smoke of plane (10)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMoveGreenPlaneInHorizontal + (radius * cos(-y)), -2.0f + (radius * sin(-y)), -6.0f);
		glRotatef(grangleGreenPlane, 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glColor3f(0.07f, 0.53f, 0.03f);			//green
		glVertex3f(-0.10f, 0.05f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.35f, 0.05f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.35f, -0.05f, 0.0f);
		glColor3f(0.07f, 0.53f, 0.03f);			//green
		glVertex3f(-0.10f, -0.05f, 0.0f);
		glEnd();


		/////////////////////////////////////////////////////////PLANE 2 (WHITE- MIDDLE) /////////////////////////////////////////////
	// | of plane (1)

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glRotatef(grangle, 0.0f, 0.0f, 1.0f);
		glTranslated(grMovePlaneInHorizontal + 0.0f, 0.0f, -6.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.3f, 0.0f);
		glVertex3f(-0.05f, 0.3f, 0.0f);
		glVertex3f(-0.05f, -0.3f, 0.0f);
		glVertex3f(0.0f, -0.3f, 0.0f);
		glEnd();

		// small | of plane (2)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal - 0.05f, 0.0f, -6.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.1f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(0.0f, -0.1f, 0.0f);
		glEnd();

		// \ of plane (3)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal - 0.10f, 0.12f, -6.0f);
		glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.15f, 0.0f);
		glVertex3f(-0.05f, 0.15f, 0.0f);
		glVertex3f(-0.05f, -0.15f, 0.0f);
		glVertex3f(0.0f, -0.15f, 0.0f);
		glEnd();

		// \ of plane (4)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal - 0.15f, 0.12f, -6.0f);
		glRotatef(40.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.05f, 0.0f);
		glVertex3f(-0.05f, 0.05f, 0.0f);
		glVertex3f(-0.05f, -0.08f, 0.0f);
		glVertex3f(0.0f, -0.08f, 0.0f);
		glEnd();

		// small / of plane (5)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal - 0.2f, -0.065f, -6.0f);
		glRotatef(140.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.05f, 0.0f);
		glVertex3f(-0.05f, 0.05f, 0.0f);
		glVertex3f(-0.05f, -0.08f, 0.0f);
		glVertex3f(0.0f, -0.08f, 0.0f);
		glEnd();

		// / of plane (6)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal - 0.15f, -0.07f, -6.0f);
		glRotatef(140.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.15f, 0.0f);
		glVertex3f(-0.05f, 0.15f, 0.0f);
		glVertex3f(-0.05f, -0.15f, 0.0f);
		glVertex3f(0.0f, -0.15f, 0.0f);
		glEnd();

		// ---------- Front side of plane
		// > of plane (7)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal + 0.0f, 0.0f, -6.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.3f, 0.0f, 0.0f);			//apex
		glVertex3f(-0.0f, 0.3f, 0.0f);
		glVertex3f(-0.0f, -0.3f, 0.0f);
		glEnd();

		// >  tip of plane (8) 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal + 0.1f, 0.0f, -6.0f);
		glColor3f(0.54f, 0.60f, 0.83f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.4f, 0.0f, 0.0f);			//apex
		glVertex3f(-0.0f, 0.1f, 0.0f);
		glVertex3f(-0.0f, -0.1f, 0.0f);
		glEnd();

		// Window of plane (9)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal + 0.15f, 0.0f, -6.0f);
		glColor3f(0.8f, 0.8f, 0.8f); // blue color
		glBegin(GL_TRIANGLES);
		glVertex3f(0.25f, 0.0f, 0.0f);			//apex
		glVertex3f(-0.0f, 0.05f, 0.0f);
		glVertex3f(-0.0f, -0.05f, 0.0f);
		glEnd();


		// Smoke of plane (10)
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(grMovePlaneInHorizontal - 0.15f, 0.0f, -6.0f);
		//glColor3f(0.8f, 0.8f, 0.8f); // blue color
		glBegin(GL_QUADS);
		glColor3f(0.8f, 0.8f, 0.8f); // blue color
		glVertex3f(0.0f, 0.05f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.25f, 0.05f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.25f, -0.05f, 0.0f);
		glColor3f(0.8f, 0.8f, 0.8f); // blue color
		glVertex3f(0.0f, -0.05f, 0.0f);
		glEnd();

	}
	Update();

	glXSwapBuffers(gpDisplay, gWindow);

}

void Update(void)
{
	if (bStartAnimation == true)
	{
		// Move I from left
		if (grMoveI <= 0)
		{
			grMoveI = grMoveI + 0.00008f;
		}
		else
		{
			grbIMoved = true;
		}

		// Move A from right
		if (grbIMoved == true)
		{
			if (grMoveA >= 0)
			{
				grMoveA = grMoveA - 0.00008f;
			}
			else
			{
				grbAMoved = true;
			}

		}

		// Move N from bottom
		if (grbAMoved == true)
		{
			if (grMoveN <= 0)
			{
				grMoveN = grMoveN + 0.00008f;
			}
			else
			{
				grbNMoved = true;
			}

		}

		// Move I2 from top
		if (grbNMoved == true)
		{
			if (grMoveI2 >= 0)
			{
				grMoveI2 = grMoveI2 - 0.00008f;
			}
			else
			{
				grbI2Moved = true;
			}

		}

		// color D from black to their respective rgb
		if (grbI2Moved == true)
		{
			if (grColorDSaffronRed <= 1.0f)
			{
				if (grColorDSaffronGreen <= 0.5f)
				{
					if (grColorDGreenBlue <= 0.10f)
					{
						grColorDGreenBlue = grColorDGreenBlue + 0.000001f;
					}

					grColorDSaffronGreen = grColorDSaffronGreen + 0.000005f;
				}
				grColorDSaffronRed = grColorDSaffronRed + 0.000010f;
			}

			if (grColorDWhite <= 1.0f)
			{
				grColorDWhite = grColorDWhite + 0.000010f;
			}

			if (grColorDGreenGreen <= 0.53f)
			{
				if (grColorDGreenRed <= 0.07f)
				{
					if (grColorDGreenBlue <= 0.03f)
					{
						grColorDGreenBlue = grColorDGreenBlue + 0.00000050f;
					}
					grColorDGreenRed = grColorDGreenRed + 0.0000010f;
				}
				grColorDGreenGreen = grColorDGreenGreen + 0.0000050f;
			}

			if (grColorDSaffronRed >= 1.0f)
			{
				grbDColored = true;
			}
		}

		if (grbDColored == true)
		{
			bPlanesVisible = true;
			////////// planes logic////////////

			if (grMovePlaneInHorizontal <= 5.0f)
			{
				if (grMovePlaneInHorizontal >= 1.8f)
					grMovePlaneInHorizontal = grMovePlaneInHorizontal + 0.0002f;
				else
					grMovePlaneInHorizontal = grMovePlaneInHorizontal + 0.00005f;
			}

			if (x <= (((PI * radius) / 2) + ((PI * radius) / 4)))
			{
				x = x + 0.0000250f;
			}
			else
			{
				grMoveOrangePlaneInHorizontal = grMoveOrangePlaneInHorizontal + 0.00005f;
				if (grMoveOrangePlaneInHorizontal >= 4.5f)
				{
					if (x <= (2 * PI))
					{
						x = x + 0.0001f;
					}
					if (grbRotateOrangePlane == true)
					{
						if (grangleOrangePlane <= 450.0f)
						{

							grangleOrangePlane = grangleOrangePlane + 0.005f;
						}

					}

				}
			}

			if (y <= (((PI * radius) / 2) + ((PI * radius) / 4)))
			{
				y = y + 0.00001850;
			}
			else
			{
				grMoveGreenPlaneInHorizontal = grMoveGreenPlaneInHorizontal + 0.00005f;
				if (grMoveGreenPlaneInHorizontal >= 2.0f)
				{

					if (y <= (2 * PI))
					{
						y = y + 0.0001f;
					}
					if (grangleGreenPlane >= -90.0f)
					{
						grangleGreenPlane = grangleGreenPlane - 0.005f;
					}


				}

			}


			if (grbRotateOrangePlane == false)
			{
				if (grangleOrangePlane <= 360.0f)
				{
					grangleOrangePlane = grangleOrangePlane + 0.00150f;
				}
				else
				{
					grbRotateOrangePlane = true;
				}
			}


			if (grbRotateGreenPlane == false)
			{
				if (grangleGreenPlane >= 0.0f)
					grangleGreenPlane = grangleGreenPlane - 0.00140f;
				else
					grbRotateGreenPlane = true;
			}

		}
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









































