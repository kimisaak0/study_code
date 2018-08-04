#pragma once
#include "header.h"
#include "inputClass.h"

class winClass
{

public:
	HWND		m_hWnd;			 // ������ �������� �ڵ鰪. msgProc���� ���Ǵ� ���̹Ƿ� public���� Ǯ����.
	HINSTANCE	m_hInstance;	 // Ŭ���� �ν��Ͻ��� �ڵ鰪.
	RECT		m_rtClient;      // ������ �������� �۾������� ũ��. (�۾����� : �������� Ÿ��Ʋ��, ��ũ�� ��, ��輱, �޴� ���� ������ ����)
	RECT		m_rtWindow;      // ������ �������� ��ü ũ��
	DWORD		m_dwStyle;       // ������ �������� ��Ÿ�� 


public:
	//�������� ��Ÿ�� ����
	void		Set(DWORD dwStyle);

	//HINSTANCE ���̶�?
	// 1) ���α׷� �ڵ带 ��� �ִ� ��⿡ ���� �ڵ鰪. 
	// 2) �޸𸮿� ��üȭ�� ���α׷��� �ν��Ͻ��鿡 ���� �ڵ鰪.
	// 3) ��, �������� ���α׷� �ϳ��� �ϳ��� �ν��Ͻ��ڵ鰪�� ���´�.
	// 4) �翬�� Ŀ���� �ο����ش�. �� ������Ʈ������ WinMain�� ù��° ���ڰ����� �޾ƿ´�.

	//HWND ���̶�?
	// 1) �� �����쿡 ���� �ڵ鰪�̴�.
	// 2) �ϳ��� ���α׷��� �������� �����츦 ���� ��찡 �����Ƿ� ������ �����쿡 ���� �ڵ鰪�� �ο����ִ� ���̴�.

	//������ Ŭ������ ����ϰ� �����츦 �����ϴ� �Լ�.
	bool		SetWindow(
		HINSTANCE        hInstance,                     // �ν��Ͻ� �ڵ鰪
		const TCHAR*     pTitleName = L"KGCA Sample",   // �������� �̸�
		UINT             iWidth     = 800,			    // �������� ���̰�
		UINT             iHeight    = 600			    // �������� ���̰�
	);

	//�����츦 ȭ�� �߾ӿ� �Ѹ���.
	void		CenterWindow();

	//�������� ��� ó���� �ϴ� �Լ�.
	bool		Run();

public:
	//�޽����� ó���ϴ� �Լ�
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//winClass -> core -> sample ���� ��ӹ޴� �Լ�.
public:
	virtual bool	GameInit() = 0;         // ���� �ʱ�ȭ
	virtual bool    GameFrame() = 0;        // ���� ������
	virtual bool    GameRender() = 0;       // ���� ������
	virtual bool	GameRun() = 0;          // ���� ����
	virtual bool	GameRelease() = 0;      // ���� ����

public:
	// Ű�Է� �̺�Ʈ�� ���� ó���� ���.
	void MsgEvent(MSG msg);

public:
	winClass();
	virtual ~winClass();
};