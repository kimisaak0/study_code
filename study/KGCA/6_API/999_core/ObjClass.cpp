#include "ObjClass.h"
#include "inputClass.h"

//__imp_TransparentBlt 사용
#pragma comment(lib, "msimg32.lib")

objClass::objClass()
{
	//
	//m_pos.x = 0;
	//m_pos.y = 0;
	//

	m_pColorBmp = nullptr;
	m_pMaskBmp = nullptr;

	m_posDraw.x = 0;
	m_posDraw.y = 0;

	m_dDir[0] = m_dDir[1] = 1.0f;
	m_dSpeed = 100.0;

	m_bDebugRect = false;
	m_bDead = false;

}

void objClass::Set(dPointClass pos)
{
	//
	//m_pos = pos;
	//

	m_posDraw = pos;
}

void objClass::Set(double x, double y, DWORD left, DWORD top, DWORD right, DWORD bottom)
{

	m_pos.x = x;
	m_pos.y = y;

	m_rtDraw.left = left;
	m_rtDraw.top = top;
	m_rtDraw.right = right;
	m_rtDraw.bottom = bottom;

	m_posDraw.x = m_pos.x - (m_rtDraw.right / 2);
	m_posDraw.y = m_pos.y - (m_rtDraw.bottom / 2);



	m_dDir[0] = (rand() % 2) ? 1.0 : -1.0;
	m_dDir[1] = (rand() % 2) ? 1.0 : -1.0;

	m_rtCollision.left = m_posDraw.x;
	m_rtCollision.top = m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;

	m_dMaxDistance = sqrt(pow(m_rtDraw.right, 2) + pow(m_rtDraw.bottom, 2));

	m_hColorRotateBmp = CreateCompatibleBitmap(g_hScreenDC, m_dMaxDistance, m_dMaxDistance);
	m_hMaskRotateBmp = CreateCompatibleBitmap(g_hScreenDC, m_dMaxDistance, m_dMaxDistance);
	
	m_hRotationDC = CreateCompatibleDC(g_hScreenDC);
	m_hMemMaskDC = CreateCompatibleDC(g_hScreenDC);
	m_hMemColorDC = CreateCompatibleDC(g_hScreenDC);
}

void objClass::GetRotationbmp(double dAngle, HBITMAP hBmp, bmpClass* pSrcBmp)
{
	double dRadian = dAngle * 3.141592f / 180.0f;
	double dCos = cos(dRadian);
	double dSin = sin(dRadian);

	HBITMAP hOldBmp = (HBITMAP)SelectObject(m_hRotationDC, hBmp);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hRotationDC, m_hbrBack);
	PatBlt(m_hRotationDC, 0, 0, m_dMaxDistance, m_dMaxDistance, PATCOPY);
	SelectObject(m_hRotationDC, hOldBrush);

	int iOldGraphic = SetGraphicsMode(m_hRotationDC, GM_ADVANCED);

	XFORM xform;
	xform.eM11 = dCos; xform.eM12 = -dSin;
	xform.eM21 = dSin; xform.eM22 = dCos;
	xform.eDx = m_dMaxDistance / 2; 
	xform.eDy = m_dMaxDistance / 2;
	SetWorldTransform(m_hRotationDC, &xform);

	BitBlt(m_hRotationDC, -(m_rtDraw.right / 2), -(m_rtDraw.bottom / 2), 
		m_rtDraw.right, m_rtDraw.bottom,
		pSrcBmp->m_hMemDC, m_rtDraw.left, m_rtDraw.top, SRCCOPY);

	SelectObject(m_hRotationDC, hOldBmp);
	SelectObject(m_hRotationDC, hOldBrush);

	xform.eM11 = 1; xform.eM12 = 0;
	xform.eM21 = 0; xform.eM22 = 1;
	xform.eDx = 0;
	xform.eDy = 0;
	SetWorldTransform(m_hRotationDC, &xform);
	SetGraphicsMode(m_hRotationDC, iOldGraphic);
}

