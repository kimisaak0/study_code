#include "Temporary.h"

int Temporary::getPay()
{
	return m_iTime * (int)pow(2, m_iPositionLevel-1);
}

Temporary::Temporary(string Name, int PL, int Time) : Employee(Name, PL)
{
	m_iTime = Time;
}
