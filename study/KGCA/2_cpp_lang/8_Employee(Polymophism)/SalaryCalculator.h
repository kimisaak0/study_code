#pragma once

#include "Permanent.h"
#include "Temporary.h"
#include "Salaryman.h"

class SalaryCalculator //급여 계산 클래스
{
	Employee* m_aEmpList[10]; //employee클래스를 배열로 저장한다.
	int m_iIndex;             //배열에 저장된 멤버 수

public:
	void AddEmployee(Employee* Employee); //멤버를 추가하는 함수
	void ShowList();                      //저장된 멤버의 이름과 급여를 출력

	SalaryCalculator() : m_iIndex(0) {}
	
};

