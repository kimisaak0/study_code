#include <windows.h>

HWND g_hWnd;
HINSTANCE g_hInst;

//메시지를 처리하는 함수 (OS에서 호출함)
LRESULT CALLBACK WndProc(HWND hWnd,      // 생성된 윈도우의 핸들값
	                     UINT msg,       // 메시지 번호 값. 매크로로 정의되어 있다.
	                     WPARAM wParam,  // 메시지 번호 값에 따라 전달되는 추가 정보 1. 
	                     LPARAM lParam)  // 메시지 번호 값에 따라 전달되는 추가 정보 2. 
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
		}break;
	}
	//기본 메시지 처리 함수. 위에서 따로 처리하지 않은 모든 메시지를 처리해준다.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void GameInit();
void GameRun();
void GameRelease();

int WINAPI WinMain(HINSTANCE  hInst,         // 프로그램에 OS커널이 부여해주는 핸들(ID), 프로그램이 수행될 때 부여받는다.
                   HINSTANCE  hPrevInst,     // 호환성을 위해서만 존재하는 인수, 현재는 항상 NULL이며 더이상 사용되지 않는다. 
	               LPSTR      lpCmdLine,     // 명령행으로 입력된 프로그램 인수, 프로그램 실행시 외부에서 넘어오는 문자열이다. 콘솔 main의 argv값과 비슷한 것.
	               int        nCmdShow)      // 윈도우가 화면에 출력될 때 형태를 정의하는 인수. 커널에서 넘어온다.  
{
	g_hInst = hInst;

	// 윈도우 클래스 등록
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));     //wc객체를 전부 0으로 초기화

	wc.cbSize = sizeof(WNDCLASSEX);         // 구조체 크기
	wc.style = CS_HREDRAW | CS_VREDRAW;     // 출력 형태
	wc.lpfnWndProc = WndProc;               // 프로시저 함수
	wc.hInstance = hInst;                   // 윈도우 인스턴스
	wc.lpszClassName = L"MyWindow";         // 클래스 이름 (중요! 윈도우를 만들때 이 이름을 사용한다!)

	if (RegisterClassEx(&wc) == FALSE) 	{   // 커널에 윈도우 클래스를 등록.
		return 1;
	}

	//// 윈도우 생성( 등록된 클래스를 사용해서 )

	//윈도우를 생성하는 함수 (윈도우 핸들값을 반환한다.)
	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW,       // 생성될 윈도우의 확장 스타일 지정
		                       L"MyWindow",           // 윈도우 클래스 이름. (위에서 만든 것을 쓰거나 미리 정의되어 있는 시스템 전역 클래스를 쓸 수도 있다.)
		                       L"KGCA SAMPLES",       // 윈도우 제목표시줄에 적힐 내용
		                       WS_OVERLAPPEDWINDOW,   // 생성될 윈도우의 스타일 지정 (타이틀바가 있는지, 최소화된 상태인지 등...)
                               0, 0,                  // 윈도우가 생성될 x, y 좌표
		                       800, 600,              // 생성된 윈도우의 수평 크기와 수직 크기
		                       NULL,                  // 부모 윈도우 핸들, 차일드 윈도우에서는 꼭 지정해줘야 함.
		                       NULL,                  // 메뉴 핸들
		                       hInst,                 // 응용 프로그램 인스턴스. 윈도우를 생성할 인스턴스 핸들 지정. 인스턴스가 종료될 때 윈도우도 같이 파괴된다.
		                       NULL                   // 생성 윈도우 정보. WM_CREATE 메시지의 lParam으로 전달될 CREATESTRUCT 구조체들의 포인터.
     );

	g_hWnd = hWnd;

	if (hWnd == NULL)
	{
		return 1;
	}

	//윈도우의 ShowState를 지정
	// hWnd : 나타낼 윈도우 핸들값, nCmdShow : ShowState값
	ShowWindow(hWnd, SW_SHOW);       

	GameInit();


	
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (1) {
		// GetMessage  : 메세지 큐에 메세지가 있는 경우에만 메세지 반환. 없으면 반환 없음.
		// PeekMessage : 메세지 큐에 메세지가 있으면 메세지 반환,없으면 false를 반환

		if (PeekMessage(&msg,        // lpMsg : 메시지가 저장된 MSG 구조체에 대한 포인터,
			            NULL,        // hWnd  : 메시지가 발생한 윈도우의 핸들 
			            0, 0,        // wMsgFilterMin, WMsgFilterMax : 조사할 메시지의 최소값과 최대값. 이 두 값을 사용하면 일정한 범위에 속하는 메시지만 조사할 수 있다.(메시지 필터링)
			            PM_REMOVE)) { // wRemoveMsg : 조사할 메시지를 처리할 방법을 지정하는 플래그.

			TranslateMessage(&msg);  // 조사한 메시지를 문자 메시지로 변환하는 함수.
			DispatchMessage(&msg);   // 메시지를 처리할 윈도우로 보내는 함수.

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
	// 지형, 오브젝트, 이펙트, UI 초기화, 로딩
	MessageBox(NULL, L"게임초기화.", L"게임실행", MB_OK);
}
void GameRun()
{
	//이미지 출력 테스트 용 (..)
	HDC onHdc = GetDC(g_hWnd);
	HDC offHdc = CreateCompatibleDC(onHdc);

	HBITMAP nowBmp = (HBITMAP)LoadImage(g_hInst, L"topVeiw_Water_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nowBmp == NULL) {
		MessageBox(g_hWnd, L"이미지 로드 실패", L"이미지 로드 실패", MB_OK);
		return;
	}

	HBITMAP oldBmp = (HBITMAP)SelectObject(offHdc, nowBmp);

	BitBlt(onHdc, 0, 0, 50, 50, offHdc, 0, 0, SRCCOPY);


	//MessageBox(NULL, L"게임 실행중.", L"게임실행", MB_OK);
}
void GameRelease()
{
	// 지형, 오브젝트, 이펙트, UI 소멸
	MessageBox(NULL, L"게임 종료.", L"게임실행", MB_OK);
}