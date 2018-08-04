#pragma once
#include "winClass.h"
#include "timerClass.h"

//각 클래스의 기능을 모아둔 것.
class core : public winClass
{
public:
	timerClass    m_Timer;           // 타이머
	
	//더블 버퍼링 : 다음 이미지를 후면 버퍼에 미리 준비해서 전면 스크린과 교체하는 방식으로 화면의 깜빡임을 제거하는 기술.
	HDC           m_hScreenDC;		 // 전면 스크린 DC
	HDC           m_hOffScreenDC;	 // 후면 스크린 DC
	HBITMAP       m_hOffScreenBmp;	 // 띄울 bmp이미지
	HBRUSH        m_hbrBack;		 // 배경색 칠하기

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

