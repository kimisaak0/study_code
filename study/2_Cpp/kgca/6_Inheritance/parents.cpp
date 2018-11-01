#include "parents.h"

void parents::Character()
{
	cout << "차분한 성품" << endl;
}
void parents::Appearance()
{
	cout << "잘생긴 외모" << endl;
}
void parents::Wealth()
{
	cout << "재산 : " << money << "원" << endl;
}
parents::parents()
{
	money = 1000000000; //10억
	cout << "--------parent 생성자" << endl;
}

parents::parents(int money)
{
	this->money = money;
	cout << "--------parent 생성자" << endl;
}

parents::~parents()
{
	cout << "--------parent 소멸자" << endl;
}
