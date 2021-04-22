#include<windows.h>
#include<stdio.h>
#include<gl\glew.h> // glew.h must be included BEFORE gl.h
#include<gl\GL.h>
#include"vmath.h"
#include"GRWindow.h"
#include"Sphere.h"


using namespace vmath;

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Sphere.lib")


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


enum
{
	GR_ATTRIBUTE_POSITION = 0,
	GR_ATTRIBUTE_COLOR,
	GR_ATTRIBUTE_NORMAL,
	GR_ATTRIBUTE_TEXCOORD
};


mat4 grgPerspectiveProjectionMatrix;

// project specific 
float grsphere_vertices[1146];
float grsphere_normals[1146];
float grsphere_textures[764];
unsigned short grsphere_elements[2280];
GLuint grgNumVertices;
GLuint grgNumElements;

GLuint grgVao1;
GLuint grgVboSpherePosition1;
GLuint grgVboSphereNormal1;
GLuint grgVboSphereElement1;
GLuint grgVao2;
GLuint grgVboSpherePosition2;
GLuint grgVboSphereNormal2;
GLuint grgVboSphereElement2;
GLuint grgVao3;
GLuint grgVboSpherePosition3;
GLuint grgVboSphereNormal3;
GLuint grgVboSphereElement3;
GLuint grgVao4;
GLuint grgVboSpherePosition4;
GLuint grgVboSphereNormal4;
GLuint grgVboSphereElement4;
GLuint grgVao5;
GLuint grgVboSpherePosition5;
GLuint grgVboSphereNormal5;
GLuint grgVboSphereElement5;
GLuint grgVao6;
GLuint grgVboSpherePosition6;
GLuint grgVboSphereNormal6;
GLuint grgVboSphereElement6;
GLuint grgVao7;
GLuint grgVboSpherePosition7;
GLuint grgVboSphereNormal7;
GLuint grgVboSphereElement7;
GLuint grgVao8;
GLuint grgVboSpherePosition8;
GLuint grgVboSphereNormal8;
GLuint grgVboSphereElement8;
GLuint grgVao9;
GLuint grgVboSpherePosition9;
GLuint grgVboSphereNormal9;
GLuint grgVboSphereElement9;
GLuint grgVao10;
GLuint grgVboSpherePosition10;
GLuint grgVboSphereNormal10;
GLuint grgVboSphereElement10;
GLuint grgVao11;
GLuint grgVboSpherePosition11;
GLuint grgVboSphereNormal11;
GLuint grgVboSphereElement11;
GLuint grgVao12;
GLuint grgVboSpherePosition12;
GLuint grgVboSphereNormal12;
GLuint grgVboSphereElement12;
GLuint grgVao13;
GLuint grgVboSpherePosition13;
GLuint grgVboSphereNormal13;
GLuint grgVboSphereElement13;
GLuint grgVao14;
GLuint grgVboSpherePosition14;
GLuint grgVboSphereNormal14;
GLuint grgVboSphereElement14;
GLuint grgVao15;
GLuint grgVboSpherePosition15;
GLuint grgVboSphereNormal15;
GLuint grgVboSphereElement15;
GLuint grgVao16;
GLuint grgVboSpherePosition16;
GLuint grgVboSphereNormal16;
GLuint grgVboSphereElement16;
GLuint grgVao17;
GLuint grgVboSpherePosition17;
GLuint grgVboSphereNormal17;
GLuint grgVboSphereElement17;
GLuint grgVao18;
GLuint grgVboSpherePosition18;
GLuint grgVboSphereNormal18;
GLuint grgVboSphereElement18;
GLuint grgVao19;
GLuint grgVboSpherePosition19;
GLuint grgVboSphereNormal19;
GLuint grgVboSphereElement19;
GLuint grgVao20;
GLuint grgVboSpherePosition20;
GLuint grgVboSphereNormal20;
GLuint grgVboSphereElement20;
GLuint grgVao21;
GLuint grgVboSpherePosition21;
GLuint grgVboSphereNormal21;
GLuint grgVboSphereElement21;
GLuint grgVao22;
GLuint grgVboSpherePosition22;
GLuint grgVboSphereNormal22;
GLuint grgVboSphereElement22;
GLuint grgVao23;
GLuint grgVboSpherePosition23;
GLuint grgVboSphereNormal23;
GLuint grgVboSphereElement23;
GLuint grgVao24;
GLuint grgVboSpherePosition24;
GLuint grgVboSphereNormal24;
GLuint grgVboSphereElement24;


// per fragment
// uniforms
GLuint grgModelMatrixUniformPF;
GLuint grgViewMatrixUniformPF;
GLuint grgProjectionMatrixUniformPF;
GLuint grgLaUniformPF;
GLuint grgLdUniformPF;
GLuint grgLsUniformPF;
GLuint grgLightPositionUniformPF;
GLuint grgKdUniformPF;					// material diffuse
GLuint grgKaUniformPF;					// material ambient
GLuint grgKsUniformPF;					// material specular
GLuint grgMaterialShinynessUniformPF;
GLuint grgLKeyPressedUniformPF;

GLuint grgVertexShaderObjectPF;
GLuint grgFragmentShaderObjectPF;
GLuint grgShaderProgramObjectPF;


