#include<windows.h>
#include<stdio.h>
#include<cmath>	// fabs()
#include<GL\gl.h>
#include<GL\Glu.h>	// graphic library utility
#include<math.h>	// sin(), cos()
#include"GRIcon.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "winmm.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PI 3.142


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


// project specific global variables declaration
GLUquadric* grquadric = NULL;
GLUquadric* grquadricTree = NULL;
int grhipsRight;
int grlegsRight;
int grfeetRight;
int grlegsLeft;
int grhipsLeft;
int grfeetLeft;
int grrotate = 0;
GLfloat grhumanX = 6.5f;
bool grhumanLegs;
GLfloat i, j;
GLint ii, ij;
GLint grbirdWings = -20;
bool bFly = true;
GLuint grtextureBird;
GLuint grtextureShirt;
GLuint grtextureLeaves;
GLuint grtextureSoil;
GLuint grtextureSky;
GLuint grtextureStem;
GLuint grtextureBirdAfraid;
GLuint grtextureDeathstar;
GLfloat grbirdX = -7.0f;
GLfloat grbirdY = 3.0f;
GLfloat grcolorPink_1[] = { 1.0f, 0.714f, 0.757f, 1.0f, 1.0f, 1.0f }; // bird wings color
GLfloat grmoonScale = 1.0f;
GLfloat gralienMove = 2.2f;
GLfloat grFadeIn = 0.0f;
GLfloat gralienColor = 1.0f;
GLfloat gralienmoveZ = 0.0f;
GLfloat grendCircle = 0.0f;
GLuint grscene = 0;
enum SCENE
{
	sc_change,
	sc_no_change
};

SCENE grscene_bird = sc_no_change;
SCENE grscene_human = sc_no_change;
SCENE grscene_bird_afraid = sc_no_change;
SCENE grscene_human_goggles = sc_no_change;
SCENE grscene_human_think_cloud = sc_no_change;
SCENE grscene_alien_reveal = sc_no_change;
SCENE grscene_moon_scale = sc_no_change;
SCENE grscene_alien_move = sc_no_change;
SCENE grscenepart1 = sc_change;
SCENE grscenepart2 = sc_no_change;
SCENE grscenepart3 = sc_no_change;
SCENE grsceneclose = sc_no_change;
SCENE grsceneend = sc_no_change;

struct Node
{
	float dataX;
	float dataY;
	float dataZ;
	struct Node* next;
};
struct Node* start = NULL;
struct Node* tempTraverse = NULL;



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

		case VK_SPACE:
			grscene = grscene + 1;
			switch (grscene)
			{
			case 1:
				PlaySound(TEXT("aasha.wav"), NULL, SND_FILENAME | SND_ASYNC);
				grscene_bird = sc_change;
				break;

			case 2:
				grscene_human = sc_change;
				break;

			case 3:
				PlaySound(TEXT("i_hate_you.wav"), NULL, SND_FILENAME | SND_ASYNC);
				grscene_human_think_cloud = sc_change;
				break;


			case 4:
				grscene_human_goggles = sc_change;
				break;

			case 5:
				grscene_bird_afraid = sc_change;
				break;

			case 6:
				PlaySound(TEXT("i_hate_you_2.wav"), NULL, SND_FILENAME | SND_ASYNC);
				grscenepart1 = sc_no_change;
				grscenepart2 = sc_change;
				break;

			case 7:
				grscene_moon_scale = sc_change;
				PlaySound(TEXT("alien_1.wav"), NULL, SND_FILENAME | SND_ASYNC);

				break;

			case 8:
				grscene_human_goggles = sc_no_change;
				break;

			case 9:
				grscenepart2 = sc_no_change;
				grscenepart3 = sc_change;
				PlaySound(TEXT("alien_2.wav"), NULL, SND_FILENAME | SND_ASYNC);
				// Playsound() //alien music
				break;

			case 10:
				grscene_alien_move = sc_change;
				break;

			case 11:
				grscene_alien_reveal = sc_change;
				break;

			case 12:
				grsceneend = sc_change;
				break;

			case 13:
				grsceneclose = sc_change;
				break;
			}

			break;


		default:
			break;
		}
		break;

	case WM_CHAR:											// for testing purpose
		switch (wParam)
		{

		case 's':
			grhipsRight = (grhipsRight - 4) % 45;
			if (grhipsRight >= 22.5f)
			{
				grlegsRight = (grlegsRight - 4) % 45;
			}
			else
			{
				grlegsRight = (grlegsRight + 4) % 45;
			}

			grfeetRight = (grfeetRight + 4) % 45;
			break;

		case 'S':
			grhipsRight = (grhipsRight + 4) % 90;
			grfeetRight = (grfeetRight + 4) % 45;
			break;

		case 'e':
			grlegsRight = (grlegsRight + 2) % 90;
			break;

		case 'E':
			grlegsRight = (grlegsRight - 2) % grhipsRight;
			break;

		case 'r':
			grrotate = grrotate + 1;
			grhipsRight = 0;
			grlegsRight = 0;
			grfeetRight = 0;
			grlegsLeft = 0;
			grlegsLeft = 0;
			grfeetLeft = 0;
			break;

		case 'a':
			if (bFly == true)
			{
				if (grbirdWings >= -180)
				{
					grbirdWings = grbirdWings - 5;
				}
				else
				{
					bFly = false;
				}
			}

			if (bFly == false)
			{
				if (grbirdWings <= -20)
				{
					grbirdWings = grbirdWings + 5;
				}
				else
					bFly = true;
			}
			break;

		case 'm':
		case 'M':
			grmoonScale = grmoonScale + 0.02f;
			break;

		case 'z':
		case 'Z':
			gralienMove = gralienMove - 0.1f;
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
	bool LoadGLTexture(GLuint*, TCHAR[]);
	struct Node* CreateNode();
	void InsertNode(float, float, float);
	void TraverseNode();

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


	// linklist code for tree coordinates
	InsertNode(-3.5f, -1.0f, -8.0f);
	InsertNode(5.5f, -1.0f, -12.0f);

	InsertNode(2.0f, -1.0f, -15.0f);
	//InsertNode(0.0f, -1.0f, -13.0f);
	InsertNode(-3.0f, -1.5f, -12.0f);

	//InsertNode(-7.5f, -1.0f, -11.0f);

	InsertNode(7.0f, -1.0f, -10.0f);


	// set clearcolor
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	LoadGLTexture(&grtextureShirt, MAKEINTRESOURCE(GRSHIRT));
	LoadGLTexture(&grtextureBird, MAKEINTRESOURCE(GRBIRD));
	LoadGLTexture(&grtextureLeaves, MAKEINTRESOURCE(GRLEAVES));
	LoadGLTexture(&grtextureSoil, MAKEINTRESOURCE(GRSOIL));
	LoadGLTexture(&grtextureSky, MAKEINTRESOURCE(GRSKY));
	LoadGLTexture(&grtextureStem, MAKEINTRESOURCE(GRSTEM));
	LoadGLTexture(&grtextureBirdAfraid, MAKEINTRESOURCE(GRBIRD_AFRAID));
	LoadGLTexture(&grtextureDeathstar, MAKEINTRESOURCE(GRDEATHSTAR));


	// enable texture
	glEnable(GL_TEXTURE_2D);

	// warm-up call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

bool LoadGLTexture(GLuint* texture, TCHAR resourceID[])
{
	// variable declarations
	bool bResult = false;
	HBITMAP hBitmap = NULL;
	BITMAP bmp;

	//code
	// OS dependent code starts from here
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), resourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);		// cx and cy  is 0,0 for bitmap img, for icon, give width and height
	if (hBitmap)
	{
		bResult = true;
		GetObject(hBitmap, sizeof(bmp), &bmp);

		// from here starts OpenGL actual code
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		// setting of texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			// wrap the texture around x axis (Texture's "S" = x axis)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);		// MAG - Magnification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);				// MIN - Minification
		// following call will actually push the graphic data into the memory with the help of graphic drivers
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits); // 3 is GL_RGBA 
		DeleteObject(hBitmap);

	}

	return(bResult);

}

