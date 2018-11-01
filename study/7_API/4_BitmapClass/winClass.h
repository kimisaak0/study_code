#pragma once
#include "header.h"
#include "inputClass.h"

class winClass
{

public:
	HWND		m_hWnd;			 // 생성된 윈도우의 핸들값. msgProc에서 사용되는 값이므로 public으로 풀어줌.
	HINSTANCE	m_hInstance;	 // 클래스 인스턴스의 핸들값.
	RECT		m_rtClient;      // 생성된 윈도우의 작업영역의 크기. (작업영역 : 윈도우의 타이틀바, 스크롤 바, 경계선, 메뉴 등을 제외한 영역)
	RECT		m_rtWindow;      // 생성된 윈도우의 전체 크기
	DWORD		m_dwStyle;       // 생성된 윈도우의 스타일 


public:
	//윈도우의 스타일 지정
	void		Set(DWORD dwStyle);

	//HINSTANCE 값이란?
	// 1) 프로그램 코드를 담고 있는 모듈에 대한 핸들값. 
	// 2) 메모리에 실체화된 프로그램의 인스턴스들에 대한 핸들값.
	// 3) 즉, 실행중인 프로그램 하나당 하나의 인스턴스핸들값을 갖는다.
	// 4) 당연히 커널이 부여해준다. 이 프로젝트에서도 WinMain의 첫번째 인자값으로 받아온다.

	//HWND 값이란?
	// 1) 각 윈도우에 대한 핸들값이다.
	// 2) 하나의 프로그램이 여러개의 윈도우를 갖는 경우가 많으므로 각각의 윈도우에 대한 핸들값을 부여해주는 것이다.

	//윈도우 클래스를 등록하고 윈도우를 생성하는 함수.
	bool		SetWindow(
		HINSTANCE        hInstance,                     // 인스턴스 핸들값
		const TCHAR*     pTitleName = L"KGCA Sample",   // 윈도우의 이름
		UINT             iWidth     = 800,			    // 윈도우의 넓이값
		UINT             iHeight    = 600			    // 윈도우의 높이값
	);

	//윈도우를 화면 중앙에 뿌리기.
	void		CenterWindow();

	//윈도우의 모든 처리를 하는 함수.
	bool		Run();

public:
	//메시지를 처리하는 함수
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//winClass -> core -> sample 각각 상속받는 함수.
public:
	virtual bool	GameInit() = 0;         // 게임 초기화
	virtual bool    GameFrame() = 0;        // 게임 프레임
	virtual bool    GameRender() = 0;       // 게임 렌더링
	virtual bool	GameRun() = 0;          // 게임 실행
	virtual bool	GameRelease() = 0;      // 게임 종료

public:
	// 키입력 이벤트에 대한 처리를 담당.
	void MsgEvent(MSG msg);

public:
	winClass();
	virtual ~winClass();
};