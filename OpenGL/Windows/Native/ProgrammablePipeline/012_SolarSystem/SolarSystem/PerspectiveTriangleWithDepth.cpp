#include<windows.h>
#include<stdio.h>
#include<gl\glew.h> // glew.h must be included BEFORE gl.h
#include<gl\GL.h>
#include"vmath.h"
#include"GRWindow.h"
#include"Sphere.h"
#include"GRStack.h"

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
FILE *grgpFile = NULL;

GLuint grgVertexShaderObject;
GLuint grgFragmentShadeerObject;
GLuint grgShaderProgramObject;

enum
{
	GR_ATTRIBUTE_POSITION = 0,
	GR_ATTRIBUTE_COLOR,
	GR_ATTRIBUTE_NORMAL,
	GR_ATTRIBUTE_TEXCOORD
};


mat4 grgPerspectiveProjectionMatrix;

// project specific
float grsphereVertices[1146];
float grsphereNormals[1146];
float grsphereTextures[764];
unsigned short grsphereElements[2280];
GLuint grgNumVertices = 0;
GLuint grgNumElements;

GLuint grgVboPositionEarth;
GLuint grgVboElementEarth;
GLuint grgVaoEarth;
GLuint grgVboPositionSun;
GLuint grgVboColorSun;
GLuint grgVboElementSun;
GLuint grgVaoSun;

// uniforms
GLuint grgModelMarixUniform;
GLuint grgViewMatrixUniform;
GLuint grgProjectionMatrixUniform;

