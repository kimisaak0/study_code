#include "core.h"

core::core()
{
}


//�ʱ�ȭ (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
bool    core::GameInit()
{
	m_Timer.Init();
	I_Input.Init();
	Init();

	return true;
}

//��� (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
bool    core::GameFrame()
{
	m_Timer.Frame();
	I_Input.Frame();
	Frame();

	return true;
}

//�׸��� (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
bool    core::GameRender()
{
	m_Timer.Render();
	I_Input.Render();
	Render();

	return true;
}

// ���α׷� ������, ����ϰ� �׸���.
bool    core::GameRun()
{
	Sleep(1);
	GameFrame();
	GameRender();
	return true;
}

//����, ���� (Ÿ�̸Ӷ� �Է�Ŭ���� ���� coreŬ������ �Լ��� �ϴ� ���� ����.)
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
