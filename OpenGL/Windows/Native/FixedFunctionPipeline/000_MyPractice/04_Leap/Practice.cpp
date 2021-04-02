#include<windows.h>
#include<stdio.h>
#include<GL\gl.h>
#include<GL\Glu.h>	// graphic library utility
#include<math.h>
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
GLfloat grfangle;
enum SCENE
{
	sc_change,
	sc_no_change
};

GLuint grscene = 0;

SCENE grsceneintro = sc_change;
SCENE grscenepart0 = sc_no_change;
SCENE grscene_rain = sc_no_change;
SCENE grscene_heavy_rain = sc_no_change;
SCENE grscenepart1 = sc_no_change;
SCENE grscene_bird_afraid = sc_no_change;
SCENE grscene_bird_fell = sc_no_change;
SCENE grscene_bird = sc_no_change;
SCENE grscene_bird_lightning = sc_no_change;
SCENE grscenepart2 = sc_no_change;
SCENE grscene_morning = sc_no_change;
SCENE grsceneCircleBlend = sc_no_change;
SCENE grscene_bird_think_cloud = sc_no_change;
SCENE grscene_zoom_window = sc_no_change;
SCENE grscene_cloud_think_bed = sc_no_change;
SCENE grscene_cloud_think_foods = sc_no_change;
SCENE grscene_cloud_think_smiley = sc_no_change;
SCENE grscene_other_bird_flying = sc_no_change;
SCENE grscene_bird_curious = sc_no_change;
SCENE grscene_bird_in_window = sc_no_change;
SCENE grscene_bird_fly_out_window = sc_no_change;
SCENE grscene_bird_fly_tree1 = sc_no_change;
SCENE grscene_bird_fly_tree2 = sc_no_change;
SCENE grscene_bird_fly_tree3 = sc_no_change;
SCENE grscene_bird_fly_tree4 = sc_no_change;
SCENE grscene_bird_fly_tree5 = sc_no_change;
SCENE grscene_bird_fly_tree6 = sc_no_change;
SCENE grscene_bird_fly_tree7 = sc_no_change;
SCENE grscene_bird_fly_tree8 = sc_no_change;
SCENE grscene_bird_fly_last = sc_no_change;


SCENE grscenepart3 = sc_no_change;
SCENE grscenepart4 = sc_no_change;
SCENE grscenepart5 = sc_no_change;
SCENE grsceneclose = sc_no_change;
SCENE grscene_present_by = sc_no_change;
SCENE grscene_mentored_by = sc_no_change;
SCENE grscene_music_by = sc_no_change;
SCENE grscene_the_end = sc_no_change;
SCENE grscene_technology_used = sc_no_change;

// human
SCENE grscene_human = sc_no_change;
SCENE grscene_human_move_in_relief = sc_no_change;


GLfloat yPosRain = 2.0f;
GLfloat rainYArray[] =
{
	0.134f,
	0.241111f,
	0.12873f,
	0.170098f,
	0.072f,
	0.31745f,
	0.255f,
	0.0923f,
	0.3264f,
	0.288f
};
struct Node
{
	float dataX;
	float dataY;
	float dataZ;
	struct Node* next;
};
struct Node* start = NULL;
struct Node* tempTraverse = NULL;

GLfloat i, j;
GLint ii, ij;
GLfloat x, y, z;
GLfloat grbirdX = 7.0f;
GLfloat grbirdY = 0.0f;
GLint grbirdWings = -20;
GLint grbirdWings2 = -20;
GLint grbirdRotateAround = 0;
GLint grbirdRotateItself = 180;
int grrotateBird = 0;
bool bFly = true;
bool bFly2 = true;
GLfloat grskyColor = 1.0f;
GLfloat grbird2MoveX = 1.3f;
GLfloat grbirdPosX = -2.0f;
GLfloat grbirdPosY = -0.3f;
GLfloat grbirdPosZ = -17.0f;
GLfloat grbirdAngle = 0.0f;
GLfloat grCount = 0.0f;
GLfloat cameraCirclei = 0.0f;
GLfloat cameraCirclej = 0.0f;


//human
GLfloat grhumanX = 6.5f;
int grhipsRight;
int grlegsRight;
int grfeetRight;
int grlegsLeft;
int grhipsLeft;
int grfeetLeft;
int grrotate = 0;

GLfloat grcolorIntro = 0.0f;
GLfloat cameraAngleY = 12.0f;
GLfloat cameraY = 12.0f;
bool grsceneChange = false;
GLint grfogMode;
GLfloat grfogColor[] =
{
	0.0f, 0.0f, 0.05f, 1.0f
};
bool grmorning = false;
bool grbZoomWindowOut = false;
bool grbisBirdAfraid = false;
bool grbCameraBlend = false;
bool grbDisplayTitle = false;
bool grbIntroText = true;
bool grbBirdMove = true;

GLUquadric* grquadric = NULL;
GLUquadric* grquadricTree = NULL;

// textures
GLuint grtextureBird;
GLuint grtextureBirdAfraid;
GLuint grtextureLeaves;
GLuint grtextureShirt;
GLuint grtextureSoil;
GLuint grtextureSky;
GLuint grtextureBirdLightning;
GLuint grtextureMorningSky;
GLuint grtextureBirdHouseDoor;
GLuint grtextureBirdFoodCan;
GLuint grtextureWhiteColorCloud;
GLuint grtextureBedFurniture;
GLuint grtextureFoods;
GLuint grtextureSmiley;
GLuint grtextureStem;
GLuint grtextureTitle;
GLuint grtextureOcean;

GLfloat tempX1 = 0.0f;
GLfloat tempX2 = 0.0f;
GLfloat tempZ1 = 2.0f;
GLfloat tempZ2 = -100.0f;
GLfloat tempY1 = 0.0f;
GLfloat tempY2 = 0.0f;

bool grbFadeOut;

