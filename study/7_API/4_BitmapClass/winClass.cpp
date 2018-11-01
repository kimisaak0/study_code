#include "winClass.h"

winClass* g_pWindow = nullptr; //������ ������ �ν��Ͻ��� �����͸� �����ϴ� ��������
HWND g_hWnd = NULL;            //���� �������� �ڵ鰪�� ���� �ִ� ��������
HINSTANCE g_hInstance = NULL;


//�޽����� ó���ϴ� �Լ� (OS���� ȣ����)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow != NULL); //��ϵ� �����찡 ������ ���α׷� ����.

	LRESULT ret; // �޽��� ó���� ��ģ �� ��ȯ�Ǵ� ���� �ޱ� ���� ����.

	// �ν��Ͻ����� �߻��� �޽����� ��ȯ��. 
	// ���� �������� ������ �ν��Ͻ��� �޽��� ó���Լ����� �޽����� ����
	if (ret = g_pWindow->MsgProc(hWnd, msg, wParam, lParam)) {
		return ret;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//������ 
winClass::winClass()
{
	m_dwStyle = WS_OVERLAPPEDWINDOW;  // ������ ��Ÿ�� ����
	g_pWindow = this;                 // ������ �ν��Ͻ��� �����͸� g_pWindow�� ����.
}

//������ ��Ÿ�� ����.
void winClass::Set(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}

//������ Ŭ������ ����ϰ� �����츦 �����ϴ� �Լ�.
bool winClass::SetWindow(
	HINSTANCE     hInst,
    const TCHAR*  pTitleName,
	UINT          iWidth,
	UINT          iHeight)
{
	m_hInstance = hInst;

	// ������ Ŭ���� ���
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = L"MyWindow";
	wc.hCursor = LoadCursor(m_hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

	// Ŭ������ ��ϵ��� ������ false�� ��ȯ
	if (RegisterClassEx(&wc) == FALSE)	{
		return false;
	}

	// ������ ����( ��ϵ� Ŭ������ ����ؼ� )
	m_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		L"MyWindow", pTitleName,
		m_dwStyle,
		0, 0, iWidth, iHeight,
		NULL, NULL, m_hInstance, NULL
	);

	// �����찡 �������� ������ false�� ��ȯ
	if (m_hWnd == NULL)	{
		return false;
	}

	//������ �������� �ڵ鰪�� ���������� ����.
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);	 //�������� ���� ��ġ�� ũ�⸦ ���ؼ� �ι�° ���ڷ� ���޵� RECT ����ü�� �����Ϳ� �־���.
	GetClientRect(m_hWnd, &m_rtClient);	 //�������� �۾����� ũ�⸦ ����ؼ� �ι�° ���ڷ� ���޵� RECT ����ü�� �����Ϳ� �־���.

	//ȭ�� �߾ӿ� ������ ����
	CenterWindow();

	//�����츦 ������.
	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}

//ȭ�� ���߾ӿ� �����츦 ���� �Լ�
void winClass::CenterWindow()
{
	//GetSystemMetrics : �ý����� ���� ������ ��ȯ��.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHegiht = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHegiht - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtWindow.right, m_rtWindow.bottom, true);
}

//�������� ���� ó��
bool winClass::Run()
{
	//�ʱ�ȭ�� ���� �ʾ����� false�� ��ȯ.
	if (!GameInit()) {
		return false;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)	{
		//�޽����� ������ �޽����� ����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			//WM_QUIT �޽����� ������ �ݺ����� ��������.
			if (msg.message == WM_QUIT)	{
				break;
			}
		}
		//�޽����� ������ GameRun()�� ����.
		else {
			GameRun();
		}
	}
	//�ݺ����� ���������� GameRelease()�� ����.
	return GameRelease();
}

//�����쿡�� ���������� �޽��� ó�� �Լ�.
LRESULT winClass::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
		}return 0;
	}
	return 0;
}

//Ű �Է¿� ���� �޽����� inputClass�� �ѱ�
void winClass::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
}

winClass::~winClass()
{
}
