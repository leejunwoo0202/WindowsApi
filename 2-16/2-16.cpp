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
	HPEN hPen, oldPen; // 펜을 만들려면 펜 핸들 변수를 먼저 선언해야 하므로 HPEN 타입 변수 hPen, oldPen을 지역 변수로 선언했다.
						// 하지만 변수를 만들었다고 해서 펜이 만들어진 것은 아니고 CreatePen() 함수를 이용해 펜의 다양한 속성 값을 가진 펜 핸들을 만든다.
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));  // CreatePen() 함수를 이용해 펜을 만든다. 만든 펜은 점선이고 굵기는 1픽셀, 색은 빨간색이다.
		oldPen = (HPEN)SelectObject(hdc, hPen);		// hPen은 SelectObject 함수를 이용해 hdc에 등록. 반환한 펜을 oldPen에 저장한다
		Ellipse(hdc, 20, 20, 150, 150);			// 등록된 빨간 펜으로 원을 그린다
		SelectObject(hdc, oldPen);		// 원 그리기를 마치면 화면 hdc에 받아둔 펜 핸들을 다시 등록해야 한다.
		DeleteObject(hPen);		// 만들었던 hPen을 DeleteObject()함수를 이용해 삭제한다.
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}