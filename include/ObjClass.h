#pragma once
#pragma once
#include "bmpMgrClass.h"

#define LR_ROTATION 0x01
#define TB_ROTATION 0x02
#define LRTB_ROTATION 0x04

class objClass
{
public:
	bmpClass * m_pColorBmp;
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
	HBITMAP       m_hColorRotateBmp;
	HBITMAP       m_hMaskRotateBmp;
	HDC           m_hRotationDC;
	HDC           m_hMemMaskDC;
	HDC           m_hMemColorDC;
	double        m_dMaxDistance;
	double        m_dAngle;
	HBRUSH        m_hbrBack;


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
	void   RotationBlt(double dAngle);
	void   GetRotationbmp(double dAngle, HBITMAP hBmp, bmpClass* pSrcBmp);

public:
	objClass();
	virtual ~objClass();
};