GLuint	base;
GLYPHMETRICSFLOAT gmf[256];

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
			ToggleFullScreen();
			break;

		case VK_SPACE:
			grscene = grscene + 1;
			switch (grscene)
			{
			case 1:
				grcolorIntro = 1.0f;
				PlaySound(TEXT("rain.wav"), NULL, SND_FILENAME | SND_ASYNC);
				grsceneintro = sc_no_change;
				grscenepart0 = sc_change;
				//grscenepart1 = sc_change;
				grscene_bird = sc_change;
				break;

			case 2:
				grscene_human = sc_change;
				break;

			case 3:
				//PlaySound(TEXT("httyd_forbidden_friendship.wav"), NULL, SND_FILENAME | SND_ASYNC);
				PlaySound(TEXT("httyd.wav"), NULL, SND_FILENAME | SND_ASYNC);
				grcolorIntro = 1.0f;
				grscenepart0 = sc_no_change;
				grscenepart2 = sc_change;
				glDisable(GL_FOG);
				break;

			case 4:
				grscene_bird_think_cloud = sc_change;
				grscene_cloud_think_bed = sc_change;
				break;

			case 5:
				grscene_cloud_think_bed = sc_no_change;
				grscene_cloud_think_foods = sc_change;
				break;


			case 6:
				grscene_cloud_think_foods = sc_no_change;
				grscene_cloud_think_smiley = sc_change;
				break;

			case 7:
				grscene_cloud_think_smiley = sc_no_change;
				grscene_bird_think_cloud = sc_no_change;
				break;

			case 8:
				grscene_zoom_window = sc_change;
				break;

			case 9:
				grbZoomWindowOut = true;
				grscene_bird_in_window = sc_change;
				grscene_zoom_window = sc_no_change;
				break;

			case 10:
				grbZoomWindowOut = false;
				grscene_other_bird_flying = sc_change;
				break;

			case 11:
				grscene_bird_curious = sc_change;
				break;

			case 12:
				//PlaySound(TEXT("httyd_flying_theme.wav"), NULL, SND_FILENAME | SND_ASYNC);
				grscene_other_bird_flying = sc_no_change;
				grscene_bird_fly_out_window = sc_change;
				break;

			case 13:
				grscenepart2 = sc_no_change;
				tempX1 = 0.0f;
				tempY1 = 0.0f;
				tempZ1 = 4.0f;
				tempX2 = 0.0f;
				tempY2 = 0.0f;
				tempZ2 = -100.0f;
				grscenepart3 = sc_change;
				grsceneCircleBlend = sc_change;
				break;

			case 14:
				grscene_bird_fly_tree1 = sc_change;
				break;

			case 15:
				grscene_bird_fly_tree1 = sc_no_change;
				grscene_bird_fly_tree2 = sc_change;
				break;

			case 16:
				grscene_bird_fly_tree2 = sc_no_change;
				grscene_bird_fly_tree3 = sc_change;
				break;

			case 17:
				grscene_bird_fly_tree3 = sc_no_change;
				grscene_bird_fly_tree4 = sc_change;
				break;

			case 18:
				grscene_bird_fly_tree4 = sc_no_change;
				grscene_bird_fly_tree5 = sc_change;
				break;

			case 19:
				grscene_bird_fly_tree5 = sc_no_change;
				grscene_bird_fly_tree6 = sc_change;
				break;

			case 20:
				grsceneCircleBlend = sc_no_change;
				grscene_bird_fly_tree6 = sc_no_change;
				grscene_bird_fly_tree7 = sc_change;
				break;

			case 21:
				grscene_bird_fly_tree7 = sc_no_change;
				grscene_bird_fly_tree8 = sc_change;
				break;

			

			case 22:
				tempX1 = 0.0f;
				tempY1 = 0.0f;
				tempZ1 = 0.0f;
				tempX2 = 0.0f;
				tempY2 = 0.0f;
				tempZ2 = -100.0f;
				grfangle = -20.0f;
				grscenepart3 = sc_no_change;
				grscenepart5 = sc_change;
				break;

			case 23:
				tempX1 = 0.0f;
				tempY1 = 0.0f;
				tempZ1 = 2.0f;
				tempX2 = 0.0f;
				tempY2 = 0.0f;
				tempZ2 = -100.0f;
				cameraAngleY = 12.0f;
				cameraY = 12.0f;
				grbirdAngle = 0.0f;
				grfangle = 0.0f;
				grbirdPosZ = 0.0f;
				grbirdPosX = 0.0f;
				grscenepart5 = sc_no_change;
				grscenepart4 = sc_change;
				break;
			

			case 24:
				PlaySound(TEXT("end_credits.wav"), NULL, SND_FILENAME | SND_ASYNC);
				grscenepart4 = sc_no_change;
				grsceneclose = sc_change;
				grcolorIntro = 0.0f;
				grscene_present_by = sc_change;
				break;

			case 25:
				grscene_present_by = sc_no_change;
				grscene_mentored_by = sc_change;
				break;

			case 26:
				grscene_mentored_by = sc_no_change;
				grscene_technology_used = sc_change;
				break;

			case 27:
				grscene_technology_used = sc_no_change;
				grscene_music_by = sc_change;
				break;

			case 28:
				grscene_music_by = sc_no_change;
				grscene_the_end = sc_change;
				break;
			}
			break;


		case VK_DOWN:
			cameraY = cameraY - 0.1f;
			cameraAngleY = cameraAngleY - 0.1f;
			break;

		case VK_UP:
			cameraY = cameraY + 0.1f;
			cameraAngleY = cameraAngleY + 0.1f;
			break;

		case VK_SUBTRACT:
			cameraAngleY = cameraAngleY + 0.01f;
			break;

		case VK_ADD:
			cameraAngleY = cameraAngleY - 0.01f;
			break;

		case VK_LEFT:
			if (grbBirdMove)
			{
				grCount = grCount + 0.10f;
				grbirdRotateAround = (grbirdRotateAround + 3) % 360;
				if (grbirdRotateAround < 180)
					grbirdRotateItself = 180 + 360 - grbirdRotateAround;
				else if (grbirdRotateAround % 180 == 0)
				{
					grbirdRotateItself = grbirdRotateItself + 180;
				}
				else
					grbirdRotateItself = 360 - grbirdRotateAround;


				if (grCount >= 12.0f && grCount <= 13.0f)
				{
					grscene_rain = sc_change;
				}
				else if (grCount >= 30.70f && grCount <= 31.0f)
				{
					grscene_heavy_rain = sc_change;
				}
				else if (grCount >= 36.0f && grCount <= 36.5f)
				{
					glEnable(GL_FOG);
					grfogMode = GL_LINEAR;
					glFogi(GL_FOG_MODE, grfogMode);
					glFogfv(GL_FOG_COLOR, grfogColor);
					glFogf(GL_FOG_DENSITY, 0.75);
					glHint(GL_FOG_HINT, GL_DONT_CARE);
					glFogf(GL_FOG_START, 3.0f);
					glFogf(GL_FOG_END, 25.0f);

					glFogi(GL_FOG_MODE, grfogMode);
				}
				else if (grCount >= 39.5f && grCount <= 39.8f)
				{
					grscene_bird_afraid = sc_change;
				}
				else if (grCount >= 42.0f && grCount <= 42.8f)
				{
					grsceneChange = !grsceneChange;
					if (grsceneChange == true)
					{
						grscenepart0 = sc_no_change;
						grscene_bird_lightning = sc_change;
					}
					else
					{
						grscene_bird_lightning = sc_no_change;
						grscenepart0 = sc_change;
						grscene_bird_fell = sc_change;
					}
				}
				else if (grCount > 42.8f)
				{
					grbBirdMove = false;
				}
			}

			break;

		case VK_RIGHT:
			grCount = grCount + 0.10f;
			grbirdRotateAround = (grbirdRotateAround + 3) % 360;
			if (grbirdRotateAround < 180)
				grbirdRotateItself = 180 + 360 - grbirdRotateAround;
			else if (grbirdRotateAround % 180 == 0)
			{
				grbirdRotateItself = grbirdRotateItself + 180;
			}
			else
				grbirdRotateItself = 360 - grbirdRotateAround;
			break;

		case VK_NUMPAD4:
			tempX1 = tempX1 + 0.1f;
			//fprintf(grgpFile, "\n 4 tempX1 : %f", tempX1);
			break;

		case VK_NUMPAD6:
			tempX1 = tempX1 - 0.1f;
			//fprintf(grgpFile, "\n 6 tempX1 : %f", tempX1);
			break;

		case VK_NUMPAD7:
			tempX2 = tempX2 + 0.1f;
			//fprintf(grgpFile, "\n 7 tempX2 : %f", tempX2);
			break;

		case VK_NUMPAD9:
			tempX2 = tempX2 - 0.1f;
			//fprintf(grgpFile, "\n 9 tempX2 : %f", tempX2);
			break;

		case VK_NUMPAD8:
			tempZ1 = tempZ1 + 0.1f;
			//fprintf(grgpFile, "\n 8 tempZ1 : %f", tempZ1);
			break;

		case VK_NUMPAD2:
			tempZ1 = tempZ1 - 0.1f;
			tempZ2 = tempZ2 - 0.1f;
			//fprintf(grgpFile, "\n 2 tempZ1 : %f", tempZ1);
			break;

		case VK_NUMPAD5:
			tempZ2 = tempZ2 + 0.1f;
			//fprintf(grgpFile, "\n 5 tempZ2 : %f", tempZ2);
			break;

		case VK_NUMPAD0:
			tempZ2 = tempZ2 - 0.1f;
			//fprintf(grgpFile, "\n 0 tempZ2 : %f", tempZ2);
			break;

		case VK_NUMPAD1:
			tempY1 = tempY1 - 0.1f;
			//fprintf(grgpFile, "\n 1 tempY1 : %f", tempY1);
			break;

		case VK_NUMPAD3:
			tempY1 = tempY1 + 0.1f;
			//fprintf(grgpFile, "\n 3 tempY1 : %f", tempY1);
			break;

		case VK_MULTIPLY:
			tempY2 = tempY2 + 0.1f;
			break;

		case VK_DIVIDE:
			tempY2 = tempY2 - 0.1f;
			break;

		default:
			break;
		}
		break;


	case WM_CHAR:
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


		case 'E':
			grlegsRight = (grlegsRight - 2) % grhipsRight;
			break;

		case 'r':
			/*
			grrotate = grrotate + 1;
			grhipsRight = 0;
			grlegsRight = 0;
			grfeetRight = 0;
			grlegsLeft = 0;
			grlegsLeft = 0;
			grfeetLeft = 0;
			*/
			grfangle = grfangle + 0.2f;
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


		case 'i':
		case 'I':

			// fog

			/*
			if (grfogMode == GL_EXP)
			{
				grfogMode = GL_EXP2;

			}
			else if (grfogMode == GL_EXP2)
			{
				grfogMode = GL_LINEAR;
			}
			else if (grfogMode == GL_LINEAR)
			{
				grfogMode = GL_EXP;
			}
			*/

			//grfogDensity = grfogDensity + 0.1f;
			glEnable(GL_FOG);
			grfogMode = GL_LINEAR;
			glFogi(GL_FOG_MODE, grfogMode);
			glFogfv(GL_FOG_COLOR, grfogColor);
			glFogf(GL_FOG_DENSITY, 0.75);
			glHint(GL_FOG_HINT, GL_DONT_CARE);
			glFogf(GL_FOG_START, 3.0f);
			glFogf(GL_FOG_END, 25.0f);

			glFogi(GL_FOG_MODE, grfogMode);

			break;

		case 'x':
		case 'X':
			grbisBirdAfraid = !grbisBirdAfraid;
			if (grbisBirdAfraid)
			{
				grscene_bird_afraid = sc_change;
			}
			else
			{
				grscene_bird_afraid = sc_no_change;
			}

			break;

		case 'y':
		case 'Y':
			//grscenepart0 = sc_no_change;
			//grscenepart1 = sc_no_change;
			grsceneChange = !grsceneChange;
			if (grsceneChange == true)
			{
				grscenepart0 = sc_no_change;
				grscene_bird_lightning = sc_change;
			}
			else
			{
				grscene_bird_lightning = sc_no_change;
				grscenepart0 = sc_change;
				grscene_bird_fell = sc_change;
			}
			break;

		case 'u':
			//fprintf(grgpFile, "\n coords birdX : %f, birdY : %f", grbirdX, grbirdY);
			grscene_rain = sc_change;
			break;

		case 'v':

			grscene_bird_fell = sc_change;
			break;

		case 'o':
			if (grscene_morning == sc_change)
			{
				if (grmorning == false)
				{
					if (grskyColor <= 1.0f)
					{
						grskyColor = grskyColor + 0.02f;
					}
					else
					{
						grmorning = true;
					}
				}


				else
				{
					if (grmorning == true)
					{
						if (grskyColor >= 0.0f)
						{
							grskyColor = grskyColor - 0.02f;
						}
						else
						{
							grmorning = false;
							grscene_morning = sc_no_change;
						}

					}

				}

			}
			else
			{
				if (grmorning == false)
				{
					if (grskyColor <= 1.0f)
					{
						grskyColor = grskyColor + 0.02f;
					}
					else
					{
						grmorning = true;
					}


				}
				else
				{
					if (grskyColor >= 0.0f)
					{
						grskyColor = grskyColor - 0.02f;
					}
					else
					{
						grmorning = false;
						grscene_morning = sc_change;
					}
				}

			}

			break;

		case 'p':
			grscene_morning = sc_change;

			break;

		case 'k':
			grscenepart0 = sc_no_change;
			grbCameraBlend = !grbCameraBlend;
			if (grbCameraBlend)
				grsceneCircleBlend = sc_change;
			else
				grsceneCircleBlend = sc_no_change;
			break;

		case 'q':
			grscene_heavy_rain = sc_change;
			break;

		case 't':
			grbirdPosZ = grbirdPosZ - 0.1f;
			break;

		case 'g':
			grbirdPosX = grbirdPosX - 0.1f;
			break;

		case 'h':
			grbirdPosX = grbirdPosX + 0.1f;
			grbirdPosZ = grbirdPosZ - 0.06f;
			break;

		case 'j':
			grbirdPosZ = grbirdPosZ + 0.1f;
			break;

		case 'b':
			/*fprintf(grgpFile, "\n tempX1 : %f, tempY1 : %f, tempZ1 : %f, tempX2 : %f, tempY2 : %f, tempZ2 : %f, grfangle : %f", tempX1,
				tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2);
				*/
			grbirdPosX= grbirdPosX + 0.1f;
			grbirdPosZ = grbirdPosZ - 0.1f;
			break;

		case 'n':
			grbirdAngle = grbirdAngle + 2.0f;
			break;

		case 'm':
			grbirdAngle = grbirdAngle - 2.0f;
			break;

		case 'c':
			if (grbirdAngle <= 360.0f)
				grbirdAngle = grbirdAngle + 0.1f;
			break;

		case 'e':
			/*
			tempY2 = tempY2 + 0.3f;
			tempZ2 = -4.0f;
			*/

			//tempZ2 = -4.0f;
			cameraCirclei = cameraCirclei + 0.01f;
			if (cameraCirclei <= 2.0f * PI)
			{
				//tempX2 = sin(cameraCirclei);
				tempZ2 = -2.0f + cos(cameraCirclei);
				//tempX1 = -2.0f + sin(cameraCirclei);
				tempX2 = -2.0f - sin(cameraCirclei);
			}
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
	void BuildFont();

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
	grpfd.cDepthBits = 32;

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

	// insert data in linked list
	InsertNode(-3.5f, -1.0f, -8.0f);
	InsertNode(5.5f, -1.0f, -12.0f);
	InsertNode(2.0f, -1.0f, -15.0f);
	//InsertNode(0.0f, -1.0f, -13.0f);
	InsertNode(-3.0f, -1.5f, -12.0f);
	//InsertNode(-7.5f, -1.0f, -11.0f);
	InsertNode(7.0f, -1.0f, -10.0f);


	// set clearcolor
	//glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// textures
	LoadGLTexture(&grtextureBirdAfraid, MAKEINTRESOURCE(GRBIRD_AFRAID));
	LoadGLTexture(&grtextureBird, MAKEINTRESOURCE(GRBIRD));
	LoadGLTexture(&grtextureLeaves, MAKEINTRESOURCE(GRLEAVES));
	LoadGLTexture(&grtextureShirt, MAKEINTRESOURCE(GRSHIRT));
	LoadGLTexture(&grtextureBirdLightning, MAKEINTRESOURCE(GRBIRD_LIGHTNING));
	LoadGLTexture(&grtextureSky, MAKEINTRESOURCE(GRSKY));
	LoadGLTexture(&grtextureSoil, MAKEINTRESOURCE(GRSOIL));
	LoadGLTexture(&grtextureMorningSky, MAKEINTRESOURCE(GRMORNING_SKY));
	LoadGLTexture(&grtextureBirdHouseDoor, MAKEINTRESOURCE(GRBIRD_HOUSE_DOOR));
	LoadGLTexture(&grtextureBirdFoodCan, MAKEINTRESOURCE(GRBIRD_FOOD_CAN));
	LoadGLTexture(&grtextureWhiteColorCloud, MAKEINTRESOURCE(GRWHITE_COLOR_CLOUD));
	LoadGLTexture(&grtextureBedFurniture, MAKEINTRESOURCE(GRBED_FURNITURE));
	LoadGLTexture(&grtextureFoods, MAKEINTRESOURCE(GRFOODS));
	LoadGLTexture(&grtextureSmiley, MAKEINTRESOURCE(GRSMILEY));
	LoadGLTexture(&grtextureStem, MAKEINTRESOURCE(GRSTEM));
	LoadGLTexture(&grtextureTitle, MAKEINTRESOURCE(GRTITLE));
	LoadGLTexture(&grtextureOcean, MAKEINTRESOURCE(GROCEAN));


	// enable texture
	glEnable(GL_TEXTURE_2D);
	BuildFont();
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// MAG - Magnification
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);				// MIN - Minification
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
	// function declaration
	void Update(void);
	void TreeCode();
	void ThinkCloud();
	void DisplayFont(const char* fmt, ...);

	// code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (grsceneintro == sc_change)
	{
		glPushMatrix();
		glLoadIdentity();

#pragma region sky code

		glPushMatrix();
		glLoadIdentity();
		gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -17.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		//glBindTexture(GL_TEXTURE_2D, grtextureSky);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(25.0f, 20.0f, 0.0f);									// right top
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-25.0f, 20.0f, 0.0f);									// left top

		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		//glTexCoord2f(0.0f, 0.0f);										// left bottom
		glVertex3f(-25.0f, -2.7f, 0.0f);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(25.0f, -2.7f, 0.0f);									// right bottom
		//glColor3f(0.5290f, 0.8080f, 0.9220f);

		glEnd();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glPopMatrix();


