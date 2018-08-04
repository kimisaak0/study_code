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
	//timeGetTime() : winmm.lib 추가해야함
    //#pragma comment(lib, "winmm.lib")

	// 1Tick == 1/1000초
	//timeGetTime() : 윈도우가 시작되어 지금까지 흐른 시간을 1Tick단위로 리턴해주는 함수.
	
	// 프로그램 시작 시간(Tick단위)
	m_dwBeforeTick = timeGetTime();  

	return true;
}

bool    timerClass::Frame()
{
	// 현재 시간(Tick단위)
	DWORD dwCurrentTick = timeGetTime(); 
	
	//이 계산을 하기까지 경과한 시간. (tick단위)
	DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick; 

	// dwElapseTick을 초단위로 변환
	m_dSecPerFrame = dwElapseTick / 1000.0;
	
	g_dSecPerFrame = m_dSecPerFrame;

	//초단위 누적
	m_dGameTimer += m_dSecPerFrame;

	//초단위 누적
	m_dTimer += m_dSecPerFrame;
	if (m_dTimer >= 1.0) { //1초 이상 지났으면
		m_dwFPS = m_dwFrameCounter; //1초 동안 누적된 Frame
		m_dwFrameCounter = 0; //Frame을 0으로 초기화
		m_dTimer -= 1.0; //다시 1을 빼줌

		//버퍼에 기록
		_stprintf_s(m_csBuffer,
			        L"FPS:%d TIME:%10.4f SPF:%10.4f",
			        m_dwFPS, m_dGameTimer, m_dSecPerFrame);
		
		//OutputDebugString(m_csBuffer);
	}

	m_dwFrameCounter++; //Frame 누적

	//현재 Tick 저장
	m_dwBeforeTick = dwCurrentTick;
	return true;
}

bool    timerClass::Render()
{
	// DC :
	// API내에서 화면 출력에 필요한 모든 정보를 가지는 데이터 구조체
	// GDI에 의해서 관리됨
	// 폰트, 색상, 굵기, 출력 방법 등에 대한 정보를 담고 있음.

	// HDC      : DC의 핸들
	// GetDC()  : 현재 프로그램의 HDC를 받아오는 함수. 

	// TextOut(hdc, nXStart, nYStart, lpString, cchString)  : 
	// api에서 단순하게 텍스를 출력하는 함수. 
	// hdc : 출력할 윈도우의 핸들
	// nXStart, nYStart : 출력할 위치
	// lpString : 출력할 문자열
	// cchString : 문자열의 길이

	//HDC hdc = GetDC(g_hWnd); 	//현재 윈도우의 HDC받아오기
	//TextOut(hdc, 0, 0, m_csBuffer, (int)wcslen(m_csBuffer));	//버퍼의 문자열 뿌리기
	//ReleaseDC(g_hWnd, hdc);  //HDC해제

	SetBkColor(g_hOffScreenDC, RGB(255, 0, 0));
	SetTextColor(g_hOffScreenDC, RGB(0, 0, 255));
	TextOut(g_hOffScreenDC, 0, 0, m_csBuffer, (int)wcslen(m_csBuffer));	//버퍼의 문자열 뿌리기

	return true;
}

bool    timerClass::Release()
{
	return true;
}

timerClass::~timerClass()
{
}
