#include<windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyHelloWorld");
	
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
	
	hwnd = CreateWindow(szAppName,
				TEXT("Hello World"),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
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
	HDC grHdc;
	PAINTSTRUCT grPS;
	RECT grRC;
	TCHAR grStr[] = TEXT("Hello World !!!");
	
	switch(iMsg)
	{
		
		case WM_PAINT :
			GetClientRect(hwnd, &grRC);
			grHdc = BeginPaint(hwnd, &grPS);
			SetBkColor(grHdc, RGB(0, 0, 0));
			SetTextColor(grHdc, RGB(0, 255, 0));
			DrawText(grHdc, grStr, -1, &grRC, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &grPS);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}





