#include "core.h"

HDC g_hOffScreenDC = nullptr;
HDC g_hScreenDC = nullptr;

core::core()
{
}

//�ʱ�ȭ (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
bool    core::GameInit()
{
	m_Timer.Init();
	I_Input.Init();

	m_hScreenDC = GetDC(m_hWnd);
	g_hScreenDC = m_hScreenDC;

	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	g_hOffScreenDC = m_hOffScreenDC;

	m_hOffScreenBmp = CreateCompatibleBitmap(m_hScreenDC, m_rtClient.right, m_rtClient.bottom);
	SelectObject(m_hOffScreenDC, m_hOffScreenBmp);

	COLORREF bkColor = RGB(255, 255, 255);
	m_hbrBack = CreateSolidBrush(bkColor);
	SelectObject(m_hOffScreenDC, m_hbrBack);

	HANDLE m_hPen = CreatePen(PS_SOLID, 0, RGB(255,0,0));
	SelectObject(m_hOffScreenDC, m_hPen);

	Init();

	return true;
}

//��� (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
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

//�׸��� (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
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

// ���α׷� ������, ����ϰ� �׸���.
bool    core::GameRun()
{
	//Sleep(1);
	GameFrame();
	GameRender();
	return true;
}

//����, ���� (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
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