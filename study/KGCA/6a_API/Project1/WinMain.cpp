#include "Header.h"

#define MAX_STRLENGTH 100

//���� ����
HINSTANCE g_hInst;                          //���� �������� �ν��Ͻ�
WCHAR     g_szTitle[MAX_STRLENGTH];         //���� ǥ���ٿ� ����� �ؽ�Ʈ.
WCHAR     g_szWindowClass[MAX_STRLENGTH];   //�⺻ ������ Ŭ���� �̸�.

//�Լ� ���� ����
ATOM               MyRegisterClass(HINSTANCE hInst);
BOOL               InitInstacnce(HINSTANCE hInst, int nCmdShow);
INT_PTR  CALLBACK  About(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT  CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
