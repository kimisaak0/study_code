#pragma once
#include "winClass.h"

//������ ���α׷��� ��Ʈ�� ����Ʈ(Entry Point)
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR   lpCmdLine, int   nCmdShow) {

	winClass win;
	win.SetWindow(hInst, L"WidnowClass", 800 , 600 ); 
	win.Run();
}
