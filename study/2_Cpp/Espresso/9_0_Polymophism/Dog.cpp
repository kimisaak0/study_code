#include "Dog.h"

//Ŭ���� �ܺο����� virtualŰ���带 �� �� ����.
void  Dog::speak()
{
	cout << "�۸�" << endl;
}

int   Dog::walk(int here)
{
	return here + speed;

}

void  Dog::setSpeed(int s)
{
	speed = s;
}
int   Dog::getSpeed()
{
	return speed;
}
void  Dog::printSpeed()
{
	cout << speed << endl;
}

void  Dog::printName()
{
	cout << name << endl;
}

void  Dog::bite()
{
	cout << "���� ���� �ִ�." << endl;
}


Dog::Dog()
{
	name = "��!";
	speed = 3;
}


Dog::~Dog()
{
}
