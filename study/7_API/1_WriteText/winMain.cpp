

#include "headerText.h"

WINMAIN(hInst)
{
	WNDCLASSEX   Wnd_1;
	ZeroMemory(&Wnd_1, sizeof(WNDCLASSEX));

	Wnd_1.cbSize = sizeof(WNDCLASSEX);
	Wnd_1.hInstance = hInst;
	Wnd_1.lpfnWndProc = WndProc;
	Wnd_1.lpszClassName = L"window_1";

	if (RegisterClassEx(&Wnd_1) == false) {
		return 1;
	}

	HWND         hwnd_1;
	hwnd_1 = CREATEDEFAULTWINDOW(L"window_1", hInst);
	if (hwnd_1 == NULL) {
		return 1;
	}
	ShowWindow(hwnd_1, SW_SHOW);

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