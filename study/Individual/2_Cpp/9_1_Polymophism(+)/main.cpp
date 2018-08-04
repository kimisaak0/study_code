#include "DynamicChild.h"

int main()
{
	{
		cout << "가상 소멸자가 없으면" << endl;

		DynamicParents_noVirtual* x = new DynamicChild_noVirtual("--", "메모리 누수 있음");

		x->printString();

		delete x;

		cout << "자식 소멸자가 호출되지 않음" << endl;
	}




	cout << endl;


	{
		cout << "가상 소멸자가 있으면" << endl;

		DynamicParents* o = new DynamicChild("--", "메모리 누수 없음");

		o->printString();

		delete o;

		cout << "부모 생성자, 자식 생성자, 자식 소멸자, 부모 소멸자 다 호출 됨" << endl;
	}
}