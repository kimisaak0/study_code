#include "Animal.h"

//어차피 오버라이딩 해야하는 함수이므로 이렇게 안에 내용이 있어도 의미가 없다.
//순수 가상으로 정의하고 내용을 만들면?
void   Animal::setSpeed(int s)
{
	speed = s;
}



Animal::Animal()
{
	speed = 0;
}

Animal::~Animal()
{
}