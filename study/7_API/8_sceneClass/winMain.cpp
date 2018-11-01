#pragma once
#include "core.h"
#include "buttonClass.h"
#include "sceneClass.h"
#include <memory>


class Sample : public core
{
	std::shared_ptr<sceneClass> m_pLobby;
	std::shared_ptr<sceneClass> m_pStage;
	std::shared_ptr<sceneClass> m_pEnd;

	sceneClass* m_pCurrentScene;
	int         m_iStageLevel;


public:
	bool  Init() override
	{
		m_iStageLevel = 1;
		
		m_pLobby = std::make_shared<sceneLobbyClass>();
		m_pStage = std::make_shared<sceneStageClass>();
		m_pEnd = std::make_shared<sceneEndClass>();

		m_pCurrentScene = m_pLobby.get();

		m_pLobby->Init();
		m_pStage->Init();
		m_pEnd->Init();

		return true;
	}

	//특별히 처리할 키 입력을 지정.
	bool  Frame() override
	{
		switch (m_pCurrentScene->m_iSceneID) {
			case SCENE_LOBBY: {
				if (m_pCurrentScene->m_bNextSceneStart == true) {
					m_pCurrentScene->m_bNextSceneStart = false;
					m_pCurrentScene = m_pStage.get();
				}
			} break;

			case SCENE_STAGE: {
				if (m_pCurrentScene->m_bNextSceneStart == true) {

					if (++m_iStageLevel > g_iMaxLevel) {
						m_pCurrentScene = m_pEnd.get();
						m_pCurrentScene->SetNpcCount(10);
						m_pCurrentScene->Reset();
						m_iStageLevel = 0;
					}
					else {
						m_pCurrentScene = m_pStage.get();
						m_pCurrentScene->SetNpcCount(m_iStageLevel * 10);
						m_pCurrentScene->Reset();
					}
				}
			} break;

			case SCENE_ENDING: {

			}break;
		}
		m_pCurrentScene->Frame();

		return true;
	}

	bool	Render() override
	{
		m_pCurrentScene->Render();
		return true;
	}

	bool	Release() override
	{
		m_pLobby->Release();
		m_pStage->Release();
		m_pEnd->Release();
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