vec4 grglightAmbientColor = { 0.0f, 0.0f, 0.0f, 1.0f };
vec4 grglightDiffuseColor = {	1.0f, 1.0f, 1.0f, 1.0f };
vec4 grglightSpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };
vec4 grglightPosition = { 0.0f, 0.0f, 100.0f, 0.0f };


bool grgbPerFragmentLighting;
bool grgbLKeyPressed = false;
GLint grgKeyPress;
GLfloat grflightAngleX;
GLfloat grflightAngleY;
GLfloat grflightAngleZ;
int i;
float left, right, bottom, top;

// 24 materials
vec4 grgKa1;
vec4 grgKd1;
vec4 grgKs1;
GLfloat grgMaterialShinyness1;

vec4 grgKa2;
vec4 grgKd2;
vec4 grgKs2;
GLfloat grgMaterialShinyness2;

vec4 grgKa3;
vec4 grgKd3;
vec4 grgKs3;
GLfloat grgMaterialShinyness3;

vec4 grgKa4;
vec4 grgKd4;
vec4 grgKs4;
GLfloat grgMaterialShinyness4;

vec4 grgKa5;
vec4 grgKd5;
vec4 grgKs5;
GLfloat grgMaterialShinyness5;

vec4 grgKa6;
vec4 grgKd6;
vec4 grgKs6;
GLfloat grgMaterialShinyness6;

vec4 grgKa7;
vec4 grgKd7;
vec4 grgKs7;
GLfloat grgMaterialShinyness7;

vec4 grgKa8;
vec4 grgKd8;
vec4 grgKs8;
GLfloat grgMaterialShinyness8;

vec4 grgKa9;
vec4 grgKd9;
vec4 grgKs9;
GLfloat grgMaterialShinyness9;

vec4 grgKa10;
vec4 grgKd10;
vec4 grgKs10;
GLfloat grgMaterialShinyness10;

vec4 grgKa11;
vec4 grgKd11;
vec4 grgKs11;
GLfloat grgMaterialShinyness11;

vec4 grgKa12;
vec4 grgKd12;
vec4 grgKs12;
GLfloat grgMaterialShinyness12;

vec4 grgKa13;
vec4 grgKd13;
vec4 grgKs13;
GLfloat grgMaterialShinyness13;

vec4 grgKa14;
vec4 grgKd14;
vec4 grgKs14;
GLfloat grgMaterialShinyness14;

vec4 grgKa15;
vec4 grgKd15;
vec4 grgKs15;
GLfloat grgMaterialShinyness15;

vec4 grgKa16;
vec4 grgKd16;
vec4 grgKs16;
GLfloat grgMaterialShinyness16;

vec4 grgKa17;
vec4 grgKd17;
vec4 grgKs17;
GLfloat grgMaterialShinyness17;

vec4 grgKa18;
vec4 grgKd18;
vec4 grgKs18;
GLfloat grgMaterialShinyness18;

vec4 grgKa19;
vec4 grgKd19;
vec4 grgKs19;
GLfloat grgMaterialShinyness19;

vec4 grgKa20;
vec4 grgKd20;
vec4 grgKs20;
GLfloat grgMaterialShinyness20;

vec4 grgKa21;
vec4 grgKd21;
vec4 grgKs21;
GLfloat grgMaterialShinyness21;

vec4 grgKa22;
vec4 grgKd22;
vec4 grgKs22;
GLfloat grgMaterialShinyness22;

vec4 grgKa23;
vec4 grgKd23;
vec4 grgKs23;
GLfloat grgMaterialShinyness23;

