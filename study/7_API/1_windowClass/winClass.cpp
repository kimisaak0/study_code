#include "winClass.h"

//생성된 윈도우 인스턴스의 포인터를 저장하는 전역변수
winClass* g_pWindow = NULL;

//메시지를 처리하는 함수 (OS에서 호출함)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow != NULL); //등록된 윈도우가 없으면 프로그램 종료.

	LRESULT ret; // 메시지 처리를 마친 후 반환되는 값을 받기 위한 변수.

	//인스턴스에서 발생한 메시지를 반환함.
	if (ret = g_pWindow->MsgProc(hWnd, msg, wParam, lParam)) {
		return ret;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//생성자 
winClass::winClass()
{
	m_dwStyle = WS_OVERLAPPEDWINDOW;  // 윈도우 스타일 지정
	g_pWindow = this;                 // 생성한 인스턴스의 포인터를 g_pWindow에 대입.
}

//윈도우 스타일 변경.
void winClass::Set(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}

//윈도우 클래스를 등록하고 윈도우를 생성하는 함수.
bool winClass::SetWindow (      HINSTANCE   hInst,
	                      const TCHAR*      pTitleName,
	                            UINT        iWidth, 
	                            UINT        iHeight)
{
	m_hInstance = hInst;

	// 윈도우 클래스 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = L"MyWindow";
	wc.hCursor = LoadCursor(m_hInstance, IDC_ARROW);

	if (RegisterClassEx(&wc) == FALSE)
	{
		return false;
	}

	//// 윈도우 생성( 등록된 클래스를 사용해서 )
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"MyWindow", pTitleName,
		m_dwStyle,
		0, 0, iWidth, iHeight,
		NULL, NULL, m_hInstance, NULL);

	if (m_hWnd == NULL)
	{
		return false;
	}

	GetWindowRect(m_hWnd, &m_rtWindow);	 //윈도우의 현재 위치와 크기를 구해서 두번째 인자로 전달된 RECT 구조체의 포인터에 넣어줌.
	GetClientRect(m_hWnd, &m_rtClient);	 //윈도우의 작업영역 크기를 계산해서 두번째 인자로 전달된 RECT 구조체의 포인터에 넣어줌.

	CenterWindow();

	//윈도우를 보여줌.
	ShowWindow(m_hWnd, SW_SHOW); 
	return true;
}

//화면 정중앙에 윈도우를 띄우는 함수
void winClass::CenterWindow()
{
	//GetSystemMetrics : 시스템의 설정 정보를 반환함.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHegiht = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHegiht - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd, x, y, m_rtWindow.right, m_rtWindow.bottom, true);
}


bool winClass::Run()
{
	//초기화가 되지 않았으면 종료.
	if (!GameInit()) {
		return false;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			GameRun();
		}
	}
	return GameRelease();
}

LRESULT winClass::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			//MessageBox(NULL, L"윈도우가 떴다.", L"윈도우생성", MB_OK);
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);// WM_QUIT--> PUSH			
		}return 0;
	}
	return 0;
}


bool winClass::GameInit()
{
	return true;
}


bool winClass::GameRun() {
	return true;
}


bool winClass::GameRelease() {
	return true;
}

winClass::~winClass()
{
}
