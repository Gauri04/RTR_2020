#include<windows.h>
#include<stdio.h>

// global fuctions declaration
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// global variables declaration
DWORD dwStyle;
WINDOWPLACEMENT grWPPrev = { sizeof(WINDOWPLACEMENT) };
bool grgbFullScreen = false;
HWND grghwnd = NULL;
int grgWndWidth = 800;
int grgWndHeight = 600;
int grgDesktopWidth, grgDesktopHeight;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("GRFullScreenWindow");
	int grWndXPos, grWndYPos;
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	RegisterClassEx(&wndclass);
	
	// Get width and height of desktop screen
	grgDesktopWidth = GetSystemMetrics(SM_CXSCREEN);
	grgDesktopHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// X position = center horizontal coordinate of screen - center horizontal coordinate of window
	grWndXPos = (grgDesktopWidth / 2) - 400;
	
	// X position = center horizontal coordinate of screen - center horizontal coordinate of window
	grWndYPos = (grgDesktopHeight / 2) - 300;
	
	
	hwnd = CreateWindow(szAppName,
				TEXT("GRFullScreenWindow"),
				WS_OVERLAPPEDWINDOW,
				grWndXPos,
				grWndYPos,
				grgWndWidth,
				grgWndHeight,
				NULL,
				NULL,
				hInstance,
				NULL);
				
	grghwnd = hwnd;
	
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ToggleFullScreen(void);
	switch(iMsg)
	{
		case WM_CREATE :
			break;
		case WM_KEYDOWN : 
			switch(wParam)
			{
				case 0x46 : 				// 'F'
				case 0x66 :					// 'f'
					ToggleFullScreen();
					break;
				
				default : 
					break;
			}
			break;
			
		
		case WM_DESTROY :
			PostQuitMessage(0);
			break;
		
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen()
{
	DEVMODE grDevmode = { sizeof(grDevmode) };
	MONITORINFO grmi = { sizeof(MONITORINFO) };
	DWORD grPrevPelsWidth, grPrevPelsHeight, grPrevBpp;
	LRESULT grlResult;
	
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &grDevmode);
	grPrevPelsWidth = grDevmode.dmPelsWidth;
	grPrevPelsHeight = grDevmode.dmPelsHeight;
	grPrevBpp = grDevmode.dmBitsPerPel; 
	
	if(grgbFullScreen == false)
	{
		
		dwStyle = GetWindowLong(grghwnd, GWL_STYLE);
		if(dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if( GetWindowPlacement(grghwnd, &grWPPrev) && GetMonitorInfo(MonitorFromWindow(grghwnd, MONITORINFOF_PRIMARY), &grmi) )
			{
				
				SetWindowLong( grghwnd, GWL_STYLE, (dwStyle & ~ WS_OVERLAPPEDWINDOW) );				
				memset(&grDevmode, 0, sizeof(grDevmode));
				grDevmode.dmSize = sizeof(grDevmode);
				grDevmode.dmPelsWidth = grgWndWidth;
				grDevmode.dmPelsHeight = grgWndHeight;
				grDevmode.dmBitsPerPel = grPrevBpp;
				grDevmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
				
				grlResult = ChangeDisplaySettings(&grDevmode, CDS_TEST);
				
				if(grlResult == DISP_CHANGE_SUCCESSFUL)
				{
					ChangeDisplaySettings(&grDevmode, CDS_FULLSCREEN);
				}
				else
					MessageBox(grghwnd, TEXT("Invalid resolution settings"), TEXT("Error"), MB_OK);
				
			}
		}
		
		ShowCursor(false);
		grgbFullScreen = true;
	}
	else
	{
		
		
		SetWindowLong( grghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW) );
		grDevmode.dmPelsWidth = grgDesktopWidth;
		grDevmode.dmPelsHeight = grgDesktopHeight;
		grDevmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
		ChangeDisplaySettings(&grDevmode, 0);
		ShowCursor(true);
		grgbFullScreen = false;
	}
}












