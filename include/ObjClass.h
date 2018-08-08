#pragma once
#include "bmpMgrClass.h"

#define LR_ROTATION 0x01
#define TB_ROTATION 0x02
#define LRTB_ROTATION 0x04

class objClass
{
public:
	bmpClass *    m_pColorBmp;
	bmpClass*     m_pMaskBmp;
	dPointClass   m_pos;
	dPointClass   m_posDraw;
	RECT          m_rtDraw;

	RECT          m_rtCollision;
	double        m_dDir[2];
	double        m_dSpeed;
	bool          m_bDebugRect;
	bool          m_bDead;

public:
	virtual void Set(dPointClass pos);
	virtual void Set(double x, double y, DWORD left, DWORD top, DWORD right, DWORD bottom);
	
	virtual bool Load(const TCHAR* pszColor, const TCHAR* pszMask = nullptr);

	virtual bool Draw(short sType, RECT* pRt = nullptr);
	virtual bool DrawColorKey(DWORD maskColor);
	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	objClass();
	virtual ~objClass();
};