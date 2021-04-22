#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>

using namespace std;

bool bFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColormap;
Window gWindow;
int giWindowWidth = 800;
int giWindowHeight = 600;
static XFontStruct *grpXFontStruct = NULL;
static GC grgc;
XGCValues grgcValues;						// similar to PAINTSTRUCT ps
XColor grgreenColor;
char grstr[] = "Hello World from Gauri Ranade";
int grstringLength;
int grstringWidth;
int grfontHeight;

int main()
{
	void CreateWindow();
	void ToggleFullscreen();
	void Uninitialize();
	int winWidth = giWindowWidth;
	int winHeight = giWindowHeight;
	
	CreateWindow();
	
	XEvent event;
	KeySym keysym;
	
	while(1)
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
						XFreeGC(gpDisplay, grgc);
						Uninitialize();
						exit(0);
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
				
			case ConfigureNotify:
				winWidth = event.xconfigure.width;
				winHeight = event.xconfigure.height;
				break;
				
			case Expose:										// similar to WM_PAINT
				grgc = XCreateGC(gpDisplay, gWindow, 0, &grgcValues);
				XSetFont(gpDisplay, grgc, grpXFontStruct->fid);
				XAllocNamedColor(gpDisplay, gColormap, "green", &grgreenColor, &grgreenColor);
				XSetForeground(gpDisplay, grgc, grgreenColor.pixel);
				grstringLength = strlen(grstr);
				grstringWidth = XTextWidth(grpXFontStruct, grstr, grstringLength);
				grfontHeight = grpXFontStruct->ascent + grpXFontStruct->descent;

				XDrawString(gpDisplay, gWindow, grgc, (winWidth / 2 - grstringWidth / 2), (winHeight / 2 - grfontHeight / 2), grstr, grstringLength);

				break;
				
			case DestroyNotify:
				break;
				
			case 33:
				XUnloadFont(gpDisplay, grpXFontStruct->fid);
				XFreeGC(gpDisplay, grgc);
				Uninitialize();
				exit(0);
			default :
				break;
		}
	}
	
	Uninitialize();
	return(0);
}


void CreateWindow()
{
	void Uninitialize();
	
	XSetWindowAttributes winAttribs;
	int defaultScreen;
	int defaultDepth;
	int styleMask;
	
	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL)
	{
		printf("\n unable to open XDisplay.. Exiting now...");
		Uninitialize();
		exit(1);
	}
	
	defaultScreen = XDefaultScreen(gpDisplay);
	defaultDepth =DefaultDepth(gpDisplay, defaultScreen);
	gpXVisualInfo = (XVisualInfo *) malloc(sizeof(XVisualInfo));
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
	
	XStoreName(gpDisplay, gWindow, "First XWindow");
	
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

void Uninitialize()
{
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










































