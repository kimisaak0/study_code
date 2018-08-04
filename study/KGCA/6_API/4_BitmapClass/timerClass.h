#pragma once
#include "header.h"

// 1) 1프레임의 경과 시간 : m_fSecFrame
// 2) 1초의 프레임 카운터 : m_dwFrameCount
// 3) 게임 실행 누적 시간 : m_dGameTimer;

class timerClass
{
	DWORD   m_dwFrameCounter; // Frame 누적
	DWORD   m_dwFPS;          // 1초동안 누적된 Frame
	DWORD   m_dwBeforeTick;   // 마지막 tick값 (클래스에서 저장하고 있어야만 계산이 제대로 됨)
	double  m_dSecPerFrame;   // dwElapseTick을 초단위로 변환한 것
	double  m_dGameTimer;     // 프로그램(게임) 실행후 총 경과시간 (초단위)
	double  m_dTimer;         // 1초 단위로 문자열을 갱신하기 위해서 1초를 모으는 변수.
	TCHAR   m_csBuffer[256];  // 문자열 버퍼

public:
	bool    Init();      // 초기화
	bool    Frame();	 // 계산
	bool    Render();	 // 드로우
	bool    Release();	 // 소멸, 삭제

public:
	timerClass();
	virtual ~timerClass();
};

