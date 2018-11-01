#include "Permanent.h"

int Permanent::getPay()
{
	return (m_iSalary + ((m_iPositionLevel-1) * 1000) + (m_iLevel * 500)) / 12;
}

Permanent::Permanent(string Name, int PL, int Level) : Employee(Name, PL)
{
	m_iSalary = 2000;
	m_iLevel = Level;
}
