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

	//virtual Animal();		//�����ڴ� �����ǵ� �� ������ �����Լ��� ������� ����.
	Animal();
	virtual ~Animal();
};

