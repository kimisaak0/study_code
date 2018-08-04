#include "SalaryCalculator.h"

void SalaryCalculator::AddEmployee(Employee* Emp)
{
	m_aEmpList[m_iIndex++] = Emp;
}

void SalaryCalculator::ShowList()
{
	for (int iCnt = 0; iCnt < m_iIndex; iCnt++) {
		cout << "name : " << m_aEmpList[iCnt]->getName() << endl;
		cout << "Salary : " << m_aEmpList[iCnt]->getPay() << "¸¸¿ø" << endl;
		cout << endl;
	}
}
