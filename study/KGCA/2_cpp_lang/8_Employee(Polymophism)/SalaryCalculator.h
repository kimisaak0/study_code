#pragma once

#include "Permanent.h"
#include "Temporary.h"
#include "Salaryman.h"

class SalaryCalculator //�޿� ��� Ŭ����
{
	Employee* m_aEmpList[10]; //employeeŬ������ �迭�� �����Ѵ�.
	int m_iIndex;             //�迭�� ����� ��� ��

public:
	void AddEmployee(Employee* Employee); //����� �߰��ϴ� �Լ�
	void ShowList();                      //����� ����� �̸��� �޿��� ���

	SalaryCalculator() : m_iIndex(0) {}
	
};

