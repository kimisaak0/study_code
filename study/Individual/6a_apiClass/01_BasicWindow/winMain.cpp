#include "wndC.h"

HINSTANCE g_hInst;

//������ ������ ������ Ŭ����ȭ ��Ŵ
//TODO : ������ �����츦 �����ϴ� �Ŵ��� Ŭ���� �ʿ�.

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