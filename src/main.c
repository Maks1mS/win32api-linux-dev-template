#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"HelloWin";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	hwnd = CreateWindow(wcex.lpszClassName,     // window class name
		L"Hello World",                         // window caption
		WS_OVERLAPPEDWINDOW,                    // window style
		CW_USEDEFAULT,                          // initial x position
		CW_USEDEFAULT,                          // initial y position
		CW_USEDEFAULT,                          // initial x size
		CW_USEDEFAULT,                          // initial y size
		NULL,                                   // parent window handle
		NULL,                                   // window menu handle
		hInstance,                              // program instance handle
		NULL);                                  // creation parameters

	if (hwnd)
	{
		ShowWindow(hwnd, iCmdShow);
		UpdateWindow(hwnd);

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	switch (iMsg)
	{
	case WM_CREATE:
		return 0; // return -1 to cancel the creation of the window

	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			RECT rect;

			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rect);
			SetBkMode(hdc, TRANSPARENT);

			DrawText(hdc, L"Hello World!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
		}
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Sure?", L"Confirm Close", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}