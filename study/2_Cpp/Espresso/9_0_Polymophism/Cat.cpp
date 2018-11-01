#include "Cat.h"

void  Cat::speak()
{
	cout << "�߿�" << endl;
}

int   Cat::walk(int here)
{
	return here + speed;
}

void  Cat::setSpeed(int s)
{
	speed = s;
}

int   Cat::getSpeed() 
{
	return speed;
}

void  Cat::printSpeed()
{
	cout << speed << endl;
}

void  Cat::printName()
{
	cout << name << endl;
}

void  Cat::claw()
{
	cout << "����̴� ���� �� �ִ�." << endl;
}

Cat::Cat()
{
	name = "�����!";
	speed = 4;
}


Cat::~Cat()
{
}
