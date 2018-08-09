#include "sceneClass.h"

//sceneLobbyClass
sceneLobbyClass::sceneLobbyClass()
{
	m_iSceneID = SCENE_LOBBY;
}

bool sceneLobbyClass::Init()
{
	m_bNextSceneStart = false;

	m_BackGround.Init();
//	m_BackGround.Set(0, 0, 0, 0, 800, 600);

	m_BackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
	m_BackGround.Load(L"../../../../data/bk.bmp");

	m_btnStart.Init();
	m_btnStart.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 334, 82);
	m_btnStart.Load(L"../../../../data/main_start_nor.bmp");

	return true;
}

bool sceneLobbyClass::Frame()
{
	m_BackGround.Frame();
	
	if (I_Input.Key(VK_LBUTTON) && 
		collisionClass::RectInPt(m_btnStart.m_rtCollision, I_Input.m_MousePos)) {
		m_bNextSceneStart = true;
	}

	m_btnStart.Frame();

	return true;
}

bool sceneLobbyClass::Render()
{
	m_BackGround.Render();
	m_btnStart.Render();
	return true;
}

bool sceneLobbyClass::Release()
{
	m_BackGround.Release();
	m_btnStart.Release();
	return true;
}


sceneLobbyClass::~sceneLobbyClass()
{

}


//sceneStageClass
sceneStageClass::sceneStageClass()
{
	m_iSceneID = SCENE_STAGE;
}

bool sceneStageClass::Init()
{
	m_BackGround.Init();
	m_BackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
	m_BackGround.Load(L"../../../../data/eye.bmp");

	m_Hero.Init();
	m_Hero.Set(300, 300, 90, 2, 42, 58);
	m_Hero.Load(L"../../../../data/bitmap1.bmp");

	m_vNpcList.resize(g_iMaxNpcCount);
	for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
		m_vNpcList[iObj].Set(100 + rand() % 600, 100 + rand() + 400, 46, 62, 68, 79);
		m_vNpcList[iObj].Load(L"../../../../data/bitmap1.bmp");
	}
	return true;
}
bool sceneStageClass::Frame()
{
	if (I_Input.Key('0') == KEY_DOWN) {
		m_Hero.m_bDebugRect = !m_Hero.m_bDebugRect;
		for (int iObj = 0; iObj < g_iMaxNpcCount; iObj++) {
			m_vNpcList[iObj].m_bDebugRect = !m_vNpcList[iObj].m_bDebugRect;
		}
	}

	m_BackGround.Frame();

	m_Hero.Frame();

	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++) {
		if (!m_vNpcList[iObj].m_bDead) {
			m_vNpcList[iObj].Frame();
		}
	}
	bool bChangeScene = true;
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++) {
		if (collisionClass::RectInRect(m_vNpcList[iObj].m_rtCollision, m_Hero.m_rtCollision)) {
			m_vNpcList[iObj].m_bDead = true;
		}

		if (I_Input.Key(VK_LBUTTON) && collisionClass::SphereInPt(m_vNpcList[iObj].m_rtCollision, I_Input.m_MousePos)) {
			m_vNpcList[iObj].m_bDead = true;
		}

		if (m_vNpcList[iObj].m_bDead == false) {
			bChangeScene = false;
		}
	}

	if (bChangeScene == true) {
		m_bNextSceneStart = true;
	}

	return true;
}

bool sceneStageClass::Render()
{
	m_BackGround.Render();
	m_Hero.Render();

	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++) {
		if (!m_vNpcList[iObj].m_bDead) {
			m_vNpcList[iObj].Render();
		}
	}
	return true;
}

bool sceneStageClass::Release()
{
	m_BackGround.Release();
	m_Hero.Release();
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++) {
		m_vNpcList[iObj].Release();
	}
	return true;
}

bool sceneStageClass::Reset()
{
	m_bNextSceneStart = false;
	
	for (int iObj = 0; iObj < m_iMaxNpcCount; iObj++) {
		m_vNpcList[iObj].m_bDead = false;
		m_vNpcList[iObj].Set(100 + rand() % 600, 100 + rand() + 400, 46, 62, 68, 79);
	}

	return true;
}

sceneStageClass::~sceneStageClass()
{

}

//	sceneEndClass

sceneEndClass::sceneEndClass()
{
	m_iSceneID = SCENE_ENDING;
}

bool sceneEndClass::Init()
{
	m_bNextSceneStart = false;

	m_BackGround.Init();
	m_BackGround.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 800, 600);
	m_BackGround.Load(L"../../../../data/RAINBOW.bmp");

	m_btnEnd.Init();
	m_btnEnd.Set(g_rtClient.right / 2, g_rtClient.bottom / 2, 0, 0, 100, 50);
	m_btnEnd.Load(L"../../../../data/end.bmp");

	return true;


}
bool sceneEndClass::Frame()
{
	m_BackGround.Frame();
	
	m_btnEnd.Frame();

	if (I_Input.Key(VK_LBUTTON) &&
		collisionClass::RectInPt(m_btnEnd.m_rtCollision, I_Input.m_MousePos)) {
		DestroyWindow(g_hWnd);
	}

	return true;

}

bool sceneEndClass::Render()
{
	m_BackGround.Render();
	m_btnEnd.Render();
	return true;
}

bool sceneEndClass::Release()
{
	m_BackGround.Release();
	m_btnEnd.Release();
	return true;
}



sceneEndClass::~sceneEndClass()
{

}