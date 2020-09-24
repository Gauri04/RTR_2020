#include<windows.h>
#include<stdio.h>
#include<GL\gl.h>
#include<GL\Glu.h>
#include"GRWindow.h"
#include<cmath>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Glu32.lib")

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

// variables for sun and moon
const float pi = 3.142f;			// for circle
bool bDay = false;
float colorGreen = 0.0f;
float colorRed = 0.0f;
float colorSun = 0.0f;
float moonSunY = -2.3f;				// y location of sun and moon
float colorLand = 0.0f;				
float colorBlue = 0.0f;
bool bClouds = false;
float alphaCloud = 0.0f;
bool startAnimation = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declaration
	void Initialize(void);
	void Display(void);
	
	// variables declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("NightAndDay");
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
				TEXT("OGLNightAndDay"),
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
				
				case VK_SPACE :
					PlaySound("Finding_Nemo_Soundtrack.wav", NULL, SND_FILENAME | SND_ASYNC);
					startAnimation = true;
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
	
	// warmup call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{
	if(height == 0)
		height = 1;
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{
	// code
	if(startAnimation == true)
	{
		if(bDay == false)
		{
			//code
			glClearColor(colorRed, colorGreen, colorBlue, 0.0f);
			//to clear all pixels
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Stars	
			glLoadIdentity();
			glTranslatef(-6.0f, -2.0f, -6.0f);
			glScalef(0.3f, 0.3f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glLineWidth(3.0f);
			for(int i=0; i < 10000; i++)
			{
		
				glBegin(GL_LINES);
					int x = rand() % 1366;
					int y = rand() % 768;
					glVertex2f(x, y);
					glVertex2f(x -0.19f, y + 0.19f);
				
					glVertex2f(x - 0.19f, y);
					glVertex2f(x, y + 0.19f);
				glEnd();
			}
	
			// Moon
			glLoadIdentity();
			glTranslatef(3.0f, moonSunY, -6.0f);
			glScalef(0.3f, 0.3f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_TRIANGLE_STRIP);

				for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
		
			glLoadIdentity();
			glTranslatef(3.0f, moonSunY, -6.0f);
			glScalef(0.28f, 0.28f, 0.0f);
			glColor3f(0.8f, 0.8f, 0.8f);
			glBegin(GL_TRIANGLE_STRIP);

				for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
		
			//Line covers moon's uncolored part 

			glLineWidth(2.0f);
			glBegin(GL_LINES);
				glVertex2f(0.0f, 0.0f);
				glVertex2f(1.0f, 0.0f);
			glEnd();
	
		}
	
		else if(bDay == true)
		{
			glClearColor(colorRed, colorGreen, colorBlue, 0.0f);
			//to clear all pixels
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
			// Sun3 border
			glLoadIdentity();
			glTranslatef(-2.8f, moonSunY, -6.0f);
			glScalef(0.3f, 0.3f, 0.0f);
			glColor3f(1.0f, 0.5f, 0.0f);
			glLineWidth(2.5);
			glBegin(GL_LINES);

				for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
		
			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_LINES);
				glVertex2f(0.0f, 0.0f);
				glVertex2f(1.0f, 0.0f);
			glEnd();
		
		
			// Sun2 border
			glLoadIdentity();
			glTranslatef(-2.8f, moonSunY, -6.0f);
			glScalef(0.28f, 0.28f, 0.0f);
			glColor3f(1.0f, 0.9f, 0.0f);
			glLineWidth(2.5);
			glBegin(GL_LINES);

				for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
			
		
			//Sun1
			glLoadIdentity();
			glTranslatef(-2.8f, moonSunY, -6.0f);
			glScalef(0.27f, 0.27f, 0.0f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLE_STRIP);
	
				for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
				}
			glEnd();
		
			if(bClouds == true)
			{
				// 1st cloud
				//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			
				glLoadIdentity();
				glTranslatef(0.4f, 1.5f, -6.0f);
				glScalef(0.27f, 0.27f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
			
				glLoadIdentity();
				glTranslatef(0.8f, 1.5f, -6.0f);
				glScalef(0.27f, 0.27f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
			
				glLoadIdentity();
				glTranslatef(1.1f, 1.4f, -6.0f);
				glScalef(0.25f, 0.27f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
			
				glLoadIdentity();
				glTranslatef(0.75f, 1.35f, -6.0f);
				glScalef(0.25f, 0.27f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((2.15*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
			
				glLineWidth(2.0f);
				glBegin(GL_LINES);
					glVertex2f(0.0f, 0.0f);
					glVertex2f(2.3f, 0.0f);
				glEnd();
			
			
				// 2nd cloud
				glColor3f(1.0f, 1.0f, 1.0f);
			
				glLoadIdentity();
				glTranslatef(2.4f, 1.7f, -6.0f);
				glScalef(0.23f, 0.23f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
			
				glLoadIdentity();
				glTranslatef(2.7f, 1.6f, -6.0f);
				glScalef(0.23f, 0.23f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
			
				glLoadIdentity();
				glTranslatef(3.0f, 1.55f, -6.0f);
				glScalef(0.21f, 0.21f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((1*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
			
				glLoadIdentity();
				glTranslatef(2.7f, 1.53f, -6.0f);
				glScalef(0.21f, 0.23f, 0.0f);
				glBegin(GL_TRIANGLE_STRIP);
					for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
					{
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f((2.25*cos(i)), (1*sin(i)), 0.0f);
					}
				glEnd();
				//glDisable(GL_BLEND);
						
			}
		

		}
	
		//Land / grass hill
		//1 border
		glLoadIdentity();
		glTranslatef(-3.0f, -2.0f, -6.0f);
		glScalef(1.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.2f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
	
			for(float i = 0; i <= 2*pi*1; i = i + 0.0001f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((2.5*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
	
		//2 border
		glLoadIdentity();
		glTranslatef(2.6f, -2.0f, -6.0f);
		glScalef(1.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.2f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.0001f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((4.0*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
	
		//3 border
		glLoadIdentity();
		glTranslatef(-1.0f, -2.0f, -6.0f);
		glScalef(1.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.2f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.0001f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((3.0*cos(i)), (1.5*sin(i)), 0.0f);
			}
		glEnd();
	
	
	
		//1
		glLoadIdentity();
		glTranslatef(-3.0f, -2.0f, -6.0f);
		glColor3f(0.0f, colorLand, 0.0f);
		glScalef(0.99f, 0.99f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);

				for(float i = 0; i <= 2*pi*1; i = i + 0.0001f)
				{
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((2.5*cos(i)), (1*sin(i)), 0.0f);
				}
		glEnd();
	

		//2
		glLoadIdentity();
		glTranslatef(2.6f, -2.0f, -6.0f);
		glColor3f(0.0f, colorLand, 0.0f);
		glScalef(0.99f, 0.99f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
	
			for(float i = 0; i <= 2*pi*1; i = i + 0.0001f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((4.0*cos(i)), (1*sin(i)), 0.0f);
			}
		glEnd();
	
	
		//3
		glLoadIdentity();
		glTranslatef(-1.0f, -2.0f, -6.0f);
		glColor3f(0.0f, colorLand, 0.0f);
		glScalef(0.99f, 0.99f, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);

			for(float i = 0; i <= 2*pi*1; i = i + 0.001f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f((3.0*cos(i)), (1.5*sin(i)), 0.0f);
			}
		glEnd();
		
		// translations and move
		if(colorLand <= 1.0f)
			colorLand = colorLand + 0.00015f;
	
		// start Animation of day when color gets black 
	
		if(bDay == true)
		{
			if(moonSunY < 0.9f)
			{
				//colorBlue = colorBlue - 0.006f;
				colorRed = colorRed + 0.001f;
				colorGreen = colorGreen + 0.0004f;
				moonSunY = moonSunY + 0.003f;
			}
			else
			{
			
				if(colorBlue < 0.8f)
				{
					colorBlue = colorBlue + 0.0035f;
					colorRed = colorRed - 0.0035f;
					moonSunY = moonSunY + 0.003f;
				}
				else
				{
					bClouds = true;
					//if(alphaCloud < 1.0f)
						//alphaCloud = alphaCloud + 0.05;
				}
			}
		}
		else															// code for night
		{
		
			if(moonSunY < 2.8f)
			{
				colorRed = colorRed + 0.00005f;
				colorGreen = colorGreen + 0.00005f;
				colorBlue = colorBlue + 0.00005f;
				moonSunY = moonSunY + 0.003f;
			}
			else
			{
				bDay = true;
				moonSunY = -1.8f;
			}
		}
	
		
	}
	
	else
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
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








