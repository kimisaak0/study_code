#include "Employee.h"

void Employee::PrintData()
{
	cout << "�̸� : " << m_sName << "���� : " << m_iPositionLevel << endl;
}

Employee::Employee(string name, int PL)
{
	m_sName = name;
	m_iPositionLevel = PL;
}
