#pragma once
#include "Animal.h"

class Dog :	public Animal
{
private:
	string name;

public:
	//오버라이딩 함수
	//vitual속성은 상속되므로 재정의한 가상 함수는 vitual키워드가 안 붙어있어도 가상함수이다.
	void  speak();
	int   walk(int here);

	void  setSpeed(int s);
	int   getSpeed();
	void  printSpeed();
	
	void  printName();

	//추가한 함수
	virtual void  bite();

public:
	Dog();
	virtual ~Dog();
};

