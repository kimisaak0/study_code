//1.윈도우 프로그래밍 개요.
// - 윈도우 API(Application Programming Interface)는 윈도우 응용 프로그램에서 필요한 기능을 라이브러리 함수 호출 형태로 사용할 수 있게 해준다.
// - API에서 제공하는 기능은 주로 화면 제어, 그래픽 출력, 통신, 프로세스 관리, 오디오 처리, 보안 등이다.
// - 이들 기능을 이용한 응용 프로그램은 사용자가 사용하기 편한 GUI(Graphical User Interface)를 제공하고 네트워크나 데이터베이스(DB)를 이용할 수 있다.
// - 윈도우 프로그램은 기반이 되는 운영체제인 윈도우의 특징을 반영한다
//   1) GUI 기반 프로그램         : 생성된 윈도우에 메뉴, 툴바, 다양한 컨트롤을 표현해 사용자에게 편의성을 제공한다.
//   2) 이벤트 기반 프로그램      : 프로그램에 의해 감지되고 처리될 수 있는 동작이나 사건을 이벤트라 한다.
//                                 이벤트는 운영체제인 윈도우가 감지하고 윈도우는 감지한 이벤트에 대한 메시지를 윈도우 프로그램에게 보낸다.
//                                 윈도우 프로그램은 수신한 메시지에 따라 반응한다.
//   3) 멀티 스레드 기반 프로그램 : 윈도우는 멀티 스레드 개념을 이용해 복수의 작업을 동시에 처리하며 이 작업들이 메모리, CPU, 디스크 등을 공유한다.

//3. 윈도우 프로그램 구조
// - 윈도우 프로그램은 크게 WinMain(메시지 전송부)와 WndProc(메시지 처리부)으로 나뉜다.
//   1) WinMain에서는 윈도우를 만들고, 화면에 윈도우를 띄우며, 윈도우에서 발생하거나 응용 프로그램과 관련해 발생하는 모든 메시지를 전송하는 역할을 한다.
//     정확히는 메시지는 이벤트가 발생하면 오는 신호이고, 이 신호는 윈도우 커널이 보낸다. WinMain은 이를 하나씩 받아서 메시저 처리부로 보낸다.
//   2) WndProc에서는 메시지를 받아 메시지에 대해 약속된 반응을 보인다. 
//     메시지에는 마우스의 움직임이나 버튼 클릭에 따른 메시지, 키보드 눌림에 따른 메시지, 다양한 컨트롤에서 발생하는 메시지, 메뉴에서 발생하는 메시지 등이 있다.

#include <Windows.h>

//콜백함수 : 직접 호출하지 않아도 신호에 의해서 자동호출되는 함수.
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//WinMain은 5가지 일을 수행한다.
// 1) 윈도우 클래스 생성 : 
//      윈도우 클래스는 만들려는 윈도우의 속성을 저장하는 구조체다.
//
// 2) 클래스에 정보 등록 : 
//      구조체에 속성을 지정한 뒤 등록함. 
//      이 때, 여러개의 윈도우를 등록할 수도 있는데 각각을 구분하기 위해 각 윈도우 클래스에 고유한 이름을 부여해줘야 한다.
//
// 3) 윈도우 생성 : 
//      등록된 윈도우 중 하나를 지정해서 화면에 생성한다.
//
// 4) 발생한 메시지를 메시지 큐에 저장 : 
//      화면에 나타난 윈도우에서 이벤트가 발생하면, 이에 대한 메시지를 커널이 프로그램에 보낸다. 
//      프로그램은 이 메시지를 순서대로 메시지 큐에 저장한다.
//
// 5) 메시지 큐에서 메시지를 꺼내서 WndProc() 함수에 보낸다.

