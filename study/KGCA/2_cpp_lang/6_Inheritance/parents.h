#pragma once
#include <iostream>
using std::cout;
using std::endl;


class parents
{
private:
	int money;

public:
	void Character();   //성품 출력
	void Appearance();  //외모 출력
	void Wealth();      //재산 출력

	parents();          //생성자
	parents(int money); //생성자
	virtual ~parents(); //소멸자
};

