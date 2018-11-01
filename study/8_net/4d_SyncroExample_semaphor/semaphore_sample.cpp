//#define _CRT_SECURE_NO_WARNINGS
//
//#include <windows.h>
//#include <tchar.h>
//
//HWND g_hWnd;
//HINSTANCE g_hInst;
//
//HANDLE hSem;
//
//int Y = 0;
//
//DWORD WINAPI TDL(LPVOID arg)
//{
//	int s = rand() % 5 + 1;
//
//	HDC hdc = GetDC(g_hWnd);
//	
//	TCHAR str[256];
//
//	Y += 20;
//	TextOut(hdc, 10, Y, _T("�����"), 3);
//	GdiFlush();
//
//	WaitForSingleObject(hSem, INFINITE);
//
//	for (int i = 0; i < 100; i++) {
//		_tprintf(str, "�ٿ�ε� �� : %d%%�Ϸ�", i);
//		for (int j = 0; j < i; j++) {
//			_tcscat(str, _T(" "));
//		}
//		TextOut(hdc, 10, Y, str, _tcslen(str));
//		Sleep(200 * s);
//	}
//
//	_tcscpy(str, _T("�ٿ�ε带 �Ϸ��߽��ϴ�."));
//	TextOut(hdc, 10, Y, str, _tcslen(str));
//
//	ReleaseSemaphore(hSem, 1, NULL);
//	ReleaseDC(g_hWnd, hdc);
//
//	return 0;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd,	UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	HANDLE hThread = 0;
//	HDC hdc;
//	PAINTSTRUCT ps;
//	const TCHAR* mes = _T("���콺 ���� ��ư�� ������ �ٿ�ε带 �����մϴ�.");
//
//	switch (msg)
//	{
//		case WM_CREATE: {
//			srand(GetTickCount());
//			hSem = CreateSemaphore(NULL, 5, 5, NULL);
//		}break;
//
//		case WM_LBUTTONDOWN: {
//			hThread = CreateThread(NULL, 0, TDL, NULL, 0, NULL);
//			//CloseHandle(hThread);
//		} break;
//
//		case WM_PAINT: {
//			hdc = BeginPaint(g_hWnd, &ps);
//			TextOut(hdc, 10, 0, mes, _tcslen(mes));
//			EndPaint(g_hWnd, &ps);
//		}
//
//		case WM_DESTROY: {
//
//			TerminateThread(hThread, -1);
//			CloseHandle(hSem);
//			PostQuitMessage(0);
//		}break;
//	}
//	
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//
//int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) 
//{
//	g_hInst = hInst;
//
//	// ������ Ŭ���� ���
//	WNDCLASSEX wc;
//	ZeroMemory(&wc, sizeof(WNDCLASSEX));    
//	wc.cbSize = sizeof(WNDCLASSEX);         
//	wc.style = CS_HREDRAW | CS_VREDRAW;     
//	wc.lpfnWndProc = WndProc;               
//	wc.hInstance = hInst;                   
//	wc.lpszClassName = L"MyWindow";         
//
//	if (RegisterClassEx(&wc) == FALSE) {   // Ŀ�ο� ������ Ŭ������ ���.
//		return 1;
//	}
//
//	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, 
//		L"MyWindow", L"KGCA SAMPLES",      
//		WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE,
//		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
//		NULL, NULL, hInst, NULL                  
//	);
//
//	g_hWnd = hWnd;
//	if (hWnd == NULL) {
//		return 1;
//	}
//
//	MSG msg;
//	ZeroMemory(&msg, sizeof(MSG));
//
//	while (1) {
//		if (GetMessage(&msg, g_hWnd, 0, 0)) {
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//
//			if (msg.message == WM_QUIT) {
//				break;
//			}
//		}
//		else {
//
//		}
//	}
//
//	return 0;
//}

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include <tchar.h>

HANDLE hSemA;
HANDLE hSemM;

int number = 0;

DWORD WINAPI addT(void * arg)
{
	int i;
	for (i = 0; i<4; i++) {
		WaitForSingleObject(hSemA, INFINITE); // hSemA �������� 1 ����!
		number++;
		printf("����!  number : %d \n", number);
		ReleaseSemaphore(hSemM, 1, NULL);		// hSemM �������� 1 ����!
	}
	return 0;
}

DWORD WINAPI minusT(void * arg)
{
	int i;
	for (i = 0; i<4; i++) {
		WaitForSingleObject(hSemM, INFINITE); // hSemM �������� 1 ����!
		number--;
		printf("����!, number : %d \n", number);
		ReleaseSemaphore(hSemA, 1, NULL); // hSemA �������� 1 ����!
	}
	return 0;
}

int main()
{
	HANDLE hThread[2] = { 0, };

	//���� ������ (���ؽ��� �ٸ��� �ʴ�.)
	hSemA = CreateSemaphore(NULL, 1, 1, NULL);
	hSemM = CreateSemaphore(NULL, 0, 1, NULL);

	hThread[0] = CreateThread(NULL, 0, addT, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, minusT, NULL, 0, NULL);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

}