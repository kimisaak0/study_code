#include "Dog.h"

//클래스 외부에서는 virtual키워드를 쓸 수 없다.
void  Dog::speak()
{
	cout << "멍멍" << endl;
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
	cout << "개는 물수 있다." << endl;
}


Dog::Dog()
{
	name = "개!";
	speed = 3;
}


Dog::~Dog()
{
}
