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

GLuint grgVao;
mat4 grgPerspectiveProjectionMatrix;

// project specific 
float grsphere_vertices[1146];
float grsphere_normals[1146];
float grsphere_textures[764];
unsigned short grsphere_elements[2280];
GLuint grgNumVertices;
GLuint grgNumElements;
GLuint grgVboSpherePosition;
GLuint grgVboSphereNormal;
GLuint grgVboSphereElement;

// per vertex
// uniforms
GLuint grgModelMarixUniformPV;
GLuint grgViewMatrixUniformPV;
GLuint grgProjectionMatrixUniformPV;
GLuint grgLaUniformPV[3];				// light ambient
GLuint grgLdUniformPV[3];				// light diffuse
GLuint grgLsUniformPV[3];				// light specular
GLuint grgLightPositionUniformPV[3];
GLuint grgKdUniformPV;
GLuint grgKaUniformPV;
GLuint grgKsUniformPV;
GLuint grgMaterialShinynessUniformPV;
GLuint grgLKeyPressedUniformPV;

GLuint grgVertexShaderObjectPV;
GLuint grgFragmentShadeerObjectPV;
GLuint grgShaderProgramObjectPV;


// per fragment
// uniforms
GLuint grgModelMatrixUniformPF;
GLuint grgViewMatrixUniformPF;
GLuint grgProjectionMatrixUniformPF;
GLuint grgLaUniformPF[3];
GLuint grgLdUniformPF[3];
GLuint grgLsUniformPF[3];
GLuint grgLightPositionUniformPF[3];
GLuint grgKdUniformPF;					// material diffuse
GLuint grgKaUniformPF;					// material ambient
GLuint grgKsUniformPF;					// material specular
GLuint grgMaterialShinynessUniformPF;
GLuint grgLKeyPressedUniformPF;

GLuint grgVertexShaderObjectPF;
GLuint grgFragmentShaderObjectPF;
GLuint grgShaderProgramObjectPF;

