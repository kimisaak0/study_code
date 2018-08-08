#include "wndC.h"

wndC::wndC()
{
}

LRESULT CALLBACK wndC::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
		case WM_CREATE: {

		}break;

		case WM_DESTROY: {
			PostQuitMessage(0);
		}break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

bool wndC::registWnd(LPCWSTR LWndName)
{
	ZeroMemory(&m_wndC, sizeof(WNDCLASSEX));

	m_wndC.cbSize = sizeof(WNDCLASSEX);
	m_wndC.hInstance = g_hInst;
	m_wndC.lpfnWndProc = MsgProc;
	m_wndC.lpszClassName = LWndName;

	if (!RegisterClassEx(&m_wndC)) {
		return false;
	}

	return true;
}

bool wndC::createWnd()
{
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, 
		m_wndC.lpszClassName, m_wndC.lpszClassName, 
		WS_OVERLAPPEDWINDOW,
		200, 200, 800, 600,
		NULL, NULL, g_hInst, NULL
		);

	if (m_hWnd == NULL) {
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);

	return true;
}

bool wndC::runWindow()
{
	MSG msg;
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

		}
	}

	return true;
}

HWND wndC::getHandle()
{
	return m_hWnd;
}


wndC::~wndC()
{

}