vec4 grgKa24;
vec4 grgKd24;
vec4 grgKs24;
GLfloat grgMaterialShinyness24;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declaration
	void Initialize(void);
	void Display(void);
	void Uninitialize(void);

	// variables declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("OGL");
	int grDesktopWidth, grDesktopHeight;
	int grWndXPos, grWndYPos;
	bool grbDone = false;
	bool grgbEscapeKeyIsPressed = false;

	if (fopen_s(&grgpFile, "GRLog.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Cannot open desired file"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf_s(grgpFile, "Log file created successfully. \n Program started successfully\n **** Logs ***** \n");
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
				Display();
			}
		}

	}

	Uninitialize();

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
			ToggleFullScreen();
			break;

		case 0x46:
		case 0x66:
			grgbPerFragmentLighting = !grgbPerFragmentLighting;
			break;

		default:
			break;
		}
		break;

	case WM_CHAR:
		switch (wParam)
		{

		case 'q':
		case 'Q':
			DestroyWindow(hwnd);
			break;

		case 'l':
		case 'L':
			grgbLKeyPressed = !grgbLKeyPressed;
			break;

		case 'x':
		case 'X':
			grgKeyPress = 1;
			break;

		case 'y':
		case 'Y':
			grgKeyPress = 2;
			break;

		case 'z':
		case 'Z':
			grgKeyPress = 3;
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
	void Uninitialize(void);
	void Initialize24Spheres(void);

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
		Uninitialize();
	}

	if (SetPixelFormat(grghdc, griPixelFormatIndex, &grpfd) == FALSE)
	{
		fprintf(grgpFile, "SetPixelFormat() failed\n");
		Uninitialize();
	}

	grghrc = wglCreateContext(grghdc);
	if (grghrc == NULL)
	{
		fprintf(grgpFile, "wglCreateContext() failed\n");
		ReleaseDC(grghwnd, grghdc);
		grghdc = NULL;
	}

	if (wglMakeCurrent(grghdc, grghrc) == FALSE)
	{
		fprintf(grgpFile, "wglMakeCurrent() failed\n");
		wglDeleteContext(grghrc);
		grghrc = NULL;
		ReleaseDC(grghwnd, grghdc);
		grghdc = NULL;
	}

	GLenum grglew_error = glewInit();
	if (grglew_error != GLEW_OK)
	{
		wglDeleteContext(grghrc);
		grghrc = NULL;
		ReleaseDC(grghwnd, grghdc);
		grghdc = NULL;
	}


	getSphereVertexData(grsphere_vertices, grsphere_normals, grsphere_textures, grsphere_elements);
	grgNumVertices = getNumberOfSphereVertices();
	grgNumElements = getNumberOfSphereElements();




	/////////////////////////////////////////////// Shader code for per fragment lighting

	// create shader
	grgVertexShaderObjectPF = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* grvertexShaderSourceCodePF =
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_l_key_pressed;" \
		"uniform vec4 u_light_position;" \
		"out vec3 transformed_normal;" \
		"out vec3 light_direction;" \
		"out vec3 view_vector;" \
		"int i;" \
		"void main(void)" \
		"{" \
			"if(u_l_key_pressed == 1)" \
			"{" \
				"vec4 eye_coordinates = u_view_matrix * u_model_matrix * vPosition;" \
				"transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
				"view_vector = normalize(-eye_coordinates.xyz);" \
				"light_direction = normalize(vec3(u_light_position - eye_coordinates));" \
			"}" \
			"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"}";

	glShaderSource(grgVertexShaderObjectPF, 1, (const GLchar**)&grvertexShaderSourceCodePF, NULL);

	// compile shader
	glCompileShader(grgVertexShaderObjectPF);
	// error check for compilation
	GLint griInfoLength = 0;
	GLint griShaderCompileStatus = 0;
	char *grszInfoLog = NULL;

	glGetShaderiv(grgVertexShaderObjectPF, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgVertexShaderObjectPF, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * griInfoLength);
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgVertexShaderObjectPF, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Vertex Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	////// fragment shader 
	grgFragmentShaderObjectPF = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* grfragmentShaderSourceCodePF =
		"#version 450 core" \
		"\n" \
		"in vec3 transformed_normal;" \
		"in vec3 light_direction;" \
		"in vec3 view_vector;" \
		"uniform vec3 u_la;" \
		"uniform vec3 u_ld;" \
		"uniform vec3 u_ls;" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_material_shinyness;" \
		"uniform int u_l_key_pressed;" \
		"vec3 fong_ads_light;" \
		"out vec4 FragColor;" \
		"int i;" \
		"void main(void)" \
		"{" \
			"if(u_l_key_pressed == 1)" \
			"{" \
				"vec3 reflection_vector = reflect(-light_direction, transformed_normal);" \
				"vec3 ambient = u_la *u_ka;" \
				"vec3 diffuse = u_ld * u_kd * max(dot(light_direction, transformed_normal), 0.0);" \
				"vec3 specular = u_ls * u_ks * pow(max(dot(reflection_vector, view_vector), 0.0), u_material_shinyness);" \
				"fong_ads_light = ambient + diffuse + specular;" \
			"}" \
			"else" \
			"{" \
				"fong_ads_light = vec3(1.0, 1.0, 1.0);" \
			"}" \
			"FragColor = vec4(fong_ads_light, 1.0);" \
		"}";

	glShaderSource(grgFragmentShaderObjectPF, 1, (const GLchar**)&grfragmentShaderSourceCodePF, NULL);

	// compile shader
	glCompileShader(grgFragmentShaderObjectPF);
	// error check for compiation
	griInfoLength = 0;
	griShaderCompileStatus = 0;
	griInfoLength = NULL;

	glGetShaderiv(grgFragmentShaderObjectPF, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgFragmentShaderObjectPF, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * griInfoLength);
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgFragmentShaderObjectPF, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Fragment Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);

			}
		}
		Uninitialize();
	}

	//****** Shader Program for Per fragment *****//
	// create
	grgShaderProgramObjectPF = glCreateProgram();

	// attach vertex shader to shader program
	glAttachShader(grgShaderProgramObjectPF, grgVertexShaderObjectPF);

	// attach fragment shader to shader program
	glAttachShader(grgShaderProgramObjectPF, grgFragmentShaderObjectPF);

	// pre-link our attribute enum with shader's attributes
	glBindAttribLocation(grgShaderProgramObjectPF, GR_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(grgShaderProgramObjectPF, GR_ATTRIBUTE_NORMAL, "vNormal");

	// link shader
	glLinkProgram(grgShaderProgramObjectPF);

	// error check for linking
	GLint griShaderProgramLinkStatus = 0;
	glGetProgramiv(grgShaderProgramObjectPF, GL_LINK_STATUS, &griShaderProgramLinkStatus);
	if (griShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(grgShaderProgramObjectPF, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(griInfoLength * sizeof(char));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetProgramInfoLog(grgShaderProgramObjectPF, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Shader Program Link Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	// uniforms for per fragment lighting
	grgModelMatrixUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_model_matrix");
	grgViewMatrixUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_view_matrix");
	grgProjectionMatrixUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_projection_matrix");

	grgLdUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ld");
	grgLaUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_la");
	grgLsUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ls");
	grgLightPositionUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_light_position");


	grgKaUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ka");
	grgKdUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_kd");
	grgKsUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ks");

	grgLKeyPressedUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_l_key_pressed");
	grgMaterialShinynessUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_material_shinyness");

	// Initialize sphere materials
	Initialize24Spheres();


	////// vao for sphere 1
	glGenVertexArrays(1, &grgVao1);
	glBindVertexArray(grgVao1);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition1);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal1);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 2
	glGenVertexArrays(1, &grgVao2);
	glBindVertexArray(grgVao2);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition2);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal2);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 3
	glGenVertexArrays(1, &grgVao3);
	glBindVertexArray(grgVao3);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition3);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal3);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 5
	glGenVertexArrays(1, &grgVao4);
	glBindVertexArray(grgVao4);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition4);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal4);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 5
	glGenVertexArrays(1, &grgVao5);
	glBindVertexArray(grgVao5);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition5);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal5);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement5);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 6
	glGenVertexArrays(1, &grgVao6);
	glBindVertexArray(grgVao6);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition6);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal6);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement6);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 7
	glGenVertexArrays(1, &grgVao7);
	glBindVertexArray(grgVao7);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition7);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal7);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement7);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 8
	glGenVertexArrays(1, &grgVao8);
	glBindVertexArray(grgVao8);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition8);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal8);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement8);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 9
	glGenVertexArrays(1, &grgVao9);
	glBindVertexArray(grgVao9);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition9);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal9);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement9);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 10
	glGenVertexArrays(1, &grgVao10);
	glBindVertexArray(grgVao10);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition10);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal10);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement10);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 11
	glGenVertexArrays(1, &grgVao11);
	glBindVertexArray(grgVao11);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition11);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal11);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement11);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 12
	glGenVertexArrays(1, &grgVao12);
	glBindVertexArray(grgVao12);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition12);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal12);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement12);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 13
	glGenVertexArrays(1, &grgVao13);
	glBindVertexArray(grgVao13);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition13);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition13);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal13);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal13);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement13);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement13);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 14
	glGenVertexArrays(1, &grgVao14);
	glBindVertexArray(grgVao14);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition14);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition14);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal14);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal14);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement14);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement14);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 15
	glGenVertexArrays(1, &grgVao15);
	glBindVertexArray(grgVao15);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition15);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition15);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal15);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal15);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement15);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement15);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 16
	glGenVertexArrays(1, &grgVao16);
	glBindVertexArray(grgVao16);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition16);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition16);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal16);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal16);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement16);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement16);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 17
	glGenVertexArrays(1, &grgVao17);
	glBindVertexArray(grgVao17);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition17);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition17);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal17);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal17);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement17);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement17);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 18
	glGenVertexArrays(1, &grgVao18);
	glBindVertexArray(grgVao18);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition18);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition18);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal18);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal18);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement18);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement18);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 19
	glGenVertexArrays(1, &grgVao19);
	glBindVertexArray(grgVao19);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition19);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition19);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal19);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal19);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement19);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement19);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 20
	glGenVertexArrays(1, &grgVao20);
	glBindVertexArray(grgVao20);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition20);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition20);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal20);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal20);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement20);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement20);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 21
	glGenVertexArrays(1, &grgVao21);
	glBindVertexArray(grgVao21);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition21);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition21);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal21);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal21);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement21);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement21);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 22
	glGenVertexArrays(1, &grgVao22);
	glBindVertexArray(grgVao22);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition22);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition22);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal22);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal22);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement22);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement22);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	/////////// vao for sphere 23
	glGenVertexArrays(1, &grgVao23);
	glBindVertexArray(grgVao23);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition23);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition23);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal23);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal23);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement23);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement23);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	/////////// vao for sphere 24
	glGenVertexArrays(1, &grgVao24);
	glBindVertexArray(grgVao24);
	// position vbo
	glGenBuffers(1, &grgVboSpherePosition24);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition24);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal24);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal24);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement24);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement24);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphere_elements), grsphere_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);


	// Depth
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	// set clearcolor
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	grgPerspectiveProjectionMatrix = mat4::identity();

	// warm-up call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{
	if (height == 0)
		height = 1;
	//glViewport(-250, 0, (GLsizei)width + 50, (GLsizei)height);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	left = 0.0f;
	right = ((GLfloat)width / (GLfloat)6);
	top = (GLfloat)0.0f;
	bottom = ((GLfloat)height / (GLfloat)4);
	fprintf(grgpFile, "\n left = %f, right = %f, top = %f, bottom = %f", left, right, top, bottom);
	grgPerspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void Display(void)
{
	// function declaration
	void Update(void);

	// code

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// OpenGL drawing code will start here
	mat4 grmodelMatrix = mat4::identity();
	mat4 grviewMatrix = mat4::identity();
	mat4 grprojectionMatrix = mat4::identity();
	mat4 grtranslateMatrix = mat4::identity();

	if(grgbPerFragmentLighting == true)
	{
		grmodelMatrix = mat4::identity();
		grviewMatrix = mat4::identity();
		grprojectionMatrix = mat4::identity();
		grtranslateMatrix = mat4::identity();
		
		// start use of shader program
		glUseProgram(grgShaderProgramObjectPF);
		
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grmodelMatrix = grtranslateMatrix;

		grprojectionMatrix = grgPerspectiveProjectionMatrix;

		if (grgbLKeyPressed == true)
		{

			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd1);
			glUniform3fv(grgKaUniformPF, 1, grgKa1);
			glUniform3fv(grgKsUniformPF, 1, grgKs1);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness1);

			if (grgKeyPress == 1)
			{
				grglightPosition[0] = 0.0;
				grglightPosition[1] = (GLfloat) 21 * sin(grflightAngleX);
				grglightPosition[2] = (GLfloat) 21 * cos(grflightAngleX);
				grglightPosition[3] = 0.0;							// w for directional light
			}
			else if (grgKeyPress == 2)
			{
				grglightPosition[0] = (GLfloat)20 * sin(grflightAngleY);
				grglightPosition[1] = 0.0;
				grglightPosition[2] = (GLfloat)20 * cos(grflightAngleY);
				grglightPosition[3] = 0.0;							// w for directional light
			}

			else if (grgKeyPress == 3)
			{
				grglightPosition[0] = (GLfloat)20 * sin(grflightAngleZ);;
				grglightPosition[1] = (GLfloat)20 * cos(grflightAngleZ);
				grglightPosition[2] = 0.0f;
				grglightPosition[3] = 0.0;							// w for directional light
			}

			glUniform3fv(grgLdUniformPF, 1, grglightDiffuseColor);
			glUniform3fv(grgLaUniformPF, 1, grglightAmbientColor);
			glUniform3fv(grgLsUniformPF, 1, grglightSpecularColor);
			glUniform4fv(grgLightPositionUniformPF, 1, grglightPosition);

		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(left, bottom * 3, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);

		// bind vao
		glBindVertexArray(grgVao1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement1);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
		
		
		//////////// sphere 2
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd2);
			glUniform3fv(grgKaUniformPF, 1, grgKa2);
			glUniform3fv(grgKsUniformPF, 1, grgKs2);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness2);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}

		glViewport(right, bottom * 3, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement2);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);
		

		//////////// sphere 3
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd3);
			glUniform3fv(grgKaUniformPF, 1, grgKa3);
			glUniform3fv(grgKsUniformPF, 1, grgKs3);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness3);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 2, bottom * 3, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement3);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////// sphere 4
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd4);
			glUniform3fv(grgKaUniformPF, 1, grgKa4);
			glUniform3fv(grgKsUniformPF, 1, grgKs4);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness4);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 3, bottom * 3, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao4);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement4);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////// sphere 5
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		glViewport(right * 2, bottom * 3, right, bottom);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd5);
			glUniform3fv(grgKaUniformPF, 1, grgKa5);
			glUniform3fv(grgKsUniformPF, 1, grgKs5);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness5);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 4, bottom * 3, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao5);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement5);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////// sphere 6
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd6);
			glUniform3fv(grgKaUniformPF, 1, grgKa6);
			glUniform3fv(grgKsUniformPF, 1, grgKs6);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness6);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 5, bottom * 3, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao6);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement6);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		////////////////////////////////////////////////////////////// sphere 7
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd7);
			glUniform3fv(grgKaUniformPF, 1, grgKa7);
			glUniform3fv(grgKsUniformPF, 1, grgKs7);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness7);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(left, bottom * 2, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao7);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement7);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		////////////////////////////////////////////////////////////// sphere 8
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd8);
			glUniform3fv(grgKaUniformPF, 1, grgKa8);
			glUniform3fv(grgKsUniformPF, 1, grgKs8);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness8);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right, bottom * 2, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao8);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement8);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		////////////////////////////////////////////////////////////// sphere 9
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd9);
			glUniform3fv(grgKaUniformPF, 1, grgKa9);
			glUniform3fv(grgKsUniformPF, 1, grgKs9);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness9);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 2, bottom * 2, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao9);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement9);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		////////////////////////////////////////////////////////////// sphere 10
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd10);
			glUniform3fv(grgKaUniformPF, 1, grgKa10);
			glUniform3fv(grgKsUniformPF, 1, grgKs10);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness10);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 3, bottom * 2, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao10);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement10);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		////////////////////////////////////////////////////////////// sphere 11
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd11);
			glUniform3fv(grgKaUniformPF, 1, grgKa11);
			glUniform3fv(grgKsUniformPF, 1, grgKs11);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness11);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 4, bottom * 2, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao11);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement11);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		////////////////////////////////////////////////////////////// sphere 12
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd12);
			glUniform3fv(grgKaUniformPF, 1, grgKa12);
			glUniform3fv(grgKsUniformPF, 1, grgKs12);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness12);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 5, bottom * 2, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao12);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement12);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		////////////// sphere 13
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd13);
			glUniform3fv(grgKaUniformPF, 1, grgKa13);
			glUniform3fv(grgKsUniformPF, 1, grgKs13);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness13);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(left, bottom, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao13);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement13);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		///////////// sphere 14
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd14);
			glUniform3fv(grgKaUniformPF, 1, grgKa14);
			glUniform3fv(grgKsUniformPF, 1, grgKs14);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness14);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right, bottom, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao14);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement14);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		///////////// sphere 15
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd15);
			glUniform3fv(grgKaUniformPF, 1, grgKa15);
			glUniform3fv(grgKsUniformPF, 1, grgKs15);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness15);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 2, bottom, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao15);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement15);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		///////////// sphere 16
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd16);
			glUniform3fv(grgKaUniformPF, 1, grgKa16);
			glUniform3fv(grgKsUniformPF, 1, grgKs16);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness16);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 3, bottom, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao16);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement16);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		///////////// sphere 17
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd17);
			glUniform3fv(grgKaUniformPF, 1, grgKa17);
			glUniform3fv(grgKsUniformPF, 1, grgKs17);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness17);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 4, bottom, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao17);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement17);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		///////////// sphere 18
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd18);
			glUniform3fv(grgKaUniformPF, 1, grgKa18);
			glUniform3fv(grgKsUniformPF, 1, grgKs18);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness18);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 5, bottom, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao18);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement18);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);
		
		////////////////////////////////////////////////////// sphere 19
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd19);
			glUniform3fv(grgKaUniformPF, 1, grgKa19);
			glUniform3fv(grgKsUniformPF, 1, grgKs19);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness19);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(left, top, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao19);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement19);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////////////////////////////////////////////////////// sphere 20
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd20);
			glUniform3fv(grgKaUniformPF, 1, grgKa20);
			glUniform3fv(grgKsUniformPF, 1, grgKs20);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness20);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right, top, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao20);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement20);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////////////////////////////////////////////////////// sphere 21
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd21);
			glUniform3fv(grgKaUniformPF, 1, grgKa21);
			glUniform3fv(grgKsUniformPF, 1, grgKs21);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness21);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 2, top, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao21);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement21);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////////////////////////////////////////////////////// sphere 22
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd22);
			glUniform3fv(grgKaUniformPF, 1, grgKa22);
			glUniform3fv(grgKsUniformPF, 1, grgKs22);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness22);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 3, top, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao22);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement22);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////////////////////////////////////////////////////// sphere 23
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd23);
			glUniform3fv(grgKaUniformPF, 1, grgKa23);
			glUniform3fv(grgKsUniformPF, 1, grgKs23);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness23);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 4, top, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao23);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement23);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		//////////////////////////////////////////////////////////// sphere 24
		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -2.0f);
		grprojectionMatrix = grgPerspectiveProjectionMatrix;
		grmodelMatrix = grtranslateMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd24);
			glUniform3fv(grgKaUniformPF, 1, grgKa24);
			glUniform3fv(grgKsUniformPF, 1, grgKs24);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness24);
		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}
		glViewport(right * 5, top, right, bottom);
		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao24);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement24);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);
		
		Update();
		// stop use of shader program
		glUseProgram(0);
	}
	SwapBuffers(grghdc);
}