struct Light
{
	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;
	vec4 lightPosition;
};
struct Light grlight[3];
vec4 grgKa = { 0.0, 0.0, 0.0, 1.0 };	// material ambient
vec4 grgKd = { 1.0, 1.0, 1.0, 1.0 };	// material diffuse
vec4 grgKs = { 1.0, 1.0, 1.0, 1.0 };	// material specular
GLfloat grgMaterialShinyness = 128;
bool grgbPerVertexLighting;
bool grgbPerFragmentLighting;
bool grgbLKeyPressed = false;
bool grgbXKeyPressed;
bool grgbYKeyPressed;
bool grgbZKeyPressed;
GLfloat grflightAngleX;
GLfloat grflightAngleY;
GLfloat grflightAngleZ;
int i;


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

		case 'v':
		case 'V':
			grgbPerVertexLighting = !grgbPerVertexLighting;
			break;

		case 'l':
		case 'L':
			grgbLKeyPressed = !grgbLKeyPressed;
			break;

		case 'x':
		case 'X':
			grgbXKeyPressed = true;
			break;

		case 'y':
		case 'Y':
			grgbYKeyPressed = true;
			break;

		case 'z':
		case 'Z':
			grgbZKeyPressed = true;
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


	/********* Shader Code *********/

	// create shader
	grgVertexShaderObjectPV = glCreateShader(GL_VERTEX_SHADER);

	///// Vertex Shader
	/*
	const GLchar* grvertexShaderSourceCode =					// also called as "pass-through shader" as it does not have any code (main is empty, no code is there in main)
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
		"out vec3 light_direction[3];" \
		"out vec3 view_vector;" \
		"int i;" \
		"void main(void)" \
		"{" \
		"if(u_l_key_pressed == 1)" \
		"{" \
			"vec4 eye_coordinates =  u_view_matrix * u_model_matrix * vPosition;" \
			"transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
			"view_vector = normalize(-eye_coordinates.xyz);" \
			"for(i = 0; i < 3; i++)" \
			"{" \
				"light_direction[i] = normalize(vec3(u_light_position[i] - eye_coordinates));" \
			"}" \
		"}" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"}";
	*/

	const GLchar* grvertexShaderSourceCodePV =					// also called as "pass-through shader" as it does not have any code (main is empty, no code is there in main)
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vNormal;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"uniform int u_l_key_pressed;" \
		"uniform vec3 u_la[3];" \
		"uniform vec3 u_ld[3];" \
		"uniform vec3 u_ls[3];" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_material_shinyness;" \
		"uniform vec4 u_light_position[3];" \
		"out vec3 phong_ads_light;" \
		"int i;" \
		"void main(void)" \
		"{" \
		"if(u_l_key_pressed == 1)" \
		"{" \
		"vec4 eye_coordinates =  u_view_matrix * u_model_matrix * vPosition;" \
		"vec3 transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
		"vec3 view_vector = normalize(-eye_coordinates.xyz);" \
		"vec3 light_direction[3];" \
		"vec3 reflection_vector[3];" \
		"vec3 ambient[3];" \
		"vec3 diffuse[3];" \
		"vec3 specular[3];" \
		"for(i = 0; i < 3; i++)" \
		"{" \
		"light_direction[i] = normalize(vec3(u_light_position[i] - eye_coordinates));" \
		"reflection_vector[i] = reflect(-light_direction[i], transformed_normal);" \
		"ambient[i] = u_la[i] * u_ka;" \
		"diffuse[i] = u_ld[i] * u_kd * max(dot(light_direction[i], transformed_normal), 0.0);" \
		"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], view_vector), 0.0), u_material_shinyness);" \
		"phong_ads_light = phong_ads_light + ambient[i] + diffuse[i] + specular[i];" \
		"}" \
		"}" \
		"else" \
		"{" \
		"phong_ads_light = vec3(1.0, 1.0, 1.0);" \
		"}" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"}";

	glShaderSource(grgVertexShaderObjectPV, 1, (const GLchar**)&grvertexShaderSourceCodePV, NULL);

	// compile shader
	glCompileShader(grgVertexShaderObjectPV);
	// error check for compilation
	GLint griInfoLength = 0;
	GLint griShaderCompileStatus = 0;
	char* grszInfoLog = NULL;

	glGetShaderiv(grgVertexShaderObjectPV, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgVertexShaderObjectPV, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * griInfoLength);
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgVertexShaderObjectPV, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Vertex Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
				Uninitialize();
			}
		}
	}

	////// Fragment Shader
	grgFragmentShadeerObjectPV = glCreateShader(GL_FRAGMENT_SHADER);

	// source code of shader
	/*
	const GLchar* grfragmentShaderSourceCode =
		"#version 450 core" \
		"\n" \
		"in vec3 transformed_normal;" \
		"in vec3 light_direction[3];" \
		"in vec3 view_vector;" \
		"uniform vec3 u_la[3];" \
		"uniform vec3 u_ld[3];" \
		"uniform vec3 u_ls[3];" \
		"uniform vec3 u_ka;" \
		"uniform vec3 u_kd;" \
		"uniform vec3 u_ks;" \
		"uniform float u_material_shinyness;" \
		"uniform int u_l_key_pressed;" \
		"vec3 fong_ads_light;"
		"out vec4 FragColor;" \
		"int i;" \
		"void main(void)" \
		"{" \
		"if(u_l_key_pressed == 1)" \
		"{" \
			"vec3 reflection_vector[3];" \
			"vec3 ambient[3];" \
			"vec3 diffuse[3];" \
			"vec3 specular[3];" \
			"for(i = 0; i < 3; i++)" \
			"{" \
				"reflection_vector[i] = reflect(-light_direction[i], transformed_normal);" \
				"ambient[i] = u_la[i] * u_ka;" \
				"diffuse[i] = u_ld[i] * u_kd * max(dot(light_direction[i], transformed_normal), 0.0);" \
				"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], view_vector), 0.0), u_material_shinyness);" \
				"fong_ads_light = fong_ads_light + ambient[i] + diffuse[i] + specular[i];" \
			"}" \
		"}" \
		"else" \
		"{" \
			"fong_ads_light = vec3(1.0, 1.0, 1.0);" \
		"}" \
		"FragColor = vec4(fong_ads_light, 1.0);" \
		"}";
	*/

	const GLchar* grfragmentShaderSourceCodePV =
		"#version 450 core" \
		"\n" \
		"in vec3 phong_ads_light;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = vec4(phong_ads_light, 1.0);" \
		"}";

	glShaderSource(grgFragmentShadeerObjectPV, 1, (const GLchar**)&grfragmentShaderSourceCodePV, NULL);

	// compile shader
	glCompileShader(grgFragmentShadeerObjectPV);
	// error check for compiation
	glGetShaderiv(grgFragmentShadeerObjectPV, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgFragmentShadeerObjectPV, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * griInfoLength);
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgFragmentShadeerObjectPV, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Fragment Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);

			}
		}
		Uninitialize();
	}

	//****** Shader Program *****//
	// create
	grgShaderProgramObjectPV = glCreateProgram();

	// attach vertex shader to shader program
	glAttachShader(grgShaderProgramObjectPV, grgVertexShaderObjectPV);

	// attach fragment shader to shader program
	glAttachShader(grgShaderProgramObjectPV, grgFragmentShadeerObjectPV);

	// pre-link our attribute enum with shader's attributes
	glBindAttribLocation(grgShaderProgramObjectPV, GR_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(grgShaderProgramObjectPV, GR_ATTRIBUTE_NORMAL, "vNormal");

	// link shader
	glLinkProgram(grgShaderProgramObjectPV);
	// error check for linking
	GLint griShaderProgramLinkStatus = 0;
	glGetProgramiv(grgShaderProgramObjectPV, GL_LINK_STATUS, &griShaderProgramLinkStatus);
	if (griShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(grgShaderProgramObjectPV, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(griInfoLength * sizeof(char));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetProgramInfoLog(grgShaderProgramObjectPV, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Shader Program Link Log : %s", grszInfoLog);
				free(grszInfoLog);
			}
		}
		Uninitialize();
	}

	grgModelMarixUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_model_matrix");
	grgViewMatrixUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_view_matrix");
	grgProjectionMatrixUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_projection_matrix");

	grgLdUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ld[0]");
	grgLaUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_la[0]");
	grgLsUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ls[0]");
	grgLdUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ld[1]");
	grgLaUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_la[1]");
	grgLsUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ls[1]");
	grgLdUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ld[2]");
	grgLaUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_la[2]");
	grgLsUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_ls[2]");
	grgLightPositionUniformPV[0] = glGetUniformLocation(grgShaderProgramObjectPV, "u_light_position[0]");
	grgLightPositionUniformPV[1] = glGetUniformLocation(grgShaderProgramObjectPV, "u_light_position[1]");
	grgLightPositionUniformPV[2] = glGetUniformLocation(grgShaderProgramObjectPV, "u_light_position[2]");

	grgKaUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_ka");
	grgKdUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_kd");
	grgKsUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_ks");

	grgLKeyPressedUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_l_key_pressed");
	grgMaterialShinynessUniformPV = glGetUniformLocation(grgShaderProgramObjectPV, "u_material_shinyness");

	// initialize colors
	grlight[0].lightAmbientColor = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[0].lightDiffuseColor = vec4(1.0, 0.0, 0.0, 1.0);
	grlight[0].lightSpecularColor = vec4(1.0, 0.0, 0.0, 1.0);

	grlight[1].lightAmbientColor = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[1].lightDiffuseColor = vec4(0.0, 1.0, 0.0, 1.0);
	grlight[1].lightSpecularColor = vec4(0.0, 1.0, 0.0, 1.0);

	grlight[2].lightAmbientColor = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[2].lightDiffuseColor = vec4(0.0, 0.0, 1.0, 1.0);
	grlight[2].lightSpecularColor = vec4(0.0, 0.0, 1.0, 1.0);

	grlight[0].lightPosition = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[1].lightPosition = vec4(0.0, 0.0, 0.0, 1.0);
	grlight[2].lightPosition = vec4(0.0, 0.0, 0.0, 1.0);


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
		"uniform vec4 u_light_position[3];" \
		"out vec3 transformed_normal;" \
		"out vec3 light_direction[3];" \
		"out vec3 view_vector;" \
		"int i;" \
		"void main(void)" \
		"{" \
		"if(u_l_key_pressed == 1)" \
		"{" \
		"vec4 eye_coordinates = u_view_matrix * u_model_matrix * vPosition;" \
		"transformed_normal = normalize(mat3(u_view_matrix * u_model_matrix) * vNormal);" \
		"view_vector = normalize(-eye_coordinates.xyz);" \
		"for(i = 0; i < 3; i++)" \
		"{" \
		"light_direction[i] = normalize(vec3(u_light_position[i] - eye_coordinates));" \
		"}" \
		"}" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"}";

	glShaderSource(grgVertexShaderObjectPF, 1, (const GLchar**)&grvertexShaderSourceCodePF, NULL);

	// compile shader
	glCompileShader(grgVertexShaderObjectPF);
	// error check for compilation
	griInfoLength = 0;
	griShaderCompileStatus = 0;
	grszInfoLog = NULL;

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
		"in vec3 light_direction[3];" \
		"in vec3 view_vector;" \
		"uniform vec3 u_la[3];" \
		"uniform vec3 u_ld[3];" \
		"uniform vec3 u_ls[3];" \
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
		"vec3 reflection_vector[3];" \
		"vec3 ambient[3];" \
		"vec3 diffuse[3];" \
		"vec3 specular[3];" \
		"for(i = 0; i < 3; i++)" \
		"{" \
		"reflection_vector[i] = reflect(-light_direction[i], transformed_normal);" \
		"ambient[i] = u_la[i] *u_ka;" \
		"diffuse[i] = u_ld[i] * u_kd * max(dot(light_direction[i], transformed_normal), 0.0);" \
		"specular[i] = u_ls[i] * u_ks * pow(max(dot(reflection_vector[i], view_vector), 0.0), u_material_shinyness);" \
		"fong_ads_light = fong_ads_light + ambient[i] + diffuse[i] + specular[i];" \
		"}" \
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
	griShaderProgramLinkStatus = 0;
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

	grgLdUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ld[0]");
	grgLaUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_la[0]");
	grgLsUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ls[0]");
	grgLdUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ld[1]");
	grgLaUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_la[1]");
	grgLsUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ls[1]");
	grgLdUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ld[2]");
	grgLaUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_la[2]");
	grgLsUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_ls[2]");
	grgLightPositionUniformPF[0] = glGetUniformLocation(grgShaderProgramObjectPF, "u_light_position[0]");
	grgLightPositionUniformPF[1] = glGetUniformLocation(grgShaderProgramObjectPF, "u_light_position[1]");
	grgLightPositionUniformPF[2] = glGetUniformLocation(grgShaderProgramObjectPF, "u_light_position[2]");

	grgKaUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ka");
	grgKdUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_kd");
	grgKsUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_ks");

	grgLKeyPressedUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_l_key_pressed");
	grgMaterialShinynessUniformPF = glGetUniformLocation(grgShaderProgramObjectPF, "u_material_shinyness");

	glGenVertexArrays(1, &grgVao);
	glBindVertexArray(grgVao);

	// position vbo
	glGenBuffers(1, &grgVboSpherePosition);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSpherePosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_vertices), grsphere_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// normal vbo
	glGenBuffers(1, &grgVboSphereNormal);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboSphereNormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphere_normals), grsphere_normals, GL_STATIC_DRAW);

	glVertexAttribPointer(GR_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(GR_ATTRIBUTE_NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboSphereElement);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement);
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	grgPerspectiveProjectionMatrix = mat4::identity();

	// warm-up call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

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

	if (grgbPerVertexLighting == true)
	{
		// start use of shader program
		glUseProgram(grgShaderProgramObjectPV);

		grmodelMatrix = mat4::identity();
		grviewMatrix = mat4::identity();
		grprojectionMatrix = mat4::identity();
		grtranslateMatrix = mat4::identity();

		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
		grmodelMatrix = grtranslateMatrix;

		// multiply modelview and orthographic matrix to get modelviewprojectionmatrix
		grprojectionMatrix = grgPerspectiveProjectionMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPV, 1);
			glUniform3fv(grgKdUniformPV, 1, grgKd);
			glUniform3fv(grgKaUniformPV, 1, grgKa);
			glUniform3fv(grgKsUniformPV, 1, grgKs);
			glUniform1f(grgMaterialShinynessUniformPV, grgMaterialShinyness);

			if (grgbXKeyPressed == true)
			{
				grlight[0].lightPosition[0] = 0.0;
				grlight[0].lightPosition[1] = (GLfloat)5.5 * sin(grflightAngleX);
				grlight[0].lightPosition[2] = (GLfloat)5.5 * cos(grflightAngleX);
				grlight[0].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}
			if (grgbYKeyPressed == true)
			{
				grlight[1].lightPosition[0] = (GLfloat)4.5 * sin(grflightAngleX);;
				grlight[1].lightPosition[1] = 0.0;
				grlight[1].lightPosition[2] = (GLfloat)4.5 * cos(grflightAngleX);
				grlight[1].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			if (grgbZKeyPressed == true)
			{
				grlight[2].lightPosition[0] = (GLfloat)6.5 * sin(grflightAngleX);;
				grlight[2].lightPosition[1] = (GLfloat)6.5 * cos(grflightAngleX);
				grlight[2].lightPosition[2] = 0.0f;
				grlight[2].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			for (i = 0; i < 3; i++)
			{
				glUniform3fv(grgLdUniformPV[i], 1, grlight[i].lightDiffuseColor);
				glUniform3fv(grgLaUniformPV[i], 1, grlight[i].lightAmbientColor);
				glUniform3fv(grgLsUniformPV[i], 1, grlight[i].lightSpecularColor);
				glUniform4fv(grgLightPositionUniformPV[i], 1, grlight[i].lightPosition);
			}

		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPV, 0);
		}

		glUniformMatrix4fv(grgModelMarixUniformPV, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPV, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPV, 1, GL_FALSE, grprojectionMatrix);
		// bind vao
		glBindVertexArray(grgVao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement);
		glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);

		// unbind vao
		glBindVertexArray(0);

		Update();
		// stop use of shader program
		glUseProgram(0);
	}
	else if (grgbPerFragmentLighting == true)
	{
		// start use of shader program
		glUseProgram(grgShaderProgramObjectPF);

		grmodelMatrix = mat4::identity();
		grviewMatrix = mat4::identity();
		grprojectionMatrix = mat4::identity();
		grtranslateMatrix = mat4::identity();

		grtranslateMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
		grmodelMatrix = grtranslateMatrix;

		// multiply modelview and orthographic matrix to get modelviewprojectionmatrix
		grprojectionMatrix = grgPerspectiveProjectionMatrix;

		if (grgbLKeyPressed == true)
		{
			glUniform1i(grgLKeyPressedUniformPF, 1);
			glUniform3fv(grgKdUniformPF, 1, grgKd);
			glUniform3fv(grgKaUniformPF, 1, grgKa);
			glUniform3fv(grgKsUniformPF, 1, grgKs);
			glUniform1f(grgMaterialShinynessUniformPF, grgMaterialShinyness);

			if (grgbXKeyPressed == true)
			{
				grlight[0].lightPosition[0] = 0.0;
				grlight[0].lightPosition[1] = (GLfloat)5.5 * sin(grflightAngleX);
				grlight[0].lightPosition[2] = (GLfloat)5.5 * cos(grflightAngleX);
				grlight[0].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}
			if (grgbYKeyPressed == true)
			{
				grlight[1].lightPosition[0] = (GLfloat)4.5 * sin(grflightAngleX);;
				grlight[1].lightPosition[1] = 0.0;
				grlight[1].lightPosition[2] = (GLfloat)4.5 * cos(grflightAngleX);
				grlight[1].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			if (grgbZKeyPressed == true)
			{
				grlight[2].lightPosition[0] = (GLfloat)6.5 * sin(grflightAngleX);;
				grlight[2].lightPosition[1] = (GLfloat)6.5 * cos(grflightAngleX);
				grlight[2].lightPosition[2] = 0.0f;
				grlight[2].lightPosition[3] = 1.0;							// w for positional light
				//grlight[0].lightPosition = vec4(0.0, (GLfloat)(1.2 * sin(grflightAngleX)), (GLfloat)(1.2 * cos(grflightAngleX)), 1.0);
			}

			for (i = 0; i < 3; i++)
			{
				glUniform3fv(grgLdUniformPF[i], 1, grlight[i].lightDiffuseColor);
				glUniform3fv(grgLaUniformPF[i], 1, grlight[i].lightAmbientColor);
				glUniform3fv(grgLsUniformPF[i], 1, grlight[i].lightSpecularColor);
				glUniform4fv(grgLightPositionUniformPF[i], 1, grlight[i].lightPosition);
			}

		}
		else
		{
			glUniform1i(grgLKeyPressedUniformPF, 0);
		}

		glUniformMatrix4fv(grgModelMatrixUniformPF, 1, GL_FALSE, grmodelMatrix);
		glUniformMatrix4fv(grgViewMatrixUniformPF, 1, GL_FALSE, grviewMatrix);
		glUniformMatrix4fv(grgProjectionMatrixUniformPF, 1, GL_FALSE, grprojectionMatrix);

		// bind vao
		glBindVertexArray(grgVao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboSphereElement);
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
	if (grgbXKeyPressed)
	{
		grflightAngleX = grflightAngleX + 0.003f;
		if (grflightAngleX >= 360.0f)
			grflightAngleX = 0.0f;

	}
	if (grgbYKeyPressed)
	{
		grflightAngleY = grflightAngleY + 0.0035f;
		if (grflightAngleY >= 360.0f)
			grflightAngleY = 0.0f;
	}
	if (grgbZKeyPressed)
	{
		grflightAngleZ = grflightAngleZ + 0.0028f;
		if (grflightAngleZ >= 360.0f)
			grflightAngleZ = 0.0f;
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

	if (grgVao)
	{
		glDeleteVertexArrays(1, &grgVao);
		grgVao = 0;
	}

	if (grgVboSpherePosition)
	{
		glDeleteBuffers(1, &grgVboSpherePosition);
		grgVboSpherePosition = 0;
	}

	if (grgVboSphereNormal)
	{
		glDeleteBuffers(1, &grgVboSphereNormal);
		grgVboSphereNormal = 0;
	}

	// free shader objects - safe elease
	if (grgShaderProgramObjectPV)
	{
		glUseProgram(grgShaderProgramObjectPV);
		GLsizei grshaderCount;
		int i;
		glGetProgramiv(grgShaderProgramObjectPV, GL_ATTACHED_SHADERS, &grshaderCount);

		GLuint* grpShaders = NULL;
		grpShaders = (GLuint*)malloc(sizeof(GLuint) * grshaderCount);
		if (grpShaders == NULL)
		{
			exit(0);
		}
		glGetAttachedShaders(grgShaderProgramObjectPV, grshaderCount, &grshaderCount, grpShaders);
		for (i = 0; i < grshaderCount; i++)
		{
			glDetachShader(grgShaderProgramObjectPV, grpShaders[i]);
			glDeleteShader(grpShaders[i]);
			grpShaders[i] = 0;
		}
		glUseProgram(0);
	}
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









