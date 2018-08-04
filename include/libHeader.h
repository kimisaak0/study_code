#pragma once
#include <Windows.h>

#pragma comment(lib, "apiCore.lib")

#define WINMAIN(hinst) int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine,int nCmdShow)
#define WNDPROC(WndProc) LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
#define CREATEDEFAULTWINDOW(windowName,hInstance) CreateWindowEx(0, windowName, windowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInstance, NULL)

int g_iWindowNum = 0;

WNDPROC(WndProc_1)
{
	switch (iMsg) {
		case WM_CREATE:
			g_iWindowNum++;
			break;

		case WM_DESTROY:
			g_iWindowNum--;
			if (g_iWindowNum == 0) {
				PostQuitMessage(0);
			}
			break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

WNDPROC(WndProc_2)
{
	switch (iMsg) {
		case WM_CREATE:
			g_iWindowNum++;
			break;

		case WM_DESTROY:
			g_iWindowNum--;
			if (g_iWindowNum == 0) {
				PostQuitMessage(0);
			}
			break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
