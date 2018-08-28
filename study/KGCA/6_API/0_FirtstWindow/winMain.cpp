#include <windows.h>

HWND g_hWnd;
HINSTANCE g_hInst;

//�޽����� ó���ϴ� �Լ� (OS���� ȣ����)
LRESULT CALLBACK WndProc(HWND hWnd,      // ������ �������� �ڵ鰪
	                     UINT msg,       // �޽��� ��ȣ ��. ��ũ�η� ���ǵǾ� �ִ�.
	                     WPARAM wParam,  // �޽��� ��ȣ ���� ���� ���޵Ǵ� �߰� ���� 1. 
	                     LPARAM lParam)  // �޽��� ��ȣ ���� ���� ���޵Ǵ� �߰� ���� 2. 
{
	switch (msg)
	{
		case WM_CREATE:
		{
			//MessageBox(NULL, L"�����찡 ����.", L"���������", MB_OK);
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);// WM_QUIT--> PUSH			
		}break;
	}
	//�⺻ �޽��� ó�� �Լ�. ������ ���� ó������ ���� ��� �޽����� ó�����ش�.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void GameInit();
void GameRun();
void GameRelease();

int WINAPI WinMain(HINSTANCE  hInst,         // ���α׷��� OSĿ���� �ο����ִ� �ڵ�(ID), ���α׷��� ����� �� �ο��޴´�.
                   HINSTANCE  hPrevInst,     // ȣȯ���� ���ؼ��� �����ϴ� �μ�, ����� �׻� NULL�̸� ���̻� ������ �ʴ´�. 
	               LPSTR      lpCmdLine,     // ��������� �Էµ� ���α׷� �μ�, ���α׷� ����� �ܺο��� �Ѿ���� ���ڿ��̴�. �ܼ� main�� argv���� ����� ��.
	               int        nCmdShow)      // �����찡 ȭ�鿡 ��µ� �� ���¸� �����ϴ� �μ�. Ŀ�ο��� �Ѿ�´�.  
{
	g_hInst = hInst;

	// ������ Ŭ���� ���
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));     //wc��ü�� ���� 0���� �ʱ�ȭ

	wc.cbSize = sizeof(WNDCLASSEX);         // ����ü ũ��
	wc.style = CS_HREDRAW | CS_VREDRAW;     // ��� ����
	wc.lpfnWndProc = WndProc;               // ���ν��� �Լ�
	wc.hInstance = hInst;                   // ������ �ν��Ͻ�
	wc.lpszClassName = L"MyWindow";         // Ŭ���� �̸� (�߿�! �����츦 ���鶧 �� �̸��� ����Ѵ�!)

	if (RegisterClassEx(&wc) == FALSE) 	{   // Ŀ�ο� ������ Ŭ������ ���.
		return 1;
	}

	//// ������ ����( ��ϵ� Ŭ������ ����ؼ� )

	//�����츦 �����ϴ� �Լ� (������ �ڵ鰪�� ��ȯ�Ѵ�.)
	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW,       // ������ �������� Ȯ�� ��Ÿ�� ����
		                       L"MyWindow",           // ������ Ŭ���� �̸�. (������ ���� ���� ���ų� �̸� ���ǵǾ� �ִ� �ý��� ���� Ŭ������ �� ���� �ִ�.)
		                       L"KGCA SAMPLES",       // ������ ����ǥ���ٿ� ���� ����
		                       WS_OVERLAPPEDWINDOW,   // ������ �������� ��Ÿ�� ���� (Ÿ��Ʋ�ٰ� �ִ���, �ּ�ȭ�� �������� ��...)
                               0, 0,                  // �����찡 ������ x, y ��ǥ
		                       800, 600,              // ������ �������� ���� ũ��� ���� ũ��
		                       NULL,                  // �θ� ������ �ڵ�, ���ϵ� �����쿡���� �� ��������� ��.
		                       NULL,                  // �޴� �ڵ�
		                       hInst,                 // ���� ���α׷� �ν��Ͻ�. �����츦 ������ �ν��Ͻ� �ڵ� ����. �ν��Ͻ��� ����� �� �����쵵 ���� �ı��ȴ�.
		                       NULL                   // ���� ������ ����. WM_CREATE �޽����� lParam���� ���޵� CREATESTRUCT ����ü���� ������.
     );

	g_hWnd = hWnd;

	if (hWnd == NULL)
	{
		return 1;
	}

	//�������� ShowState�� ����
	// hWnd : ��Ÿ�� ������ �ڵ鰪, nCmdShow : ShowState��
	ShowWindow(hWnd, SW_SHOW);       

	GameInit();


	
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (1) {
		// GetMessage  : �޼��� ť�� �޼����� �ִ� ��쿡�� �޼��� ��ȯ. ������ ��ȯ ����.
		// PeekMessage : �޼��� ť�� �޼����� ������ �޼��� ��ȯ,������ false�� ��ȯ

		if (PeekMessage(&msg,        // lpMsg : �޽����� ����� MSG ����ü�� ���� ������,
			            NULL,        // hWnd  : �޽����� �߻��� �������� �ڵ� 
			            0, 0,        // wMsgFilterMin, WMsgFilterMax : ������ �޽����� �ּҰ��� �ִ밪. �� �� ���� ����ϸ� ������ ������ ���ϴ� �޽����� ������ �� �ִ�.(�޽��� ���͸�)
			            PM_REMOVE)) { // wRemoveMsg : ������ �޽����� ó���� ����� �����ϴ� �÷���.

			TranslateMessage(&msg);  // ������ �޽����� ���� �޽����� ��ȯ�ϴ� �Լ�.
			DispatchMessage(&msg);   // �޽����� ó���� ������� ������ �Լ�.

			if (msg.message == WM_QUIT)	{ 
				break;
			}
		}
		else {
			GameRun();
		}
	}

	GameRelease();
	
	return 0;
}


void GameInit()
{
	// ����, ������Ʈ, ����Ʈ, UI �ʱ�ȭ, �ε�
	MessageBox(NULL, L"�����ʱ�ȭ.", L"���ӽ���", MB_OK);
}
void GameRun()
{
	//�̹��� ��� �׽�Ʈ �� (..)
	HDC onHdc = GetDC(g_hWnd);
	HDC offHdc = CreateCompatibleDC(onHdc);

	HBITMAP nowBmp = (HBITMAP)LoadImage(g_hInst, L"topVeiw_Water_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nowBmp == NULL) {
		MessageBox(g_hWnd, L"�̹��� �ε� ����", L"�̹��� �ε� ����", MB_OK);
		return;
	}

	HBITMAP oldBmp = (HBITMAP)SelectObject(offHdc, nowBmp);

	BitBlt(onHdc, 0, 0, 50, 50, offHdc, 0, 0, SRCCOPY);


	//MessageBox(NULL, L"���� ������.", L"���ӽ���", MB_OK);
}
void GameRelease()
{
	// ����, ������Ʈ, ����Ʈ, UI �Ҹ�
	MessageBox(NULL, L"���� ����.", L"���ӽ���", MB_OK);
}