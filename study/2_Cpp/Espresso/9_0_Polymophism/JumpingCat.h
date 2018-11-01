#pragma once
#include "Cat.h"
class JumpingCat :	public Cat
{
private:
	string name;

public:
	//오버라이딩 함수
	//부모에 vitual이 안 붙어있어도 부모의 부모에 붙은 virtual이 상속된다.
	void  speak();
	int   walk(int here);

	void  printName();

	//추가한 함수
	void jump();

public:
	JumpingCat();
	virtual ~JumpingCat();
};