void Resize(int width, int height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void Display(void)
{
	// function delcaration
	void Update();
	void TreeCode();
	void HumanThinkCloud();
	// code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (grscenepart1 == sc_change)
	{

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/////////////////////////////////////////////////////////////// BIRD //////////////////////////////////

#pragma region bird code
		glLoadIdentity();

		glPushMatrix();																				// 1

		glTranslatef(grbirdX, grbirdY, -6.0f);
		//glRotatef((GLfloat)grrotate, 0.0f, 1.0f, 0.0f);

		////// BODY
		glPushMatrix();																				// 2
		//glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.33f, 0.22f, 0.22f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureBird);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 20, 20);
		glPopMatrix();																				////2

		///// Tail
		glPushMatrix();
		glTranslatef(-0.2f, 0.08f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(30.0f, -1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.1f, 0.1f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(-0.05f, -0.1f, 0.0f);
		glVertex3f(0.05f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();

		///// HEAD
		glPushMatrix();																				// 3
		glTranslatef(0.18f, 0.11f, 0.0f);
		//glRotatef(-24.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.23f, 0.25f, 0.18f);
		//glColor3f(1.0f, 1.0f, 0.0f);
		if (grscene_bird_afraid == sc_no_change)
		{
			glBindTexture(GL_TEXTURE_2D, grtextureBird);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, grtextureBirdAfraid);
		}
		gluQuadricTexture(grquadric, GLU_TRUE);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 30, 30);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glPopMatrix();


		if (grscene_bird_afraid == sc_no_change)
		{
			/// Eyes - happy right
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, 0.08f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 0.8 * PI; i = i + 0.01f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.04f * cos(i), 0.03f * sin(i), 0.0095f);
			}
			glEnd();
			glPopMatrix();

			//// Eyes - happy left
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, -0.08f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 0.8 * PI; i = i + 0.01f)
			{
				glVertex3f(0.04f * cos(i), 0.03f* sin(i), -0.0095f);
			}
			glEnd();
			glPopMatrix();


		}

		else
		{
			/// Eyes - right afraid
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, 0.085f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 2.0 * PI; i = i + 0.005f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.03f * cos(i), 0.03f * sin(i), 0.0095f);
			}
			glEnd();
			glPopMatrix();


			/// Eyes - left afraid
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, -0.085f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 2.0 * PI; i = i + 0.005f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.03f * cos(i), 0.03f * sin(i), -0.0095f);
			}
			glEnd();
			glPopMatrix();



		}


		//// PEAK
		glPushMatrix();																				// 4
		glTranslatef(0.32f, 0.1f, 0.0f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.1f, 0.1f, 0.1f);
		glColor3f(0.68f, 0.57f, 0.0f);

		glBegin(GL_TRIANGLES);

		// upper right
		glVertex3f(0.0f, 0.5f, 0.0f);	//apex

		glVertex3f(-0.5f, -0.5f, 0.0f);

		glVertex3f(0.5f, -0.5f, 0.5f);

		// upper left
		glVertex3f(0.0f, 0.5f, 0.0f);	//apex

		glVertex3f(-0.5f, -0.5f, 0.0f);

		glVertex3f(0.5f, -0.5f, -0.5f);

		// bottom 

		glVertex3f(0.0f, 0.5f, 0.0f);

		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(0.5f, -0.5f, -0.5f);

# pragma region peak bottom code
		/*
		// lower right
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);	//apex

		glColor3f(0.0f, 1.0f, 0.0f);	//left
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);	//right
		glVertex3f(1.0f, -1.0f, 0.0f);

		// lower left
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);	//apex

		glColor3f(0.0f, 1.0f, 0.0f);	//left
		glVertex3f(0.0f, -1.0f, 1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);	//right
		glVertex3f(1.0f, -1.0f, -1.0f);
		*/
#pragma endregion peak bottom code

		glEnd();
		glPopMatrix();																				//// 4

		// Bird feet
		glPushMatrix();																				// 5
		glTranslatef(-0.03f, -0.1f, 0.0f);

		glPushMatrix();																				// 6
		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(4.5f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.05f);
		glVertex3f(0.0f, -0.04f, 0.05f);
		glEnd();
		glPopMatrix();																				//// 6

		// bird paws right
		glPushMatrix();																				// 7
		glTranslatef(0.0f, -0.05f, 0.05f);
		glScalef(0.08f, 0.05f, 0.05f);
		glColor3f(1.0f, 1.0f, 0.0f);
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();																				//// 7
		glPopMatrix();																				//// 5

		// left feet
		glPushMatrix();																				// 8
		glTranslatef(-0.03f, -0.1f, 0.0f);

		glPushMatrix();																				// 9
		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(4.5f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -0.05f);
		glVertex3f(0.0f, -0.04f, -0.05f);
		glEnd();
		glPopMatrix();																				//// 9

		// bird paws left
		glPushMatrix();																				// 10
		glTranslatef(0.0f, -0.05f, -0.05f);
		glScalef(0.08f, 0.05f, 0.05f);
		glColor3f(1.0f, 1.0f, 0.0f);
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();																				//// 10

		glPopMatrix();																				//// 8


		/////////////////////// Bird Wings
		// Right Wing
		glPushMatrix();																				// 11
		glTranslatef(-0.05f, 0.08f, 0.08f);

		glPushMatrix();																				// 12
		glRotatef((GLfloat)grbirdWings, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		glScalef(0.4f, 0.4f, 0.4f);
		glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.412f, 0.706f);
		ii = 6;
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 2.8f; i < (2 * PI); i = i + 0.02f)
		{
			ii = ii + 3;
			ij = ii % 6;
			//glColor3f(1.0f, 1.0f, 1.0f);
			//glColor3f(grcolorPink_1[0], grcolorPink_1[1], grcolorPink_1[2]);
			glVertex3f(0.0f, 0.0f, 0.0f);
			//glColor3f(grcolorPink_1[0 + ij], grcolorPink_1[1 + ij], grcolorPink_1[2 + ij]);
			glVertex3f(0.3f * cos(i), 0.3f * sin(i), 0.0f);
		}
		glEnd();
		glPopMatrix();																				//// 12
		glPopMatrix();																				//// 11


		/// Left Wing
		glPushMatrix();
		glTranslatef(-0.05f, 0.1f, -0.08f);

		glPushMatrix();
		glRotatef((GLfloat)-grbirdWings, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		glScalef(0.4f, 0.4f, 0.4f);
		glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.412f, 0.706f);
		glBegin(GL_TRIANGLE_STRIP);
		ii = 6;
		for (i = 3.0f; i < (2 * PI); i = i + 0.02f)
		{
			ii = ii + 3;
			ij = ii % 6;
			//glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			//fprintf(grgpFile, "\n ii : %d, ij : %d", ii, ij);
			//glColor3f(grcolorPink_1[0 + ij], grcolorPink_1[1 + ij], grcolorPink_1[2 + ij]);
			glVertex3f(0.3f * cos(i), 0.3f * sin(i), 0.0f);
		}
		glEnd();
		glPopMatrix();
		glPopMatrix();


		glPopMatrix();																				//// 1

#pragma endregion bird code

