#include "child.h"

void child::Humanity()
{
	cout << "��ġ�� �ΰ���" << endl;
}

void child::Character()
{
	cout << "�� ���� ��ǰ" << endl;
}
void child::Apperance()
{
	parents::Appearance();		  //��� Ŭ�������� ������ ���
	cout << "��ĥ�� Ű" << endl;  //�Ļ� Ŭ�������� Ȯ��� ���
}

//child::child()
//{
//	cout << "child ������" << endl;
//}

child::child() : parents(1000)
{
	cout << "--------child ������" << endl;
}

child::~child()
{
	cout << "--------child �Ҹ���" << endl;
}
