#pragma once

#include "Employee.h"

class Salaryman : public Employee //������
{
	int m_iSalary;
	int m_iLevel;

public:
	int getPay() override;

	Salaryman(string name, int PL, int Level);
};


