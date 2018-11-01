//WinMain�� MsgProc, CreateWindow�Լ��� ���ڸ� ������ �� ��ũ�� �Լ��� � �����, �����츦 2�� ���� �Լ�.
//���� �ٸ� �޽��� ó�� �Լ��� ����ϸ�, ������ â�� ��� �������� ���α׷��� ����ǵ��� �Ͽ���.

#include "CoreHeader.h"

WINMAIN(hInst)
{
	//������ Ŭ���� ��� 1
	WNDCLASSEX   Wnd_1;
	ZeroMemory(&Wnd_1, sizeof(WNDCLASSEX));

	Wnd_1.cbSize = sizeof(WNDCLASSEX);
	Wnd_1.hInstance = hInst;
	Wnd_1.lpfnWndProc = WndProc_1;
	Wnd_1.lpszClassName = L"window_1";

	if (RegisterClassEx(&Wnd_1) == false) {
		return 1;
	}

	//������ Ŭ���� ��� 2
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
		//�ι�° ���ڰ��� NULL�� �ָ� ��� �Ǵ°���...?
		//- hWnd�� NULL�̸�, ������ thread�� ȣ���� ������� ���õ� �޽����� ���Եȴ�.

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
