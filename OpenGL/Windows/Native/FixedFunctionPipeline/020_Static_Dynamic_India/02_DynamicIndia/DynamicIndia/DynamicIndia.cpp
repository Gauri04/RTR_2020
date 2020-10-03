#include<windows.h>
#include<stdio.h>
#include<GL\gl.h>
#include<GL\Glu.h>	// graphic library utility
#include"GRIcon.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Glu32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global fuctions declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// global variables declaration
DWORD grdwStyle;
WINDOWPLACEMENT grgwpPrev = { sizeof(WINDOWPLACEMENT) };
bool grgbFullScreen = false;
HWND grghwnd = NULL;
bool grgbActiveWindow = false;
HDC grghdc = NULL;
HGLRC grghrc = NULL;
FILE *grgpFile = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declaration
	void Initialize(void);
	void Display(void);
	
	// variables declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("OGL");
	int grDesktopWidth, grDesktopHeight;
	int grWndXPos, grWndYPos;
	bool grbDone = false;
	
	if(fopen_s(&grgpFile, "GRLog.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Cannot open desired file"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(grgpFile, "Log file created successfully. \n Program started successfully\n **** Logs ***** \n");
	}
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(GRICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(GRICON));
	
	RegisterClassEx(&wndclass);
	
	// Get width and height of desktop screen
	grDesktopWidth = GetSystemMetrics(SM_CXSCREEN);
	grDesktopHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// Get center horizontal point
	grDesktopWidth = grDesktopWidth / 2;
	// Get center vertical point
	grDesktopHeight = grDesktopHeight / 2;
	
	// X position = center horizontal coordinate of screen - center horizontal coordinate of window
	grWndXPos = grDesktopWidth - 400;
	
	// X position = center horizontal coordinate of screen - center horizontal coordinate of window
	grWndYPos = grDesktopHeight - 300;
	
	
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
				szAppName,
				TEXT("OpenGL"),
				WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
				grWndXPos,
				grWndYPos,
				WIN_WIDTH,
				WIN_HEIGHT,
				NULL,
				NULL,
				hInstance,
				NULL);
				
	grghwnd = hwnd;
	
	Initialize();
	
	ShowWindow(hwnd, iCmdShow);
	
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	
	while(grbDone == false)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			grbDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(grgbActiveWindow == true)
			{
				//update function
				
				//display function
				Display();
			}
		}
		
	}
	
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declaration
	void ToggleFullScreen(void);
	void Resize(int, int);
	void Uninitialize(void);
	
	switch(iMsg)
	{
		case WM_SETFOCUS : 
			grgbActiveWindow = true;
			break;
			
		case WM_KILLFOCUS :
			grgbActiveWindow = false;
			break;
			
		case WM_ERASEBKGND :
			return(0);
		
			
		case WM_SIZE :
			Resize(LOWORD(lParam), HIWORD(lParam));
			break;
		
		case WM_KEYDOWN : 
			switch(wParam)
			{
				case VK_ESCAPE :
					DestroyWindow(hwnd);
					break;
				
				case 0x46 : 
				case 0x66 :
					ToggleFullScreen();
					break;
				
				default : 
					break;
			}
			break;
			
		case WM_CLOSE :
			DestroyWindow(hwnd);
			break;
		
		case WM_DESTROY :
			Uninitialize();
			PostQuitMessage(0);
			break;
		
	}
	
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen()
{
	MONITORINFO mi = { sizeof(MONITORINFO) };
	
	if(grgbFullScreen == false)
	{
		grdwStyle = GetWindowLong(grghwnd, GWL_STYLE);
		if(grdwStyle & WS_OVERLAPPEDWINDOW)
		{
			if( GetWindowPlacement(grghwnd, &grgwpPrev) && GetMonitorInfo(MonitorFromWindow(grghwnd, MONITORINFOF_PRIMARY), &mi) )
			{
				SetWindowLong( grghwnd, GWL_STYLE, (grdwStyle & ~ WS_OVERLAPPEDWINDOW) );
				SetWindowPos( grghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
					(mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top), SWP_NOZORDER | SWP_FRAMECHANGED );
			}
		}
		ShowCursor(false);
		grgbFullScreen = true;
	}
	else
	{
		SetWindowLong( grghwnd, GWL_STYLE, (grdwStyle | WS_OVERLAPPEDWINDOW) );
		SetWindowPlacement(grghwnd, &grgwpPrev);
		SetWindowPos(grghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(true);
		grgbFullScreen = false;
	}
}

void Initialize()
{
	// function declaration
	void Resize(int, int);
	
	//variable declarations
	PIXELFORMATDESCRIPTOR grpfd;
	int griPixelFormatIndex;
	
	//code
	grghdc = GetDC(grghwnd);
	
	ZeroMemory(&grpfd, sizeof(PIXELFORMATDESCRIPTOR));
	grpfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	grpfd.nVersion = 1;
	grpfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	grpfd.iPixelType = PFD_TYPE_RGBA;
	grpfd.cColorBits = 32;
	grpfd.cRedBits = 8;
	grpfd.cGreenBits = 8;
	grpfd.cBlueBits = 8;
	grpfd.cAlphaBits = 8;
	
	griPixelFormatIndex = ChoosePixelFormat(grghdc, &grpfd);
	if(griPixelFormatIndex == 0)
	{
		fprintf(grgpFile, "ChoosePixelFormat() failed\n");
		DestroyWindow(grghwnd);
	}
	
	if(SetPixelFormat(grghdc, griPixelFormatIndex, &grpfd) == FALSE)
	{
		fprintf(grgpFile, "SetPixelFormat() failed\n");
		DestroyWindow(grghwnd);
	}
	
	grghrc = wglCreateContext(grghdc);
	if(grghrc == NULL)
	{
		fprintf(grgpFile, "wglCreateContext() failed\n");
		DestroyWindow(grghwnd);
	}
	
	if(wglMakeCurrent(grghdc, grghrc) == FALSE)
	{
		fprintf(grgpFile, "wglMakeCurrent() failed\n");
		DestroyWindow(grghwnd);
	}
	
	// set clearcolor
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// warm-up call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{
	if(height == 0)
		height = 1;
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	
}

void Display(void)
{
	// code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//////////////////////////////////////////////////////////// I ////////////////////////////////////////////////////////////////
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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
	glMatrixMode(GL_MODELVIEW);
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



	SwapBuffers(grghdc);
}

void Uninitialize(void)
{
	//code
	if(grgbFullScreen == true)
	{
		grdwStyle = GetWindowLong(grghwnd, GWL_STYLE);
		SetWindowLong(grghwnd, GWL_STYLE, (grdwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(grghwnd, &grgwpPrev);
		SetWindowPos(grghwnd, HWND_TOP, 0, 0, 0, 0, 
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(true);
		
	}
	if(wglGetCurrentContext() == grghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}
		
	if(grghrc)
	{
		wglDeleteContext(grghrc);
		grghrc = NULL;
	}
		
	if(grghdc)
	{
		ReleaseDC(grghwnd, grghdc);
		grghdc = NULL;
	}
		
	if(grgpFile)
	{
		fprintf(grgpFile, "\n **** End ****\nLog File closed successfully. \n Program terminated successfully");
		fclose(grgpFile);
		grgpFile = NULL;
	}
}









