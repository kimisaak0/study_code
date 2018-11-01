#pragma once
#include "Header.h"

class Animal
{
protected:
	int speed;

public:
	virtual void  speak() = 0;
	virtual int   walk(int here) = 0;
	
	virtual void  setSpeed(int s) = 0;
	virtual int   getSpeed() = 0;
	virtual void  printSpeed() = 0;

	virtual void  printName() = 0;

public:

	//virtual Animal();		//생성자는 재정의될 수 없으니 가상함수로 만들수도 없다.
	Animal();
	virtual ~Animal();
};

