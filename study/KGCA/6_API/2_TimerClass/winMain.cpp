#pragma once
#include "core.h"

class Sample : public core
{
public:
	Sample() {}
	~Sample() {}
};

//������ ���α׷��� ��Ʈ�� ����Ʈ(Entry Point)
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR   lpCmdLine, int   nCmdShow) {

	Sample win;
	win.SetWindow(hInst, L"WidnowClass", 800 , 600 ); 
	win.Run();
}