#pragma region humanoid code
		glPushMatrix();

		glTranslatef(grhumanX, -1.0f, -6.0f);
		glScalef(0.4f, 0.4f, 0.4f);
		glPushMatrix();


		////// body
		glTranslatef(0.0f, 1.0f, 0.0f);
		glRotatef((GLfloat)grrotate, 0.0f, 1.0f, 0.0f);

		///// stomach
		glPushMatrix();
		glScalef(0.4f, 1.2f, 0.6f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);									// stomach
		gluSphere(grquadric, 1.0f, 15, 15);
		glPopMatrix();	// matrix of stomach popped

		///// hips - 1
		glPushMatrix();
		glTranslatef(0.0f, -1.0f, 0.3f);
		glRotatef((GLfloat)grhipsRight, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.3f, 0.0f);

		glPushMatrix();
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(0.44f, 0.44f, 1.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		///// Leg-1
		glTranslatef(0.0f, -0.35f, 0.0f);
		glRotatef((GLfloat)grlegsRight, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.4f, 0.0f);

		//glPushMatrix();
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(1.0f, 0.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);						// Leg
		//glPopMatrix();


		////// Feet 1
		glTranslatef(-0.3f, -0.35f, 0.0f);						// position the feet
		//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);						// axis change to z
		//glRotatef((GLfloat) grfeetRight, 0.0f, 0.0f, 1.0f);
		//glTranslatef(-0.25f, 0.0f, 0.0f);						// move the feet up according to legs

		glScalef(1.3f, 0.3f, 1.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);						// feet
		glPopMatrix();

		///////////////////////////// Head ///////////////////////////
		glPushMatrix();
		glTranslatef(0.0f, 1.4f, 0.0f);
		glScalef(0.7f, 0.7f, 0.7f);
		glColor3f(0.95f, 0.76f, 0.70f);		// skin color
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();

		// cap
		glPushMatrix();
		glTranslatef(0.0f, 1.6f, 0.0f);
		glScalef(0.7f, 0.7f, 0.7f);
		glColor3f(0.0f, 0.0f, 0.70f);		// skin color
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();

		// cap part 2
		glPushMatrix();
		glTranslatef(0.4f, 1.5f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(40.0f, -1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.70f);		// skin color
		glBegin(GL_QUADS);
		glVertex3f(0.25f, 0.3f, 0.0f);
		glVertex3f(-0.25f, 0.3f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();

		if (grscene_human_goggles == sc_no_change)
		{
			// Right Eye

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, 0.18f);
			glScalef(0.2f, 0.2f, 0.2f);
			glColor3f(0.1f, 0.5f, 0.5f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// Left Eye

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, -0.18f);
			glScalef(0.2f, 0.2f, 0.2f);
			glColor3f(0.1f, 0.5f, 0.5f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();


		}
		else
		{
			// right goggle

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, 0.14f);
			glScalef(0.3f, 0.3f, 0.3f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();



			// left goggle

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, -0.14f);
			glScalef(0.3f, 0.3f, 0.3f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// goggle strip
			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, 0.0f);
			glScalef(0.3f, 0.1f, 0.3f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// right strip
			glPushMatrix();
			glTranslatef(0.0f, 1.48f, 0.1f);
			glScalef(0.6f, 0.1f, 0.55f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// left strip
			glPushMatrix();
			glTranslatef(0.0f, 1.48f, -0.1f);
			glScalef(0.6f, 0.1f, 0.55f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			/*
			// smile 1
			glPushMatrix();
			glTranslatef(-0.2f, 1.2f, 0.0f);
			glScalef(0.3f, 0.05f, 0.23f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// smile 2
			glPushMatrix();
			glTranslatef(-0.2f, 1.17f, 0.0f);
			glScalef(0.2f, 0.05f, 0.19f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();
			*/

			glPushMatrix();
			glTranslatef(-0.33f, 1.22f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 0.8 * PI; i = i + 0.01f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.04f * cos(i), 0.03f * sin(i), 0.0095f);
			}
			glEnd();
			glPopMatrix();
		}



		/////////////////////// Right Hand ////////////////////////
		// Shoulder
		glPushMatrix();
		glTranslatef(0.0f, 0.6f, 0.6f);
		glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		// Hand
		glTranslatef(0.0f, -0.4f, 0.0f);
		glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(0.95f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		glTranslatef(0.0f, -0.6f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 0.5f, 0.5f);
		glColor3f(0.95f, 0.76f, 0.70f);		// skin color
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();


		glPopMatrix();


		//////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////// LEFT 
		glPushMatrix();
		glTranslatef(0.0f, -1.0f, -0.3f);
		glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);

		glPushMatrix();
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(0.44f, 0.44f, 1.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);								// Hips
		glPopMatrix();

		////// Leg 2
		//glPushMatrix();
		glTranslatef(0.0f, -0.35f, 0.0f);
		glRotatef((GLfloat)grlegsLeft, 0.0f, 0.0f, 1.0f);

		glTranslatef(0.0f, -0.4f, 0.0f);
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(1.0f, 0.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);

		//glPopMatrix();

		//glPushMatrix();
		glTranslatef(-0.3f, -0.35f, 0.0f);						// position the feet
		//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);						// axis change to z
		//glRotatef((GLfloat) grfeetRight, 0.0f, 0.0f, 1.0f);
		//glTranslatef(-0.25f, 0.0f, 0.0f);						// move the feet up according to legs

		glScalef(1.3f, 0.3f, 1.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);						// feet
		//glPopMatrix();
		glPopMatrix();

		//////////////////////////////////////// LEFT HAND
		// Shoulder
		glPushMatrix();
		glTranslatef(0.0f, 0.6f, -0.6f);
		glRotatef((GLfloat)grhipsRight, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		// Hand
		glTranslatef(0.0f, -0.4f, 0.0f);
		glRotatef((GLfloat)grhipsRight, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(0.95f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		glTranslatef(0.0f, -0.6f, 0.0f);
		//glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, -1.0f);				// rotate the modelview matrix
		//glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 0.5f, 0.5f);
		glColor3f(0.95f, 0.76f, 0.70f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();


		glPopMatrix();
		glPopMatrix();


		glPopMatrix();

#pragma endregion humanoid code

#pragma region soil code
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, -2.0f, -15.0f);
		//glColor3f(0.910f, 0.7140f, 0.310f);
		glColor3f(0.46270f, 0.36570f, 0.17160f); // dark brown
		//glBindTexture(GL_TEXTURE_2D, grtextureSoil);
		glBegin(GL_QUADS);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(25.0f, 0.0f, 0.0f); // right top
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-25.0f, 0.0f, 0.0f);//lt
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-25.0f, 0.0f, 15.0f);//rb
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(25.0f, 0.0f, 15.0f);//lb
		glEnd();

		// working code 1 for soil

		for (GLfloat i = 28.0f; i >= -30.0f; i = i - 0.5f)
		{

			for (GLfloat j = 15.0f; j >= -15.0f; j = j - 1.0f)
			{
				glBegin(GL_TRIANGLES);
				glColor3f(0.46270f, 0.36570f, 0.17160f); // dark brown
				//glColor3f(0.0f, 0.7140f, 0.310f);
				glVertex3f(i, 0.0f, j - 2.0f);
				glColor3f(0.38610f, 0.33660f, 0.27720f); // darkest brown
				//glColor3f(0.0f, 0.7140f, 0.310f);
				glVertex3f(i, 0.0f, j);
				glColor3f(0.570f, 0.4080f, 0.1610f); // brown
				//glColor3f(0.0f, 0.7140f, 0.310f);
				glVertex3f(i + 2.5f, 0.0f, j);
				glEnd();

			}

		}

		glPopMatrix();

#pragma endregion soil code

#pragma region sky code
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, 1.0f, -17.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureSky);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(25.0f, 6.2f, 0.0f);									// right top
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-25.0f, 6.2f, 0.0f);									// left top

		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		glTexCoord2f(0.0f, 0.0f);										// left bottom
		glVertex3f(-25.0f, -2.7f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(25.0f, -2.7f, 0.0f);									// right bottom
		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		glBindTexture(GL_TEXTURE_2D, NULL);

		glEnd();
		glPopMatrix();

#pragma endregion sky code

		//////////////////////////////////////////////////////////// TREE ////////////////////////////////

		tempTraverse = start;
		while (tempTraverse != NULL)
		{

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(tempTraverse->dataX, tempTraverse->dataY, tempTraverse->dataZ);


			//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			//glRotatef((GLfloat)grrotate, 0.0f, 1.0f, 0.0f);
			TreeCode();
			glPopMatrix();


			tempTraverse = tempTraverse->next;
		}



		//////////////////////////////// Human think cloud
#pragma region Human think cloud
		if (grscene_human_think_cloud == sc_change)
		{

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.0f, 0.18f, -6.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glScalef(0.4f, 0.3f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.25f, 0.32f, -6.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glScalef(0.5f, 0.4f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			// clouds
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.5f, 0.8f, -6.0f);
			glColor3f(1.0f, 1.0f, 1.0f);

			glPushMatrix();
			glScalef(1.2f, 1.0f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();


			glPushMatrix();
			glTranslatef(0.3f, 0.0f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.2f, -0.2f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.1f, -0.2f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.3f, 0.0f, 0.0f);
			glScalef(1.3f, 1.1f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.2f, 0.2f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.1f, 0.2f, 0.0f);
			//glScalef(1.2f, 1.1f, 0.0f);
			HumanThinkCloud();
			glPopMatrix();

			glPopMatrix();

			// code for cage in human think cloud

#pragma region cage

			glPushMatrix();
			//glTranslatef(-1.8f, 0.0f, -6.0f);
			glTranslatef(1.2f, 0.5f, -5.0f);
			glScalef(0.3f, 0.3f, 0.0f);
			glRotatef(-85.0f, 1.0f, 0.0f, 0.0f);

			glColor3f(0.0f, 0.0f, 0.0f);
			//glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);

			glPushMatrix();

			glBegin(GL_QUADS);
			glVertex3f(0.5f, 0.5f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.0f);
			glEnd();
			glPopMatrix();


			glPushMatrix();
			glBegin(GL_QUADS);
			glVertex3f(0.5f, 0.5f, 1.1f);
			glVertex3f(-0.5f, 0.5f, 1.1f);
			glVertex3f(-0.5f, -0.5f, 1.1f);
			glVertex3f(0.5f, -0.5f, 1.1f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glBegin(GL_LINES);
			glColor3f(0.3f, 0.3f, 0.3f);
			for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
			{

				glVertex3f(i, -0.49f, 0.0f);
				glVertex3f(i, -0.49f, 1.1f);

			}
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glBegin(GL_LINES);
			glColor3f(0.3f, 0.3f, 0.3f);
			for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
			{

				glVertex3f(i, 0.49f, 0.0f);
				glVertex3f(i, 0.49f, 1.1f);

			}
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glBegin(GL_LINES);
			glColor3f(0.3f, 0.3f, 0.3f);
			for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
			{

				glVertex3f(0.49f, i, 0.0f);
				glVertex3f(0.49f, i, 1.1f);

			}
			glEnd();
			glPopMatrix();


			glPushMatrix();
			glBegin(GL_LINES);
			glColor3f(0.3f, 0.3f, 0.3f);
			for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
			{

				glVertex3f(-0.49f, i, 0.0f);
				glVertex3f(-0.49f, i, 1.1f);

			}
			glEnd();
			glPopMatrix();

			glPopMatrix();

#pragma endregion cage
		}


#pragma endregion Human think cloud



	}

	else if (grscenepart2 == sc_change)
	{
#pragma region room
		glPushMatrix();
		glLoadIdentity();

		glPushMatrix();
		// central wall
		glTranslatef(0.0f, 0.0f, -20.0f);
		glColor3f(0.96f, 0.97f, 0.46f);
		glBegin(GL_QUADS);

		glVertex3f(12.0f, 7.0f, 0.0f);

		glVertex3f(-12.0f, 7.0f, 0.0f);

		glVertex3f(-12.0f, -5.0f, 0.0f);

		glVertex3f(12.0f, -5.0f, 0.0f);
		glEnd();
		glPopMatrix();

		// Ceiling
		//
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, 6.0f, -20.0f);
		glColor3f(0.5f, 0.50f, 0.2f);
		glBegin(GL_QUADS);
		glVertex3f(12.0f, 1.0f, 0.0f);

		glVertex3f(-12.0f, 1.0f, 0.0f);

		glVertex3f(-12.0f, -1.0f, 20.0f);

		glVertex3f(12.0f, -1.0f, 20.0f);
		glEnd();
		glPopMatrix();



		// Floor
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, -5.0f, -20.0f);
		glColor3f(1.0f, 0.73f, 0.06f);
		glBegin(GL_QUADS);
		glVertex3f(12.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, 0.0f, 0.0f);
		glVertex3f(-12.0f, -1.0f, 20.0f);
		glVertex3f(12.0f, -1.0f, 20.0f);
		glEnd();
		glPopMatrix();


		// Tiles on floor (vertical)
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, -0.0f, -20.0f);
		glLineWidth(2.0f);
		glColor3f(1.0f, 0.87f, 0.96f);
		for (GLfloat i = -18.0f; i <= 18.0f; i = i + 4.0f)
		{
			glBegin(GL_LINES);
			glVertex3f(i, -5.0f, -20.0f);
			glVertex3f(i, -5.0f, 20.0f);
			glEnd();
		}
		glPopMatrix();

		// Tiles on floor (horizontal)
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -20.0f);
		glColor3f(1.0f, 0.87f, 0.96f);
		for (GLfloat i = -20.0f; i <= 20.0f; i = i + 3.0f)
		{
			glBegin(GL_LINES);
			glVertex3f(-30.0f, -5.0f, i);
			glVertex3f(30.0f, -5.0f, i);
			glEnd();
		}
		glPopMatrix();


		// left wall
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-10.0f, 0.0f, -20.0f);
		glColor3f(0.96f, 0.97f, 0.46f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 7.0f, 0.0f);
		glVertex3f(0.0f, 7.0f, 20.0f);
		glVertex3f(0.0f, -5.0f, 20.0f);
		glVertex3f(0.0f, -5.0f, 0.0f);
		glEnd();
		glPopMatrix();


		// left corner
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-10.0f, 0.0f, -20.0f);
		glColor3f(0.92f, 0.92f, 0.44f); // blue color
		//glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 7.0f, 0.0f);	// right top
		glVertex3f(0.0f, 7.0f, 0.05f);	// left top
		glVertex3f(0.0f, -5.0f, 0.05f);	// left bottom
		glVertex3f(0.0f, -5.0f, 0.0f);		// right bottom
		glEnd();
		glPopMatrix();

		// left corner
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-10.0f, 0.0f, -20.0f);
		glColor3f(0.92f, 0.92f, 0.44f); // blue color
		//glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 7.0f, -0.05f);	// right top
		glVertex3f(0.0f, 7.0f, 0.0f);	// left top
		glVertex3f(0.0f, -5.0f, 0.0f);	// left bottom
		glVertex3f(0.0f, -5.0f, -0.05f);		// right bottom
		glEnd();
		glPopMatrix();

		// right wall
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(10.0f, 0.0f, -20.0f);
		glColor3f(0.96f, 0.97f, 0.46f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 7.0f, 0.0f);
		glVertex3f(0.0f, 7.0f, 20.0f);
		glVertex3f(0.0f, -5.0f, 20.0f);
		glVertex3f(0.0f, -5.0f, 0.0f);
		glEnd();
		glPopMatrix();


		// right corner
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(10.0f, 0.0f, -20.0f);
		glColor3f(0.92f, 0.92f, 0.44f); // blue color
		//glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 7.0f, 0.0f);	// right top
		glVertex3f(0.0f, 7.0f, 0.05f);	// left top
		glVertex3f(0.0f, -5.0f, 0.05f);	// left bottom
		glVertex3f(0.0f, -5.0f, 0.0f);		// right bottom
		glEnd();
		glPopMatrix();


		// right corner
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(10.0f, 0.0f, -20.0f);
		glColor3f(0.92f, 0.92f, 0.44f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 7.0f, -0.05f);	// right top
		glVertex3f(0.0f, 7.0f, 0.0f);	// left top
		glVertex3f(0.0f, -5.0f, 0.0f);	// left bottom
		glVertex3f(0.0f, -5.0f, -0.05f);		// right bottom
		glEnd();
		glPopMatrix();


		// window
		glPushMatrix();
		glTranslatef(1.0f, 0.0f, -20.0f);
		glColor3f(0.0f, 0.0f, 0.0f); // blue color
		glBegin(GL_QUADS);

		glVertex3f(8.0f, 4.0f, 0.0f);

		glVertex3f(0.0f, 4.0f, 0.0f);

		glVertex3f(0.0f, -1.0f, 0.0f);

		glVertex3f(8.0f, -1.0f, 0.0f);
		glEnd();
		glPopMatrix();

		// window grill
		glPushMatrix();
		glTranslatef(1.0f, 0.0f, -19.0f);
		glColor3f(1.0f, 1.0f, 1.0f); // blue color
		glBegin(GL_LINES);
		for (i = 1.0f; i < 8.0f; i = i + 1.0f)
		{
			glVertex3f(i, 3.83f, 0.0f);
			glVertex3f(i, -1.0f, 0.0f);
		}
		glEnd();
		glPopMatrix();


		// moon
		glPushMatrix();
		glTranslatef(2.2f, 2.5f, -20.0f);
		glColor3f(1.0f, 0.8f, 0.0f);
		glScalef(grmoonScale, grmoonScale, 0.0f);
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0.0f; i <= 2 * PI; i = i + 0.01f)
		{
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.4f * cos(i), 0.4f * sin(i), 0.0f);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.2f, 2.5f, -20.0f);
		glColor3f(1.0f, 0.8f, 0.0f);
		glLineWidth(2.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.4f, 0.0f);
		glEnd();
		glPopMatrix();



		glPopMatrix();
