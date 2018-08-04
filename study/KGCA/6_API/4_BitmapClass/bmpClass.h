#pragma once
#include "header.h"

class bmpClass
{
public:
	T_STR   m_szName;      // bmp �̸�
	HBITMAP m_hBitmap;     // bmp �ڵ鰪
	HDC     m_hMemDC;      // bmp�� �׸��� ���� DC
	BITMAP  m_bmpInfo;     // bmp ����

public:
	//�̹��� �ҷ�����
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

