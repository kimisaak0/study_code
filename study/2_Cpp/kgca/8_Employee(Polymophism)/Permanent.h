#pragma once

#include "Employee.h"

class Permanent : public Employee //연봉제
{
	int m_iSalary;
	int m_iLevel;

public:
	//추상클래스를 상속한 클래스는 부모의 순수가상함수를 꼭 구현해야한다. 
	int getPay() override;	//재정의

	Permanent(string name, int PL, int Level);
};

