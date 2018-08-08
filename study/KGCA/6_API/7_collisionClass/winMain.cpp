#pragma once
#include "core.h"
#include "collisionClass.h"

const int g_iMaxNpcCount = 10;

class Sample : public core
{

	bkObjClass m_backGround;
	objClass   m_Hero;
	std::vector<npcClass> m_npcList;

public:
	bool  Init() override
	{
		
		m_backGround.Init();
		m_backGround.Set(0, 0, 0, 0, 800, 600);
//		m_backGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
	    m_backGround.Load(L"../../../../data/bk.bmp");
		
		m_Hero.Set(300, 300, 90, 2, 42, 58);
		m_Hero.Load(L"../../../../data/bitmap1.bmp");

		m_npcList.resize(g_iMaxNpcCount);
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
			m_npcList[iObj].Set(100 + rand() % 600, 100 + rand() % 400, 46, 62, 68, 79);
			m_npcList[iObj].Load(L"../../../../data/bitmap1.bmp");
		}
		return true;

	}

	//특별히 처리할 키 입력을 지정.
	bool  Frame() override
	{
		if (I_Input.Key('0') == KEY_DOWN) {
			m_Hero.m_bDebugRect = !m_Hero.m_bDebugRect;
			for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
				m_npcList[iObj].m_bDebugRect = !m_npcList[iObj].m_bDebugRect;

			}
		}

		m_backGround.Frame();
		m_Hero.Frame();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
			if (!m_npcList[iObj].m_bDead) {
				m_npcList[iObj].Frame();
			}
		}

		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
			if (collisionClass::RectInRect(m_npcList[iObj].m_rtCollision, m_Hero.m_rtCollision)) {
				m_npcList[iObj].m_bDead = true;
			}
		}

		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
			if (I_Input.Key(VK_LBUTTON) && collisionClass::SphereInPt(m_npcList[iObj].m_rtCollision, I_Input.m_MousePos)) {
				m_npcList[iObj].m_bDead = true;
			}
		}

		return true;
	}

	bool	Render() override
	{
		m_backGround.Render();
		m_Hero.Render();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
			if (!m_npcList[iObj].m_bDead) {
				m_npcList[iObj].Render();
			}
		}
		return true;
	}

	bool	Release() override
	{
		m_backGround.Release();
		m_Hero.Release();
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
			m_npcList[iObj].Release();
		}
		return true;
	}

	Sample() {}
	~Sample() {}
};

//윈도우 프로그램의 엔트리 포인트(Entry Point)
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR   lpCmdLine, int   nCmdShow) {

	Sample win;
	win.SetWindow(hInst, L"WidnowClass", 800, 600);
	win.Run();
}