void objClass::RotationBlt(double dAngle)
{
	m_dAngle = dAngle;
	GetRotationbmp(dAngle, m_hMaskRotateBmp, m_pMaskBmp);
	GetRotationbmp(dAngle, m_hColorRotateBmp, m_pColorBmp);

	HBITMAP hOldMask = (HBITMAP)SelectObject(m_hMemMaskDC, m_hMaskRotateBmp);
	HBITMAP hOldColor = (HBITMAP)SelectObject(m_hMemColorDC, m_hColorRotateBmp);


		BitBlt(g_hOffScreenDC,
			m_pos.x - (m_dMaxDistance / 2), 
			m_pos.y - (m_dMaxDistance / 2),
			m_dMaxDistance,
			m_dMaxDistance,
			m_hMemMaskDC,
			0, 0,
			SRCAND
		); //AND연산

		BitBlt(g_hOffScreenDC,
			m_pos.x - (m_dMaxDistance / 2),
			m_pos.y - (m_dMaxDistance / 2),
			m_dMaxDistance,
			m_dMaxDistance,
			m_hMemColorDC,
			0, 0,
			SRCINVERT
		); //XOR연산

		BitBlt(g_hOffScreenDC,
			m_pos.x - (m_dMaxDistance / 2),
			m_pos.y - (m_dMaxDistance / 2),
			m_dMaxDistance,
			m_dMaxDistance,
			m_hMemMaskDC,
			0, 0,
			SRCINVERT
		); //XOR연산

		SelectObject(m_hMemMaskDC, hOldMask);
		SelectObject(m_hMemColorDC, hOldColor);
}

bool objClass::Load(const TCHAR* pszColor, const TCHAR* pszMask)
{
	int iIndex = I_bmpMgr.Load(pszColor);
	m_pColorBmp = I_bmpMgr.getPtr(iIndex);
	if (pszMask != nullptr) {
		iIndex = I_bmpMgr.Load(pszMask);
		m_pMaskBmp = I_bmpMgr.getPtr(iIndex);
	}
	return true;
}

bool objClass::Draw(short sType, RECT* pRt)
{
	RECT rtDraw = m_rtDraw;
	if (pRt != nullptr) {
		rtDraw = *pRt;
	}

	switch (sType) {
		case LR_ROTATION: {
			StretchBlt(g_hOffScreenDC,
				(int)m_posDraw.x + rtDraw.right, (int)m_posDraw.y,
				(int)-rtDraw.right, (int)rtDraw.bottom,
				m_pColorBmp->m_hMemDC,
				(int)rtDraw.left, (int)rtDraw.top,
				(int)rtDraw.right, (int)rtDraw.bottom,
				SRCCOPY
			);
		}break;

		case TB_ROTATION: {
			StretchBlt(g_hOffScreenDC,
				(int)m_posDraw.x, (int)m_posDraw.y + rtDraw.bottom,
				(int)rtDraw.right, (int)-rtDraw.bottom,
				m_pColorBmp->m_hMemDC,
				(int)rtDraw.left, (int)rtDraw.top,
				(int)rtDraw.right, (int)rtDraw.bottom,
				SRCCOPY
			);
		}break;

		case LRTB_ROTATION: {
			StretchBlt(g_hOffScreenDC,
				(int)m_posDraw.x + rtDraw.right, (int)m_posDraw.y + rtDraw.bottom,
				(int)-rtDraw.right, (int)-rtDraw.bottom,
				m_pColorBmp->m_hMemDC,
				(int)rtDraw.left, (int)rtDraw.top,
				(int)rtDraw.right, (int)rtDraw.bottom,
				SRCCOPY
			);
		}break;

		default: {
			StretchBlt(g_hOffScreenDC,
				(int)m_posDraw.x, (int)m_posDraw.y,
				(int)rtDraw.right, (int)rtDraw.bottom,
				m_pColorBmp->m_hMemDC,
				(int)rtDraw.left, (int)rtDraw.top,
				(int)rtDraw.right, (int)rtDraw.bottom,
				SRCCOPY
			);
		}break;

	}
	return true;
}
bool objClass::DrawColorKey(DWORD maskColor)
{
	TransparentBlt(g_hOffScreenDC,
		(int)m_posDraw.x, (int)m_posDraw.y,
		(int)m_rtDraw.right, (int)m_rtDraw.bottom,
		m_pColorBmp->m_hMemDC,
		(int)m_rtDraw.left, (int)m_rtDraw.top,
		(int)m_rtDraw.right, (int)m_rtDraw.bottom,
		maskColor
	);
	return true;
}


