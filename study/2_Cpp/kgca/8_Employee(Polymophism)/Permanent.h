#pragma once

#include "Employee.h"

class Permanent : public Employee //������
{
	int m_iSalary;
	int m_iLevel;

public:
	//�߻�Ŭ������ ����� Ŭ������ �θ��� ���������Լ��� �� �����ؾ��Ѵ�. 
	int getPay() override;	//������

	Permanent(string name, int PL, int Level);
};

