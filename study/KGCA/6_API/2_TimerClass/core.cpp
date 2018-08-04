#include "core.h"



core::core()
{
}


bool    core::GameInit()
{
	m_Timer.Init();
	return true;
}
bool    core::GameRun()
{
	Sleep(1);
	m_Timer.Frame();
	m_Timer.Render();
	return true;
}
bool    core::GameRelease()
{
	m_Timer.Release();
	return true;
}

core::~core()
{
}
