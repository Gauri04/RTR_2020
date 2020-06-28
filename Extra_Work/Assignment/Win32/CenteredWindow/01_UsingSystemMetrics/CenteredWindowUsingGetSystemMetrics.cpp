#include<windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyCenteredWindow");
	int desktopWidth, desktopHeight;
	int myWndXPos, myWndYPos;
	
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
	desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	desktopHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// Get center horizontal point
	desktopWidth = desktopWidth / 2;
	// Get center vertical point
	desktopHeight = desktopHeight / 2;
	
	// X position = center horizontal coordinate of screen - center horizontal coordinate of window
	myWndXPos = desktopWidth - 400;
	
	// X position = center horizontal coordinate of screen - center horizontal coordinate of window
	myWndYPos = desktopHeight - 300;
	
	
	hwnd = CreateWindow(szAppName,
				TEXT("My Centered Window"),
				WS_OVERLAPPEDWINDOW,
				myWndXPos,
				myWndYPos,
				800,
				600,
				NULL,
				NULL,
				hInstance,
				NULL);
				
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
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}




