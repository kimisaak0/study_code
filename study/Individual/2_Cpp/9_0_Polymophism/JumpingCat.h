#pragma once
#include "Cat.h"
class JumpingCat :	public Cat
{
private:
	string name;

public:
	//�������̵� �Լ�
	//�θ� vitual�� �� �پ��־ �θ��� �θ� ���� virtual�� ��ӵȴ�.
	void  speak();
	int   walk(int here);

	void  printName();

	//�߰��� �Լ�
	void jump();

public:
	JumpingCat();
	virtual ~JumpingCat();
};

