#pragma once
#include "winClass.h"
#include "timerClass.h"

//�� Ŭ������ ����� ��Ƶ� ��.
class core : public winClass
{
public:
	timerClass    m_Timer;           // Ÿ�̸�
	
	//���� ���۸� : ���� �̹����� �ĸ� ���ۿ� �̸� �غ��ؼ� ���� ��ũ���� ��ü�ϴ� ������� ȭ���� �������� �����ϴ� ���.
	HDC           m_hScreenDC;		 // ���� ��ũ�� DC
	HDC           m_hOffScreenDC;	 // �ĸ� ��ũ�� DC
	HBITMAP       m_hOffScreenBmp;	 // ��� bmp�̹���
	HBRUSH        m_hbrBack;		 // ���� ĥ�ϱ�

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

