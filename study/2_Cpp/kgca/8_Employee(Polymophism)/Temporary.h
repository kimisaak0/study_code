#pragma once

#include "Employee.h"

class Temporary : public Employee //½Ã±ÞÁ¦
{
	int m_iTime;

public:
	int getPay() override;

	Temporary(string name, int PL, int Time);
};

