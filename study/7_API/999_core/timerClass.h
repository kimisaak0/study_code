#pragma once
#include "header.h"

// 1) 1�������� ��� �ð� : m_fSecFrame
// 2) 1���� ������ ī���� : m_dwFrameCount
// 3) ���� ���� ���� �ð� : m_dGameTimer;

class timerClass
{
	DWORD   m_dwFrameCounter; // Frame ����
	DWORD   m_dwFPS;          // 1�ʵ��� ������ Frame
	DWORD   m_dwBeforeTick;   // ������ tick�� (Ŭ�������� �����ϰ� �־�߸� ����� ����� ��)
	double  m_dSecPerFrame;   // dwElapseTick�� �ʴ����� ��ȯ�� ��
	double  m_dGameTimer;     // ���α׷�(����) ������ �� ����ð� (�ʴ���)
	double  m_dTimer;         // 1�� ������ ���ڿ��� �����ϱ� ���ؼ� 1�ʸ� ������ ����.
	TCHAR   m_csBuffer[256];  // ���ڿ� ����

public:
	bool    Init();      // �ʱ�ȭ
	bool    Frame();	 // ���
	bool    Render();	 // ��ο�
	bool    Release();	 // �Ҹ�, ����

public:
	timerClass();
	virtual ~timerClass();
};

