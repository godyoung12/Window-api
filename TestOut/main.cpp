#include <Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");


void MyTextOut(HDC hdc, int x, int y, LPCWSTR Text);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION
	);
	WndClass.hInstance = hInstance;
	
	WndClass.lpfnWndProc = WndProc;

	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_VSCROLL, 0, 0, 640, 480, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
		// ���̸� ���� Ÿ���� �ϴ� �����, ȯ�濡 ���� �޶� �̽ļ��� ������. (ex) ��Ƽ����Ʈ -> 8, �����ڵ� -> 4
		// ������ ���
		// const wchar_t* can't convert TCHAR* -> 
		//const wchar_t* str = TEXT("Beatiful Korea");
		//TextOut(hdc, 100, 100, str,lstrlen(str));

		int Score = 85;
		wchar_t  str[128];
		wsprintf(str, TEXT("���� ������ %d�� �Դϴ�."), Score);
		// wsprintf, API�Լ� -> �뷮�� �������� ����, �����ڵ� ���� but �Ǽ� ����ȭ X
		// sprintf ǥ�� �Լ� or �����ڵ� ������ swpirntf ����ϱ�

		SetTextAlign(hdc, TA_UPDATECP);
		MyTextOut(hdc, 200, 60, str);
		//MyTextOut(hdc, 200, 80, TEXT("Two"));
		//MyTextOut(hdc, 200, 100, TEXT("Three"));

		EndPaint(hWnd, &ps);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void MyTextOut(HDC hdc, int x, int y, LPCWSTR Text) {
	TextOut(hdc, x, y, Text, lstrlen(Text));
}