#pragma once
#include <iostream>
using std::cout;
using std::endl;


class parents
{
private:
	int money;

public:
	void Character();   //��ǰ ���
	void Appearance();  //�ܸ� ���
	void Wealth();      //��� ���

	parents();          //������
	parents(int money); //������
	virtual ~parents(); //�Ҹ���
};

