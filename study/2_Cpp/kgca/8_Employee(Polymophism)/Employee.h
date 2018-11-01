#pragma once

#include <iostream>
#include <string>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;


class Employee  //기본 추상 클래스
{

protected:
	string	m_sName;
	int		m_iPositionLevel;

public:

	string getName() const { return m_sName; }
	virtual int getPay() = 0;	//순수가상함수 //급여를 계산하는 함수

	void PrintData();


	Employee(string name, int PL);
};

