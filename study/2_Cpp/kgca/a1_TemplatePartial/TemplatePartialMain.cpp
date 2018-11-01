#include "Dictionary.h"
#include "OriginalTemplate.h"

int main()
{

	cout << "�Ѱ��� �����͸� �޴� ���" << endl << endl;

	cout << "int�� Ŭ���� ���� �� �׽�Ʈ" << endl;
	Bag<int> xi;
	xi.add(8);
	xi.add(10);
	xi.add(2);
	xi.print();

	cout << "������ ����" << endl;
	xi.sort();
	xi.print();

	cout << "char�� Ŭ���� ���� �� �׽�Ʈ" << endl;
	Bag<char> xc;
	xc.add('b');
	xc.add('x');
	xc.add('e');
	xc.print();

	cout << "������ ����" << endl;
	xc.sort();
	xc.print();

	cout << "uses partial specialization for pointer types." << endl;
	cout << "int*�� Ŭ���� ���� �� �׽�Ʈ" << endl;

	Bag<int*> xp;
	
	//�ּҸ� �޾ƿ� int�� ���� ����
	int* p = new int[2];
	p[0] = 8;
	p[1] = 100;
	int i = 3;
	int j = 87;
	int* pn = nullptr; //nullptr ����

	xp.add(&i);
	xp.add(&j);
	xp.add(p);
	xp.add(p+1);
	xp.add(pn);   //���� ����
	xp.print();

	cout << "������ ����" << endl;
	xp.sort();
	xp.print();
	
	cout << "�ΰ��� �����͸� �޴� ���" << endl << endl;

	cout << "�⺻ ���ø� Ŭ���� ���� �� �׽�Ʈ" << endl;
	dictionary<string, string>* dict = new dictionary<string, string>(10);
	
	cout << "������ �Ѱ� �Է�" << endl;
	dict->add("apple", "fruit");
	dict->print();

	cout << "������ ���� �Է�" << endl;
	dict->add("banana", "fruit");
	dict->add("dog", "animal");
	dict->print();

	cout << "Ư��ȭ�� ���ø� Ŭ���� ���� �� �׽�Ʈ" << endl;
	dictionary<int, string>* dict_s = new dictionary<int, string>(10);

	cout << "������ �Ѱ� �Է�" << endl;
	dict_s->add(100, "apple");
	dict_s->print();

	cout << "������ ���� �Է�" << endl;
	dict_s->add(101, "banana");
	dict_s->add(89, "dog");
	dict_s->add(103 , "cat");
	dict_s->print();

	dict_s->sort();
	cout << "������ ����" << endl;
	cout << "sorted list :" << endl;
	dict_s->print();

}


