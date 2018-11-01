#include "Salaryman.h"

int Salaryman::getPay()
{
	return (m_iSalary + ((m_iPositionLevel-1) * 20) + (m_iLevel * 5));
}

Salaryman::Salaryman(string Name, int PL, int Level) : Employee(Name, PL)
{
	m_iSalary = 200;
	m_iLevel = Level;
}

