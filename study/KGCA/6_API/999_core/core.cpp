#include "core.h"

HDC g_hOffScreenDC = nullptr;
HDC g_hScreenDC = nullptr;

core::core()
{
}

//초기화 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameInit()
{
	m_Timer.Init();
	I_Input.Init();

	m_hScreenDC = GetDC(m_hWnd);
	g_hScreenDC = m_hScreenDC;

	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);

	g_hOffScreenDC = m_hOffScreenDC;

	m_hOffScreenBmp = CreateCompatibleBitmap(m_hScreenDC, m_rtClient.right, m_rtClient.bottom);
	SelectObject(m_hOffScreenDC, m_hOffScreenBmp);

	COLORREF bkColor = RGB(255, 255, 255);
	m_hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, m_hbrBack);

	Init();

	return true;
}

//계산 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameFrame()
{
	m_Timer.Frame();
	I_Input.Frame();
	Frame();

	return true;
}



bool    core::GamePreRender()
{
	PatBlt(m_hOffScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, PATCOPY);
	return true;
}

//그리기 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameRender()
{
	GamePreRender();

	m_Timer.Render();
	I_Input.Render();
	Render();

	GamePostRender();
	return true;
}

bool    core::GamePostRender()
{
	BitBlt(m_hScreenDC, 0, 0, m_rtClient.right, m_rtClient.bottom, m_hOffScreenDC, 0, 0, SRCCOPY);
	return true;
}

// 프로그램 돌리기, 계산하고 그린다.
bool    core::GameRun()
{
	//Sleep(1);
	GameFrame();
	GameRender();
	return true;
}

//종료, 삭제 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameRelease()
{
	Release();
	m_Timer.Release();
	I_Input.Release();

	DeleteObject(m_hbrBack);
	DeleteObject(m_hOffScreenBmp);
	ReleaseDC(m_hWnd, m_hScreenDC);
	ReleaseDC(m_hWnd, m_hOffScreenDC);

	return true;
}

core::~core()
{
}
