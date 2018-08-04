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
	bool    Init();      // �ʱ�ȭ
	bool    Frame();	 // ���
	bool    Render();	 // ��ο�
	bool    Release();	 // �Ҹ�, ����

public:
	bmpClass();
	virtual ~bmpClass();
};

