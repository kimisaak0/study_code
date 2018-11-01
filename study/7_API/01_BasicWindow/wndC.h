#pragma once

#include "header.h"

class wndC
{
private:
	WNDCLASSEX   m_wndC;
	HWND         m_hWnd;
	LPCWSTR      m_lWndName;

	//메시지 처리 함수
	static LRESULT CALLBACK MsgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
public:

	bool registWnd(LPCWSTR LWndName);
	bool createWnd();
	bool runWindow();

	HWND getHandle();

public:
	wndC();
	~wndC();
};