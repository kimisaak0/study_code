#pragma once
#include "core.h"

class Sample : public core
{
public:
	bool  Init() override
	{
		return true;
	}

	//특별히 처리할 키 입력을 지정.
	bool  Frame() override
	{
		if (I_Input.Key(VK_LBUTTON) == KEY_DOWN) {
			MessageBox(NULL, L"VK_LBUTTON", L"MOUSE", MB_OK);
		}

		if (I_Input.Key(VK_RBUTTON) == KEY_DOWN) {
			MessageBox(NULL, L"VK_RBUTTON", L"MOUSE", MB_OK);
		}

		if (I_Input.Key(VK_MBUTTON) == KEY_DOWN) {
			MessageBox(NULL, L"VK_MBUTTON", L"MOUSE", MB_OK);
		}

		bool bComboKey = I_Input.Key(VK_LCONTROL) == KEY_HOLD && I_Input.Key(VK_LBUTTON) == KEY_DOWN;

		if (bComboKey) {
			MessageBox(NULL, L"VK_LCONTROL + P", L"MOUSE+KEY", MB_OK);
		}

		return true;
	}

	bool	Render() override
	{
		return true;
	}

	bool	Release() override
	{
		return true;
	}

	Sample() {}
	~Sample() {}
};

//윈도우 프로그램의 엔트리 포인트(Entry Point)
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR   lpCmdLine, int   nCmdShow) {

	Sample win;
	win.SetWindow(hInst, L"WidnowClass", 800 , 600 ); 
	win.Run();
}
