#pragma once
#include "buttonClass.h"
#include "core.h"

const int g_iMaxLevel = 10;
const int g_iMaxNpcCount = 100;

enum gameScene
{
	SCENE_LOBBY = 0,
	SCENE_STAGE,
	SCENE_ENDING,
};

class sceneClass
{
public:
	int         m_iSceneID;
	bkObjClass  m_BackGround;
	bool        m_bNextSceneStart;
	int         m_iMaxNpcCount;

public:
	virtual bool Init() { return true; }
	virtual bool Frame() { return true; }
	virtual bool Render() { return true; }
	virtual bool Release() { return true; }
	virtual bool Reset() { return true; }
	virtual bool IsDead() { return false; }
	
	virtual void SetNpcCount(int iNpc)
	{
		if (g_iMaxNpcCount <= iNpc) {
			m_iMaxNpcCount = g_iMaxNpcCount;
		}
		else {
			m_iMaxNpcCount = iNpc;
		}
	}


public:
	sceneClass()
	{
		m_bNextSceneStart = false;
		m_iMaxNpcCount = 10;
	}
	virtual ~sceneClass() {}
};


class sceneLobbyClass : public sceneClass
{
public:
	buttonClass m_btnStart;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Reset() { return true; }
	bool IsDead() { return m_btnStart.m_bDead; }

public:
	sceneLobbyClass();
	virtual ~sceneLobbyClass();
};

class sceneStageClass : public sceneClass
{
public:
	objClass m_Hero;
	std::vector<npcClass> m_vNpcList;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Reset();

public:
	sceneStageClass();
	virtual ~sceneStageClass();
};

class sceneEndClass : public sceneClass
{
public:
	buttonClass m_btnEnd;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Reset() { return true; }
	bool IsDead() { return m_btnEnd.m_bDead; }

public:
	sceneEndClass();
	virtual ~sceneEndClass();
};