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
	POINT point[10] = { { 10, 150} , {250, 30}, {500,150},  // �������� ��ǥ�� ������ POINT Ÿ�� �迭 ������ �����Ѵ�. 
		{350,300}, {150,300} };								// ���⼭�� ��ǥ�� �ִ� 10�� ������ �� �ִ� point �迭�� ���������� �����ϰ� �ʱ갪�� 5���� �����ߴ�.

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:						// WM_PAINT �޽����� �߻����� �� ȭ���� ������ hdc�� �������� 5���� �ٰ����� �׸���. �ٰ����� ���� �����Ƿ�
		hdc = BeginPaint(hwnd, &ps);	// ���ΰ� ������ ä�����µ� ���� �������� ������ �⺻ ���� ������� ä������. �ݸ鿡 ���� �⺻ ���� �����̴�.
		Polygon(hdc, point, 5);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}