int grgDay = 0;
int grgYear = 0;

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
	
	if(fopen_s(&grgpFile, "GRLog.txt", "w") != 0)
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
			case 'D':
				grgDay = (grgDay + 6) % 360;
				break;

			case 'd':
				grgDay = (grgDay - 6) % 360;
				break;

			case 'Y':
				grgYear = (grgYear + 3) % 360;
				break;

			case 'y':
				grgYear = (grgYear - 3) % 360;
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
	if(griPixelFormatIndex == 0)
	{
		fprintf(grgpFile, "ChoosePixelFormat() failed\n");
		Uninitialize();
	}
	
	if(SetPixelFormat(grghdc, griPixelFormatIndex, &grpfd) == FALSE)
	{
		fprintf(grgpFile, "SetPixelFormat() failed\n");
		Uninitialize();
	}
	
	grghrc = wglCreateContext(grghdc);
	if(grghrc == NULL)
	{
		fprintf(grgpFile, "wglCreateContext() failed\n");
		ReleaseDC(grghwnd, grghdc);
		grghdc = NULL;
	}
	
	if(wglMakeCurrent(grghdc, grghrc) == FALSE)
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


	getSphereVertexData(grsphereVertices, grsphereNormals, grsphereTextures, grsphereElements);
	grgNumVertices = getNumberOfSphereVertices();
	grgNumElements = getNumberOfSphereElements();


	/********* Shader Code *********/

	// create shader
	grgVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	
	const GLchar* grvertexShaderSourceCode =					// also called as "pass-through shader" as it does not have any code (main is empty, no code is there in main)
		"#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec3 vColor;" \
		"uniform mat4 u_model_matrix;" \
		"uniform mat4 u_view_matrix;" \
		"uniform mat4 u_projection_matrix;" \
		"out vec3 out_color;" \
		"void main(void)" \
		"{" \
		"out_color = vColor;" \
		"gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vPosition;" \
		"}";
	
	glShaderSource(grgVertexShaderObject, 1, (const GLchar **) &grvertexShaderSourceCode, NULL);

	// compile shader
	glCompileShader(grgVertexShaderObject);
	// error check for compilation
	GLint griInfoLength = 0;
	GLint griShaderCompileStatus = 0;
	char* grszInfoLog = NULL;

	glGetShaderiv(grgVertexShaderObject, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgVertexShaderObject, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgVertexShaderObject, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Vertex Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
				
			}
		}
		Uninitialize();
	}

	////// Fragment Shader
	grgFragmentShadeerObject = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* grfragmentShaderSourceCode =
		"#version 450 core" \
		"\n" \
		"in vec3 out_color;" \
		"out vec4 FragColor;" \
		"void main(void)" \
		"{" \
		"FragColor = vec4(out_color, 1.0);" \
		"}";

	glShaderSource(grgFragmentShadeerObject, 1, (const GLchar **) &grfragmentShaderSourceCode, NULL);

	// compile shader
	glCompileShader(grgFragmentShadeerObject);
	// error check for compiation
	glGetShaderiv(grgFragmentShadeerObject, GL_COMPILE_STATUS, &griShaderCompileStatus);
	if (griShaderCompileStatus == GL_FALSE)
	{
		glGetShaderiv(grgFragmentShadeerObject, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(char) * sizeof(griInfoLength));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetShaderInfoLog(grgFragmentShadeerObject, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Fragment Shader Compilation Log : %s", grszInfoLog);
				free(grszInfoLog);
				
			}
		}
		Uninitialize();
	}

	//****** Shader Program *****//
	// create
	grgShaderProgramObject = glCreateProgram();

	// attach vertex shader to shader program
	glAttachShader(grgShaderProgramObject, grgVertexShaderObject);

	// attach fragment shader to shader program
	glAttachShader(grgShaderProgramObject, grgFragmentShadeerObject);

	// pre-link our attribute enum with shader's attributes
	glBindAttribLocation(grgShaderProgramObject, GR_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(grgShaderProgramObject, GR_ATTRIBUTE_COLOR, "vColor");

	// link shader
	glLinkProgram(grgShaderProgramObject);
	// error check for linking
	GLint griShaderProgramLinkStatus = 0;
	glGetProgramiv(grgShaderProgramObject, GL_LINK_STATUS, &griShaderProgramLinkStatus);
	if (griShaderProgramLinkStatus == GL_FALSE)
	{
		glGetProgramiv(grgShaderProgramObject, GL_INFO_LOG_LENGTH, &griInfoLength);
		if (griInfoLength > 0)
		{
			grszInfoLog = (char*)malloc(sizeof(griInfoLength) * sizeof(char));
			if (grszInfoLog != NULL)
			{
				GLsizei grwritten;
				glGetProgramInfoLog(grgShaderProgramObject, griInfoLength, &grwritten, grszInfoLog);
				fprintf(grgpFile, "\n Shader Program Link Log : %s", grszInfoLog);
				Uninitialize();
			}
		}
	}

	grgModelMarixUniform = glGetUniformLocation(grgShaderProgramObject, "u_model_matrix");
	grgViewMatrixUniform = glGetUniformLocation(grgShaderProgramObject, "u_view_matrix");
	grgProjectionMatrixUniform = glGetUniformLocation(grgShaderProgramObject, "u_projection_matrix");

	GLfloat *colors = (GLfloat *)malloc(grgNumElements * sizeof(GLfloat));

	for (int i = 0; i < grgNumElements; i = i + 3)
	{
		colors[i] = 1.0f;
		colors[i + 1] = 1.0f;
		colors[i + 2] = 0.0f;
	}

	
	// sun
	glGenVertexArrays(1, &grgVaoSun);
	glBindVertexArray(grgVaoSun);
	glGenBuffers(1, &grgVboPositionSun);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboPositionSun);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphereVertices), grsphereVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &grgVboColorSun);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboColorSun);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphereVertices), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_COLOR, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// element vbo
	glGenBuffers(1, &grgVboElementSun);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboElementSun);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphereElements), grsphereElements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);



	//EARTH
	glGenVertexArrays(1, &grgVaoEarth);
	glBindVertexArray(grgVaoEarth);
	glGenBuffers(1, &grgVboPositionEarth);
	glBindBuffer(GL_ARRAY_BUFFER, grgVboPositionEarth);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grsphereVertices), grsphereVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(GR_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(GR_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 0.0f, 1.0f);
	

	// element vbo
	glGenBuffers(1, &grgVboElementEarth);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboElementEarth);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphereElements), grsphereElements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 0.0f, 1.0f);

	glBindVertexArray(0);

	/*
	// element vbo
	glGenBuffers(1, &grgVboElementEarth);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboElementEarth);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grsphereElements), grsphereElements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glVertexAttrib3f(GR_ATTRIBUTE_COLOR, 0.0f, 0.0f, 1.0f);
	*/


	

	// Depth
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// set clearcolor
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// initialize stack logs
	initLog();

	grgPerspectiveProjectionMatrix = mat4::identity();
	
	// warm-up call to resize
	Resize(WIN_WIDTH, WIN_HEIGHT);
}

void Resize(int width, int height)
{
	if(height == 0)
		height = 1;
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	grgPerspectiveProjectionMatrix = vmath::perspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);

}

