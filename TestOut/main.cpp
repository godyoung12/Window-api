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
		// 길이를 직접 타이핑 하는 방식은, 환경에 따라 달라 이식성이 안좋다. (ex) 멀티바이트 -> 8, 유니코드 -> 4
		// 개선된 방식
		// const wchar_t* can't convert TCHAR* -> 
		//const wchar_t* str = TEXT("Beatiful Korea");
		//TextOut(hdc, 100, 100, str,lstrlen(str));

		int Score = 85;
		wchar_t  str[128];
		wsprintf(str, TEXT("현재 점수는 %d점 입니다."), Score);
		// wsprintf, API함수 -> 용량상 불이익은 없고, 유니코드 지원 but 실수 서식화 X
		// sprintf 표준 함수 or 유니코드 버전의 swpirntf 사용하기

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