#pragma endregion room

#pragma region humanoid code
		glPushMatrix();

		glTranslatef(1.0f, -1.2f, -6.0f);
		glScalef(0.5f, 0.5f, 0.5f);
		glPushMatrix();


		////// body
		glTranslatef(0.0f, 1.0f, 0.0f);
		glRotatef((GLfloat)grrotate, 0.0f, 1.0f, 0.0f);

		///// stomach
		glPushMatrix();
		glScalef(0.4f, 1.2f, 0.6f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);									// stomach
		gluSphere(grquadric, 1.0f, 15, 15);
		glPopMatrix();	// matrix of stomach popped

		///// hips - 1
		glPushMatrix();
		glTranslatef(0.0f, -1.0f, 0.3f);
		glRotatef((GLfloat)grhipsRight, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.3f, 0.0f);

		glPushMatrix();
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(0.44f, 0.44f, 1.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		///// Leg-1
		glTranslatef(0.0f, -0.35f, 0.0f);
		glRotatef((GLfloat)grlegsRight, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, -0.4f, 0.0f);

		//glPushMatrix();
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(1.0f, 0.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);						// Leg
		//glPopMatrix();


		////// Feet 1
		glTranslatef(-0.3f, -0.35f, 0.0f);						// position the feet
		//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);						// axis change to z
		//glRotatef((GLfloat) grfeetRight, 0.0f, 0.0f, 1.0f);
		//glTranslatef(-0.25f, 0.0f, 0.0f);						// move the feet up according to legs

		glScalef(1.3f, 0.3f, 1.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);						// feet
		glPopMatrix();

		///////////////////////////// Head ///////////////////////////
		glPushMatrix();
		glTranslatef(0.0f, 1.4f, 0.0f);
		glScalef(0.7f, 0.7f, 0.7f);
		glColor3f(0.95f, 0.76f, 0.70f);		// skin color
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();

		// cap
		glPushMatrix();
		glTranslatef(0.0f, 1.6f, 0.0f);
		glScalef(0.7f, 0.7f, 0.7f);
		glColor3f(0.0f, 0.0f, 0.70f);		// skin color
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();

		// cap part 2
		glPushMatrix();
		glTranslatef(0.4f, 1.5f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(40.0f, -1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.70f);		// skin color
		glBegin(GL_QUADS);
		glVertex3f(0.25f, 0.3f, 0.0f);
		glVertex3f(-0.25f, 0.3f, 0.0f);
		glVertex3f(-0.1f, -0.1f, 0.0f);
		glVertex3f(0.1f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();

		if (grscene_human_goggles == sc_no_change)
		{
			// Right Eye

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, 0.18f);
			glScalef(0.2f, 0.2f, 0.2f);
			glColor3f(0.1f, 0.5f, 0.5f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// Left Eye

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, -0.18f);
			glScalef(0.2f, 0.2f, 0.2f);
			glColor3f(0.1f, 0.5f, 0.5f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();


		}
		else
		{
			// right goggle

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, 0.14f);
			glScalef(0.3f, 0.3f, 0.3f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();



			// left goggle

			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, -0.14f);
			glScalef(0.3f, 0.3f, 0.3f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// goggle strip
			glPushMatrix();
			glTranslatef(-0.22f, 1.48f, 0.0f);
			glScalef(0.3f, 0.1f, 0.3f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// right strip
			glPushMatrix();
			glTranslatef(0.0f, 1.48f, 0.1f);
			glScalef(0.6f, 0.1f, 0.55f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			// left strip
			glPushMatrix();
			glTranslatef(0.0f, 1.48f, -0.1f);
			glScalef(0.6f, 0.1f, 0.55f);
			glColor3f(0.1f, 0.0f, 0.0f);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 10, 10);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.33f, 1.22f, 0.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 0.8 * PI; i = i + 0.01f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.04f * cos(i), 0.03f * sin(i), 0.0095f);
			}
			glEnd();
			glPopMatrix();
		}



		/////////////////////// Right Hand ////////////////////////
		// Shoulder
		glPushMatrix();
		glTranslatef(0.0f, 0.6f, 0.6f);
		glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		// Hand
		glTranslatef(0.0f, -0.4f, 0.0f);
		glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(0.95f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		glTranslatef(0.0f, -0.6f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 0.5f, 0.5f);
		glColor3f(0.95f, 0.76f, 0.70f);		// skin color
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();


		glPopMatrix();


		//////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////// LEFT 
		glPushMatrix();
		glTranslatef(0.0f, -1.0f, -0.3f);
		glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);

		glPushMatrix();
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(0.44f, 0.44f, 1.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);								// Hips
		glPopMatrix();

		////// Leg 2
		//glPushMatrix();
		glTranslatef(0.0f, -0.35f, 0.0f);
		glRotatef((GLfloat)grlegsLeft, 0.0f, 0.0f, 1.0f);

		glTranslatef(0.0f, -0.4f, 0.0f);
		glScalef(0.5f, 1.0f, 0.5f);
		glColor3f(1.0f, 0.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);

		//glPopMatrix();

		//glPushMatrix();
		glTranslatef(-0.3f, -0.35f, 0.0f);						// position the feet
		//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);						// axis change to z
		//glRotatef((GLfloat) grfeetRight, 0.0f, 0.0f, 1.0f);
		//glTranslatef(-0.25f, 0.0f, 0.0f);						// move the feet up according to legs

		glScalef(1.3f, 0.3f, 1.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5f, 10, 10);						// feet
		//glPopMatrix();
		glPopMatrix();

		//////////////////////////////////////// LEFT HAND
		// Shoulder
		glPushMatrix();
		glTranslatef(0.0f, 0.6f, -0.6f);
		glRotatef((GLfloat)grhipsRight, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		// Hand
		glTranslatef(0.0f, -0.4f, 0.0f);
		glRotatef((GLfloat)grhipsRight, 0.0f, 0.0f, 1.0f);				// rotate the modelview matrix
		glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 1.2f, 0.5f);
		glColor3f(0.95f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureShirt);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();

		glTranslatef(0.0f, -0.6f, 0.0f);
		//glRotatef((GLfloat)grhipsLeft, 0.0f, 0.0f, -1.0f);				// rotate the modelview matrix
		//glTranslatef(0.0f, -0.3f, 0.0f);
		glPushMatrix();
		glScalef(0.5f, 0.5f, 0.5f);
		glColor3f(0.95f, 0.76f, 0.70f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 10, 10);
		glPopMatrix();


		glPopMatrix();
		glPopMatrix();


		glPopMatrix();

#pragma endregion humanoid code


#pragma region cage

		glPushMatrix();
		glTranslatef(-1.8f, 0.0f, -6.0f);
		glRotatef(-88.0f, 1.0f, 0.0f, 0.0f);
		//glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);

		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(0.5f, 0.5f, 1.1f);
		glVertex3f(-0.5f, 0.5f, 1.1f);
		glVertex3f(-0.5f, -0.5f, 1.1f);
		glVertex3f(0.5f, -0.5f, 1.1f);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(0.3f, 0.3f, 0.3f);
		for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
		{

			glVertex3f(i, -0.49f, 0.0f);
			glVertex3f(i, -0.49f, 1.1f);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(0.3f, 0.3f, 0.3f);
		for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
		{

			glVertex3f(i, 0.49f, 0.0f);
			glVertex3f(i, 0.49f, 1.1f);

		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(0.3f, 0.3f, 0.3f);
		for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
		{

			glVertex3f(0.49f, i, 0.0f);
			glVertex3f(0.49f, i, 1.1f);

		}
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(0.3f, 0.3f, 0.3f);
		for (i = -0.48f; i <= 0.54f; i = i + 0.18f)
		{

			glVertex3f(-0.49f, i, 0.0f);
			glVertex3f(-0.49f, i, 1.1f);

		}
		glEnd();
		glPopMatrix();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.8f, 0.0f, -6.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 6.0f, 0.0f);
		glEnd();
		glPopMatrix();
#pragma endregion cage


#pragma region bird code

		glLoadIdentity();

		glPushMatrix();																				// 1

		glTranslatef(-1.8f, 0.15f, -6.0f);
		//glRotatef((GLfloat)grrotate, 0.0f, 1.0f, 0.0f);

		////// BODY
		glPushMatrix();																				// 2
		//glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.33f, 0.22f, 0.22f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureBird);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 20, 20);
		glPopMatrix();																				////2

		///// Tail
		glPushMatrix();
		glTranslatef(-0.2f, 0.08f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(30.0f, -1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.1f, 0.1f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(-0.05f, -0.1f, 0.0f);
		glVertex3f(0.05f, -0.1f, 0.0f);
		glEnd();
		glPopMatrix();

		///// HEAD
		glPushMatrix();																				// 3
		glTranslatef(0.18f, 0.11f, 0.0f);
		//glRotatef(-24.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.23f, 0.25f, 0.18f);
		//glColor3f(1.0f, 1.0f, 0.0f);
		if (grscene_bird_afraid == sc_no_change)
		{
			glBindTexture(GL_TEXTURE_2D, grtextureBird);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, grtextureBirdAfraid);
		}
		gluQuadricTexture(grquadric, GLU_TRUE);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 30, 30);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glPopMatrix();


		if (grscene_bird_afraid == sc_no_change)
		{
			/// Eyes - happy right
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, 0.08f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 0.8 * PI; i = i + 0.01f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.04f * cos(i), 0.03f * sin(i), 0.0095f);
			}
			glEnd();
			glPopMatrix();

			//// Eyes - happy left
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, -0.08f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 0.8 * PI; i = i + 0.01f)
			{
				glVertex3f(0.04f * cos(i), 0.03f * sin(i), -0.0095f);
			}
			glEnd();
			glPopMatrix();


		}

		else
		{
			/// Eyes - right afraid
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, 0.085f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 2.0 * PI; i = i + 0.005f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.03f * cos(i), 0.03f * sin(i), 0.0095f);
			}
			glEnd();
			glPopMatrix();


			/// Eyes - left afraid
			glPushMatrix();
			glTranslatef(0.2f, 0.1f, -0.085f);
			glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glPointSize(1.2f);
			glBegin(GL_POINTS);
			for (i = 0.0f; i < 2.0 * PI; i = i + 0.005f)
			{
				//glVertex2f(0.0f, 0.0f);
				glVertex3f(0.03f * cos(i), 0.03f * sin(i), -0.0095f);
			}
			glEnd();
			glPopMatrix();



		}


		//// PEAK
		glPushMatrix();																				// 4
		glTranslatef(0.32f, 0.1f, 0.0f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(0.1f, 0.1f, 0.1f);
		glColor3f(0.68f, 0.57f, 0.0f);

		glBegin(GL_TRIANGLES);

		// upper right
		glVertex3f(0.0f, 0.5f, 0.0f);	//apex

		glVertex3f(-0.5f, -0.5f, 0.0f);

		glVertex3f(0.5f, -0.5f, 0.5f);

		// upper left
		glVertex3f(0.0f, 0.5f, 0.0f);	//apex

		glVertex3f(-0.5f, -0.5f, 0.0f);

		glVertex3f(0.5f, -0.5f, -0.5f);

		// bottom 

		glVertex3f(0.0f, 0.5f, 0.0f);

		glVertex3f(0.5f, -0.5f, 0.5f);

		glVertex3f(0.5f, -0.5f, -0.5f);

# pragma region peak bottom code
		/*
		// lower right
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);	//apex

		glColor3f(0.0f, 1.0f, 0.0f);	//left
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);	//right
		glVertex3f(1.0f, -1.0f, 0.0f);

		// lower left
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);	//apex

		glColor3f(0.0f, 1.0f, 0.0f);	//left
		glVertex3f(0.0f, -1.0f, 1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);	//right
		glVertex3f(1.0f, -1.0f, -1.0f);
		*/
#pragma endregion peak bottom code

		glEnd();
		glPopMatrix();																				//// 4

		// Bird feet
		glPushMatrix();																				// 5
		glTranslatef(-0.03f, -0.1f, 0.0f);

		glPushMatrix();																				// 6
		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(4.5f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.05f);
		glVertex3f(0.0f, -0.04f, 0.05f);
		glEnd();
		glPopMatrix();																				//// 6

		// bird paws right
		glPushMatrix();																				// 7
		glTranslatef(0.0f, -0.05f, 0.05f);
		glScalef(0.08f, 0.05f, 0.05f);
		glColor3f(1.0f, 1.0f, 0.0f);
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();																				//// 7
		glPopMatrix();																				//// 5

		// left feet
		glPushMatrix();																				// 8
		glTranslatef(-0.03f, -0.1f, 0.0f);

		glPushMatrix();																				// 9
		glColor3f(1.0f, 0.0f, 0.0f);
		glLineWidth(4.5f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, -0.05f);
		glVertex3f(0.0f, -0.04f, -0.05f);
		glEnd();
		glPopMatrix();																				//// 9

		// bird paws left
		glPushMatrix();																				// 10
		glTranslatef(0.0f, -0.05f, -0.05f);
		glScalef(0.08f, 0.05f, 0.05f);
		glColor3f(1.0f, 1.0f, 0.0f);
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();																				//// 10

		glPopMatrix();																				//// 8


		/////////////////////// Bird Wings
		// Right Wing
		glPushMatrix();																				// 11
		glTranslatef(-0.05f, 0.08f, 0.08f);

		glPushMatrix();																				// 12
		glRotatef((GLfloat)grbirdWings, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		glScalef(0.4f, 0.4f, 0.4f);
		glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.412f, 0.706f);
		ii = 6;
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 2.8f; i < (2 * PI); i = i + 0.02f)
		{
			ii = ii + 3;
			ij = ii % 6;
			//glColor3f(1.0f, 1.0f, 1.0f);
			//glColor3f(grcolorPink_1[0], grcolorPink_1[1], grcolorPink_1[2]);
			glVertex3f(0.0f, 0.0f, 0.0f);
			//glColor3f(grcolorPink_1[0 + ij], grcolorPink_1[1 + ij], grcolorPink_1[2 + ij]);
			glVertex3f(0.3f * cos(i), 0.3f * sin(i), 0.0f);
		}
		glEnd();
		glPopMatrix();																				//// 12
		glPopMatrix();																				//// 11


		/// Left Wing
		glPushMatrix();
		glTranslatef(-0.05f, 0.1f, -0.08f);

		glPushMatrix();
		glRotatef((GLfloat)-grbirdWings, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -0.1f, 0.0f);
		glScalef(0.4f, 0.4f, 0.4f);
		glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.412f, 0.706f);
		glBegin(GL_TRIANGLE_STRIP);
		ii = 6;
		for (i = 3.0f; i < (2 * PI); i = i + 0.02f)
		{
			ii = ii + 3;
			ij = ii % 6;
			//glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			//fprintf(grgpFile, "\n ii : %d, ij : %d", ii, ij);
			//glColor3f(grcolorPink_1[0 + ij], grcolorPink_1[1 + ij], grcolorPink_1[2 + ij]);
			glVertex3f(0.3f * cos(i), 0.3f * sin(i), 0.0f);
		}
		glEnd();
		glPopMatrix();
		glPopMatrix();


		glPopMatrix();																				//// 1

