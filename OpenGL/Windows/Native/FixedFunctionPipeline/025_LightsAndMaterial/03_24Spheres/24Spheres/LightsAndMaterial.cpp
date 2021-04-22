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
FILE* grgpFile = NULL;

// project specific variables
int i, j;
bool grgbLight = false;


GLfloat grlightAmbient[] =
{
	0.0f, 0.0f, 0.0f, 1.0f
};
GLfloat grlightDiffuse[] =
{
	1.0f, 1.0f, 1.0f, 1.0f
};
//GLfloat grlightSpecular[] =
//{
//	1.0f, 1.0f, 1.0f, 1.0f
//};
GLfloat grlightPosition[] =
{
	0.0f, 3.0f, 3.0f, 0.0f
};

GLfloat grlight_model_ambient[] =
{
	0.2f, 0.2f, 0.2f, 1.0f
};

GLfloat grlight_model_local_viewer[] =
{
	0.0f
};

GLfloat grangleForXRotation = 0.0f;
GLfloat grangleForYRotation = 0.0f;
GLfloat grangleForZRotation = 0.0f;




/*
GLfloat grmaterialAmbient[] =
{
	0.0f, 0.0f, 0.0f, 1.0f
};
GLfloat grmaterialDiffuse[] =
{
	0.5f, 0.2f, 0.7f, 1.0f
};
GLfloat grmaterialSpecular[] =
{
	0.7f, 0.7f, 0.7f, 1.0f
};
GLfloat grmaterialShinyness = 128.0f;
*/
GLUquadric* grquadric[24];
GLint grkeyPress = 0;


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

	if (fopen_s(&grgpFile, "GRLog.txt", "w") != 0)
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

	while (grbDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				grbDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (grgbActiveWindow == true)
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

	switch (iMsg)
	{
	case WM_SETFOCUS:
		grgbActiveWindow = true;
		break;

	case WM_KILLFOCUS:
		grgbActiveWindow = false;
		break;

	case WM_ERASEBKGND:
		return(0);


	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;

		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;

		default:
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

		case 'x':
		case 'X':
			grkeyPress = 1;
			grangleForXRotation = 0.0f;
			break;

		case 'y':
		case 'Y':
			grkeyPress = 2;
			grangleForYRotation = 0.0f;
			break;

		case 'z':
		case 'Z':
			grkeyPress = 3;
			grangleForZRotation = 0.0f;
			break;

		default :
			break;
		}
		break;


	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		Uninitialize();
		PostQuitMessage(0);
		break;

	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen()
{
	MONITORINFO mi = { sizeof(MONITORINFO) };

	if (grgbFullScreen == false)
	{
		grdwStyle = GetWindowLong(grghwnd, GWL_STYLE);
		if (grdwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(grghwnd, &grgwpPrev) && GetMonitorInfo(MonitorFromWindow(grghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(grghwnd, GWL_STYLE, (grdwStyle & ~WS_OVERLAPPEDWINDOW));
				SetWindowPos(grghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
					(mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top), SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(false);
		grgbFullScreen = true;
	}
	else
	{
		SetWindowLong(grghwnd, GWL_STYLE, (grdwStyle | WS_OVERLAPPEDWINDOW));
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
	if (griPixelFormatIndex == 0)
	{
		fprintf(grgpFile, "ChoosePixelFormat() failed\n");
		DestroyWindow(grghwnd);
	}

	if (SetPixelFormat(grghdc, griPixelFormatIndex, &grpfd) == FALSE)
	{
		fprintf(grgpFile, "SetPixelFormat() failed\n");
		DestroyWindow(grghwnd);
	}

	grghrc = wglCreateContext(grghdc);
	if (grghrc == NULL)
	{
		fprintf(grgpFile, "wglCreateContext() failed\n");
		DestroyWindow(grghwnd);
	}

	if (wglMakeCurrent(grghdc, grghrc) == FALSE)
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



	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	// Light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, grlight_model_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, grlight_model_local_viewer);


	glLightfv(GL_LIGHT0, GL_AMBIENT, grlightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, grlightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, grlightPosition);
	glEnable(GL_LIGHT0);
	

	/*
	// material
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, grmaterialShinyness);
	glEnable(GL_LIGHT1);
	*/

	for (i = 0; i < 24; i++)
	{
		grquadric[i] = gluNewQuadric();
	}

	// set clearcolor
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	// warm-up call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height)
	{
		glOrtho(-100.0f,
			100.0f,
			-100.0f * ((GLfloat)height / (GLfloat)width),
			100.0f * ((GLfloat)height / (GLfloat)width),
			-100.0f,
			100.0f);
	}
	else
	{
		glOrtho(0.0f * ((GLfloat)width / (GLfloat)height),	//left
			15.5f * ((GLfloat)width / (GLfloat)height),	//right
			0.0f,									//bottom
			15.5f,										//top
			-10.0f,									//near
			10.0f);									// far
	}

}

void Display(void)
{
	// function declaration
	void Draw24Spheres();
	void Update();

	// code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (grkeyPress == 1)
	{
		glRotatef(grangleForXRotation, 1.0f, 0.0f, 0.0f);
		grlightPosition[1] = grangleForXRotation;
	}

	else if (grkeyPress == 2)
	{
		glRotatef(grangleForYRotation, 0.0f, 1.0f, 0.0f);
		grlightPosition[2] = grangleForYRotation;
	}

	else if (grkeyPress == 3)
	{
		glRotatef(grangleForZRotation, 0.0f, 0.0f, 1.0f);
		grlightPosition[0] = grangleForZRotation;
	}

	//fprintf(grgpFile, "\n keyPress : %d, x : %f, lightPositionX : %f, lightPositionY : %f, lightPositionZ : %f", keyPress, angleForXRotation,grlightPosition[0], grlightPosition[1], grlightPosition[2]);
	glLightfv(GL_LIGHT0, GL_POSITION, grlightPosition);

	Draw24Spheres();
	/*
	glLightfv(GL_LIGHT1, GL_POSITION, grlightPosition);

	glTranslatef(0.0f, 0.0f, -0.55f);
	//glRotatef(grflight, 1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	grquadric = gluNewQuadric();
	gluSphere(grquadric, 0.2, 30, 30);

	// normals are calculated by glu library, we dont need to calculate normals explicitely
	*/

	Update();
	SwapBuffers(grghdc);
}

void Draw24Spheres()
{
#pragma region initialization
	// initialize
	GLfloat grmaterialAmbient1[] =
	{
		0.0215,
		0.1745,
		0.0215,
		1.0f

	};

	GLfloat grmaterialDiffuse1[] =
	{
		0.07568,
		0.61424,
		0.07568,
		1.0f
	};

	GLfloat grmaterialSpecular1[] =
	{
		0.633,
		0.727811,
		0.633,
		1.0f
	};

	GLfloat grmeterialShinyness1 = 0.6 * 128;

	// 2nd sphere
	GLfloat grmaterialAmbient2[] =
	{
		0.135, 
		0.2225, 
		0.1575, 
		1.0f  

	};

	GLfloat grmaterialDiffuse2[] =
	{
		0.54, // r
		0.89, // g
		0.63, // b
		1.0f // a
	};

	GLfloat grmaterialSpecular2[] =
	{
		0.316228, // r
		0.316228, // g
		0.316228, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness2 = 0.1 * 128;

	// 3rd sphere
	GLfloat grmaterialAmbient3[] =
	{
		0.05375, // r
		0.05,    // g
		0.06625, // b
		1.0f    // a
	};

	GLfloat grmaterialDiffuse3[] =
	{
		0.18275, // r
		0.17,    // g
		0.22525, // b
		1.0f    // a
	};

	GLfloat grmaterialSpecular3[] =
	{
		0.332741, // r
		0.328634, // g
		0.346435, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness3 = 0.3 * 128;

	//4th sphere
	GLfloat grmaterialAmbient4[] =
	{
		0.25,    // r
		0.20725, // g
		0.20725, // b
		1.0f    // a
	};

	GLfloat grmaterialDiffuse4[] =
	{
		1.0,   // r
		0.829, // g
		0.829, // b
		1.0f  // a
	};

	GLfloat grmaterialSpecular4[] =
	{
		0.296648, // r
		0.296648, // g
		0.296648, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness4 = 0.088 * 128;


	//5th sphere
	GLfloat grmaterialAmbient5[] =
	{
		0.1745,  // r
		0.01175, // g
		0.01175, // b
		1.0f    // a
	};

	GLfloat grmaterialDiffuse5[] =
	{
		0.61424, // r
		0.04136, // g
		0.04136, // b
		1.0f    // a
	};

	GLfloat grmaterialSpecular5[] =
	{
		0.727811, // r
		0.626959, // g
		0.626959, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness5 = 0.6 * 128;

	//6th sphere
	GLfloat grmaterialAmbient6[] =
	{
		0.1,     // r
		0.18725, // g
		0.1745,  // b
		1.0f    // a
	};

	GLfloat grmaterialDiffuse6[] =
	{
		0.396,   // r
		0.74151, // g
		0.69102, // b
		1.0f    // a
	};

	GLfloat grmaterialSpecular6[] =
	{
		0.297254, // r
		0.30829,  // g
		0.306678, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness6 = 0.1 * 128;

	//7th sphere
	GLfloat grmaterialAmbient7[] =
	{
		0.329412, // r
		0.223529, // g
		0.027451, // b
		1.0f     // a
	};

	GLfloat grmaterialDiffuse7[] =
	{
		0.780392, // r
		0.568627, // g
		0.113725, // b
		1.0f     // a
	};

	GLfloat grmaterialSpecular7[] =
	{
		0.992157, // r
		0.941176, // g
		0.807843, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness7 = 0.21794872 * 128;

	//8th sphere
	GLfloat grmaterialAmbient8[] =
	{
		0.2125, // r
		0.1275, // g
		0.054,  // b
		1.0f   // a
	};

	GLfloat grmaterialDiffuse8[] =
	{
		0.714,   // r
		0.4284,  // g
		0.18144, // b
		1.0f    // a
	};

	GLfloat grmaterialSpecular8[] =
	{
		0.393548, // r
		0.271906, // g
		0.166721, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness8 = 0.2 * 128;

	// 9th sphere
	GLfloat grmaterialAmbient9[] =
	{
		0.25, // r
		0.25, // g
		0.25, // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse9[] =
	{
		0.4,  // r
		0.4,  // g
		0.4,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular9[] =
	{
		0.774597, // r
		0.774597, // g
		0.774597, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness9 = 0.6 * 128;

	//10th sphere
	GLfloat grmaterialAmbient10[] =
	{
		0.19125, // r
		0.0735,  // g
		0.0225,  // b
		1.0f    // a
	};

	GLfloat grmaterialDiffuse10[] =
	{
		0.7038,  // r
		0.27048, // g
		0.0828,  // b
		1.0f    // a
	};

	GLfloat grmaterialSpecular10[] =
	{
		0.256777, // r
		0.137622, // g
		0.086014, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness10 = 0.1 * 128;

	//11 th sphere

	GLfloat grmaterialAmbient11[] =
	{
		0.24725, // r
		0.1995,  // g
		0.0745,  // b
		1.0f    // a
	};

	GLfloat grmaterialDiffuse11[] =
	{
		0.75164, // r
		0.60648, // g
		0.22648, // b
		1.0f    // a
	};

	GLfloat grmaterialSpecular11[] =
	{
		0.628281, // r
		0.555802, // g
		0.366065, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness11 = 0.4 * 128;

	// 12th sphere
	GLfloat grmaterialAmbient12[] =
	{
		0.19225, // r
		0.19225, // g
		0.19225, // b
		1.0f    // a
	};

	GLfloat grmaterialDiffuse12[] =
	{
		0.50754, // r
		0.50754, // g
		0.50754, // b
		1.0f    // a
	};

	GLfloat grmaterialSpecular12[] =
	{
		0.508273, // r
		0.508273, // g
		0.508273, // b
		1.0f     // a
	};

	GLfloat grmeterialShinyness12 = 0.4 * 128;

	// 13th sphere
	GLfloat grmaterialAmbient13[] =
	{
		0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse13[] =
	{
		0.01, // r
		0.01, // g
		0.01, // b
		1.0f // a
	};

	GLfloat grmaterialSpecular13[] =
	{
		0.50, // r
		0.50, // g
		0.50, // b
		1.0f // a
	};

	GLfloat grmeterialShinyness13 = 0.25 * 128;

	// 14th
	GLfloat grmaterialAmbient14[] =
	{
		0.0,  // r
		0.1,  // g
		0.06, // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse14[] =
	{
		0.0,        // r
		0.50980392, // g
		0.50980392, // b
		1.0f       // a
	};

	GLfloat grmaterialSpecular14[] =
	{
		0.50196078, // r
		0.50196078, // g
		0.50196078, // b
		1.0f       // a
	};

	GLfloat grmeterialShinyness14 = 0.25 * 128;

	// 15th
	GLfloat grmaterialAmbient15[] =
	{
		0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse15[] =
	{
		0.1,  // r
		0.35, // g
		0.1,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular15[] =
	{
		0.45, // r
		0.55, // g
		0.45, // b
		1.0f // a
	};

	GLfloat grmeterialShinyness15 = 0.25 * 128;

	// 16th
	GLfloat grmaterialAmbient16[] =
	{
		0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a

	};

	GLfloat grmaterialDiffuse16[] =
	{
		0.5,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular16[] =
	{
		0.7,  // r
		0.6,  // g
		0.6,  // b
		1.0f // a
	};

	GLfloat grmeterialShinyness16 = 0.25 * 128;

	//17th
	GLfloat grmaterialAmbient17[] =
	{
		0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse17[] =
	{
		0.55, // r
		0.55, // g
		0.55, // b
		1.0f // a
	};

	GLfloat grmaterialSpecular17[] =
	{
		0.70, // r
		0.70, // g
		0.70, // b
		1.0f // a

	};

	GLfloat grmeterialShinyness17 = 0.25 * 128;

	//18th
	GLfloat grmaterialAmbient18[] =
	{
		0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse18[] =
	{
		0.5,  // r
		0.5,  // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular18[] =
	{
		0.60, // r
		0.60, // g
		0.50, // b
		1.0f // a
	};

	GLfloat grmeterialShinyness18 = 0.25 * 128;

	//19th
	GLfloat grmaterialAmbient19[] =
	{
		0.02, // r
		0.02, // g
		0.02, // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse19[] =
	{
		0.01, // r
		0.01, // g
		0.01, // b
		1.0f // a
	};

	GLfloat grmaterialSpecular19[] =
	{
		0.4,  // r
		0.4,  // g
		0.4,  // b
		1.0f // a
	};

	GLfloat grmeterialShinyness19 = 0.078125 * 128;

	//20th
	GLfloat grmaterialAmbient20[] =
	{
		0.0,  // r
		0.05, // g
		0.05, // b
		1.0f // a

	};

	GLfloat grmaterialDiffuse20[] =
	{
		0.4,  // r
		0.5,  // g
		0.5,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular20[] =
	{
		0.04, // r
		0.7,  // g
		0.7,  // b
		1.0f // a
	};

	GLfloat grmeterialShinyness20 = 0.078125 * 128;

	//21st
	GLfloat grmaterialAmbient21[] =
	{
		0.0,  // r
		0.05, // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse21[] =
	{
		0.4,  // r
		0.5,  // g
		0.4,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular21[] =
	{
		0.04, // r
		0.7,  // g
		0.04, // b
		1.0f // a
	};

	GLfloat grmeterialShinyness21 = 0.078125 * 128;

	// 22nd
	GLfloat grmaterialAmbient22[] =
	{
		0.05, // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse22[] =
	{
		0.5,  // r
		0.4,  // g
		0.4,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular22[] =
	{
		0.7,  // r
		0.04, // g
		0.04, // b
		1.0f // a
	};

	GLfloat grmeterialShinyness22 = 0.078125 * 128;

	//23rd
	GLfloat grmaterialAmbient23[] =
	{
		0.05, // r
		0.05, // g
		0.05, // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse23[] =
	{
		0.5,  // r
		0.5,  // g
		0.5,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular23[] =
	{
		0.7,  // r
		0.7,  // g
		0.7,  // b
		1.0f // a
	};

	GLfloat grmeterialShinyness23 = 0.078125 * 128;

	//24th
	GLfloat grmaterialAmbient24[] =
	{
		0.05, // r
		0.05, // g
		0.0,  // b
		1.0f // a
	};

	GLfloat grmaterialDiffuse24[] =
	{
		0.5,  // r
		0.5,  // g
		0.4,  // b
		1.0f // a
	};

	GLfloat grmaterialSpecular24[] =
	{
		0.7,  // r
		0.7,  // g
		0.04, // b
		1.0f // a
	};

	GLfloat grmeterialShinyness24 = 0.078125 * 128;

#pragma endregion initialization

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// 1st
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular1);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness1);


	glLoadIdentity();
	glTranslatef(1.5f, 14.0f, 0.0f);
	gluSphere(grquadric[0], 1.0, 30, 30);

	//2
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular2);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness2);


	glLoadIdentity();
	glTranslatef(6.5f, 14.0f, 0.0f);
	gluSphere(grquadric[1], 1.0, 30, 30);

	//3
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular3);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness3);

	glLoadIdentity();
	glTranslatef(11.5f, 14.0f, 0.0f);
	gluSphere(grquadric[2], 1.0, 30, 30);

	//4
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular4);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness4);

	glLoadIdentity();
	glTranslatef(16.5f, 14.0f, 0.0f);
	gluSphere(grquadric[3], 1.0, 30, 30);

	//5
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse5);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular5);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness5);

	glLoadIdentity();
	glTranslatef(21.5f, 14.0f, 0.0f);
	gluSphere(grquadric[4], 1.0, 30, 30);

	//6
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient6);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse6);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular6);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness6);

	glLoadIdentity();
	glTranslatef(26.0f, 14.0f, 0.0f);
	gluSphere(grquadric[5], 1.0, 30, 30);

	//7
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient7);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse7);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular7);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness7);

	glLoadIdentity();
	glTranslatef(1.5f, 10.0f, 0.0f);
	gluSphere(grquadric[6], 1.0, 30, 30);

	//8
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient8);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse8);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular8);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness8);

	glLoadIdentity();
	glTranslatef(6.5f, 10.0f, 0.0f);
	gluSphere(grquadric[7], 1.0, 30, 30);

	//9
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient9);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse9);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular9);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness9);

	glLoadIdentity();
	glTranslatef(11.5f, 10.0f, 0.0f);
	gluSphere(grquadric[8], 1.0, 30, 30);

	//10
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient10);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse10);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular10);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness10);

	glLoadIdentity();
	glTranslatef(16.5f, 10.0f, 0.0f);
	gluSphere(grquadric[9], 1.0, 30, 30);

	//11
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient11);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse11);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular11);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness11);


	glLoadIdentity();
	glTranslatef(21.5f, 10.0f, 0.0f);
	gluSphere(grquadric[10], 1.0, 30, 30);

	//12
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient12);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse12);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular12);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness12);


	glLoadIdentity();
	glTranslatef(26.0f, 10.0f, 0.0f);
	gluSphere(grquadric[11], 1.0, 30, 30);

	//13
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient13);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse13);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular13);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness13);

	glLoadIdentity();
	glTranslatef(1.5f, 6.0f, 0.0f);
	gluSphere(grquadric[12], 1.0, 30, 30);


	//14
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient14);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse14);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular14);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness14);

	glLoadIdentity();
	glTranslatef(6.5f, 6.0f, 0.0f);
	gluSphere(grquadric[13], 1.0, 30, 30);

	//15
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient15);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse15);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular15);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness15);


	glLoadIdentity();
	glTranslatef(11.5f, 6.0f, 0.0f);
	gluSphere(grquadric[14], 1.0, 30, 30);

	//16
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient16);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse16);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular16);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness16);

	glLoadIdentity();
	glTranslatef(16.5f, 6.0f, 0.0f);
	gluSphere(grquadric[15], 1.0, 30, 30);

	//17
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient17);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse17);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular17);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness17);

	glLoadIdentity();
	glTranslatef(21.5f, 6.0f, 0.0f);
	gluSphere(grquadric[16], 1.0, 30, 30);

	//18
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient18);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse18);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular18);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness18);

	glLoadIdentity();
	glTranslatef(26.0f, 6.0f, 0.0f);
	gluSphere(grquadric[17], 1.0, 30, 30);

	//19
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient19);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse19);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular19);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness19);

	glLoadIdentity();
	glTranslatef(1.5f, 2.0f, 0.0f);
	gluSphere(grquadric[18], 1.0, 30, 30);

	//20
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient20);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse20);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular20);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness20);

	glLoadIdentity();
	glTranslatef(6.5f, 2.0f, 0.0f);
	gluSphere(grquadric[19], 1.0, 30, 30);


	//21
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient21);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse21);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular21);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness21);

	glLoadIdentity();
	glTranslatef(11.5f, 2.0f, 0.0f);
	gluSphere(grquadric[20], 1.0, 30, 30);


	//22
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient22);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse22);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular22);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness22);

	glLoadIdentity();
	glTranslatef(16.5f, 2.0f, 0.0f);
	gluSphere(grquadric[21], 1.0, 30, 30);

	//23
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient23);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse23);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular23);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness23);

	glLoadIdentity();
	glTranslatef(21.5f, 2.0f, 0.0f);
	gluSphere(grquadric[22], 1.0, 30, 30);


	//24
	glMaterialfv(GL_FRONT, GL_AMBIENT, grmaterialAmbient24);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grmaterialDiffuse24);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grmaterialSpecular24);
	glMaterialf(GL_FRONT, GL_SHININESS, grmeterialShinyness24);

	glLoadIdentity();
	glTranslatef(26.0f, 2.0f, 0.0f);
	gluSphere(grquadric[23], 1.0, 30, 30);


}