bool objClass::Init()
{
	m_hbrBack = CreateSolidBrush(RGB(255, 255, 255));
	m_dAngle = 0.0;
	return true;
}
bool objClass::Frame()
{
	if (I_Input.Key('W')) {
		m_pos.y += -1 * g_dSecPerFrame * 300.0;
	}

	if (I_Input.Key('S')) {
		m_pos.y += 1 * g_dSecPerFrame * 300.0;
	}

	if (I_Input.Key('A')) {
		m_pos.x += -1 * g_dSecPerFrame * 300.0;
	}

	if (I_Input.Key('D')) {
		m_pos.x += 1 * g_dSecPerFrame * 300.0;
	}
	m_posDraw.x = m_pos.x - (m_rtDraw.right / 2);
	m_posDraw.y = m_pos.y - (m_rtDraw.bottom / 2);

	m_rtCollision.left = (LONG)m_posDraw.x;
	m_rtCollision.top = (LONG)m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;

	return true;
}
bool objClass::Render()
{
	if (m_pMaskBmp == nullptr) {
		BitBlt(g_hOffScreenDC,
			m_posDraw.x, m_posDraw.y,
			m_rtDraw.right, m_rtDraw.bottom,
			m_pColorBmp->m_hMemDC,
			m_rtDraw.left, m_rtDraw.top,
			SRCCOPY
		);

		//TransparentBlt(g_hOffScreenDC,
		//	(int)m_posDraw.x, (int)m_posDraw.y,
		//	(int)m_rtDraw.right, (int)m_rtDraw.bottom,
		//	m_pColorBmp->m_hMemDC,
		//	(int)m_rtDraw.left, (int)m_rtDraw.top,
		//	(int)m_rtDraw.right, (int)m_rtDraw.bottom,
		//	RGB(255, 255, 255)
		//);

		return true;
	}
	else {
		//TransparentBlt(g_hOffScreenDC,
		//	(int)m_posDraw.x, (int)m_posDraw.y,
		//	(int)m_rtDraw.right, (int)m_rtDraw.bottom,
		//	m_pColorBmp->m_hMemDC,
		//	(int)m_rtDraw.left, (int)m_rtDraw.top,
		//	(int)m_rtDraw.right, (int)m_rtDraw.bottom,
		//	RGB(255, 255, 255)
		//);



			BitBlt(g_hOffScreenDC,
				m_posDraw.x, m_posDraw.y,
				m_rtDraw.right, m_rtDraw.bottom,
				m_pMaskBmp->m_hMemDC,
				m_rtDraw.left, m_rtDraw.top,
				SRCAND
			); //AND연산

			BitBlt(g_hOffScreenDC,
				m_posDraw.x, m_posDraw.y,
				m_rtDraw.right, m_rtDraw.bottom,
				m_pColorBmp->m_hMemDC,
				m_rtDraw.left, m_rtDraw.top,
				SRCINVERT
			); //XOR연산

			BitBlt(g_hOffScreenDC,
				m_posDraw.x, m_posDraw.y,
				m_rtDraw.right, m_rtDraw.bottom,
				m_pMaskBmp->m_hMemDC,
				m_rtDraw.left, m_rtDraw.top,
				SRCINVERT
			); //XOR연산
	}

	//coolision rect
	if (m_bDebugRect) {
		int prevMode = SetROP2(g_hOffScreenDC, R2_XORPEN);
		Rectangle(g_hOffScreenDC,
			m_rtCollision.left,
			m_rtCollision.top,
			m_rtCollision.left + m_rtCollision.right,
			m_rtCollision.top + m_rtCollision.bottom);
		SetROP2(g_hOffScreenDC, prevMode);
	}
	return true;
}

bool objClass::Release()
{
	DeleteObject(m_hbrBack);
	DeleteObject(m_hColorRotateBmp);
	DeleteObject(m_hMaskRotateBmp);
	ReleaseDC(g_hWnd, m_hRotationDC);
	ReleaseDC(g_hWnd, m_hMemMaskDC);
	ReleaseDC(g_hWnd, m_hMemColorDC);
	return true;
}


objClass::~objClass()
{

}