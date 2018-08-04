#pragma once
#include "header.h"

class bmpClass
{
public:
	T_STR   m_szName;
	HBITMAP m_hBitmap;
	HDC     m_hMemDC;
	BITMAP  m_bmpInfo;

public:
	bool    Load(T_STR szLoadFile);

public:
	bool    Init();      // 초기화
	bool    Frame();	 // 계산
	bool    Render();	 // 드로우
	bool    Release();	 // 소멸, 삭제

public:
	bmpClass();
	virtual ~bmpClass();
};

