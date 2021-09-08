#include <windows.h>
#include <TCHAR.H>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM iParam);

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
	HDC hdc;                      // HDC Ÿ�� hdc ������ PAINTSTRUCT Ÿ���� ����ü ���� ps�� �����.
	PAINTSTRUCT ps;				  // ps�� ȭ�鿡 ���� �پ��� ������ �����µ� ��������� ���⼭�� ��������ʴ´�.

	switch (iMsg)
	{
	case WM_CREATE:				// WndProc() �Լ��� �پ��� �޽����� ���޵ȴ�. ���� �����ϴ� �޽����� �����찡 ó�� ��������� �� �߻��ϴ� 
		break;					// WM_CREATE�� ���� � �ϵ� ���� �ʰ� switch ���� ���´�.
	case WM_PAINT:				// �����찡 ȭ�鿡 �����ϸ鼭 WM_PAINT �޽����� �߻��Ѵ�. �̋� ����̽� ���ؽ�Ʈ�� ���� ���� TextOut() �Լ��� �̿���
		hdc = BeginPaint(hwnd, &ps);		// ȭ���� hdc�� 'Hello �ȳ�'�� ����Ѵ�. ����� �����Ŀ��� EndPaint()�� ����� �������� �˸���.
		TextOut(hdc, 100, 100, _T("Hello �ȳ�"), _tcslen(_T("Hello �ȳ�")));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:			// �������� �ݱ� ��ư�� �����ų� �����ϸ� WM_DESTROY �޽����� �߻��Ѵ�. ���⼭�� PostQuitMessage(0)�� �����ϰ� �ִµ�
		PostQuitMessage(0);		// �̴� WinMaint()�� while���� �ִ� GetMessage()�Լ��� 0�� ��ȯ�ϰ� �Ѵ�. �� while ���� �����̹Ƿ� ������ ����ǰ�
		break;					// WinMain()�� ������. �̴� ��ü ���α׷��� �����Ų��.
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}