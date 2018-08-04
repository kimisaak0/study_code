#pragma once
#include "parents.h"

class child :public parents
{
public:
	void Humanity();	//추가된 멤버함수
	void Character();	//수정된 멤버함수
	void Apperance();	//확장된 멤버함수

	child();
	~child();
};

