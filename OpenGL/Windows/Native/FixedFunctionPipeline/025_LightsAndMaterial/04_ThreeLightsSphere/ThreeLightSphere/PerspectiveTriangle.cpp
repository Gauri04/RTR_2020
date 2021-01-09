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

// project specific variables
bool grgbLight = false;
GLUquadric *grquadric = NULL;

GLfloat grlightAmbientZero[] =
{ 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat grlightDiffuseZero[] =
{ 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat grlightSpecularZero[] =
{ 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat grlightPositionZero[] =
{ 0.0f, 0.0f, 0.0f, 1.0f };				// positional light


GLfloat grlightAmbientOne[] =
{ 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat grlightDiffuseOne[] =
{ 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat grlightSpecularOne[] =
{ 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat grlightPositionOne[] =
{ 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat grlightAmbientTwo[] =
{ 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat grlightDiffuseTwo[] =
{ 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat grlightSpecularTwo[] =
{ 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat grlightPositionTwo[] =
{ 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat grmaterialAmbient[] =
{ 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat grmaterialDiffuse[] =
{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat grmaterialShininess = 50.0f;

GLfloat grlightAngle0 = 0.0f;
GLfloat grlightAngle1 = 0.0f;
GLfloat grlightAngle2 = 0.0f;

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
			
		case WM_CHAR:
			switch (wParam)
			{
			case 'l':
			case 'L':
				grgbLight = !grgbLight;
				if (grgbLight == true)
				{
					glEnable(GL_LIGHTING);
				}
				else
				{
					glDisable(GL_LIGHTING);
				}
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
	
	// Depth
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	// lights initialization
	glLightfv(GL_LIGHT0, GL_AMBIENT, grlightAmbientZero);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, grlightDiffuseZero);
	glLightfv(GL_LIGHT0, GL_SPECULAR, grlightSpecularZero);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, grlightAmbientOne);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, grlightDiffuseOne);
	glLightfv(GL_LIGHT1, GL_SPECULAR, grlightSpecularOne);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, grlightAmbientTwo);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, grlightDiffuseTwo);
	glLightfv(GL_LIGHT2, GL_SPECULAR, grlightSpecularTwo);
	glEnable(GL_LIGHT2);


	// material initialization
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, grmaterialShininess);

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
	// function declaration
	void Update(void);
	
	// code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	gluLookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// first light - red
	glPushMatrix();
	glRotatef(grlightAngle0, 1.0f, 0.0f, 0.0f);
	grlightPositionZero[1] = grlightAngle0;
	glLightfv(GL_LIGHT0, GL_POSITION, grlightPositionZero);
	glPopMatrix();

	// second light - green
	glPushMatrix();
	glRotatef(grlightAngle1, 0.0f, 1.0f,  0.0f);
	grlightPositionOne[2] = grlightAngle1;
	glLightfv(GL_LIGHT1, GL_POSITION, grlightPositionOne);
	glPopMatrix();

	glPushMatrix();
	glRotatef(grlightAngle2, 0.0f, 0.0f, 1.0f);
	grlightPositionTwo[1] = grlightAngle2;
	glLightfv(GL_LIGHT2, GL_POSITION, grlightPositionTwo);
	glPopMatrix();
	
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	grquadric = gluNewQuadric();
	gluSphere(grquadric, 0.2, 50, 50);
	glPopMatrix();

	// normals are calculated by glu library, we dont need to calculate normals explicitely

	Update();
	SwapBuffers(grghdc);
}

void Update()
{
	grlightAngle0 = grlightAngle0 + 0.5f;
	if (grlightAngle0 >= 360.0f)
		grlightAngle0 = 0.0f;

	grlightAngle1 = grlightAngle1 + 0.5f;
	if (grlightAngle1 >= 360.0f)
		grlightAngle1 = 0.0f;

	grlightAngle2 = grlightAngle2 + 0.5f;
	if (grlightAngle2 >= 360.0f)
		grlightAngle2 = 0.0f;

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
	
	if (grquadric)
	{
		gluDeleteQuadric(grquadric);
		grquadric = NULL;
	}
}