void Display(void)
{

	// code
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// start use of shader program
	glUseProgram(grgShaderProgramObject);

	// OpenGL drawing code will start here
	mat4 grmodelMatrix = mat4::identity();
	mat4 grviewMatrix = mat4::identity();
	mat4 grprojectionMatrix = mat4::identity();
	mat4 grrotateMatrix = mat4::identity();
	mat4 grtranslateMatrix = mat4::identity();
	mat4 grscaleMatrix = mat4::identity();

	#pragma region solar system
	// push matrix for whole geometry
	grtranslateMatrix = vmath::translate(0.0f, 0.0f, -6.0f);
	grmodelMatrix = grtranslateMatrix;
	PushToStack(grmodelMatrix);

	// sun
	grmodelMatrix = mat4::identity();
	grviewMatrix = mat4::identity();
	grprojectionMatrix = mat4::identity();
	grrotateMatrix = mat4::identity();
	grtranslateMatrix = mat4::identity();
	grscaleMatrix = mat4::identity();

	grrotateMatrix = vmath::rotate(90.0f, 1.0f, 0.0f, 0.0f);		// rotate to match south-north pole to its right directions 
	grmodelMatrix = grrotateMatrix;
	grmodelMatrix = PushToStack(grmodelMatrix);
	PopFromStack();

	grprojectionMatrix = grgPerspectiveProjectionMatrix;

	glUniformMatrix4fv(grgProjectionMatrixUniform, 1, GL_FALSE, grprojectionMatrix);
	glUniformMatrix4fv(grgViewMatrixUniform, 1, GL_FALSE, grviewMatrix);
	glUniformMatrix4fv(grgModelMarixUniform, 1, GL_FALSE, grmodelMatrix);

	// bind vao of square
	glBindVertexArray(grgVaoSun);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboElementSun);
	glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_LINE_STRIP, 0, grgNumVertices);
	// unbind vao
	glBindVertexArray(0);

	
	// Earth
	grmodelMatrix = mat4::identity();
	grviewMatrix = mat4::identity();
	grprojectionMatrix = mat4::identity();
	grrotateMatrix = mat4::identity();
	grtranslateMatrix = mat4::identity();
	grscaleMatrix = mat4::identity();


	grrotateMatrix = vmath::rotate((GLfloat)grgYear, 0.0f, 1.0f, 0.0f);
	grtranslateMatrix = vmath::translate(2.0f, 0.0f, 0.0f);
	grmodelMatrix = grrotateMatrix * grtranslateMatrix;
	grrotateMatrix = vmath::rotate(270.0f, 1.0f, 0.0f, 0.0f);
	grrotateMatrix = grrotateMatrix * vmath::rotate((GLfloat)grgDay, 0.0f, 0.0f, 1.0f);
	grmodelMatrix = grmodelMatrix * grrotateMatrix;
	grmodelMatrix = PushToStack(grmodelMatrix);
	PopFromStack();

	grprojectionMatrix = grgPerspectiveProjectionMatrix;

	glUniformMatrix4fv(grgProjectionMatrixUniform, 1, GL_FALSE, grprojectionMatrix);
	glUniformMatrix4fv(grgViewMatrixUniform, 1, GL_FALSE, grviewMatrix);
	glUniformMatrix4fv(grgModelMarixUniform, 1, GL_FALSE, grmodelMatrix);

	// bind vao of square
	glBindVertexArray(grgVaoEarth);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grgVboElementEarth);
	glDrawElements(GL_TRIANGLES, grgNumElements, GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, grgNumVertices);
	// unbind vao
	glBindVertexArray(0);
	

	PopFromStack();
	#pragma endregion solar system 

	// stop use of shader program
	glUseProgram(0);

	//Update();
	SwapBuffers(grghdc);
}



void Uninitialize(void)
{
	//code

	// free stack memory
	destroyLog();

	if(grgbFullScreen == true)
	{
		grdwStyle = GetWindowLong(grghwnd, GWL_STYLE);
		SetWindowLong(grghwnd, GWL_STYLE, (grdwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(grghwnd, &grgwpPrev);
		SetWindowPos(grghwnd, HWND_TOP, 0, 0, 0, 0, 
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		
		ShowCursor(true);
		
	}
	//  delete vbo

	if (grgVboPositionSun)
	{
		glDeleteBuffers(1, &grgVboPositionSun);
		grgVboPositionSun = 0;
	}
	if (grgVboElementSun)
	{
		glDeleteBuffers(1, &grgVboElementSun);
		grgVboElementSun = 0;
	}
	if (grgVboColorSun)
	{
		glDeleteBuffers(1, &grgVboColorSun);
		grgVboColorSun = 0;
	}

	if (grgVboPositionEarth)
	{
		glDeleteBuffers(1, &grgVboPositionEarth);
		grgVboPositionEarth = 0;
	}
	if (grgVboElementEarth)
	{
		glDeleteBuffers(1, &grgVboElementEarth);
		grgVboElementEarth = 0;
	}


	// delete square vao and vbo
	if (grgVaoSun)
	{
		glDeleteVertexArrays(1, &grgVaoSun);
		grgVaoSun = 0;
	}
	if (grgVaoEarth)
	{
		glDeleteVertexArrays(1, &grgVaoEarth);
		grgVaoEarth = 0;
	}
	
	

	// free shader objects - safe elease
	if (grgShaderProgramObject)
	{
		glUseProgram(grgShaderProgramObject);
		GLsizei grshaderCount;
		int i;
		glGetProgramiv(grgShaderProgramObject, GL_ATTACHED_SHADERS, &grshaderCount);

		GLuint* grpShaders = NULL;
		grpShaders = (GLuint*)malloc(sizeof(GLuint) * grshaderCount);
		if (grpShaders == NULL)
		{
			exit(0);
		}
		glGetAttachedShaders(grgShaderProgramObject, grshaderCount, &grshaderCount, grpShaders);
		for (i = 0; i < grshaderCount; i++)
		{
			glDetachShader(grgShaderProgramObject, grpShaders[i]);
			glDeleteShader(grpShaders[i]);
			grpShaders[i] = 0;
		}
		glUseProgram(0);
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