#pragma endregion bird code


	}

	else if (grscenepart3 == sc_change)
	{
		glLoadIdentity();

		glPushMatrix();

#pragma region soil code
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, -2.0f, -15.0f);
		//glColor3f(0.910f, 0.7140f, 0.310f);
		glColor3f(0.5f, 0.5f, 0.5f); // dark brown
		//glBindTexture(GL_TEXTURE_2D, grtextureSoil);
		glBegin(GL_QUADS);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(25.0f, 0.0f, 0.0f); // right top
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-25.0f, 0.0f, 0.0f);//lt
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-25.0f, 0.0f, 15.0f);//rb
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(25.0f, 0.0f, 15.0f);//lb
		glEnd();

		// working code 1 for soil

		for (GLfloat i = 28.0f; i >= -30.0f; i = i - 0.5f)
		{

			for (GLfloat j = 15.0f; j >= -15.0f; j = j - 1.0f)
			{
				glBegin(GL_TRIANGLES);
				glColor3f(0.45f, 0.45f, 0.45f); // dark brown
				//glColor3f(0.0f, 0.7140f, 0.310f);
				glVertex3f(i, 0.0f, j - 2.0f);
				glColor3f(0.38f, 0.38f, 0.38f); // darkest brown
				//glColor3f(0.0f, 0.7140f, 0.310f);
				glVertex3f(i, 0.0f, j);
				glColor3f(0.4f, 0.4f, 0.4f); // brown
				//glColor3f(0.0f, 0.7140f, 0.310f);
				glVertex3f(i + 2.5f, 0.0f, j);
				glEnd();

			}

		}

		glPopMatrix();

