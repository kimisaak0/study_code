#include <Windows.h>

DWORD g_dwKeyState[256];
int g_x = 0;
int g_y = 0;


LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInst;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = L"Window_1";

	if (RegisterClassEx(&wc) == false) {
		return false;
	}

	HWND hWnd = CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"Window_1", L"titleBar", 
		WS_OVERLAPPEDWINDOW,
		300, 200, 800, 600,
		NULL, NULL, hInst, NULL);

	if (hWnd == NULL) {
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);


	HBITMAP hBmp = (HBITMAP)LoadImage(hInst, L"../../../../data/topVeiw_Water_deepdark.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

	HDC hdc = GetDC(hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hMemDC, hBmp);

	MSG msg;

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else {
			for (int iKey = 0; iKey < 255; iKey++) {
				SHORT sKey = GetAsyncKeyState(iKey);
				g_dwKeyState[iKey] = (sKey & 0x8000) ? 1 : 0;
			}


			//타이머가 필요한 이유...
			if (g_dwKeyState['W']) {
				g_y += -1;
			}

			if (g_dwKeyState['S']) {
				g_y += 1;
			}

			if (g_dwKeyState['A']) {
				g_x += -1;
			}

			if (g_dwKeyState['D']) {
				g_x += 1;
			}

			if (g_dwKeyState['Q']) {
				g_x = 10; 
				g_y = 10;
			}

			BitBlt(hdc, g_x, g_y, 37, 35, hMemDC, 115, 62, SRCCOPY);
		}
	}

	SelectObject(hMemDC, hOldBmp);
	DeleteObject(hBmp);

	ReleaseDC(hWnd, hMemDC);
	ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_DESTROY: {
			PostQuitMessage(0);
		} break;

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}
