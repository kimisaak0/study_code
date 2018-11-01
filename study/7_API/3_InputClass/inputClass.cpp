#include "inputClass.h"

DWORD   inputClass::KeyCheck(DWORD dwKey)
{
	//typedef short SHORT;

	//GetKeyState()       - 동기적          호출된 시점에서 조사한 키상태를 메시지큐에 넣는다. 즉, 메시지 처리 루틴내에서 키입력을 처리해야한다.
	//GetAsyncKeyState()  - 비동기적        호출된 시점에서 키 상태를 조사하여, 메시지 큐를 거치지 않고 키입력을 리턴해준다.
	SHORT sKey = GetAsyncKeyState(dwKey);
	
	// 0x8000 : 이전X ~ 지금0
	// 0x8001 : 이전O ~ 지금O
	// 0x0000 : 이전X ~ 지금X
	// 0x0001 : 이전O ~ 지금X
	if (sKey & 0x8000) { // 지금 키를 눌렀는가?
		if (m_dwKeyState[dwKey] == KEY_FREE || //저장된 상태가 눌러져있지 않았거나,
			m_dwKeyState[dwKey] == KEY_UP) {   //키를 땠음.
				m_dwKeyState[dwKey] = KEY_DOWN;  //키를 눌렀다.
		}
		else {
				m_dwKeyState[dwKey] = KEY_HOLD; //키를 누르고 있다.
		}
	}
	else { //지금 키를 안 눌렀는가?
		if (m_dwKeyState[dwKey] == KEY_DOWN ||  //저장된 상태가 키를 눌렀거나.
			m_dwKeyState[dwKey] == KEY_HOLD) {  //키를 누르고 있음.
				m_dwKeyState[dwKey] = KEY_UP;   //키를 땠다.
		}
		else {
				m_dwKeyState[dwKey] = KEY_FREE; //키가 안 눌러져있다.
		}
	}
	return m_dwKeyState[dwKey];   //현재 키 상태 반환
}

//키 입력 상태를 저장하는 버퍼들을 0으로 초기화해줌.
bool    inputClass::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);
	ZeroMemory(m_dwBeforeMouseState, sizeof(DWORD) * 3);
	return true;
}

bool    inputClass::Frame()
{

	//스크린 좌표 : 전체 모니터 상을 기준으로 한 좌표
	//클라이언트 좌표 : 윈도우 객체를 기준으로 한 좌표

	GetCursorPos(&m_MousePos); // 마우스의 현재 스크린 좌표를 받아옴.
	ScreenToClient(g_hWnd, &m_MousePos); //스크린 좌표를 클라이언트 좌표로 변환

	//루프를 돌며 키보드 입력 상태를 조사함.
	for (int iKey = 0; iKey < 255; iKey++) {
		m_dwKeyState[iKey] = KeyCheck(iKey);
	}

	//마우스는 키체크 함수를 만들지 않았으므로 여기서 처리하는 것.

	//루프를 돌며 마우스 입력 상태를 조사함.
	for (int iButton = 0; iButton < 3; iButton++) {
		if (m_dwBeforeMouseState[iButton] == KEY_DOWN) {
			if (m_dwMouseState[iButton] == KEY_DOWN) {
					m_dwMouseState[iButton] = KEY_HOLD;
			}
		}
		if (m_dwBeforeMouseState[iButton] == KEY_UP) {
			if (m_dwMouseState[iButton] == KEY_UP) {
					m_dwMouseState[iButton] = KEY_FREE;
			}
		}
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}
	return true;
}

bool    inputClass::Render()
{
	return true;
}

bool    inputClass::Release()
{
	return true;
}

// 지정한 키의 상태를 반환.
DWORD   inputClass::Key(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}

//마우스 입력에 따라 현재 키 상태를 변경.
void    inputClass::MsgEvent(MSG msg)
{
	switch (msg.message) {
		case WM_LBUTTONDOWN: {
			m_dwMouseState[0] = KEY_DOWN;
		} break;

		case WM_LBUTTONUP: {
			m_dwMouseState[0] = KEY_UP;
		} break;

		case WM_RBUTTONDOWN: {
			m_dwMouseState[1] = KEY_DOWN;
		} break;

		case WM_RBUTTONUP: {
			m_dwMouseState[1] = KEY_UP;
		} break;

		case WM_MBUTTONDOWN: {
			m_dwMouseState[2] = KEY_DOWN;
		} break;

		case WM_MBUTTONUP: {
			m_dwMouseState[2] = KEY_UP;
		} break;
	}
}