#pragma endregion soil code

#pragma region alien sky
		glPushMatrix();
		glTranslatef(0.0f, 1.0f, -17.0f);
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);			// orange-ish color
		glVertex3f(25.0f, -2.7f, 0.0f);									// right bottom
		//glColor3f(0.5290f , 0.8080f, 0.9220f);
		glVertex3f(-25.0f, -2.7f, 0.0f);
		//glColor3f(0.5290f, 0.8080f , 0.9220f);
		glVertex3f(-25.0f, 6.2f, 0.0f);
		glVertex3f(25.0f, 6.2f, 0.0f);
		glEnd();
		glPopMatrix();
#pragma endregion alien sky

#pragma region house
		// house
		glPushMatrix();
		glTranslatef(2.0f, 0.8f, -6.0f);
		glScalef(0.4f, 0.4f, 0.4f);
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f);

		glBegin(GL_QUADS);
		// front face (all z +ve)
		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(1.5f, 1.0f, 1.0f);
		glVertex3f(-1.5f, 1.0f, 1.0f);
		glVertex3f(-1.5f, -1.0f, 1.0f);
		glVertex3f(1.5f, -1.0f, 1.0f);

		// right face (all x +ve)
		glColor3f(0.698f, 0.133f, 0.133f);
		glVertex3f(1.5f, 1.0f, -1.0f);
		glVertex3f(1.5f, 1.0f, 1.0f);
		glVertex3f(1.5f, -1.0f, 1.0f);
		glVertex3f(1.5f, -1.0f, -1.0f);

		// back face (all z -ve)
		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(-1.5f, 1.0f, -1.0f);
		glVertex3f(1.5f, 1.0f, -1.0f);
		glVertex3f(1.5f, -1.0f, -1.0f);
		glVertex3f(-1.5f, -1.0f, -1.0f);

		// left face (all x -ve)
		glColor3f(1.0, 0.627f, 0.478f);
		glVertex3f(-1.5f, 1.0f, 1.0f);
		glVertex3f(-1.5f, 1.0f, -1.0f);
		glVertex3f(-1.5f, -1.0f, -1.0f);
		glVertex3f(-1.5f, -1.0f, 1.0f);

		// top face (all y +ve)
		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(1.5f, 1.0f, -1.0f);
		glVertex3f(-1.5f, 1.0f, -1.0f);
		glVertex3f(-1.5f, 1.0f, 1.0f);
		glVertex3f(1.5f, 1.0f, 1.0f);

		// bottom face (all y -ve)
		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(1.5f, -1.0f, -1.0f);
		glVertex3f(-1.5f, -1.0f, -1.0f);
		glVertex3f(-1.5f, -1.0f, 1.0f);
		glVertex3f(1.5f, -1.0f, 1.0f);

		// roof of house
		glColor3f(0.518f, 0.122f, 0.153f);
		glVertex3f(1.5f, 1.8f, 0.0f);
		glVertex3f(-1.5f, 1.8f, 0.0f);
		glVertex3f(-1.5f, 1.0f, 1.0f);
		glVertex3f(1.5f, 1.0f, 1.0f);

		// roof of house - back side
		glColor3f(0.518f, 0.122f, 0.153f);
		glVertex3f(1.5f, 1.8f, 0.0f);
		glVertex3f(-1.5f, 1.8f, 0.0f);
		glVertex3f(-1.5f, 1.0f, -1.0f);
		glVertex3f(1.5f, 1.0f, -1.0f);

		// roof of house
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.5f, 1.8f, 0.0f);
		glVertex3f(-1.5f, 1.8f, 0.0f);
		glVertex3f(-1.5f, 1.0f, -1.0f);
		glVertex3f(-1.5f, 1.0f, 1.0f);

		// roof of house
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.5f, 1.8f, 0.0f);
		glVertex3f(1.5f, 1.8f, 0.0f);
		glVertex3f(1.5f, 1.0f, 1.0f);
		glVertex3f(1.5f, 1.0f, -1.0f);

		glEnd();
		glPopMatrix();

		// wire
		glPushMatrix();
		glTranslatef(2.0f, 0.8f, -6.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, 6.0f);
		glVertex2f(0.0f, 0.5f);
		glEnd();
		glPopMatrix();

