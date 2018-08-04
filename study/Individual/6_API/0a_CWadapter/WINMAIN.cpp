//WinMain과 MsgProc, CreateWindow함수의 인자를 간략히 한 매크로 함수를 몇개 만들고, 윈도우를 2개 띄우는 함수.
//각각 다른 메시지 처리 함수를 사용하며, 윈도우 창이 모두 꺼졌을때 프로그램이 종료되도록 하였다.

#include "CoreHeader.h"

WINMAIN(hInst)
{
	//윈도우 클래스 등록 1
	WNDCLASSEX   Wnd_1;
	ZeroMemory(&Wnd_1, sizeof(WNDCLASSEX));

	Wnd_1.cbSize = sizeof(WNDCLASSEX);
	Wnd_1.hInstance = hInst;
	Wnd_1.lpfnWndProc = WndProc_1;
	Wnd_1.lpszClassName = L"window_1";

	if (RegisterClassEx(&Wnd_1) == false) {
		return 1;
	}

	//윈도우 클래스 등록 2
	WNDCLASSEX   Wnd_2;
	ZeroMemory(&Wnd_2, sizeof(WNDCLASSEX));

	Wnd_2.cbSize = sizeof(WNDCLASSEX);
	Wnd_2.hInstance = hInst;
	Wnd_2.lpfnWndProc = WndProc_2;
	Wnd_2.lpszClassName = L"window_2";

	if (RegisterClassEx(&Wnd_2) == false) {
		return 1;
	}

	HWND         hwnd_1;
	hwnd_1 = CREATEDEFAULTWINDOW(L"window_1", hInst);
	if (hwnd_1 == NULL) {
		return 1;
	}
	ShowWindow(hwnd_1, SW_SHOW);

	HWND         hwnd_2;
	hwnd_2 = CREATEDEFAULTWINDOW(L"window_2", hInst);
	if (hwnd_2 == NULL) {
		return 1;
	}
	ShowWindow(hwnd_2, SW_SHOW);

	MSG          msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true) {
		//두번째 인자값을 NULL을 주면 어떻게 되는거지...?
		//- hWnd가 NULL이면, 현재의 thread를 호출한 윈도우와 관련된 메시지를 보게된다.

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) { 
				break;
			}
		}
		else {
			//IdleTime
		}
	}
	return 0;
}
