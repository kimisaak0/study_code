#include "parents.h"

void parents::Character()
{
	cout << "������ ��ǰ" << endl;
}
void parents::Appearance()
{
	cout << "�߻��� �ܸ�" << endl;
}
void parents::Wealth()
{
	cout << "��� : " << money << "��" << endl;
}
parents::parents()
{
	money = 1000000000; //10��
	cout << "--------parent ������" << endl;
}

parents::parents(int money)
{
	this->money = money;
	cout << "--------parent ������" << endl;
}

parents::~parents()
{
	cout << "--------parent �Ҹ���" << endl;
}