#pragma endregion house

		// alien body code
		if (grscene_alien_reveal == sc_change)
		{
			glPushMatrix();
			glTranslatef(gralienMove, 1.2f, -8.0f + gralienmoveZ);
			//fprintf(grgpFile, "\n gralienmoveZ : %f", gralienmoveZ);
			glScalef(3.4f, 4.4f, 1.2f);
			glColor3f(gralienColor * grFadeIn, gralienColor * 4 * grFadeIn, 0.0f * grFadeIn);
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.2, 30, 30);
			glPopMatrix();

		}

		// alien eyes
		glPushMatrix();
		glTranslatef(gralienMove, 1.2f, -7.9f + gralienmoveZ);
		glScalef(2.2f, 1.8f, 1.2f);
		glColor3f(0.0f, 0.0f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.2, 30, 30);
		glPopMatrix();

		// alien eyes = yellow
		glPushMatrix();
		glTranslatef(gralienMove, 1.22f, -7.8f + gralienmoveZ);
		glScalef(0.55f, 0.55f, 0.4f);
		glColor3f(1.0f, 0.8f, 0.0f);
		grquadric = gluNewQuadric();
		gluSphere(grquadric, 0.5, 30, 30);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-6.0f, 2.2f, -10.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureDeathstar);
		grquadric = gluNewQuadric();
		gluQuadricTexture(grquadric, GLU_TRUE);
		gluSphere(grquadric, 0.5, 50, 50);
		glPopMatrix();

		// pop matrix of scene 3
		glPopMatrix();

		if (grsceneclose == sc_change)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, -3.0f);
			glScalef(grendCircle, grendCircle, 0.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
		
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0.0f; i < 2 * PI; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(cos(i), sin(i), 0.0f);
			}
			glEnd();
			glPopMatrix();
		}
	}


	



	Update();
	SwapBuffers(grghdc);
}

