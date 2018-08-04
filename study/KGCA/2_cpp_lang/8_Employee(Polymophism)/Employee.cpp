#include "Employee.h"

void Employee::PrintData()
{
	cout << "이름 : " << m_sName << "직급 : " << m_iPositionLevel << endl;
}

Employee::Employee(string name, int PL)
{
	m_sName = name;
	m_iPositionLevel = PL;
}
