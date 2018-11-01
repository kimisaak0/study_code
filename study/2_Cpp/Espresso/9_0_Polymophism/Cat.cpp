#include "Cat.h"

void  Cat::speak()
{
	cout << "야옹" << endl;
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
	cout << "고양이는 할퀼 수 있다." << endl;
}

Cat::Cat()
{
	name = "고양이!";
	speed = 4;
}


Cat::~Cat()
{
}
