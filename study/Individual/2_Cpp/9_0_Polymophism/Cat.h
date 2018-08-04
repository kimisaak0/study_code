#pragma once
#include "Animal.h"

class Cat :	public Animal
{
private:
	string name;

public:
	//�������̵� �Լ�
	//vitual�Ӽ��� ��ӵǹǷ� �������� ���� �Լ��� vitualŰ���尡 �� �پ��־ �����Լ��̴�.
	void  speak();
	int   walk(int here);

	void  setSpeed(int s);
	int   getSpeed();
	void  printSpeed();

	void  printName();

	//�߰��� �Լ�
	virtual void  claw();

public:
	Cat();
	virtual ~Cat();
};

