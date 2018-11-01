#include "Dictionary.h"
#include "OriginalTemplate.h"

int main()
{

	cout << "한개의 데이터를 받는 경우" << endl << endl;

	cout << "int형 클래스 생성 및 테스트" << endl;
	Bag<int> xi;
	xi.add(8);
	xi.add(10);
	xi.add(2);
	xi.print();

	cout << "데이터 정렬" << endl;
	xi.sort();
	xi.print();

	cout << "char형 클래스 생성 및 테스트" << endl;
	Bag<char> xc;
	xc.add('b');
	xc.add('x');
	xc.add('e');
	xc.print();

	cout << "데이터 정렬" << endl;
	xc.sort();
	xc.print();

	cout << "uses partial specialization for pointer types." << endl;
	cout << "int*형 클래스 생성 및 테스트" << endl;

	Bag<int*> xp;
	
	//주소를 받아올 int형 변수 생성
	int* p = new int[2];
	p[0] = 8;
	p[1] = 100;
	int i = 3;
	int j = 87;
	int* pn = nullptr; //nullptr 생성

	xp.add(&i);
	xp.add(&j);
	xp.add(p);
	xp.add(p+1);
	xp.add(pn);   //들어가지 않음
	xp.print();

	cout << "데이터 정렬" << endl;
	xp.sort();
	xp.print();
	
	cout << "두개의 데이터를 받는 경우" << endl << endl;

	cout << "기본 템플릿 클래스 생성 및 테스트" << endl;
	dictionary<string, string>* dict = new dictionary<string, string>(10);
	
	cout << "데이터 한개 입력" << endl;
	dict->add("apple", "fruit");
	dict->print();

	cout << "데이터 세개 입력" << endl;
	dict->add("banana", "fruit");
	dict->add("dog", "animal");
	dict->print();

	cout << "특수화한 템플릿 클래스 생성 및 테스트" << endl;
	dictionary<int, string>* dict_s = new dictionary<int, string>(10);

	cout << "데이터 한개 입력" << endl;
	dict_s->add(100, "apple");
	dict_s->print();

	cout << "데이터 세개 입력" << endl;
	dict_s->add(101, "banana");
	dict_s->add(89, "dog");
	dict_s->add(103 , "cat");
	dict_s->print();

	dict_s->sort();
	cout << "데이터 정렬" << endl;
	cout << "sorted list :" << endl;
	dict_s->print();

}


