#include<windows.h>
#include<stdio.h>
#include<GL\gl.h>
#include"GRWindow.h"

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
				100,
				100,
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
	//void Display(void);
	
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
		/*	
		case WM_PAINT :
			Display();
			break;
		*/
			
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
	grpfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
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
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	
	// warmup call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{
	if(height == 0)
		height = 1;
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void Display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	
	glFinish();
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

/* compile and linking *
cl.exe /c /EHsc OGLBlueWindowNewCode_Changed.cpp
rc.exe GRWindow.rc
link.exe OGLBlueWindowNewCode_Changed.obj GRWindow.res user32.lib kernel32.lib gdi32.lib /SUBSYSTEM:WINDOWS
OGLBlueWindowNewCode_Changed.exe
*/