#pragma endregion sky code
		if (grbIntroText)
		{
			// font
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.5f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.4f, 0.5f, 0.0f);
			DisplayFont("AstroMediComp Presents", "-%1.0f"); //
			glPopMatrix();
		}


		else if (grbDisplayTitle)
		{
			// rectangle for title
			glPushMatrix();
			glLoadIdentity();

			glTranslatef(0.0f, 0.0f, -6.0f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glBindTexture(GL_TEXTURE_2D, grtextureTitle);
			glBegin(GL_QUADS);
			//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.5f, 1.0f, 0.0f);									// right top
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-1.5f, 1.0f, 0.0f);									// left top
			glTexCoord2f(0.0f, 0.0f);										// left bottom
			glVertex3f(-1.5f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.5f, -1.0f, 0.0f);									// right bottom
			glEnd();
			glPopMatrix();
		}


		glPopMatrix();
	}

	else if (grscenepart0 == sc_change)
	{
		glLoadIdentity();
		gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, -100.0f, 0.0f, 1.0f, 0.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/////////////////////////////////////////////////////////////// BIRD //////////////////////////////////




		if (grscene_rain == sc_change)
		{

			if (grscene_heavy_rain == sc_change)
			{

				if (yPosRain >= -2.0f && yPosRain <= 2.0f)
				{
					y = 0.0f;
					yPosRain = yPosRain - 0.04f;
					glPushMatrix();
					ii = 10;
					for (x = -5.5f; x <= 5.5f; x = x + 0.1f)
					{
						ii--;
						if (ii == 0)
							ii = 9;
						glLoadIdentity();
						glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
						glLineWidth(0.8f);
						glBegin(GL_LINES);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
						glEnd();

					}
					glPopMatrix();

				}
				else
				{
					yPosRain = 0.0f;
				}
				y = -0.2f;
				glPushMatrix();
				ii = 0;
				for (x = -5.5f; x <= 5.5f; x = x + 0.132)
				{
					i++;
					if (i == 10)
						i = 0;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				// 3
				y = -0.4f;
				glPushMatrix();
				ii = 10;
				for (x = -5.3f; x <= 5.5f; x = x + 0.12f)
				{
					ii--;
					if (ii == 0)
						ii = 9;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				// 4
				y = -0.6f;
				glPushMatrix();
				ii = 10;
				for (x = -5.5f; x <= 5.5f; x = x + 0.1176f)
				{
					ii--;
					if (ii == 0)
						ii = 9;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				//5
				y = -0.8f;
				glPushMatrix();
				ii = 0;
				for (x = -5.0f; x <= 5.5f; x = x + 0.125f)
				{
					//for(y = 2.5f; y )

					ii++;
					if (ii == 7)
						ii = 0;
					glLoadIdentity();
					glTranslatef(x, yPosRain + y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				// 6
				y = -1.0f;
				glPushMatrix();
				ii = 1;
				for (x = -5.5f; x <= 5.5f; x = x + 0.11f)
				{
					ii++;
					if (ii == 9)
						ii = 0;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				// 7
				y = -1.2f;
				glPushMatrix();
				ii = 5;
				for (x = -5.5f; x <= 5.5f; x = x + 0.14f)
				{
					ii++;
					if (ii == 10)
						ii = 0;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				//8
				y = -1.4f;
				glPushMatrix();
				ii = 8;
				for (x = -5.5f; x <= 5.5f; x = x + 0.142f)
				{
					ii++;
					if (ii == 10)
						ii = 0;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				//9
				y = -1.7f;
				glPushMatrix();
				ii = 7;
				for (x = -5.5f; x <= 5.5f; x = x + 0.15f)
				{
					ii--;
					if (ii == 3)
						ii = 9;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				// 10
				y = -1.9f;
				glPushMatrix();
				ii = 3;
				for (x = -5.5f; x <= 5.5f; x = x + 0.1f)
				{
					ii--;
					if (ii == 1)
						ii = 9;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				//11
				y = -2.2f;
				glPushMatrix();
				ii = 9;
				for (x = -5.5f; x <= 5.5f; x = x + 0.1f)
				{
					ii--;
					if (ii == 5)
						ii = 9;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				//12 
				y = -2.3f;
				glPushMatrix();
				ii = 0;
				for (x = -5.5f; x <= 5.5f; x = x + 0.1f)
				{
					ii++;
					if (ii == 9)
						ii = 0;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				//13 
				y = -2.5f;
				glPushMatrix();
				ii = 2;
				for (x = -5.5f; x <= 5.5f; x = x + 0.1f)
				{
					ii++;
					if (ii == 9)
						ii = 4;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();

				//14 
				y = -2.72f;
				glPushMatrix();
				ii = 9;
				for (x = -5.5f; x <= 5.5f; x = x + 0.12f)
				{
					ii++;
					if (ii == 2)
						ii = 8;
					glLoadIdentity();
					glTranslatef(x, yPosRain - y - rainYArray[ii], -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 0.2f);
					glVertex3f(x, yPosRain - y - rainYArray[ii], 0.0f);
					//glColor3f(0.9f, 0.9f, 0.9f);
					glColor3f(0.7f, 0.7f, 0.7f);
					glVertex3f(x, yPosRain - y - rainYArray[ii] - 0.09f, 0.0f);
					glEnd();

				}
				glPopMatrix();


			}
			else
			{

				for (ii = 0; ii <= 20000; ii++)
				{

					//2
					glPushMatrix();
					glLoadIdentity();
					glTranslatef(0.0f, 0.0f, -4.0f);
					glLineWidth(0.8f);
					glBegin(GL_LINES);
					for (ii = 0; ii <= 20000; ii++)
					{

						x = ((GLfloat)rand() / 20.0f) * 0.5f;
						y = ((GLfloat)rand() / 20.0f) * 0.5f;
						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, y, 0.0f);
						glColor3f(0.7f, 0.7f, 0.7f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glVertex3f(-x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, -y, 0.0f);
						glColor3f(0.7f, 0.7f, 0.7f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glVertex3f(-x, -y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, -y, 0.0f);
						glColor3f(0.7f, 0.7f, 0.7f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glVertex3f(x, -y - 0.09f, 0.0f);

					}
					glEnd();
					glPopMatrix();

					//3
					glPushMatrix();
					glLoadIdentity();
					glTranslatef(0.0f, 0.0f, -4.0f);
					glBegin(GL_LINES);
					for (ii = 0; ii <= 20000; ii++)
					{

						x = ((GLfloat)rand() / 20.0f) * 0.2f;
						y = ((GLfloat)rand() / 20.0f) * 0.2f;
						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(-x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, -y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(-x, -y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, -y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, -y - 0.09f, 0.0f);

					}
					glEnd();
					glPopMatrix();

					// 4
					glPushMatrix();
					glLoadIdentity();
					glTranslatef(0.0f, 0.0f, -4.0f);
					glBegin(GL_LINES);
					for (ii = 0; ii <= 20000; ii++)
					{

						x = ((GLfloat)rand() / 20.0f) * 0.3f;
						y = ((GLfloat)rand() / 20.0f) * 0.3f;
						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(-x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, -y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(-x, -y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, -y, 0.0f);
						//glColor3f(0.9f, 0.9f, 0.9f);
						glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, -y - 0.09f, 0.0f);

					}
					glEnd();
					glPopMatrix();

					// 5
					glPushMatrix();
					glLoadIdentity();
					glTranslatef(0.0f, 0.0f, -4.0f);

					glBegin(GL_LINES);
					for (ii = 0; ii <= 20000; ii++)
					{

						x = ((GLfloat)rand() / 20.0f) * 0.35f;
						y = ((GLfloat)rand() / 20.0f) * 0.35f;
						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, y, 0.0f);
						glColor3f(0.9f, 0.9f, 0.9f);
						//glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, y, 0.0f);
						glColor3f(0.9f, 0.9f, 0.9f);
						//glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(-x, y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(-x, -y, 0.0f);
						glColor3f(0.9f, 0.9f, 0.9f);
						//glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(-x, -y - 0.09f, 0.0f);

						glColor3f(0.0f, 0.0f, 0.2f);
						glVertex3f(x, -y, 0.0f);
						glColor3f(0.9f, 0.9f, 0.9f);
						//glColor3f(0.7f, 0.7f, 0.7f);
						glVertex3f(x, -y - 0.09f, 0.0f);

					}
					glEnd();
					glPopMatrix();
				}


			}
		}
		if (grscenepart1 == sc_change)
		{
#pragma region bird code
			gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
			glLoadIdentity();

			glPushMatrix();																				// 1

			glTranslatef(grbirdX, grbirdY, -6.0f);


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
			//glColor3f(1.0f, 1.0f, 1.0f);
			glColor3f(1.0f, 0.616f, 0.769f);
			//glColor3f(1.0f, 0.616f, 0.617f);
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
			//glColor3f(1.0f, 0.412f, 0.706f);
			glColor3f(1.0f, 0.616f, 0.769f);
			//glColor3f(1.0f, 1.0f, 1.0f);
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
			//glBindTexture(GL_TEXTURE_2D, NULL);
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
		else
		{
#pragma region bird code
			gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
			glLoadIdentity();

			glPushMatrix();
			glTranslatef(-1.0f, 0.0f, -8.0f);

			glPushMatrix();																				// 1
			glRotatef((GLfloat)grbirdRotateAround, 0.0f, 1.0f, 0.0f);
			glTranslatef(grbirdX, grbirdY, 0.0f);
			glRotatef((GLfloat)grrotateBird, 1.0f, 0.0f, 0.0f);
			glRotatef((GLfloat)grbirdRotateItself, 0.0f, 1.0f, 0.0f);		// axis changed 

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
			//glColor3f(1.0f, 1.0f, 1.0f);
			glColor3f(1.0f, 0.616f, 0.769f);
			//glColor3f(1.0f, 0.616f, 0.617f);
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
			//glColor3f(1.0f, 0.412f, 0.706f);
			glColor3f(1.0f, 0.616f, 0.769f);
			//glColor3f(1.0f, 1.0f, 1.0f);
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
			//glBindTexture(GL_TEXTURE_2D, NULL);
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
			glPopMatrix();
#pragma endregion bird code
		}

#pragma region humanoid code
		glPushMatrix();

		glTranslatef(grhumanX, -1.5f, -5.0f);
		glScalef(0.3f, 0.3f, 0.3f);
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

		//if (grscene_human_goggles == sc_no_change)
		//{
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


		//}
		/*
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


			// smile 1
			//glPushMatrix();
			//glTranslatef(-0.2f, 1.2f, 0.0f);
			//glScalef(0.3f, 0.05f, 0.23f);
			//glColor3f(0.1f, 0.0f, 0.0f);
			//grquadric = gluNewQuadric();
			//gluSphere(grquadric, 0.5, 10, 10);
			//glPopMatrix();

			// smile 2
			//glPushMatrix();
			//glTranslatef(-0.2f, 1.17f, 0.0f);
			//glScalef(0.2f, 0.05f, 0.19f);
			//glColor3f(0.1f, 0.0f, 0.0f);
			//grquadric = gluNewQuadric();
			//gluSphere(grquadric, 0.5, 10, 10);
			//glPopMatrix();


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
		*/


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
		gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -2.0f, -15.0f);
		//glColor3f(0.910f, 0.7140f, 0.310f);
		//glColor3f(0.46270f, 0.36570f, 0.17160f); // dark brown
		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, grtextureSoil);
		glBegin(GL_QUADS);
		glTexCoord2f(4.0f, 4.0f);
		glVertex3f(25.0f, 0.0f, -15.0f); // right top
		glTexCoord2f(0.0f, 4.0f);
		glVertex3f(-25.0f, 0.0f, -15.0f);//lt
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-25.0f, 0.0f, 15.0f);//rb
		glTexCoord2f(4.0f, 0.0f);
		glVertex3f(25.0f, 0.0f, 15.0f);//lb
		glEnd();
		// working code 1 for soil
		/*
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
		*/
		glPopMatrix();

#pragma endregion soil code

#pragma region sky code

		glPushMatrix();
		glLoadIdentity();
		gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 1.0f, -17.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureSky);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(25.0f, 20.0f, 0.0f);									// right top
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-25.0f, 20.0f, 0.0f);									// left top

		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		glTexCoord2f(0.0f, 0.0f);										// left bottom
		glVertex3f(-25.0f, -2.7f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(25.0f, -2.7f, 0.0f);									// right bottom
		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		//glBindTexture(GL_TEXTURE_2D, NULL);

		glEnd();
		glPopMatrix();


#pragma endregion sky code

		//////////////////////////////////////////////////////////// TREE ////////////////////////////////

		tempTraverse = start;
		while (tempTraverse != NULL)
		{
			glPushMatrix();
			glLoadIdentity();
			gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(tempTraverse->dataX, tempTraverse->dataY, tempTraverse->dataZ);

			//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			//glRotatef((GLfloat)grrotate, 0.0f, 1.0f, 0.0f);
				// STEM
			glPushMatrix();
			glTranslatef(0.0f, 1.3f, 0.0f);
			glColor3f(0.3f, 0.22f, 0.0f);
			glScalef(0.8f, 4.7f, 0.8f);
			grquadricTree = gluNewQuadric();
			gluSphere(grquadricTree, 0.7f, 40, 40);
			glPopMatrix();


			glTranslatef(0.0f, 2.5f, 0.0f);
			TreeCode();
			glPopMatrix();

			tempTraverse = tempTraverse->next;
		}

		// fade in effect via quad
#pragma region fade in

		glPushMatrix();
		//gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, -100.0f, 0.0f, 1.0f, 0.0f);
		glLoadIdentity();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTranslatef(0.0f, 0.0f, -5.5f);
		glColor4f(0.0f, 0.0f, 0.0f, grcolorIntro);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		glVertex3f(10.0f, 5.0f, 0.0f);									// right top
		glVertex3f(-10.0f, 5.0f, 0.0f);									// left top
		glVertex3f(-10.0f, -5.0f, 0.0f);
		glVertex3f(10.0f, -5.0f, 0.0f);									// right bottom
		glEnd();
		glDisable(GL_BLEND);
		glPopMatrix();

#pragma endregion fade in

	}

	else if (grscene_bird_lightning == sc_change)
	{
		//fprintf(grfgpFile, "\n lightning scene");

		glPushMatrix();
		glLoadIdentity();

		glTranslatef(0.0f, 0.0f, -17.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureBirdLightning);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(12.55f, 7.4f, 0.0f);									// right top
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-12.55f, 7.4f, 0.0f);									// left top

		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		glTexCoord2f(0.0f, 0.0f);										// left bottom
		glVertex3f(-12.55f, -7.4f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(12.55f, -7.4f, 0.0f);									// right bottom
		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		//glBindTexture(GL_TEXTURE_2D, NULL);

		glEnd();
		glPopMatrix();
	}

	else if (grscenepart2 == sc_change)
	{

#pragma region room
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		// central wall
		glTranslatef(0.0f, 0.0f, -20.0f);
		glColor3f(0.90f, 0.87f, 0.36f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -5.0f, -20.0f);
		glColor3f(1.0f, 0.73f, 0.06f);
		//glColor3f(1.0f, 0.992f, 0.816f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
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
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(10.0f, 0.0f, -20.0f);
		glColor3f(0.92f, 0.92f, 0.44f); // blue color
		glBegin(GL_QUADS);
		glVertex3f(0.0f, 7.0f, -0.05f);	// right top
		glVertex3f(0.0f, 7.0f, 0.0f);	// left top
		glVertex3f(0.0f, -5.0f, 0.0f);	// left bottom
		glVertex3f(0.0f, -5.0f, -0.05f);		// right bottom
		glEnd();
		glPopMatrix();

		// window grill
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.0f, 0.0f, -19.0f);
		glColor3f(0.3f, 0.3f, 0.3f); // grey color
		glBegin(GL_LINES);
		for (i = 1.0f; i < 8.0f; i = i + 1.0f)
		{
			glVertex3f(i, 3.83f, 0.0f);
			glVertex3f(i, -1.0f, 0.0f);
		}
		glEnd();
		glPopMatrix();

		if (grscene_morning == sc_change)
		{
			glPushMatrix();
			glLoadIdentity();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(1.0f, 0.0f, -19.5f);
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glColor3f(grskyColor, grskyColor, grskyColor); // blue color
			glBindTexture(GL_TEXTURE_2D, grtextureMorningSky);

			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(8.0f, 4.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f, 4.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(8.0f, -1.0f, 0.0f);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, NULL);
			glPopMatrix();


			glPopMatrix();
		}

		else
		{
			glPushMatrix();
			glLoadIdentity();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(1.0f, 0.0f, -19.5f);

			// black sky
			glPushMatrix();
			//glLoadIdentity();
			glTranslatef(0.0f, 0.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_QUADS);

			glVertex3f(8.0f, 4.0f, 0.0f);

			glVertex3f(0.0f, 4.0f, 0.0f);

			glVertex3f(0.0f, -1.0f, 0.0f);

			glVertex3f(8.0f, -1.0f, 0.0f);
			glEnd();
			glPopMatrix();


			// stars
			glPushMatrix();
			glLoadIdentity();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(2.5f, 2.0f, -19.5f);
			glColor3f(1.0f * grskyColor, 1.0f * grskyColor, 1.0f * grskyColor);
			glPointSize(2.5f);

			glPushMatrix();
			glPointSize(1.5f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.8f, 0.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(5.0f, 0.3f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(3.0f, -1.0f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(4.2f, -0.8f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(2.2f, -0.6f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();


			glPushMatrix();
			glTranslatef(4.8f, -0.8f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();


			glPushMatrix();
			glTranslatef(5.3f, -1.8f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.8f, -1.4f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(2.9f, 1.2f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(1.2f, 1.4f, 0.0f);
			glBegin(GL_POINTS);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glPopMatrix();

			glPopMatrix();

			// moon
			glPushMatrix();
			glLoadIdentity();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(2.2f, 2.5f, -19.3f);
			glScalef(0.6f, 0.6f, 0.0f);
			glColor3f(1.0f * grskyColor, 1.0f * grskyColor, 1.0f * grskyColor);
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0.0f; i <= 2 * PI; i = i + 0.01f)
			{
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.4f * cos(i), 0.4f * sin(i), 0.0f);
			}
			glEnd();
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(2.2f, 2.5f, -19.3f);
			glScalef(0.6f, 1.0f, 0.0f);
			glColor3f(1.0f * grskyColor, 1.0f * grskyColor, 1.0f * grskyColor);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.4f, 0.0f);
			glEnd();
			glPopMatrix();

			glPopMatrix();
		}

		if (grscene_other_bird_flying == sc_change)
		{
			glPushMatrix();

			// bird flying
#pragma region bird code

			glLoadIdentity();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glPushMatrix();																				// 1

			glTranslatef(grbird2MoveX, 0.0f, -19.5f);
			//glRotatef(90, 0.0f, 1.0f, 0.0f);
			glScalef(1.2f, 1.2f, 1.2f);

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
			glRotatef((GLfloat)grbirdWings2, 1.0f, 0.0f, 0.0f);
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
			glRotatef((GLfloat)-grbirdWings2, 1.0f, 0.0f, 0.0f);
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

			glPopMatrix();
		}

		glPopMatrix();
#pragma endregion room

		if (grscene_morning == sc_no_change)
		{
#pragma region humanoid code
			glPushMatrix();
			glLoadIdentity();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(1.0f, -3.5f, -10.0f);
			glScalef(0.8f, 0.8f, 0.8f);
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

			//if (grscene_human_fear_eyes == sc_change)
			//{
			//	glPushMatrix();
			//	glTranslatef(0.0f, 1.4f, 0.0f);
			//	glScalef(0.7f, 0.7f, 0.7f);
			//	glColor3f(0.95f, 0.76f, 0.70f);		// skin color
			//	glBindTexture(GL_TEXTURE_2D, grtextureAfraidColor);
			//	grquadric = gluNewQuadric();
			//	gluQuadricTexture(grquadric, GLU_TRUE);
			//	gluSphere(grquadric, 0.5, 30, 30);
			//	glBindTexture(GL_TEXTURE_2D, NULL);
			//	glPopMatrix();

			//}
			//else
			//{
			glPushMatrix();
			glTranslatef(0.0f, 1.4f, 0.0f);
			glScalef(0.7f, 0.7f, 0.7f);
			glColor3f(0.95f, 0.76f, 0.70f);		// skin color
			grquadric = gluNewQuadric();
			gluSphere(grquadric, 0.5, 30, 30);
			glPopMatrix();

			//}

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

			//if (grscene_human_goggles == sc_no_change)
			//{

				//if (grscene_human_fear_eyes == sc_change)
				//{
				//	glPushMatrix();
				//	glTranslatef(-0.32f, 1.45f, -0.22f);
				//	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);			// to make eyes on correct angle
				//	glColor3f(0.0f, 0.0f, 0.0f);
				//	glPointSize(1.0f);
				//	glBegin(GL_POINTS);
				//	for (i = 0.0f; i <= PI * 2; i = i + 0.01f)
				//	{
				//		glVertex2f(0.05 * cos(i), 0.07 * sin(i));
				//	}
				//	glEnd();
				//	glPopMatrix();

				//	glPushMatrix();
				//	glTranslatef(-0.32f, 1.45f, 0.18f);
				//	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);			// to make eyes on correct angle
				//	glColor3f(0.0f, 0.0f, 0.0f);
				//	glPointSize(1.0f);
				//	glBegin(GL_POINTS);
				//	for (i = 0.0f; i <= PI * 2; i = i + 0.01f)
				//	{
				//		glVertex2f(0.05 * cos(i), 0.07 * sin(i));
				//	}
				//	glEnd();
				//	glPopMatrix();
				//}
				//else
				//{
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

			//}


		//}
		//else
		//{
		//	// right goggle

		//	glPushMatrix();
		//	glTranslatef(-0.22f, 1.48f, 0.14f);
		//	glScalef(0.3f, 0.3f, 0.3f);
		//	glColor3f(0.1f, 0.0f, 0.0f);
		//	grquadric = gluNewQuadric();
		//	gluSphere(grquadric, 0.5, 10, 10);
		//	glPopMatrix();



		//	// left goggle

		//	glPushMatrix();
		//	glTranslatef(-0.22f, 1.48f, -0.14f);
		//	glScalef(0.3f, 0.3f, 0.3f);
		//	glColor3f(0.1f, 0.0f, 0.0f);
		//	grquadric = gluNewQuadric();
		//	gluSphere(grquadric, 0.5, 10, 10);
		//	glPopMatrix();

		//	// goggle strip
		//	glPushMatrix();
		//	glTranslatef(-0.22f, 1.48f, 0.0f);
		//	glScalef(0.3f, 0.1f, 0.3f);
		//	glColor3f(0.1f, 0.0f, 0.0f);
		//	grquadric = gluNewQuadric();
		//	gluSphere(grquadric, 0.5, 10, 10);
		//	glPopMatrix();

		//	// right strip
		//	glPushMatrix();
		//	glTranslatef(0.0f, 1.48f, 0.1f);
		//	glScalef(0.6f, 0.1f, 0.55f);
		//	glColor3f(0.1f, 0.0f, 0.0f);
		//	grquadric = gluNewQuadric();
		//	gluSphere(grquadric, 0.5, 10, 10);
		//	glPopMatrix();

		//	// left strip
		//	glPushMatrix();
		//	glTranslatef(0.0f, 1.48f, -0.1f);
		//	glScalef(0.6f, 0.1f, 0.55f);
		//	glColor3f(0.1f, 0.0f, 0.0f);
		//	grquadric = gluNewQuadric();
		//	gluSphere(grquadric, 0.5, 10, 10);
		//	glPopMatrix();

		//	glPushMatrix();
		//	glTranslatef(-0.33f, 1.22f, 0.0f);
		//	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		//	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		//	glColor3f(0.0f, 0.0f, 0.0f);
		//	glPointSize(1.2f);
		//	glBegin(GL_POINTS);
		//	for (i = 0.0f; i < 0.8 * PI; i = i + 0.01f)
		//	{
		//		//glVertex2f(0.0f, 0.0f);
		//		glVertex3f(0.04f * cos(i), 0.03f * sin(i), 0.0095f);
		//	}
		//	glEnd();
		//	glPopMatrix();
		//}



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
		}


#pragma region house
		// house
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(-5.8f, 0.0f, -18.0f);
		glScalef(0.5f, 0.6f, 0.6f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		//glRotatef((GLfloat)grrotate, 0.0f, 1.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, grtextureBirdHouseDoor);
		glBegin(GL_QUADS);
		// front face (all z +ve)

		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, -1.0f, 1.0f);

		glVertex3f(1.0f, -1.0f, 1.0f);

		// right face (all x +ve)
		glColor3f(0.698f, 0.133f, 0.133f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// back face (all z -ve)
		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// left face (all x -ve)

		//glColor3f(1.0, 0.627f, 0.478f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// top face (all y +ve)
		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// bottom face (all y -ve)
		glColor3f(1.0f, 0.49f, 0.3f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// roof of house
		glColor3f(0.518f, 0.122f, 0.153f);
		glVertex3f(1.0f, 1.8f, 0.0f);
		glVertex3f(-1.0f, 1.8f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// roof of house - back side
		glColor3f(0.518f, 0.122f, 0.153f);
		glVertex3f(1.0f, 1.8f, 0.0f);
		glVertex3f(-1.0f, 1.8f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		// roof of house
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.8f, 0.0f);
		glVertex3f(-1.0f, 1.8f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		// roof of house
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.8f, 0.0f);
		glVertex3f(1.0f, 1.8f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glEnd();
		glPopMatrix();

#pragma endregion house

#pragma region bird code

		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glPushMatrix();																				// 1

		if (grscene_bird_in_window == sc_no_change)
		{
			glTranslatef(-4.3f, -0.3f, -17.0f);
		}
		else if (grscene_bird_in_window == sc_change)
		{
			if (grscene_bird_fly_out_window == sc_no_change)
			{
				glTranslatef(-2.0f, -0.3f, -17.0f);
			}
			else
			{
				glTranslatef(grbirdPosX, grbirdPosY, grbirdPosZ);
				glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

			}

		}

		//glRotatef(90, 0.0f, 1.0f, 0.0f);
		glScalef(1.8f, 1.8f, 1.8f);

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
			if (grscene_bird_curious == sc_change)
			{
				/// Eyes - right afraid
				glPushMatrix();
				glTranslatef(0.2f, 0.1f, 0.1f);
				glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
				glColor3f(0.0f, 0.0f, 0.0f);
				glPointSize(1.2f);
				glBegin(GL_TRIANGLE_STRIP);
				for (i = 0.0f; i < 2.0 * PI; i = i + 0.005f)
				{
					glVertex2f(0.0f, 0.0f);
					glVertex3f(0.03f * cos(i), 0.04f * sin(i), 0.0095f);
				}
				glEnd();
				glPopMatrix();


				/// Eyes - left afraid
				glPushMatrix();
				glTranslatef(0.2f, 0.1f, 0.1f);
				glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
				glColor3f(0.0f, 0.0f, 0.0f);
				glPointSize(1.2f);
				glBegin(GL_TRIANGLE_STRIP);
				for (i = 0.0f; i < 2.0 * PI; i = i + 0.005f)
				{
					glVertex2f(0.0f, 0.0f);
					glVertex3f(0.03f * cos(i), 0.04f * sin(i), -0.0095f);
				}
				glEnd();
				glPopMatrix();

				// white color dot eye
				glPushMatrix();
				glTranslatef(0.21f, 0.11f, 0.12f);
				glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glPointSize(1.2f);
				glBegin(GL_TRIANGLE_STRIP);
				for (i = 0.0f; i < 2.0 * PI; i = i + 0.005f)
				{
					glVertex2f(0.0f, 0.0f);
					glVertex3f(0.015f * cos(i), 0.015f * sin(i), -0.0095f);
				}
				glEnd();
				glPopMatrix();
			}
			else
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


#pragma region table 
			// table
		glPushMatrix();
		//gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(-4.0f, -0.7f, -18.4f);

		// table front desk
		///
		glPushMatrix();

		glTranslatef(0.0f, 0.0f, 0.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glScalef(3.0f, 0.1f, 1.8f);
		glColor3f(0.918f, 0.749f, 0.49f);

		glBegin(GL_QUADS);
		// front face (all z +ve)
		glColor3f(0.475f, 0.3042f, 0.2208f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// right face (all x +ve)
		glColor3f(0.475f, 0.3042f, 0.2208f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// back face (all z -ve)
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// left face (all x -ve)
		glColor3f(0.475f, 0.3042f, 0.2208f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// top face (all y +ve)
		glColor3f(0.918f, 0.749f, 0.49f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// bottom face (all y -ve)
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();

		glPopMatrix();


		// table legs left
		glPushMatrix();
		glTranslatef(-2.2f, -2.18f, 0.0f);

		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(2.0f, 0.1f, 1.0f);
		glColor3f(0.475f, 0.3042f, 0.2208f);

		glBegin(GL_QUADS);
		// front face (all z +ve)
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// right face (all x +ve)
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// back face (all z -ve)
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// left face (all x -ve)
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// top face (all y +ve)
		glColor3f(0.29f, 0.18f, 0.15f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// bottom face (all y -ve)
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();

		glPopMatrix();


		// table legs right
		glPushMatrix();
		glTranslatef(2.2f, -2.18f, 0.0f);

		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(2.0f, 0.1f, 1.0f);
		glColor3f(0.475f, 0.3042f, 0.2208f);

		glBegin(GL_QUADS);
		// front face (all z +ve)
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// right face (all x +ve)
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// back face (all z -ve)
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// left face (all x -ve)
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// top face (all y +ve)
		glColor3f(0.29f, 0.18f, 0.15f);
		//glColor3f(0.55f, 0.37f, 0.18f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// bottom face (all y -ve)
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();

		glPopMatrix();


		glPopMatrix();

#pragma endregion table

#pragma region food
		// food can
		glPushMatrix();
		//gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(-3.5f, -0.08f, -18.0f);
		glScalef(0.5f, 0.5f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureBirdFoodCan);
		glColor3f(1.0f, 1.0f, 1.0f);
		//glColor3f(0.90f, 0.87f, 0.36f);
		glBegin(GL_QUADS);
		// front face (all z +ve)
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();
		glPopMatrix();
#pragma endregion food

		if (grsceneCircleBlend == sc_change)
		{

			glPushMatrix();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, -3.0f);

			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0.0f; i < 4 * 2 * PI; i = i + 0.01f)
			{
				glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
				//glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.5f * cos(i), 0.5f * sin(i), 0.0f);
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				glVertex3f(4 * cos(i), 4 * sin(i), 0.0f);
			}
			glEnd();
			glDisable(GL_BLEND);
			glPopMatrix();
		}

		// think cloud		
		if (grscene_bird_think_cloud == sc_change)
		{

			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, NULL);

			glLoadIdentity();
			//gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(-1.7f, 0.0f, 0.0f);

			glPushMatrix();
			//glLoadIdentity();
			glTranslatef(1.0f, 0.18f, -6.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glScalef(0.4f, 0.3f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			glPushMatrix();
			//glLoadIdentity();
			glTranslatef(1.25f, 0.32f, -6.0f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glScalef(0.5f, 0.4f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			// clouds
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			//glLoadIdentity();
			glTranslatef(1.5f, 0.8f, -6.0f);
			glColor3f(1.0f, 1.0f, 1.0f);

			glPushMatrix();
			glScalef(1.2f, 1.0f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.3f, 0.0f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.2f, -0.2f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.1f, -0.2f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.3f, 0.0f, 0.0f);
			glScalef(1.3f, 1.1f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.2f, 0.2f, 0.0f);
			ThinkCloud();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.1f, 0.2f, 0.0f);
			//glScalef(1.2f, 1.1f, 0.0f);
			ThinkCloud();
			glPopMatrix();


			// sleep texture
			glPushMatrix();
			glTranslatef(-0.03f, 0.0f, 0.05f);
			glScalef(0.3f, 0.25f, 0.0f);
			if (grscene_cloud_think_bed == sc_change)
			{
				glBindTexture(GL_TEXTURE_2D, grtextureBedFurniture);
			}
			else if (grscene_cloud_think_foods == sc_change)
			{
				glBindTexture(GL_TEXTURE_2D, grtextureFoods);
			}
			else if (grscene_cloud_think_smiley == sc_change)
			{
				glBindTexture(GL_TEXTURE_2D, grtextureSmiley);
			}
			//glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, NULL);
			glPopMatrix();

			glPopMatrix();
			glPopMatrix();


		}

#pragma region fade in

		glPushMatrix();
		//gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, -100.0f, 0.0f, 1.0f, 0.0f);
		glLoadIdentity();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTranslatef(0.0f, 0.0f, -5.5f);
		glColor4f(0.0f, 0.0f, 0.0f, grcolorIntro);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		glVertex3f(10.0f, 5.0f, 0.0f);									// right top
		glVertex3f(-10.0f, 5.0f, 0.0f);									// left top
		glVertex3f(-10.0f, -5.0f, 0.0f);
		glVertex3f(10.0f, -5.0f, 0.0f);									// right bottom
		glEnd();
		glDisable(GL_BLEND);
		glPopMatrix();

#pragma endregion fade in
	}

	else if (grscenepart3 == sc_change)
	{
		glPushMatrix();
		glLoadIdentity();

#pragma region soil code
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -2.0f, -15.0f);
		//glColor3f(0.910f, 0.7140f, 0.310f);
		//glColor3f(0.46270f, 0.36570f, 0.17160f); // dark brown
		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, grtextureSoil);
		glBegin(GL_QUADS);
		glTexCoord2f(4.0f, 4.0f);
		glVertex3f(25.0f, 0.0f, -15.0f); // right top
		glTexCoord2f(0.0f, 4.0f);
		glVertex3f(-25.0f, 0.0f, -15.0f);//lt
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-25.0f, 0.0f, 15.0f);//rb
		glTexCoord2f(4.0f, 0.0f);
		glVertex3f(25.0f, 0.0f, 15.0f);//lb
		glEnd();
		// working code 1 for soil
		/*
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
		*/
		glPopMatrix();

#pragma endregion soil code

#pragma region sky
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.0f, 1.0f, -27.0f);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glBindTexture(GL_TEXTURE_2D, grtextureSky);
		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(25.0f, 20.0f, 0.0f);									// right top
		glColor3f(1.0f, 0.4f, 0.0f);			// orange-ish color
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-25.0f, 20.0f, 0.0f);									// left top
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-25.0f, -2.9f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(25.0f, -2.9f, 0.0f);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, NULL);

		glPopMatrix();
#pragma endregion sky


#pragma region trees
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -6.0f);

		// tree 1
		glPushMatrix();
		glTranslatef(0.0f, 2.5f, 0.0f);
		glPushMatrix();

		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();


		// tree 2
		glPushMatrix();
		glTranslatef(-2.5f, 2.3f, -1.5f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		// tree 3
		glPushMatrix();
		glTranslatef(-1.0f, 2.1f, -3.5f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();


		// tree 4
		glPushMatrix();
		glTranslatef(-3.0f, 2.4f, -6.5f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		// tree 5
		glPushMatrix();
		glTranslatef(-1.0f, 2.4f, -9.0f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//////////////////////////////////////////////////////////////////////////////// random trees
		// 1   9.0
		glPushMatrix();
		glTranslatef(1.0f, 2.4f, -9.0f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		// 2
		glPushMatrix();
		glTranslatef(6.5f, 2.4f, -9.5f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		// 3
		glPushMatrix();
		glTranslatef(-5.0f, 2.4f, -9.0f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		// 4
		glPushMatrix();
		glTranslatef(4.0f, 2.4f, -9.0f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		// 5
		glPushMatrix();
		glTranslatef(-8.5f, 2.4f, -8.5f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		/// 1 6.5
		glPushMatrix();
		glTranslatef(-5.0f, 2.4f, -7.0f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//2
		glPushMatrix();
		glTranslatef(4.0f, 2.4f, -6.8f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//// 1 3.5
		glPushMatrix();
		glTranslatef(-4.5f, 2.1f, -4.2f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		///// 1 -1.5
		glPushMatrix();
		glTranslatef(2.5f, 2.3f, -1.0f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//2
		glPushMatrix();
		glTranslatef(4.5f, 2.3f, -1.2f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//3
		glPushMatrix();
		glTranslatef(-4.5f, 2.3f, -1.4f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//4
		glPushMatrix();
		glTranslatef(5.0f, 2.3f, -2.5f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//5
		glPushMatrix();
		glTranslatef(6.5f, 2.3f, -3.0f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		//glColor3f(0.3f, 0.22f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//6
		glPushMatrix();
		glTranslatef(-6.0f, 2.3f, -1.3f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();


		//7
		glPushMatrix();
		glTranslatef(-8.0f, 2.3f, -11.3f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		//8
		glPushMatrix();
		glTranslatef(7.0f, 2.3f, -12.3f);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureStem);
		grquadricTree = gluNewQuadric();
		gluQuadricTexture(grquadricTree, GLU_TRUE);
		gluCylinder(grquadricTree, 0.6f, 0.6f, 8.0f, 32, 32);
		glPopMatrix();

		TreeCode();
		glPopMatrix();

		glPopMatrix();

#pragma endregion trees

		// bird flying
#pragma region bird code
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glPushMatrix();																				// 1

		glTranslatef(tempX1, tempY1, tempZ1 - 0.5f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glRotatef(grbirdAngle, 1.0f, 0.0f, 0.0f);
		glScalef(0.5f, 0.5f, 0.5f);

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
		glPopMatrix();
#pragma endregion bird code


		if (grsceneCircleBlend == sc_change)
		{

			glPushMatrix();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glLoadIdentity();
			glPushMatrix();
			gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
			glTranslatef(tempX1, tempY1, tempZ1 - 2.5f);

			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0.0f; i < 4 * 2 * PI; i = i + 0.01f)
			{
				glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
				//glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.5f * cos(i), 0.5f * sin(i), 0.0f);
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				glVertex3f(4 * cos(i), 4 * sin(i), 0.0f);
			}
			glEnd();
			glDisable(GL_BLEND);
			glPopMatrix();
			glPopMatrix();
		}


		glPopMatrix();
	}

	else if (grscenepart5 == sc_change)
	{
		glPushMatrix();
		glLoadIdentity();

#pragma region ocean
		// ocean code
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -2.0f, -30.0f);
		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, grtextureOcean);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(50.0f, 0.0f, -30.0f); // right top
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-50.0f, 0.0f, -30.0f);//lt
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-50.0f, 0.0f, 30.0f);//rb
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(50.0f, 0.0f, 30.0f);//lb
		glEnd();
		glPopMatrix();
		glEnd();
#pragma endregion ocean


#pragma region sky
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 7.7f, -70.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, grtextureSky);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(70.0f, 70.0f, 0.0f);									// right top
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-70.0f, 70.0f, 0.0f);									// left top

		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		glTexCoord2f(0.0f, 0.0f);										// left bottom
		glVertex3f(-70.0f, -20.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(70.0f, -20.0f, 0.0f);									// right bottom
		glEnd();
		glPopMatrix();
#pragma endregion sky


#pragma region bird code
		glPushMatrix();
		glLoadIdentity();
		gluLookAt(0.0f, tempY1, 2.0f, 0.0f, tempY2, 0.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();																				// 1

		glTranslatef(0.0f, tempY1 - 0.1f, 2.0f - 0.5f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glRotatef(grfangle, 0.0f, 0.0f, -1.0f);
		glScalef(0.5f, 0.5f, 0.5f);

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
		glPopMatrix();
#pragma endregion bird code

		glPopMatrix();
	}

		else if (grscenepart4 == sc_change)
	{
	glPushMatrix();
	glLoadIdentity();


#pragma region sky
	glPushMatrix();
	glLoadIdentity();
	glRotatef(grfangle, 0.0f, 1.0f, 0.0f);
	gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
	//gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -27.0f);
	//glRotatef(grfangle, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, grtextureSky);

	glPushMatrix();
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(40.0f, 25.0f, 0.0f);									// right top
	//glColor3f(1.0f, 0.4f, 0.0f);			// orange-ish color
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-40.0f, 25.0f, 0.0f);									// left top
	//glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-40.0f, -25.9f, 0.0f);									// left bottom
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(40.0f, -25.9f, 0.0f);								// right bottom

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-40.0f, 25.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-40.0f, 25.0f, 40.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-40.0f, -25.9f, 40.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-40.0f, -25.9f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(40.0f, 25.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(40.0f, 25.0f, 40.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(40.0f, -25.9f, 40.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(40.0f, -25.9f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(40.0f, 25.0f, 40.0f);									// right top
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-40.0f, 25.0f, 40.0f);									// left top
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-40.0f, -25.9f, 40.0f);									// left bottom
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(40.0f, -25.9f, 40.0f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();

#pragma endregion sky


#pragma region bird code
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2, 0.0f, 1.0f, 0.0f);
	

	glPushMatrix();
	glTranslatef(-1.0f + grbirdPosX, 0.0f, -8.0f + grbirdPosZ);

	glPushMatrix();																				// 1
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
	//glColor3f(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.616f, 0.769f);
	//glColor3f(1.0f, 0.616f, 0.617f);
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
	//glColor3f(1.0f, 0.412f, 0.706f);
	glColor3f(1.0f, 0.616f, 0.769f);
	//glColor3f(1.0f, 1.0f, 1.0f);
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
	//glBindTexture(GL_TEXTURE_2D, NULL);
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
	glPopMatrix();
	glPopMatrix();
#pragma endregion bird code



	glPopMatrix();
	}

	else if (grsceneclose == sc_change)
	{
		glPushMatrix();
		glLoadIdentity();

#pragma region sky code

		glPushMatrix();
		glLoadIdentity();
		gluLookAt(0.0f, cameraAngleY, 2.0f, 0.0f, cameraY, 0.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -27.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		//glBindTexture(GL_TEXTURE_2D, grtextureSky);
		glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.8f, 0.0f);			// orange-ish color
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(25.0f, 20.0f, 0.0f);									// right top
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-25.0f, 20.0f, 0.0f);									// left top

		//glColor3f(0.5290f, 0.8080f, 0.9220f);
		//glTexCoord2f(0.0f, 0.0f);										// left bottom
		glVertex3f(-25.0f, -10.7f, 0.0f);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(25.0f, -10.7f, 0.0f);									// right bottom
		//glColor3f(0.5290f, 0.8080f, 0.9220f);

		glEnd();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glPopMatrix();


#pragma endregion sky code

		if (grscene_present_by == sc_change)
		{
			// font
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.1f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.3f, 0.3f, 0.0f);
			DisplayFont("Created By", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, -0.2f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Gauri Ranade", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, -0.5f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Blend Group", "-%1.0f");
			glPopMatrix();
		}


		else if (grscene_mentored_by == sc_change)
		{
			// font
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.8f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Mentored By", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.5f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Gokhale Sir", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.2f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Gokhale Ma'am", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, -0.1f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Pradnya Ma'am", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, -0.4f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Aditya Boob", "-%1.0f");
			glPopMatrix();
		}
		else if (grscene_technology_used == sc_change)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.8f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Technology Used", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-1.0f, 0.5f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Windowing :         ", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.0f, 0.5f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Win32 SDK  ", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-1.0f, 0.2f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Rendering :         ", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.0f, 0.2f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("OpenGL       ", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-1.0f, -0.1f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Language :          ", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.0f, -0.1f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("C++               ", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-1.0f, -0.4f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Data Structure :", "-%1.0f");
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.0f, -0.4f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Linked List", "-%1.0f");
			glPopMatrix();
		}
		else if (grscene_music_by == sc_change)
		{
			// font
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.5f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Music By", "-%1.0f"); //
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.2f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Finding Nemo - Thomas Newman", "-%1.0f"); //
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, -0.1f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("How To Train Your Dragon - John Powell", "-%1.0f"); //
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, -0.4f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.2f, 0.2f, 0.0f);
			DisplayFont("Rain and Thunder sound effects - Youtube", "-%1.0f"); //
			glPopMatrix();
		}
		else if (grscene_the_end == sc_change)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, -6.0f);
			//glColor3f(0.85f, 0.647f, 0.125f);
			glColor3f(grcolorIntro, grcolorIntro, grcolorIntro);
			glScalef(0.4f, 0.5f, 0.0f);
			DisplayFont("The End", "-%1.0f"); //
			glPopMatrix();
		}




		glPopMatrix();
	}

	Update();
	SwapBuffers(grghdc);
}

void Update(void)
{
	if (grsceneintro == sc_change)
	{
		if (grbIntroText)
		{
			if (grcolorIntro <= 1.0f)
			{
				grcolorIntro = grcolorIntro + 0.002f;
			}
			else
			{
				grbFadeOut = true;
			}
			if (grbFadeOut == true)
			{
				if (grcolorIntro >= 0.0f)
					grcolorIntro = grcolorIntro - 0.01f;
				else
				{
					grbFadeOut = false;
					grbIntroText = false;
					grbDisplayTitle = true;
					grcolorIntro = 0.0f;
				}

			}

		}

		else if (grbDisplayTitle)
		{
			if (grcolorIntro <= 1.0f)
			{
				grcolorIntro = grcolorIntro + 0.004f;
			}
			else
			{
				grbFadeOut = true;
			}
			if (grbFadeOut == true)
			{
				if (grcolorIntro >= 0.0f)
					grcolorIntro = grcolorIntro - 0.01f;
				else
				{
					grbFadeOut = false;
					grbDisplayTitle = false;
				}

			}

		}
	}
	else if (grscenepart0 == sc_change)
	{
		if (grcolorIntro >= 0.0f)
		{
			grcolorIntro = grcolorIntro - 0.01f;
		}

		if (grscene_bird_fell == sc_change)
		{

			if (grbirdY >= -2.5f)
			{
				if (grrotateBird >= -90)
				{
					grrotateBird = grrotateBird - 2;
				}


				grbirdY = grbirdY - 0.06f;
				cameraY = cameraY - 0.24f;
				cameraAngleY = cameraAngleY - 0.24f;

			}
			else
			{
				grbirdWings = 0;
				//grscene_bird_fell = sc_no_change;

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
			// bird wings
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

			// bird move to come in scene
			if (grbirdX > 3.0f)
			{
				grbirdX = grbirdX - 0.02f;
			}
		}

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

		if (grscenepart1 == sc_change)
		{

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
							grbirdWings = grbirdWings - 20;
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
							grbirdWings = grbirdWings + 20;
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
		}

	}
	else if (grscenepart2 == sc_change)
	{
		if (grcolorIntro >= 0.0f)
		{
			grcolorIntro = grcolorIntro - 0.002f;
		}
		if (grscene_zoom_window == sc_change)
		{
			if (tempZ1 >= -14.100019f)
			{
				tempZ1 = tempZ1 - 0.1f;
			}
			if (tempX2 <= 4.999998f)
			{
				tempX2 = tempX2 + 0.1f;
			}
			if (tempX1 <= 4.999997f)
			{
				tempX1 = tempX1 + 0.1f;
			}
			if (tempY1 <= 1.60)
			{
				tempY1 = tempY1 + 0.1f;
			}
		}
		else
		{
			if (grbZoomWindowOut)
			{
				if (tempZ1 <= 2.0f)
				{
					tempZ1 = tempZ1 + 0.1f;
				}
				if (tempX2 >= 0.0f)
				{
					tempX2 = tempX2 - 0.1f;
				}
				if (tempX1 >= 0.0f)
				{
					tempX1 = tempX1 - 0.1f;
				}
				if (tempY1 >= 0.0f)
				{
					tempY1 = tempY1 - 0.1f;
				}
			}

		}

		if (grscene_other_bird_flying == sc_change)
		{
			if (grbird2MoveX <= 8.6f)
				grbird2MoveX = grbird2MoveX + 0.01f;
			else
				grscene_other_bird_flying = sc_no_change;
			// bird fly wings
			if (bFly2 == true)
			{
				if (grbirdWings2 >= -180)
				{
					grbirdWings2 = grbirdWings2 - 5;
				}
				else
				{
					bFly2 = false;
				}
			}

			if (bFly2 == false)
			{
				if (grbirdWings2 <= -20)
				{
					grbirdWings2 = grbirdWings2 + 5;
				}
				else
					bFly2 = true;
			}

		}
		if (grscene_bird_fly_out_window == sc_change)
		{
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
	}
	else if (grscenepart3 == sc_change)
	{
		if (grscene_bird_fly_tree1 == sc_change)
		{
			if (grbirdAngle >= -92.000000)
			{
				grbirdAngle = grbirdAngle - 1.0f;
			}
			if (tempZ1 >= -2.900000f)
			{
				tempZ1 = tempZ1 - 0.05f;

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

		}
		else if (grscene_bird_fly_tree2 == sc_change)
		{
			if (grbirdAngle <= 90.000000)
			{
				grbirdAngle = grbirdAngle + 30.0f;
			}
			if (tempX1 >= -1.500000f)
			{
				tempX1 = tempX1 - 0.05f;
			}
			if (tempZ1 >= -4.099998f)
			{
				tempZ1 = tempZ1 - 0.05f;

				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 20;
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
						grbirdWings = grbirdWings + 20;
					}
					else
						bFly = true;
				}
			}

		}
		else if (grscene_bird_fly_tree3 == sc_change)
		{
			if (grbirdAngle >= -90.000000)
			{
				grbirdAngle = grbirdAngle - 20.0f;
			}

			if (tempX1 >= -1.700000f)
			{
				tempX1 = tempX1 - 0.05f;
			}
			if (tempZ1 >= -7.500005f)
			{
				tempZ1 = tempZ1 - 0.05f;

				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 20;
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
						grbirdWings = grbirdWings + 20;
					}
					else
						bFly = true;
				}
			}

		}
		else if (grscene_bird_fly_tree4 == sc_change)
		{
			if (grbirdAngle <= 80.000000)
			{
				grbirdAngle = grbirdAngle + 10.0f;
			}
			if (tempX1 >= -2.000000f)
			{
				tempX1 = tempX1 - 0.05f;
			}
			if (tempZ1 >= -9.500000)
			{
				tempZ1 = tempZ1 - 0.05f;

				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 20;
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
						grbirdWings = grbirdWings + 20;
					}
					else
						bFly = true;
				}
			}
		}
		else if (grscene_bird_fly_tree5 == sc_change)
		{
			if (grbirdAngle >= -90.000000)
			{
				grbirdAngle = grbirdAngle - 10.0f;
			}
			if (tempX1 <= -1.900000)
			{
				tempX1 = tempX1 + 0.05f;
			}
			if (tempZ1 >= -12.700012)
			{
				tempZ1 = tempZ1 - 0.05f;

				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 20;
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
						grbirdWings = grbirdWings + 20;
					}
					else
						bFly = true;
				}
			}
		}
		else if (grscene_bird_fly_tree6 == sc_change)
		{
			if (grbirdAngle <= 0.000000)
			{
				grbirdAngle = grbirdAngle + 10.0f;
			}
			if (tempX1 <= -2.10000f)
			{
				tempX1 = tempX1 + 0.05f;
			}
			if (tempZ1 >= -18.600019f)
			{
				tempZ1 = tempZ1 - 0.05f;

				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 20;
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
						grbirdWings = grbirdWings + 20;
					}
					else
						bFly = true;
				}
			}
		}

		else if (grscene_bird_fly_tree7 == sc_change)
		{
			if (grbirdAngle >= 0.000000)
			{
				grbirdAngle = grbirdAngle - 1.0f;
			}
			/*
			else if (grbirdAngle <= 0.000000)
			{
				grbirdAngle = grbirdAngle + 1.0f;
			}
			*/
			if (tempY1 <= 7.399995f)
			{
				tempY1 = tempY1 + 0.05f;
				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 20;
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
						grbirdWings = grbirdWings + 20;
					}
					else
						bFly = true;
				}
			}


		}

		else if (grscene_bird_fly_tree8 == sc_change)
		{

			if (tempZ1 >= -25.200077f)
			{
				tempZ1 = tempZ1 - 0.05f;

				if (bFly == true)
				{
					if (grbirdWings >= -180)
					{
						grbirdWings = grbirdWings - 20;
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
						grbirdWings = grbirdWings + 20;
					}
					else
						bFly = true;
				}
			}
		}

	}
	else if (grscenepart4 == sc_change)
	{
		if (grbirdPosY <= 0.0f)
			grbirdPosY = grbirdPosY + 0.05f;

		if (grbirdAngle >= -180.0f)
			grbirdAngle = grbirdAngle - 0.1f;

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
	else if (grscenepart5 == sc_change)
	{
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
		if (tempZ1 >= -30.0f)
		{
			tempZ1 = tempZ1 - 0.05f;
			tempZ2 = tempZ2 - 0.05f;
		}
		else
		{
			if (tempY1 <= 20.0f)
			{
				tempY1 = tempY1 + 0.05f;
				tempY2 = tempY2 + 0.05f;
			}
			else
			{
				tempZ1 = tempZ1 - 0.05f;
				tempZ2 = tempZ2 - 0.05f;
			}
		}
	}
	else if (grsceneclose == sc_change)
	{
		if (grscene_present_by == sc_change)
		{

			if (grcolorIntro <= 1.0f)
			{
				grcolorIntro = grcolorIntro + 0.005f;
			}
			else
			{
				grbFadeOut = true;
			}
			if (grbFadeOut == true)
			{
				if (grcolorIntro >= 0.0f)
					grcolorIntro = grcolorIntro - 0.01f;
				else
				{
					grbFadeOut = false;
					grscene_present_by = sc_no_change;
					grscene_mentored_by = sc_change;
					grcolorIntro = 0.0f;
				}
			}
		}
		else if (grscene_mentored_by == sc_change)
		{
			if (grcolorIntro <= 1.0f)
			{
				grcolorIntro = grcolorIntro + 0.005f;
			}
			else
			{
				grbFadeOut = true;
			}
			if (grbFadeOut == true)
			{
				if (grcolorIntro >= 0.0f)
					grcolorIntro = grcolorIntro - 0.01f;
				else
				{
					grbFadeOut = false;
					grscene_mentored_by = sc_no_change;
					grscene_technology_used = sc_change;
					grcolorIntro = 0.0f;
				}
			}
		}
		else if (grscene_technology_used == sc_change)
		{
			if (grcolorIntro <= 1.0f)
			{
				grcolorIntro = grcolorIntro + 0.005f;
			}
			else
			{
				grbFadeOut = true;
			}
			if (grbFadeOut == true)
			{
				if (grcolorIntro >= 0.0f)
					grcolorIntro = grcolorIntro - 0.01f;
				else
				{
					grbFadeOut = false;
					grscene_technology_used = sc_no_change;
					grscene_music_by = sc_change;
					grcolorIntro = 0.0f;
				}
			}
		}
		else if (grscene_music_by == sc_change)
		{
			if (grcolorIntro <= 1.0f)
			{
				grcolorIntro = grcolorIntro + 0.005f;
			}
			else
			{
				grbFadeOut = true;
			}
			if (grbFadeOut == true)
			{
				if (grcolorIntro >= 0.0f)
					grcolorIntro = grcolorIntro - 0.01f;
				else
				{
					grbFadeOut = false;
					grscene_music_by = sc_no_change;
					grscene_the_end = sc_change;
					grcolorIntro = 0.0f;
				}
			}
		}
		else if (grscene_the_end == sc_change)
		{
			if (grcolorIntro <= 1.0f)
			{
				grcolorIntro = grcolorIntro + 0.005f;
			}
			else
			{
				grbFadeOut = true;
			}
			if (grbFadeOut == true)
			{
				if (grcolorIntro >= 0.0f)
					grcolorIntro = grcolorIntro - 0.01f;
				else
				{
					grbFadeOut = false;
					grscene_the_end = sc_no_change;
				}
			}
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
	glTranslatef(0.0f, 1.0f, 0.0f);
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

void ThinkCloud()
{
	glBindTexture(GL_TEXTURE_2D, grtextureWhiteColorCloud);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	for (i = 0.0f; i < 2 * PI; i = i + 0.02f)
	{

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.2f * cos(i), 0.2f * sin(i), 0.0f);
	}
	glEnd();
}

void BuildFont()                    // Build Our Bitmap Font
{
	HFONT font;
	base = glGenLists(256);                 // Storage For 256 Characters
	font = CreateFont(-12,                  // Height Of Font
		0,                                  // Width Of Font
		0,                                  // Angle Of Escapement
		0,                                  // Orientation Angle
		0,                                  // Font Weight
		FALSE,                              // Italic
		FALSE,                              // Underline
		FALSE,                              // Strikeout
		ANSI_CHARSET,                       // Character Set Identifier
		OUT_TT_PRECIS,                      // Output Precision
		CLIP_DEFAULT_PRECIS,                // Clipping Precision
		ANTIALIASED_QUALITY,                // Output Quality
		FF_DONTCARE | DEFAULT_PITCH,        // Family And Pitch
		TEXT("Cooper Black"));					// Font Name

	SelectObject(grghdc, font);
	wglUseFontOutlines(grghdc,             // Select The Current DC
		0,                                  // Starting Character
		255,                                // Number Of Display Lists To Build
		base,                               // Starting Display Lists
		0.0f,                               // Deviation From The True Outlines
		0.05f,                              // Font Thickness In The Z Direction
		WGL_FONT_POLYGONS,                  // Use Polygons, Not Lines
		gmf);

}

void DeleteFont()
{
	glDeleteLists(base, 256);
}

void DisplayFont(const char* fmt, ...)
{
	float		length = 0;
	char		text[256];
	va_list		ap;

	if (fmt == NULL)
		return;

	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	for (unsigned int loop = 0; loop < (strlen(text)); loop++)
	{
		length += gmf[text[loop]].gmfCellIncX;
	}

	glTranslatef(-length / 2, 0.0f, 0.0f);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
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
	// texture
	//GLuint grtextureBird;
	//GLuint grtextureBirdAfraid;
	//GLuint grtextureLeaves;
	//GLuint grtextureShirt;
	//GLuint grtextureSoil;
	//GLuint grtextureSky;
	//GLuint grtextureBirdLightning;
	//GLuint grtextureMorningSky;
	//GLuint grtextureBirdHouseDoor;
	//GLuint grtextureBirdFoodCan;
	//GLuint grtextureWhiteColorCloud;
	if (grtextureBird)
	{
		glDeleteTextures(1, &grtextureBird);
		grtextureBird = 0;
	}
	if (grtextureBirdAfraid)
	{
		glDeleteTextures(1, &grtextureBirdAfraid);
		grtextureBirdAfraid = 0;
	}
	if (grtextureLeaves)
	{
		glDeleteTextures(1, &grtextureLeaves);
		grtextureLeaves = 0;
	}
	if (grtextureShirt)
	{
		glDeleteTextures(1, &grtextureShirt);
		grtextureShirt = 0;
	}
	if (grtextureSoil)
	{
		glDeleteTextures(1, &grtextureSoil);
		grtextureSoil = 0;
	}
	if (grtextureSky)
	{
		glDeleteTextures(1, &grtextureSky);
		grtextureSky = 0;
	}
	if (grtextureBirdLightning)
	{
		glDeleteTextures(1, &grtextureBirdLightning);
		grtextureBirdLightning = 0;
	}
	if (grtextureMorningSky)
	{
		glDeleteTextures(1, &grtextureMorningSky);
		grtextureMorningSky = 0;
	}
	if (grtextureBirdHouseDoor)
	{
		glDeleteTextures(1, &grtextureBirdHouseDoor);
		grtextureBirdHouseDoor = 0;
	}
	if (grtextureBirdFoodCan)
	{
		glDeleteTextures(1, &grtextureBirdFoodCan);
		grtextureBirdFoodCan = 0;

	}
	if (grtextureWhiteColorCloud)
	{
		glDeleteTextures(1, &grtextureWhiteColorCloud);
		grtextureWhiteColorCloud = 0;

	}
	if (grtextureBedFurniture)
	{
		glDeleteTextures(1, &grtextureBedFurniture);
		grtextureBedFurniture = 0;

	}
	if (grtextureFoods)
	{
		glDeleteTextures(1, &grtextureFoods);
		grtextureFoods = 0;
	}
	if (grtextureSmiley)
	{
		glDeleteTextures(1, &grtextureSmiley);
		grtextureSmiley = 0;
	}
	if (grtextureStem)
	{
		glDeleteTextures(1, &grtextureStem);
		grtextureStem = 0;
	}
	if (grtextureTitle)
	{
		glDeleteTextures(1, &grtextureTitle);
		grtextureTitle = 0;
	}
	if (grtextureOcean)
	{
		glDeleteTextures(1, &grtextureOcean);
		grtextureOcean = 0;
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









