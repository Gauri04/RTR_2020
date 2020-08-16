#include<windows.h>
#include<stdio.h>
#include<GL\gl.h>
#include"GRWindow.h"
#include<cmath>
#include<mmsystem.h>
#include<GL\Glu.h>
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global fuctions declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// global variables declaration
DWORD grdwStyle;
WINDOWPLACEMENT grwpPrev = { sizeof(WINDOWPLACEMENT) };
bool grgbFullScreen = false;
HWND grghwnd = NULL;
bool grgbActiveWindow = false;
HDC grghdc = NULL;
HGLRC grghrc = NULL;
FILE *grgpFile = NULL;

bool grbFullScreen = false;
const float grPI = 3.142f;
float gri;
float grSmileyEyes = 0.9f;
bool grEyeFlag = false;
float grZCoord = -15.0f;
bool grZoomFlag = false;
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
	TCHAR szAppName[] = TEXT("OGLBlueWindow");
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
				TEXT("OpenGL Blue window"),
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
			
		case WM_CHAR : 
			switch(wParam)
			{
				case 'g':
					PlaySound(TEXT("walle2.wav"), NULL, SND_FILENAME | SND_ASYNC);
					grEyeFlag = true;
					grSmileyEyes = 0.9f;
					break;
			
				case 'h':
					grSmileyEyes = 0.9f;
					break;
			
				case 'z' :
					grZoomFlag = true;
					break;
			
				default:
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
			if( GetWindowPlacement(grghwnd, &grwpPrev) && GetMonitorInfo(MonitorFromWindow(grghwnd, MONITORINFOF_PRIMARY), &mi) )
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
		SetWindowPlacement(grghwnd, &grwpPrev);
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
	
		
	gluPerspective(45.0f, (GLfloat) width/ (GLfloat) height, 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void Display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/* ******* Code for Walle *******/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*** CIRCLE CODE ***/
	// white face
	glLoadIdentity();
	glTranslatef(0.0f, 1.0f, grZCoord);
	glScalef(0.5f, 0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
			if(gri <= (grPI + 0.1))
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1.35*cos(gri)), (1.3*sin(gri)), 0.0f);
			}
		}
	glEnd();
	
	// white face remaining line color
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.35f, 0.0f);
	glEnd();
		
	
	
	glLoadIdentity();
	glTranslatef(0.0f, 1.0f, grZCoord);
	glScalef(0.5f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1.35*cos(gri)), (1.0*sin(gri)), 0.0f);
		}
	glEnd();
	
	// black face

	glLoadIdentity();
	glTranslatef(0.0f, 0.98f, grZCoord);
	glScalef(0.4f, 0.4f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
			if(gri <= (grPI + 0.1))
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1.35*cos(gri)), (1.0*sin(gri)), 0.0f);
			}
		}
	glEnd();
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.97f, grZCoord);
	glScalef(0.4f, 0.2f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1.35*cos(gri)), (0.9*sin(gri)), 0.0f);
		}
	glEnd();

		// white face remaining line color
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.35f, 0.0f);
	glEnd();
	
	
	// eyes
	glLoadIdentity();
	glTranslatef(-0.2f, 1.07f, grZCoord);
	glScalef(0.15f, 0.1f, 0.0f);
	glRotatef(40, 1.0f, -0.35f, 0.0f);
	glColor3f(0.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
		}
	glEnd();
	
	glLoadIdentity();
	glTranslatef(0.2f, 1.07f, grZCoord);
	glScalef(0.15f, 0.1f, 0.0f);
	glRotatef(40, 1.0f, 0.35f, 0.0f);
	glColor3f(0.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
		}
	glEnd();
	
	
	// smiley eyes
	glLoadIdentity();
	glTranslatef(-0.2f, grSmileyEyes, grZCoord);
	glScalef(0.15f, 0.1f, 0.0f);
	glRotatef(40, 1.0f, -0.35f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
		}
	glEnd();
	
	glLoadIdentity();
	glTranslatef(0.2f, grSmileyEyes, grZCoord);
	glScalef(0.15f, 0.1f, 0.0f);
	glRotatef(40, 1.0f, 0.35f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
		}
	glEnd();
	
	// hands
	glLoadIdentity();
	glTranslatef(0.0f, 0.56f, grZCoord);
	glScalef(0.9f, 1.6f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
			if(gri > grPI && gri < (2 * grPI))
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
			}
		}
	glEnd();
	
	// space between hands and body
	glLoadIdentity();
	glTranslatef(0.0f, 0.7f, grZCoord);
	glScalef(0.78f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
			if(gri > grPI && gri < (2 * grPI))
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
			}
		}
	glEnd();
	
	
	// body
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.65f, grZCoord);
	glScalef(0.66f, 1.7f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
			if(gri > grPI && gri < (2 * grPI))
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
			}
		}
	glEnd();
	
	
	
	// space between hands and body
	glLoadIdentity();
	glTranslatef(0.0f, 0.7f, grZCoord);
	glScalef(1.0f, 0.125f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
		for(float gri = 0; gri <= 2*grPI*1; gri = gri + 0.01f)
		{
			if(gri > grPI && gri < (2 * grPI))
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((1*cos(gri)), (1*sin(gri)), 0.0f);
			}
		}
	glEnd();
			
	if(grZoomFlag == true)
	{
		if(grZCoord < -6.0f)
			grZCoord = grZCoord + 0.06;
	}
	if(grEyeFlag == true)
	{
		if(grSmileyEyes < 1.009f)
			grSmileyEyes = grSmileyEyes + 0.004;
		
		else
			grEyeFlag = false;
	}
	SwapBuffers(grghdc);
}

void Uninitialize(void)
{
	//code
	if(grgbFullScreen == true)
	{
		grdwStyle = GetWindowLong(grghwnd, GWL_STYLE);
		SetWindowLong(grghwnd, GWL_STYLE, (grdwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(grghwnd, &grwpPrev);
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