void Update()
{
	if (grkeyPress == 1)
	{
		grangleForXRotation = grangleForXRotation + 1.0f;
	}
	else if (grkeyPress == 2)
	{
		grangleForYRotation = grangleForYRotation + 1.0f;
	}
	if (grkeyPress == 3)
	{
		grangleForZRotation = grangleForZRotation + 1.0f;
	}
}

void Uninitialize(void)
{
	//code
	if (grgbFullScreen == true)
	{
		grdwStyle = GetWindowLong(grghwnd, GWL_STYLE);
		SetWindowLong(grghwnd, GWL_STYLE, (grdwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(grghwnd, &grgwpPrev);
		SetWindowPos(grghwnd, HWND_TOP, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(true);

	}
	if (wglGetCurrentContext() == grghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (grghrc)
	{
		wglDeleteContext(grghrc);
		grghrc = NULL;
	}

	if (grghdc)
	{
		ReleaseDC(grghwnd, grghdc);
		grghdc = NULL;
	}

	if (grgpFile)
	{
		fprintf(grgpFile, "\n **** End ****\nLog File closed successfully. \n Program terminated successfully");
		fclose(grgpFile);
		grgpFile = NULL;
	}

	if (grquadric)
	{

		for (i = 0; i < 24; i++)
		{
			gluDeleteQuadric(grquadric[i]);
			grquadric[i] = NULL;
		}
		
	}
}