void Update()
{
	// first scene part 2 : human
	if (grscenepart1 == sc_change)
	{
		if (grscene_human == sc_change)
		{
			if (grhumanX >= 0.8f && grhumanX <= 6.5f)
			{
				if (grhipsLeft == 0)
				{
					grhumanX = grhumanX - 0.005f;
					if (abs(grhipsRight) <= 40)
					{
						grhipsRight = grhipsRight - 2;
						if (grhipsRight >= -22)
						{
							grlegsRight = (grlegsRight + 1) % 45;
						}
						else
						{
							grlegsRight = (grlegsRight + 1) % 45;
							//fprintf(grgpFile, "\n in else grlegs : %d", grlegs);
						}
						grfeetRight = (grfeetRight - 1) % 30;
					}
					else
					{
						grhipsRight = 0;
						grlegsRight = 0;
						grfeetRight = 0;
						//grhumanX = grhumanX - 0.25f;
					}


				}

				if (grhipsRight == 0)
				{
					grhumanX = grhumanX - 0.005f;
					if (abs(grhipsLeft) <= 40)
					{
						grhipsLeft = grhipsLeft - 1;
						if (grhipsLeft >= -22)
						{
							grlegsLeft = (grlegsLeft + 1) % 45;
						}
						else
						{
							grlegsLeft = (grlegsLeft + 1) % 45;
							//fprintf(grgpFile, "\n in else grlegs : %d", grlegs);
						}
						//grlegsLeft = (grlegsLeft - 2) % 30;
						grfeetLeft = (grfeetLeft - 1) % 30;
					}
					else
					{
						grhipsLeft = 0;
						grlegsLeft = 0;
						//grhumanX = grhumanX - 0.25f;
					}

				}
			}
			else
			{
				grhipsLeft = 0;
				grhipsRight = 0;
				grlegsLeft = 0;
				grlegsRight = 0;
				grfeetLeft = 0;
				grfeetRight = 0;
				grscene_human = sc_no_change;
			}

		}


		// first scene part 1 : bird
		if (grscene_bird == sc_change)
		{
			if (grbirdX <= -1.5f)
			{
				grbirdX = grbirdX + 0.01f;
				if (grbirdY >= -1.5f)
				{
					grbirdY = grbirdY - 0.008f;
				}

				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 10;
					}
					else
					{
						bFly = false;
					}
				}

				if (bFly == false)
				{
					if (grbirdWings <= -20)
					{
						grbirdWings = grbirdWings + 10;
					}
					else
						bFly = true;
				}
			}
			else
			{
				grbirdWings = 0;
				grscene_bird = sc_no_change;

			}

		}

		// first scene part 3 : bird afraid
			// make eyes afraid -scene sets in update when human stops - eyes code in display

		// first scene part 4 : human goggles
			// show goggles on human - scene sets on space key - goggles code in display
	}

	else if (grscenepart2 == sc_change)
	{
		if (grscene_moon_scale == sc_change)
		{
			if (grmoonScale <= 2.5f)
			{
				grmoonScale = grmoonScale + 0.01f;
			}
		}
	}

	else if (grscenepart3 == sc_change)
	{
		if (grscene_alien_reveal == sc_change)
		{
			if (gralienColor > 0.2f)
			{
				gralienColor = gralienColor - 0.001f;
			}
			if (grFadeIn <= 1.0f)
				grFadeIn = grFadeIn + 0.001f;
		}

		if (grsceneend == sc_change)
		{
			//fprintf(grgpFile, "\n in if, grsceneend gralienmoveZ : %f", gralienmoveZ);
			if (gralienmoveZ <= 10.0f)
			{
				//fprintf(grgpFile, "\n in if, gralienmoveZ : %f", gralienmoveZ);
				gralienmoveZ = gralienmoveZ + 0.1f;
			}
		}

		if (grscene_alien_move == sc_change)
		{
			if (gralienMove >= -1.5f)
				gralienMove = gralienMove - 0.01f;

		}

		if (grsceneclose == sc_change)
		{
			if (grendCircle <= 10.0f)
				grendCircle = grendCircle + 0.1f;
		}

	}

	


}

struct Node* CreateNode()
{
	printf("\n in create node");
	struct Node* temp;
	temp = (struct Node*)malloc(sizeof(struct Node));
	return(temp);
}

void InsertNode(float x, float y, float z)
{
	printf("\n in insertnode");
	struct Node* CreateNode();
	struct Node* t;
	struct Node* temp;
	temp = CreateNode();

	temp->dataX = x;
	temp->dataY = y;
	temp->dataZ = z;
	temp->next = NULL;

	printf("\n insertnode- above condition");
	if (start == NULL)
	{
		printf("\n insertnode- in if");
		start = temp;
		printf("\n insertnode- in if- start->dataX : %f", start->dataX);
	}
	else
	{
		t = start;
		while (t->next != NULL)
		{
			t = t->next;
		}

		t->next = temp;
	}
	printf("\n insertnode-after conditions ");


}

void TreeCode()
{

	// STEM
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.22f, 0.0f);
	glScalef(0.8f, 4.5f, 0.8f);
	grquadricTree = gluNewQuadric();
	gluSphere(grquadricTree, 0.7f, 40, 40);
	glPopMatrix();

	// branch
	/*
	glPushMatrix();
	glTranslatef(0.05f, 1.4f, 0.1f);

	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	glPushMatrix();

	glTranslatef(0.0f, 0.5f, 0.0f);
	glScalef(0.3f, 0.6f, 0.3f);
	glColor3f(0.5f, 0.5f, 0.0f);
	gluSphere(grquadric, 0.6f, 40, 40);;
	glPopMatrix();
	glPopMatrix();
	*/



	// tree leaves
	glPushMatrix();
	glTranslatef(0.0f, 2.8f, 0.0f);
	glScalef(1.5f, 1.5f, 1.5f);

	glPushMatrix();												// center 1
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1.3f, 1.5f, 1.3f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();

	glPushMatrix();											// bottom right 2
	glTranslatef(0.4f, -0.3f, 0.0f);
	glRotatef(70.0f, 0.0f, 1.0f, 1.0f);
	glScalef(1.3f, 1.3f, 1.3f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();										// middle right 3
	glTranslatef(1.0f, 0.0f, 0.0f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();										// up 4
	glTranslatef(-0.1f, 0.7f, 0.0f);
	//glRotatef(60.0f, 1.0f, 1.0f, 1.0f);
	glScalef(1.3f, 1.3f, 1.6f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// upper left 5
	glTranslatef(-0.4f, 0.3f, 0.0f);
	//glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.5f, 1.5f, 1.3f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// middle left 6
	glTranslatef(-0.6f, -0.3f, 0.0f);
	glScalef(1.35f, 1.35f, 1.35f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// bottom left 7
	glTranslatef(-0.6f, -0.2f, 0.0f);
	glScalef(1.35f, 1.35f, 1.35f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// right 8
	glTranslatef(0.7f, 0.5f, 0.0f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// right 9
	glTranslatef(0.63f, 0.8f, 0.1f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// right 10
	glTranslatef(-0.74f, 0.66f, 0.1f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();

	glPushMatrix();												// right 10
	glTranslatef(-0.9f, 0.2f, 0.0f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// upper left middle 10
	glTranslatef(-0.1f, 1.0f, 0.0f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();


	glPushMatrix();												// right 10
	glTranslatef(-1.2f, 0.34f, 0.0f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();



	glPushMatrix();												// right 10
	glTranslatef(-0.5f, 1.0f, 0.0f);
	glScalef(1.2f, 1.2f, 1.4f);
	glBindTexture(GL_TEXTURE_2D, grtextureLeaves);
	grquadricTree = gluNewQuadric();
	gluQuadricTexture(grquadricTree, GLU_TRUE);
	gluSphere(grquadricTree, 0.4f, 30, 30);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();

	glPopMatrix();
}

void HumanThinkCloud()
{
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0.0f; i < 2 * PI; i = i + 0.02f)
	{
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.2f * cos(i), 0.2f * sin(i), 0.0f);
	}
	glEnd();
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
	glDeleteTextures(1, &grtextureBird);
	glDeleteTextures(1, &grtextureLeaves);
	gluDeleteQuadric(grquadric);
	gluDeleteQuadric(grquadricTree);
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
}









