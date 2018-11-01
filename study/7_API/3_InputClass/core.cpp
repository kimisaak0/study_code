#include "core.h"

core::core()
{
}


//초기화 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameInit()
{
	m_Timer.Init();
	I_Input.Init();
	Init();

	return true;
}

//계산 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameFrame()
{
	m_Timer.Frame();
	I_Input.Frame();
	Frame();

	return true;
}

//그리기 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameRender()
{
	m_Timer.Render();
	I_Input.Render();
	Render();

	return true;
}

// 프로그램 돌리기, 계산하고 그린다.
bool    core::GameRun()
{
	Sleep(1);
	GameFrame();
	GameRender();
	return true;
}

//종료, 삭제 (타이머랑 입력클래스 아직 core클래스의 함수는 하는 일이 없다.)
bool    core::GameRelease()
{
	m_Timer.Release();
	I_Input.Release();
	Release();
	return true;
}

core::~core()
{
}
