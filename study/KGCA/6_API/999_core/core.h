#pragma once
#include "winClass.h"
#include "timerClass.h"

class core : public winClass
{
public:
	timerClass m_Timer;
	HDC        m_hScreenDC;
	HDC        m_hOffScreenDC;
	HBITMAP    m_hOffScreenBmp;
	HBRUSH     m_hbrBack;

public:
	bool    GameInit()    override;  // 게임 초기화
	bool    GameFrame()   override;  // 게임 프레임
	bool    GameRender()  override;	 // 게임 렌더링
	bool    GameRun()     override;  // 게임 실행
	bool    GameRelease() override;  // 게임 종료

	bool    GamePreRender();
	bool    GamePostRender();

public:
	virtual bool	Init() { return true; }       // 초기화
	virtual bool	Frame() { return true; }	  // 계산
	virtual bool	Render() { return true; }	  // 드로우
	virtual bool	Release() { return true; }	  // 소멸, 삭제

public:
	core();
	virtual ~core();
};

