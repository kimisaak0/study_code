#include "winClass.h"

winClass* g_pWindow = nullptr; //생성된 윈도우 인스턴스의 포인터를 저장하는 전역변수
HWND g_hWnd = NULL;            //현재 윈도우의 핸들값을 갖고 있는 전역변수
HINSTANCE g_hInstance = NULL;


//메시지를 처리하는 함수 (OS에서 호출함)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow != NULL); //등록된 윈도우가 없으면 프로그램 종료.

	LRESULT ret; // 메시지 처리를 마친 후 반환되는 값을 받기 위한 변수.

	// 인스턴스에서 발생한 메시지를 반환함. 
	// 현재 실행중인 윈도우 인스턴스의 메시지 처리함수에서 메시지를 받음
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
bool winClass::SetWindow(
	HINSTANCE     hInst,
    const TCHAR*  pTitleName,
	UINT          iWidth,
	UINT          iHeight)
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
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

	// 클래스가 등록되지 않으면 false를 반환
	if (RegisterClassEx(&wc) == FALSE)	{
		return false;
	}

	// 윈도우 생성( 등록된 클래스를 사용해서 )
	m_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		L"MyWindow", pTitleName,
		m_dwStyle,
		0, 0, iWidth, iHeight,
		NULL, NULL, m_hInstance, NULL
	);

	// 윈도우가 생성되지 않으면 false를 반환
	if (m_hWnd == NULL)	{
		return false;
	}

	//생성된 윈도우의 핸들값을 전역변수에 대입.
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);	 //윈도우의 현재 위치와 크기를 구해서 두번째 인자로 전달된 RECT 구조체의 포인터에 넣어줌.
	GetClientRect(m_hWnd, &m_rtClient);	 //윈도우의 작업영역 크기를 계산해서 두번째 인자로 전달된 RECT 구조체의 포인터에 넣어줌.

	//화면 중앙에 윈도우 띄우기
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

//실질적인 내용 처리
bool winClass::Run()
{
	//초기화가 되지 않았으면 false를 반환.
	if (!GameInit()) {
		return false;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)	{
		//메시지가 있으면 메시지를 실행
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			//WM_QUIT 메시지를 받으면 반복문을 빠져나감.
			if (msg.message == WM_QUIT)	{
				break;
			}
		}
		//메시지가 없으면 GameRun()을 실행.
		else {
			GameRun();
		}
	}
	//반복문을 빠져나오면 GameRelease()를 실행.
	return GameRelease();
}

//윈도우에서 보내져오는 메시지 처리 함수.
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

//키 입력에 대한 메시지를 inputClass로 넘김
void winClass::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
}

winClass::~winClass()
{
}
