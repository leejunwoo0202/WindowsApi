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
	HDC hdc;                      // HDC 타입 hdc 변수와 PAINTSTRUCT 타입의 구조체 변수 ps를 만든다.
	PAINTSTRUCT ps;				  // ps는 화면에 관한 다양한 정보를 얻어오는데 사용하지만 여기서는 사용하지않는다.

	switch (iMsg)
	{
	case WM_CREATE:				// WndProc() 함수에 다양한 메시지가 전달된다. 먼저 도착하는 메시지는 윈도우가 처음 만들어졌을 때 발생하는 
		break;					// WM_CREATE에 대해 어떤 일도 하지 않고 switch 문을 끝냈다.
	case WM_PAINT:				// 윈도우가 화면에 등장하면서 WM_PAINT 메시지가 발생한다. 이떄 디바이스 콘텍스트를 얻어온 다음 TextOut() 함수를 이용해
		hdc = BeginPaint(hwnd, &ps);		// 화면인 hdc에 'Hello 안녕'을 출력한다. 출력이 끝난후에는 EndPaint()로 출력을 마쳤음을 알린다.
		TextOut(hdc, 100, 100, _T("Hello 안녕"), _tcslen(_T("Hello 안녕")));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:			// 윈도우의 닫기 버튼을 누르거나 종료하면 WM_DESTROY 메시지가 발생한다. 여기서는 PostQuitMessage(0)을 수행하고 있는데
		PostQuitMessage(0);		// 이는 WinMaint()의 while문에 있는 GetMessage()함수가 0을 반환하게 한다. 즉 while 문이 거짓이므로 루프가 종료되고
		break;					// WinMain()이 끝난다. 이는 전체 프로그램을 종료시킨다.
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}