#pragma once
#include "core.h"
#include "bmpClass.h"

struct pt
{
	double x, y;
};

class Sample : public core
{
	bmpClass m_bmp;
	pt       m_pos;

public:
	bool  Init() override
	{
		m_pos.x = 100;
		m_pos.y = 100;
		m_bmp.Load(L"../../../../data/bitmap1.bmp");
		return true;
	}

	//특별히 처리할 키 입력을 지정.
	bool  Frame() override
	{
		if (I_Input.Key('W')) {
			m_pos.y += -1 * g_dSecPerFrame*300.0;
		}

		if (I_Input.Key('S')) {
			m_pos.y += 1 * g_dSecPerFrame*300.0;
		}

		if (I_Input.Key('A')) {
			m_pos.x += -1 * g_dSecPerFrame*300.0;
		}

		if (I_Input.Key('D')) {
			m_pos.x += 1 * g_dSecPerFrame*300.0;
		}
		
		return true;
	}

	bool	Render() override
	{
		BitBlt(m_hOffScreenDC, m_pos.x, m_pos.y, 800, 600, m_bmp.m_hMemDC, 0, 0, SRCCOPY);
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
