#include "wndC.h"

HINSTANCE g_hInst;

//윈도우 생성을 완전히 클래스화 시킴
//TODO : 생성한 윈도우를 관리하는 매니저 클래스 필요.

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) 
{
	g_hInst = hInst;

	wndC firstWnd;

	firstWnd.registWnd(L"firstWnd");
	firstWnd.createWnd();
	firstWnd.runWindow();


	wndC secondWnd;

	secondWnd.registWnd(L"secondWnd");
	secondWnd.createWnd();
	secondWnd.runWindow();

}