#include "DynamicChild.h"

int main()
{
	{
		cout << "���� �Ҹ��ڰ� ������" << endl;

		DynamicParents_noVirtual* x = new DynamicChild_noVirtual("--", "�޸� ���� ����");

		x->printString();

		delete x;

		cout << "�ڽ� �Ҹ��ڰ� ȣ����� ����" << endl;
	}




	cout << endl;


	{
		cout << "���� �Ҹ��ڰ� ������" << endl;

		DynamicParents* o = new DynamicChild("--", "�޸� ���� ����");

		o->printString();

		delete o;

		cout << "�θ� ������, �ڽ� ������, �ڽ� �Ҹ���, �θ� �Ҹ��� �� ȣ�� ��" << endl;
	}
}