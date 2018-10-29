#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <tchar.h>

HWND g_hWnd;
HINSTANCE g_hInst;

HANDLE hSem;

int Y = 0;

DWORD WINAPI TDL(LPVOID arg)
{
	int s = rand() % 5 + 1;

	HDC hdc = GetDC(g_hWnd);
	
	TCHAR str[256];

	Y += 20;
	TextOut(hdc, 10, Y, _T("대기중"), 6);
	GdiFlush();
	WaitForSingleObject(hSem, INFINITE);

	for (int i = 0; i < 100; i++) {
		_tprintf(str, "다운로드 중 : %d%%완료", i);
		for (int j = 0; j < i; j++) {
			_tcscat(str, _T("0"));
		}
		TextOut(hdc, 10, Y, str, _tcslen(str));
		Sleep(200 * s);
	}

	_tcscpy(str, _T("다운로드를 완료했습니다."));
	TextOut(hdc, 10, Y, str, _tcslen(str));

	ReleaseSemaphore(hSem, 1, NULL);
	ReleaseDC(g_hWnd, hdc);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,	UINT msg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThread;
	HDC hdc;
	PAINTSTRUCT ps;
	const TCHAR* mes = _T("마우스 왼쪽 버튼을 누르면 다운로드를 시작합니다.");

	switch (msg)
	{
		case WM_CREATE: {
			srand(GetTickCount());
			hSem = CreateSemaphore(NULL, 3, 3, NULL);
		}break;

		case WM_LBUTTONDOWN: {
			hThread = CreateThread(NULL, 0, TDL, NULL, 0, NULL);
			CloseHandle(hThread);
		} break;

		case WM_PAINT: {
			hdc = BeginPaint(g_hWnd, &ps);
			TextOut(hdc, 10, 0, mes, _tcslen(mes));
			EndPaint(g_hWnd, &ps);
		}

		case WM_DESTROY: {
			CloseHandle(hSem);
			PostQuitMessage(0);
		}break;
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) 
{
	g_hInst = hInst;

	// 윈도우 클래스 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));    
	wc.cbSize = sizeof(WNDCLASSEX);         
	wc.style = CS_HREDRAW | CS_VREDRAW;     
	wc.lpfnWndProc = WndProc;               
	wc.hInstance = hInst;                   
	wc.lpszClassName = L"MyWindow";         

	if (RegisterClassEx(&wc) == FALSE) {   // 커널에 윈도우 클래스를 등록.
		return 1;
	}

	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, 
		L"MyWindow", L"KGCA SAMPLES",      
		WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInst, NULL                  
	);

	g_hWnd = hWnd;
	if (hWnd == NULL) {
		return 1;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (1) {
		if (GetMessage(&msg, g_hWnd, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else {

		}
	}

	return 0;
}
