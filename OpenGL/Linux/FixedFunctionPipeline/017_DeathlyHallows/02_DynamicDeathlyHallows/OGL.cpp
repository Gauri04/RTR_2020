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
	// function declaration
	void Update(void);

	// local variable delaration
	GLdouble gri, grs;
	const GLdouble PI = 3.14159655359f;
	GLdouble grlength1, grlength2, grlength3;
	GLdouble grradius;
	GLdouble grincenterX, grincenterY;
	GLdouble sqrt;
	GLdouble grbase, grheight, grarea;

	// code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	////////////////////////////////////////////////////// STONE ///////////////////////////////////////////////////////////////
	glLoadIdentity();

	glTranslatef(grmoveStoneX, grmoveStoneY, -6.0f);
	glRotatef(grangleStone, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 1.0f, 0.0f);	// ax, ay
	glVertex3f(-1.0f, -1.0f, 0.0f);	// bx, by
	glVertex3f(1.0f, -1.0f, 0.0f);	// cx, cy	
	glVertex3f(0.0f, 1.0f, 0.0f);	// ax, ay
	glEnd();

	////////////////////////////////////////////////////// CLOAK ///////////////////////////////////////////////////////////////
	/*** Formula for incircle ****/
	// calculate length between the coordinates of triangle
	// distance between ax,ay and bx, by : bx-ax, by-ay (bx = -1.0, by = -1.0) (ax = 0.0, ay = 1.0) VERTEX B
	grlength3 = sqrtl(pow((-1.0f - 0.0f), 2) + pow((-1.0f - 1.0f), 2));
	// distance between bx, by and cx, cy : cx-bx, cy- by (cx = 1.0, cy = -1.0) (bx = -1.0, by = -1.0) VERTEX A
	grlength1 = sqrtl(pow((1.0f + 1.0f), 2) + pow((-1.0f + 1.0f), 2));
	// distance between ax, ay and cx, cy : cx-ax, cy-ay (cx = 1.0, cy = -1.0) (ax = 0.0, ay = 1.0) VERTEX C
	grlength2 = sqrtl(pow((1.0 - 0.0), 2) + pow((-1.0 - 1.0), 2));

	// x = (ax*length1 + bx*length2 + cx*length3) / length1 + length2 + length3 
	grincenterX = ((0.0f * grlength1) + (-1.0f * grlength2) + (1.0f * grlength3)) / (grlength1 + grlength2 + grlength3);
	// y = (ay*length + by*length + cy*length) / 3*length
	grincenterY = ((1.0f * grlength1) + (-1.0f * grlength2) + (-1.0f * grlength3)) / (grlength1 + grlength2 + grlength3);

	// s = (length1 + length2 + length3) / 2
	grs = (grlength1 + grlength2 + grlength3) / 2;

	/*	commented the formula for radius from wikipedia
	// radius = (sqrt(s * (s - length1) * (s - length2) * (s - length3))) / s
	sqrt = grs * (grs - grlength1) * (grs - grlength2) * (grs - grlength3);
	fprintf(grgpFile, "\n sqrt : %lf", sqrt);
	sqrt = sqrtl(sqrt);
	grradius = sqrt / grs;
	*/

	grbase = 2;
	grheight = 2;
	grarea = (2 * 2) / 2;
	grradius = grarea / grs;

	glLoadIdentity();
	glTranslatef(grmoveCloakX, grmoveCloakY, -6.0f);
	glRotatef(grangleCloak, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	//fprintf(grgpFile, "\n incenter x = %lf incenter y = %lf, radius = %lf, length1 = %lf, length2 : %lf, length3 : %lf, s : %lf, sqrt : %lf", grincenterX, grincenterY, grradius, grlength1, grlength2, grlength3, grs, sqrt);
	glBegin(GL_POINTS);
	for (gri = 0.0f; gri <= (2 * PI); gri = gri + 0.005)
	{
		//glVertex2d(grincenterX, grincenterY);
		glVertex2d((grincenterX + (grradius * cos(gri))), grincenterY + (grradius * sin(gri)));
	}
	glEnd();

	////////////////////////////////////////////////////// WAND ///////////////////////////////////////////////////////////////

	glLoadIdentity();
	glTranslated(0.0f, grmoveWandY, -6.0);
	glRotatef(grangleWand, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();

	Update();

	glXSwapBuffers(gpDisplay, gWindow);

}

void Update(void)
{

	if (grmoveStoneX <= 0.0f && grmoveStoneY <= 0.0f)
	{

		grmoveStoneX = grmoveStoneX + 0.000150f;
		grmoveStoneY = grmoveStoneY + 0.00010f;
		if (grangleStone >= 360.0f)
		{
			grangleStone = 0.0f;
		}
		grangleStone = grangleStone + 0.0090f;
	}

	if (grmoveCloakX >= 0.0f && grmoveCloakY >= 0.0f)
	{
		grmoveCloakX = grmoveCloakX - 0.000150f;
		grmoveCloakY = grmoveCloakY - 0.00010f;
		if (grangleCloak >= 360.0f)
		{
			grangleCloak = 0.0f;
		}
		grangleCloak = grangleCloak + 0.0180f;

	}

	if (grmoveWandY >= 0.0f)
	{
		grmoveWandY = grmoveWandY - 0.0001f;
		if (grangleWand >= 360.0f)
		{
			grangleWand = 0.0f;
		}
		grangleWand = grangleWand + 0.04090f;
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









































