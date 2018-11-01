#pragma once
#include "header.h"

class winClass
{

public:
	HWND		m_hWnd;			 // ������ �������� �ڵ鰪. msgProc���� ���Ǵ� ���̹Ƿ� public���� Ǯ����.

private:
	HINSTANCE	m_hInstance;	 // Ŭ���� �ν��Ͻ��� �ڵ鰪.
	RECT		m_rtClient;      // ������ �������� �۾������� ũ��. (�۾����� : �������� Ÿ��Ʋ��, ��ũ�� ��, ��輱, �޴� ���� ������ ����)
	RECT		m_rtWindow;      // ������ �������� ��ü ũ��
	DWORD		m_dwStyle;       // ������ �������� ��Ÿ�� 


public:
	//�������� ��Ÿ�� ����
	void		Set(DWORD dwStyle);

	//������ Ŭ������ ����ϰ� �����츦 �����ϴ� �Լ�.
	bool		SetWindow(
		HINSTANCE        hInstance,
		const TCHAR*     pTitleName = L"KGCA Sample",
		UINT             iWidth     = 800,
		UINT             iHeight    = 600
	);

	//�����츦 ȭ�� �߾ӿ� �Ѹ���.
	void		CenterWindow();

	//�������� ��� ó���� �ϴ� �Լ�.
	bool		Run();

public:
	//�޽����� ó���ϴ� �Լ�
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool	GameInit() = 0;         // ���� �ʱ�ȭ
	virtual bool	GameRun() = 0;          // ���� ����
	virtual bool	GameRelease() = 0;      // ���� ����

public:
	winClass();
	virtual ~winClass();
};