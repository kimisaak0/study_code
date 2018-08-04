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
	bool    GameInit()    override;  // ���� �ʱ�ȭ
	bool    GameFrame()   override;  // ���� ������
	bool    GameRender()  override;	 // ���� ������
	bool    GameRun()     override;  // ���� ����
	bool    GameRelease() override;  // ���� ����

	bool    GamePreRender();
	bool    GamePostRender();

public:
	virtual bool	Init() { return true; }       // �ʱ�ȭ
	virtual bool	Frame() { return true; }	  // ���
	virtual bool	Render() { return true; }	  // ��ο�
	virtual bool	Release() { return true; }	  // �Ҹ�, ����

public:
	core();
	virtual ~core();
};

