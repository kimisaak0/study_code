#include "JumpingCat.h"

//�������̵� �Լ�
void  JumpingCat::speak()
{
	cout << "grrrrrrr" << endl;
}

int   JumpingCat::walk(int here)
{
	//�θ��� ��� ������ �״�� �� �� �ִ�.
	return here + speed;
}

void  JumpingCat::printName()
{
	cout << name << endl;
}

//�߰��� �Լ�
void JumpingCat::jump()
{
	cout << "JumpingCat�� ������ �� �� �ִ�!" << endl;
}

JumpingCat::JumpingCat()
{
	//��� ������ �������̵� �ϸ� �ڽ� Ŭ������ ��� ������ �θ� Ŭ������ ��� ������ �̸��� ������ �����Եȴ�.
	name = "���� Ĺ!";
	//�θ��� ��� ������ ���Ӱ� �ʱ�ȭ�ؼ� �״�� �� �� �ִ�.
	speed = 5;
}


JumpingCat::~JumpingCat()
{
}
