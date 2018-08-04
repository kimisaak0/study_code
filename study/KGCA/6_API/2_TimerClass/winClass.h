#pragma once
#include "header.h"

class winClass
{

public:
	HWND		m_hWnd;			 // 생성된 윈도우의 핸들값. msgProc에서 사용되는 값이므로 public으로 풀어줌.

private:
	HINSTANCE	m_hInstance;	 // 클래스 인스턴스의 핸들값.
	RECT		m_rtClient;      // 생성된 윈도우의 작업영역의 크기. (작업영역 : 윈도우의 타이틀바, 스크롤 바, 경계선, 메뉴 등을 제외한 영역)
	RECT		m_rtWindow;      // 생성된 윈도우의 전체 크기
	DWORD		m_dwStyle;       // 생성된 윈도우의 스타일 


public:
	//윈도우의 스타일 지정
	void		Set(DWORD dwStyle);

	//윈도우 클래스를 등록하고 윈도우를 생성하는 함수.
	bool		SetWindow(
		HINSTANCE        hInstance,
		const TCHAR*     pTitleName = L"KGCA Sample",
		UINT             iWidth     = 800,
		UINT             iHeight    = 600
	);

	//윈도우를 화면 중앙에 뿌리기.
	void		CenterWindow();

	//윈도우의 모든 처리를 하는 함수.
	bool		Run();

public:
	//메시지를 처리하는 함수
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool	GameInit() = 0;         // 게임 초기화
	virtual bool	GameRun() = 0;          // 게임 실행
	virtual bool	GameRelease() = 0;      // 게임 종료

public:
	winClass();
	virtual ~winClass();
};