void Update(void)
{
	if (grgKeyPress == 1)
	{
		grflightAngleX = grflightAngleX + 0.03f;
		if (grflightAngleX >= 360.0f)
			grflightAngleX = 0.0f;

	}
	else if (grgKeyPress == 2)
	{
		grflightAngleY = grflightAngleY + 0.035f;
		if (grflightAngleY >= 360.0f)
			grflightAngleY = 0.0f;
	}
	else if (grgKeyPress == 3)
	{
		grflightAngleZ = grflightAngleZ + 0.028f;
		if (grflightAngleZ >= 360.0f)
			grflightAngleZ = 0.0f;
	}


}

void Initialize24Spheres()
{
	grgKa1 = vec4(0.0215,
		0.1745,
		0.0215,
		1.0f);
	grgKd1 = vec4(0.07568,
		0.61424,
		0.07568,
		1.0f);
	grgKs1 = vec4(0.633,
		0.727811,
		0.633,
		1.0f);
	grgMaterialShinyness1 = 0.6 * 128;

	grgKa2 = vec4(0.135,
		0.2225,
		0.1575,
		1.0f);
	grgKd2 = vec4(0.54, // r
		0.89, // g
		0.63, // b
		1.0f // a
	);
	grgKs2 = vec4(0.316228, // r
		0.316228, // g
		0.316228, // b
		1.0f // a
	);
	grgMaterialShinyness2 = 0.1 * 128;

	grgKa3 = vec4(0.05375, // r
		0.05,    // g
		0.06625, // b
		1.0f    // a
	);
	grgKd3 = vec4(0.18275, // r
		0.17,    // g
		0.22525, // b
		1.0f    // a
	);
	grgKs3 = vec4(0.332741, // r
		0.328634, // g
		0.346435, // b
		1.0f     // a
	);
	grgMaterialShinyness3 = 0.3 * 128;

	grgKa4 = vec4(0.25,    // r
		0.20725, // g
		0.20725, // b
		1.0f    // a
	);
	grgKd4 = vec4(1.0,   // r
		0.829, // g
		0.829, // b
		1.0f  // a
	);
	grgKs4 = vec4(0.296648, // r
		0.296648, // g
		0.296648, // b
		1.0f     // a
	);
	grgMaterialShinyness4 = 0.088 * 128;

	grgKa5 = vec4(0.1745,  // r
		0.01175, // g
		0.01175, // b
		1.0f    // a
	);
	grgKd5 = vec4(0.61424, // r
		0.04136, // g
		0.04136, // b
		1.0f    // a
	);
	grgKs5 = vec4(0.727811, // r
		0.626959, // g
		0.626959, // b
		1.0f     // a
	);
	grgMaterialShinyness5 = 0.6 * 128;

	grgKa6 = vec4(0.1,     // r
		0.18725, // g
		0.1745,  // b
		1.0f    // a
	);
	grgKd6 = vec4(0.396,   // r
		0.74151, // g
		0.69102, // b
		1.0f    // a
	);
	grgKs6 = vec4(0.297254, // r
		0.30829,  // g
		0.306678, // b
		1.0f     // a
	);
	grgMaterialShinyness6 = 0.1 * 128;

	grgKa7 = vec4(0.329412, // r
		0.223529, // g
		0.027451, // b
		1.0f     // a
	);
	grgKd7 = vec4(0.780392, // r
		0.568627, // g
		0.113725, // b
		1.0f    // a
	);
	grgKs7 = vec4(0.992157, // r
		0.941176, // g
		0.807843, // b
		1.0f     // a
	);
	grgMaterialShinyness7 = 0.21794872 * 128;

	grgKa8 = vec4(0.2125, // r
		0.1275, // g
		0.054,  // b
		1.0f   // a
	);
	grgKd8 = vec4(0.714,   // r
		0.4284,  // g
		0.18144, // b
		1.0f    // a
	);
	grgKs8 = vec4(0.393548, // r
		0.271906, // g
		0.166721, // b
		1.0f     // a
	);
	grgMaterialShinyness8 = 0.2 * 128;

	grgKa9 = vec4(0.25, // r
		0.25, // g
		0.25, // b
		1.0f // a
	);
	grgKd9 = vec4(0.4,  // r
		0.4,  // g
		0.4,  // b
		1.0f // a
	);
	grgKs9 = vec4(0.774597, // r
		0.774597, // g
		0.774597, // b
		1.0f     // a
	);
	grgMaterialShinyness9 = 0.6 * 128;

	grgKa10 = vec4(0.19125, // r
		0.0735,  // g
		0.0225,  // b
		1.0f    // a
	);
	grgKd10 = vec4(0.7038,  // r
		0.27048, // g
		0.0828,  // b
		1.0f    // a
	);
	grgKs10 = vec4(0.256777, // r
		0.137622, // g
		0.086014, // b
		1.0f     // a
	);
	grgMaterialShinyness10 = 0.1 * 128;

	grgKa11 = vec4(0.24725, // r
		0.1995,  // g
		0.0745,  // b
		1.0f    // a
	);
	grgKd11 = vec4(0.75164, // r
		0.60648, // g
		0.22648, // b
		1.0f    // a
	);
	grgKs11 = vec4(
		0.628281, // r
		0.555802, // g
		0.366065, // b
		1.0f     // a
	);
	grgMaterialShinyness11 = 0.4 * 128;

	grgKa12 = vec4(0.19225, // r
		0.19225, // g
		0.19225, // b
		1.0f    // a
	);
	grgKd12 = vec4(0.50754, // r
		0.50754, // g
		0.50754, // b
		1.0f    // a
	);
	grgKs12 = vec4(0.508273, // r
		0.508273, // g
		0.508273, // b
		1.0f     // a
	);
	grgMaterialShinyness12 = 0.4 * 128;

	grgKa13 = vec4(0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	);
	grgKd13 = vec4(0.01, // r
		0.01, // g
		0.01, // b
		1.0f // a
	);
	grgKs13 = vec4(0.50, // r
		0.50, // g
		0.50, // b
		1.0f // a
	);
	grgMaterialShinyness13 = 0.25 * 128;

	grgKa14 = vec4(0.0,  // r
		0.1,  // g
		0.06, // b
		1.0f // a
	);
	grgKd14 = vec4(0.0,        // r
		0.50980392, // g
		0.50980392, // b
		1.0f       // a
	);
	grgKs14 = vec4(0.50196078, // r
		0.50196078, // g
		0.50196078, // b
		1.0f       // a
	);
	grgMaterialShinyness14 = 0.25 * 128;

	grgKa15 = vec4(0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	);
	grgKd15 = vec4(0.1,  // r
		0.35, // g
		0.1,  // b
		1.0f // a
	);
	grgKs15 = vec4(0.45, // r
		0.55, // g
		0.45, // b
		1.0f // a
	);
	grgMaterialShinyness15 = 0.25 * 128;

	grgKa16 = vec4(0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	);
	grgKd16 = vec4(0.5,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	);
	grgKs16 = vec4(0.7,  // r
		0.6,  // g
		0.6,  // b
		1.0f // a
	);
	grgMaterialShinyness16 = 0.25 * 128;

	grgKa17 = vec4(0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	);
	grgKd17 = vec4(0.55, // r
		0.55, // g
		0.55, // b
		1.0f // a
	);
	grgKs17 = vec4(0.70, // r
		0.70, // g
		0.70, // b
		1.0f // a
	);
	grgMaterialShinyness17 = 0.25 * 128;

	grgKa18 = vec4(0.0,  // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	);
	grgKd18 = vec4(0.5,  // r
		0.5,  // g
		0.0,  // b
		1.0f // a
	);
	grgKs18 = vec4(0.60, // r
		0.60, // g
		0.50, // b
		1.0f // a
	);
	grgMaterialShinyness18 = 0.25 * 128;

	grgKa19 = vec4(0.02, // r
		0.02, // g
		0.02, // b
		1.0f // a
	);
	grgKd19 = vec4(0.01, // r
		0.01, // g
		0.01, // b
		1.0f // a
	);
	grgKs19 = vec4(0.4,  // r
		0.4,  // g
		0.4,  // b
		1.0f // a
	);
	grgMaterialShinyness19 = 0.078125 * 128;

	grgKa20 = vec4(0.0,  // r
		0.05, // g
		0.05, // b
		1.0f // a
	);
	grgKd20 = vec4(0.4,  // r
		0.5,  // g
		0.5,  // b
		1.0f // a
	);
	grgKs20 = vec4(0.04, // r
		0.7,  // g
		0.7,  // b
		1.0f // a
	);
	grgMaterialShinyness20 = 0.078125 * 128;

	grgKa21 = vec4(0.0,  // r
		0.05, // g
		0.0,  // b
		1.0f // a
	);
	grgKd21 = vec4(0.4,  // r
		0.5,  // g
		0.4,  // b
		1.0f // a
	);
	grgKs21 = vec4(0.04, // r
		0.7,  // g
		0.04, // b
		1.0f // a
	);
	grgMaterialShinyness21 = 0.078125 * 128;

	grgKa22 = vec4(0.05, // r
		0.0,  // g
		0.0,  // b
		1.0f // a
	);
	grgKd22 = vec4(0.5,  // r
		0.4,  // g
		0.4,  // b
		1.0f // a
	);
	grgKs22 = vec4(0.7,  // r
		0.04, // g
		0.04, // b
		1.0f // a
	);
	grgMaterialShinyness22 = 0.078125 * 128;

	grgKa23 = vec4(0.05, // r
		0.05, // g
		0.05, // b
		1.0f // a
	);
	grgKd23 = vec4(0.5,  // r
		0.5,  // g
		0.5,  // b
		1.0f // a
	);
	grgKs23 = vec4(0.7,  // r
		0.7,  // g
		0.7,  // b
		1.0f // a
	);
	grgMaterialShinyness23 = 0.078125 * 128;

	grgKa24 = vec4(0.05, // r
		0.05, // g
		0.0,  // b
		1.0f // a
	);
	grgKd24 = vec4(0.5,  // r
		0.5,  // g
		0.4,  // b
		1.0f // a
	);
	grgKs24 = vec4(0.7,  // r
		0.7,  // g
		0.04, // b
		1.0f // a
	);
	grgMaterialShinyness24 = 0.078125 * 128;

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

	if (grgVao1)
	{
		glDeleteVertexArrays(1, &grgVao1);
		grgVao1 = 0;
	}

	if (grgVboSpherePosition1)
	{
		glDeleteBuffers(1, &grgVboSpherePosition1);
		grgVboSpherePosition1 = 0;
	}

	if (grgVboSphereNormal1)
	{
		glDeleteBuffers(1, &grgVboSphereNormal1);
		grgVboSphereNormal1 = 0;
	}

	// free shader objects - safe elease
	if (grgShaderProgramObjectPF)
	{
		glUseProgram(grgShaderProgramObjectPF);
		GLsizei grshaderCount;
		int i;
		glGetProgramiv(grgShaderProgramObjectPF, GL_ATTACHED_SHADERS, &grshaderCount);

		GLuint* grpShaders = NULL;
		grpShaders = (GLuint*)malloc(sizeof(GLuint) * grshaderCount);
		if (grpShaders == NULL)
		{
			exit(0);
		}
		glGetAttachedShaders(grgShaderProgramObjectPF, grshaderCount, &grshaderCount, grpShaders);
		for (i = 0; i < grshaderCount; i++)
		{
			glDetachShader(grgShaderProgramObjectPF, grpShaders[i]);
			glDeleteShader(grpShaders[i]);
			grpShaders[i] = 0;
		}
		glUseProgram(0);
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
}









