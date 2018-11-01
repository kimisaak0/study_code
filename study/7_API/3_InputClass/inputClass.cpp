#include "inputClass.h"

DWORD   inputClass::KeyCheck(DWORD dwKey)
{
	//typedef short SHORT;

	//GetKeyState()       - ������          ȣ��� �������� ������ Ű���¸� �޽���ť�� �ִ´�. ��, �޽��� ó�� ��ƾ������ Ű�Է��� ó���ؾ��Ѵ�.
	//GetAsyncKeyState()  - �񵿱���        ȣ��� �������� Ű ���¸� �����Ͽ�, �޽��� ť�� ��ġ�� �ʰ� Ű�Է��� �������ش�.
	SHORT sKey = GetAsyncKeyState(dwKey);
	
	// 0x8000 : ����X ~ ����0
	// 0x8001 : ����O ~ ����O
	// 0x0000 : ����X ~ ����X
	// 0x0001 : ����O ~ ����X
	if (sKey & 0x8000) { // ���� Ű�� �����°�?
		if (m_dwKeyState[dwKey] == KEY_FREE || //����� ���°� ���������� �ʾҰų�,
			m_dwKeyState[dwKey] == KEY_UP) {   //Ű�� ����.
				m_dwKeyState[dwKey] = KEY_DOWN;  //Ű�� ������.
		}
		else {
				m_dwKeyState[dwKey] = KEY_HOLD; //Ű�� ������ �ִ�.
		}
	}
	else { //���� Ű�� �� �����°�?
		if (m_dwKeyState[dwKey] == KEY_DOWN ||  //����� ���°� Ű�� �����ų�.
			m_dwKeyState[dwKey] == KEY_HOLD) {  //Ű�� ������ ����.
				m_dwKeyState[dwKey] = KEY_UP;   //Ű�� ����.
		}
		else {
				m_dwKeyState[dwKey] = KEY_FREE; //Ű�� �� �������ִ�.
		}
	}
	return m_dwKeyState[dwKey];   //���� Ű ���� ��ȯ
}

//Ű �Է� ���¸� �����ϴ� ���۵��� 0���� �ʱ�ȭ����.
bool    inputClass::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	ZeroMemory(m_dwMouseState, sizeof(DWORD) * 3);
	ZeroMemory(m_dwBeforeMouseState, sizeof(DWORD) * 3);
	return true;
}

bool    inputClass::Frame()
{

	//��ũ�� ��ǥ : ��ü ����� ���� �������� �� ��ǥ
	//Ŭ���̾�Ʈ ��ǥ : ������ ��ü�� �������� �� ��ǥ

	GetCursorPos(&m_MousePos); // ���콺�� ���� ��ũ�� ��ǥ�� �޾ƿ�.
	ScreenToClient(g_hWnd, &m_MousePos); //��ũ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ

	//������ ���� Ű���� �Է� ���¸� ������.
	for (int iKey = 0; iKey < 255; iKey++) {
		m_dwKeyState[iKey] = KeyCheck(iKey);
	}

	//���콺�� Űüũ �Լ��� ������ �ʾ����Ƿ� ���⼭ ó���ϴ� ��.

	//������ ���� ���콺 �Է� ���¸� ������.
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

// ������ Ű�� ���¸� ��ȯ.
DWORD   inputClass::Key(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}

//���콺 �Է¿� ���� ���� Ű ���¸� ����.
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
