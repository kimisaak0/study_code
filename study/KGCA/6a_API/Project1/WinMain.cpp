#include "Header.h"

#define MAX_STRLENGTH 100

//전역 변수
HINSTANCE g_hInst;                          //현재 윈도우의 인스턴스
WCHAR     g_szTitle[MAX_STRLENGTH];         //제목 표시줄에 띄워질 텍스트.
WCHAR     g_szWindowClass[MAX_STRLENGTH];   //기본 윈도우 클래스 이름.

//함수 원형 선언
ATOM               MyRegisterClass(HINSTANCE hInst);
BOOL               InitInstacnce(HINSTANCE hInst, int nCmdShow);
INT_PTR  CALLBACK  About(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT  CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
