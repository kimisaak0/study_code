#include "timerClass.h"

double g_dSecPerFrame = 0.0;

timerClass::timerClass()
{
	m_dwFrameCounter  =	(DWORD)0.0;
	m_dwFPS			  = (DWORD)0.0;
	m_dwBeforeTick	  = (DWORD)0.0;
	m_dSecPerFrame	  =	 0.0;
	m_dGameTimer	  =	 0.0;
	m_dTimer		  =	 0.0;
}

bool    timerClass::Init()
{
	//timeGetTime() : winmm.lib �߰��ؾ���
    //#pragma comment(lib, "winmm.lib")

	// 1Tick == 1/1000��
	//timeGetTime() : �����찡 ���۵Ǿ� ���ݱ��� �帥 �ð��� 1Tick������ �������ִ� �Լ�.
	
	// ���α׷� ���� �ð�(Tick����)
	m_dwBeforeTick = timeGetTime();  

	return true;
}

bool    timerClass::Frame()
{
	// ���� �ð�(Tick����)
	DWORD dwCurrentTick = timeGetTime(); 
	
	//�� ����� �ϱ���� ����� �ð�. (tick����)
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick; 

	// dwElapseTick�� �ʴ����� ��ȯ
	m_dSecPerFrame = dwElapseTick / 1000.0;
	
	g_dSecPerFrame = m_dSecPerFrame;

	//�ʴ��� ����
	m_dGameTimer += m_dSecPerFrame;

	//�ʴ��� ����
	m_dTimer += m_dSecPerFrame;
	if (m_dTimer >= 1.0) { //1�� �̻� ��������
		m_dwFPS = m_dwFrameCounter; //1�� ���� ������ Frame
		m_dwFrameCounter = 0; //Frame�� 0���� �ʱ�ȭ
		m_dTimer -= 1.0; //�ٽ� 1�� ����

		//���ۿ� ���
		_stprintf_s(m_csBuffer,
			        L"FPS:%d TIME:%10.4f SPF:%10.4f",
			        m_dwFPS, m_dGameTimer, m_dSecPerFrame);
		
		//OutputDebugString(m_csBuffer);
	}

	m_dwFrameCounter++; //Frame ����

	//���� Tick ����
	m_dwBeforeTick = dwCurrentTick;
	return true;
}

bool    timerClass::Render()
{
	// DC :
	// API������ ȭ�� ��¿� �ʿ��� ��� ������ ������ ������ ����ü
	// GDI�� ���ؼ� ������
	// ��Ʈ, ����, ����, ��� ��� � ���� ������ ��� ����.

	// HDC      : DC�� �ڵ�
	// GetDC()  : ���� ���α׷��� HDC�� �޾ƿ��� �Լ�. 

	// TextOut(hdc, nXStart, nYStart, lpString, cchString)  : 
	// api���� �ܼ��ϰ� �ؽ��� ����ϴ� �Լ�. 
	// hdc : ����� �������� �ڵ�
	// nXStart, nYStart : ����� ��ġ
	// lpString : ����� ���ڿ�
	// cchString : ���ڿ��� ����

	//HDC hdc = GetDC(g_hWnd); 	//���� �������� HDC�޾ƿ���
	//TextOut(hdc, 0, 0, m_csBuffer, (int)wcslen(m_csBuffer));	//������ ���ڿ� �Ѹ���
	//ReleaseDC(g_hWnd, hdc);  //HDC����

	SetBkColor(g_hOffScreenDC, RGB(255, 0, 0));
	SetTextColor(g_hOffScreenDC, RGB(0, 0, 255));
	TextOut(g_hOffScreenDC, 0, 0, m_csBuffer, (int)wcslen(m_csBuffer));	//������ ���ڿ� �Ѹ���

	return true;
}

bool    timerClass::Release()
{
	return true;
}

timerClass::~timerClass()
{
}