int WINAPI WinMain(
	HINSTANCE  hInst,         // 프로그램에 OS커널이 부여해주는 핸들(ID), 프로그램이 수행될 때 부여받는다.
	HINSTANCE  hPrevInst,     // 호환성을 위해서만 존재하는 인수, 현재는 항상 NULL이며 더이상 사용되지 않는다. 
	LPSTR      lpCmdLine,     // 명령행으로 입력된 프로그램 인수, 프로그램 실행시 외부에서 넘어오는 문자열이다. 콘솔 main의 argv값과 비슷한 것.
	int        nCmdShow       // 윈도우가 화면에 출력될 때 형태를 정의하는 인수. 커널에서 넘어온다.  
)
{
	HWND         hwnd;          // 윈도우 핸들
	MSG          msg;           // 메시지 구조체
	WNDCLASSEX   WndClass;      // 윈도우 구조체

	WndClass.cbSize = sizeof(WNDCLASSEX);                         // 구조체 크기
	WndClass.style = CS_HREDRAW | CS_VREDRAW;                     // 출력 형태
	WndClass.lpfnWndProc = WndProc;                               // 메시지 처리에 사용할 함수 이름. (중요!) (즉, 각각의 윈도우 구조체마다 서로 다른 메시지 처리 함수를 사용할 수도 있다.)
	WndClass.cbClsExtra = 0;                                      // 클래스 여분 메모리
	WndClass.cbWndExtra = 0;                                      // 윈도우 여분 메모리
	WndClass.hInstance = hInst;                                   // 윈도우 인스턴스 핸들 값. (중요!)
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // 아이콘
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);               // 커서
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경색
	WndClass.lpszMenuName = NULL;                                 // 메뉴 이름
	WndClass.lpszClassName = L"MyWinodw";                         // 클래스 이름 (중요!)
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);           // 작은 아이콘

	//윈도우 클래스 등록
	RegisterClassEx(&WndClass);
	
	hwnd =	                               //CreateWindow()가 반환하는 윈도우 핸들값을 저장
		CreateWindow(                      //등록한 클래스로 윈도우를 생성하는 함수
			L"MyWinodw",                   //위에서 등록한 클래스 이름
			L"Windows",                    //타이틀바에 적을 내용
			WS_OVERLAPPEDWINDOW,           //윈도우 스타일
			CW_USEDEFAULT,                 //윈도우가 표시될 x좌표
			CW_USEDEFAULT,                 //윈도우가 표시될 y좌표
			CW_USEDEFAULT,                 //윈도우 가로 크기 (넓이)
			CW_USEDEFAULT,                 //윈도우 세로 크기 (높이)
			NULL,                          //이 윈도우를 생성한 부모 윈도우의 핸들값
			NULL,                          //메뉴 핸들
			hInst,                         //이 윈도우를 생성한 프로그램의 핸들값
			NULL                           //생성된 윈도우의 정보
		);


	ShowWindow(hwnd, SW_SHOW);      	//윈도우를 화면에 나타낼 방법을 지정.
	UpdateWindow(hwnd);                 //윈도우에 WM_PAINT메시지를 보내 화면에 기본 출력을 한다.

	//메시지 처리 과정
	// 1) 이벤트 발생
	// 2) 윈도우 커널이 이벤트 감지
	// 3) 커널에서 프로그램으로 메시지 전달. (기본적으로 메시지 큐에 쌓임)
	// 4) 메시지 큐에서 메시지 꺼냄
	// 5) 꺼낸 메시지를 메시지 처리 함수로 보냄.
	// 6) 지정된 반응 처리.


	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

//메시지 처리 함수 (함수명은 바뀔 수 있다.)
LRESULT CALLBACK WndProc(   
	HWND hwnd,      //이벤트를 처리할 윈도우의 핸들값
	UINT iMsg,      //받은 메시지의 번호
	WPARAM wParam,  //메시지에 대한 추가 정보 1
	LPARAM lParam   //메시지에 대한 추가 정보 2
)
{
	//특별히 처리할 메시지는 switch문에서 관리.
	switch (iMsg) {
		case WM_CREATE: 
			break;

		//윈도우를 닫을때 프로그램을 종료시키기 위해서는
		case WM_DESTROY:
			//아래의 함수를 호출해줘야 한다. 
			PostQuitMessage(0);
			break;
	}

	//나머지 메시지들은 디폴트 함수로 처리한다.
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
