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
	HBRUSH hBrush, oldBrush;  // ������ �귯�ø� ����� ���� �귯�� �ڵ� ������ �����Ѵ�. �� �ڵ� ������ ����� ��ó�� oldBrush ������ �����Ѵ�.

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));  // WM_PAINT �޽������� ������ �귯�ø� ����� hBrush ������ �����Ѵ�
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);   // SelectObject() �Լ��� �̿��� ȭ�� hdc�� ����ϰ� ������ ����� �귯�ô� oldBrush�� �޾Ƶд�.
		Ellipse(hdc, 20, 20, 150, 150);				// ���� �׸���. ���� ���� ����� ������� �ʾ����Ƿ� �⺻�� 1�ȼ� �β��� ������ �Ǽ� ���� �̿��Ѵ�.
		SelectObject(hdc, oldBrush);		// �׸� �׸��⸦ ��ģ �� SelectObject() �Լ��� �̿��� �޾Ƶ� oldBrush�� ����ϰ� ������� hBrush �귯�ô� �����Ѵ�.
		DeleteObject(hBrush);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}