#include "core.h"


class sample : public core
{
	bkObjClass  m_BackGround;
	objClass    m_Hero;
	npcClass    m_npc;

public:
	bool Init() 
	{
		m_BackGround.Init();
		m_BackGround.Set(0, 0, 0, 0, 800, 600);
		m_BackGround.Load(L"../../../../data/bk.bmp");
		
		m_Hero.Set(300, 300, 90, 2, 42, 58);
		//m_Hero.Load(L"../../../../data/bitmap1.bmp", L"../../../../data/bitmap2.bmp");
		m_Hero.Load(L"../../../../data/bitmap1.bmp");


		m_npc.Set(600, 300, 46, 62, 68, 79);
		m_npc.Load(L"../../../../data/bitmap1.bmp", L"../../../../data/bitmap2.bmp");

		return true;
	}

	bool Frame() {
		m_BackGround.Frame();
		m_npc.Frame();
		m_Hero.Frame();
		return true;
	}

	bool Render() {
	//	m_BackGround.Draw(LR_ROTATION);
	//	m_BackGround.DrawColorKey(RGB(0, 0, 0)); //지정한 색을 투명하게 한다.
		m_BackGround.Render();
		m_Hero.Render();
	//	m_Hero.Draw(LRTB_ROTATION);
		m_npc.Render();

		return true;
	}

	bool Release() 
	{
		m_BackGround.Release();
		m_Hero.Release();
		m_npc.Release();
		return true;
	}

public:
	sample() {}
	~sample() {}
};

//윈도우 프로그램의 엔트리 포인트(Entry Point)
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR   lpCmdLine, int   nCmdShow) {

	sample win;
	win.SetWindow(hInst, L"WidnowClass", 800, 600);
	win.Run();
}
