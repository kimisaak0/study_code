#include "CoreHeader.h"

WINMAIN(hInst)
{
	//윈도우 클래스 등록
	WNDCLASSEX   Wnd_1;
	ZeroMemory(&Wnd_1, sizeof(WNDCLASSEX));

	Wnd_1.cbSize = sizeof(WNDCLASSEX);
	Wnd_1.hInstance = hInst;
	Wnd_1.lpfnWndProc = WndProc_1;
	Wnd_1.lpszClassName = L"window_1";

	if (RegisterClassEx(&Wnd_1) == false) {
		return 1;
	}

	HWND         hwnd;
	hwnd = CREATEDEFAULTWINDOW(L"window_1", hInst);
	if (hwnd == NULL) {
		return 1;
	}

	ShowWindow(hwnd, SW_SHOW);

	MSG          msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true) {
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

//임시