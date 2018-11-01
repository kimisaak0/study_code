#pragma once

#include <iostream>
#include <string>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;


class Employee  //�⺻ �߻� Ŭ����
{

protected:
	string	m_sName;
	int		m_iPositionLevel;

public:

	string getName() const { return m_sName; }
	virtual int getPay() = 0;	//���������Լ� //�޿��� ����ϴ� �Լ�

	void PrintData();


	Employee(string name, int PL);
};

