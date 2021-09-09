#include <windows.h>
#include <TCHAR.H>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW || CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, oldBrush;  // 빨간색 브러시를 만들기 위해 브러시 핸들 변수를 선언한다. 펜 핸들 변수를 사용할 때처럼 oldBrush 변수도 선언한다.

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));  // WM_PAINT 메시지에서 빨간색 브러시를 만들어 hBrush 변수에 저장한다
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);   // SelectObject() 함수를 이용해 화면 hdc에 등록하고 이전에 등록한 브러시는 oldBrush에 받아둔다.
		Ellipse(hdc, 20, 20, 150, 150);				// 원을 그린다. 펜을 따로 만들어 등록하지 않았으므로 기본인 1픽셀 두께의 검은색 실선 펜을 이용한다.
		SelectObject(hdc, oldBrush);		// 그림 그리기를 마친 뒤 SelectObject() 함수를 이용해 받아둔 oldBrush를 등록하고 만들었던 hBrush 브러시는 삭제한다.
		DeleteObject(hBrush);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}