#include <iostream>
using std::cout;
using std::endl;
using std::cin;

//first, second, third, forth, fifth_functor, fifth_stl, sixth

#define problem

//a. �Լ� ��ü�� �Լ�ó�� ȣ�� ������ Ŭ���� ��ü�̴�. 
//b. �Լ� ��ü�� �Լ�ó�� ����� �� �����鼭�� ���¸� ���� �� �ִ�.
//c. ��ü�� �Լ�ó�� �����Ϸ��� '()'�����ڸ� �������ؾ� �Ѵ�.

#ifdef first

void print()
{
	cout << "���� �Լ�" << endl;
}

struct Functor
{
	void operator() ()
	{
		cout << "�Լ� ��ü" << endl;
	}
};

int main()
{
//	functor print;
//
//	//�̸��� ������ �Լ� ��ü�� �켱�õȴ�.
//	print();     //��� �Լ� ȣ�� (functor.operator()�� ����)
//	::print();   //���� �Լ� ȣ��

	Functor functor;

	print();    //���� �Լ� ȣ��
	functor();  //��� �Լ� ȣ��
}

#endif

//�Ű����� ����Ʈ�� ���� �Լ� ��ü �����

#ifdef second

void printAdd(int a, int b)
{
	cout << "���� �Լ� : ";
	printf("%d+%d=%d\n", a, b, a + b);
}

struct Functor
{
	void operator() (int a, int b)
	{
		cout << "�Լ� ��ü : ";
		printf("%d+%d=%d\n", a, b, a + b);
	}
};

int main()
{
	Functor functorAdd;

	printAdd(2, 4);
	functorAdd(2, 4);
}

#endif

//�Լ� ��ü�� ����
//1. �Ϲ� �Լ��ʹ� �ٸ��� �ٸ� ��� ������ ��� �Լ��� ���� �� �ִ�.
//2. �Լ� ��ü�� �ñ״�ó�� ���Ƶ� ��ü Ÿ���� �ٸ��� ���� �ٸ� Ÿ������ �ν��Ѵ�.
//3. �Ϲ� �Լ����� �Լ� ��ü�� �� ������.
//4. �Ϲ� �Լ��� �Լ� �����ʹ� �ζ��� �� �� ������ �Լ� ��ü�� �ζ��� �� �� �ְ�, �����Ϸ��� ���� ����ȭ �� �� �ִ�.

#ifdef third

class Adder
{
	int total;

public:
	explicit Adder(int n = 0) : total(n) {}
	
	//Ŭ���� ���ο� ���Ǿ����Ƿ� �ζ��� �Լ�.
	int operator() (int n) 
	{
		return total += n;
	}
};

class Miner
{
	int total;

public:
	explicit Miner(int n = 0) : total(n) {}
	int operator() (int n)
	{
		return total -= n;
	}
};

int main()
{
	//��� ������ ���� �Լ� ��ü
	Adder add(0); // �ʱ갪 0
	
	cout << add(10) << endl;
	cout << add(20) << endl;
	cout << add(30) << endl;

	//(�Լ�)��ü������ ���� 
	Adder add_a(10); // �ʱ갪 0
	Miner min(0); // �ʱ갪 0

	add = add_a;
	cout << add(0) << endl;

	//�ñ״�ó�� ������ ��ü Ÿ���� �ٸ��Ƿ� (�⺻������) ������ �ȵȴ�.
	//add = min;
}

#endif

//�ݹ� �Լ� ������ �Լ� ��ü�� ����Ͽ� ������ ��
//for_each() �˰��� �Լ��� �ƴ� �Լ� ��ü�� ������ ���� �ִٴ� ���� �����ش�.
//for_each() �˰����� ���ø����� �����Ǿ� �ֱ� �����̴�.

#ifdef forth

#include <algorithm>
using std::for_each;

//Ŭ���̾�Ʈ �Լ� ��ü��
struct Functor_a {
	void operator() (int a) {
		cout << a << ' ';
	}
};

struct Functor_b {
	void operator() (int b) {
		cout << b * b << ' ';
	}
};

struct Functor_c {
	void operator() (int c) {
		cout << "���� : " << c << endl;
	}
};

int main()
{
	int arr[5] = { 10,20,30,40,50 };

	for_each(arr, arr + 5, Functor_a());
	cout << endl << endl;
	for_each(arr, arr + 5, Functor_b());
	cout << endl << endl;
	for_each(arr, arr + 5, Functor_c());
	cout << endl << endl;
}


#endif

//bool���� ��ȯ�ϴ� less�� greater�Լ� ��ü. 
//������(predicate)

#ifdef fifth_functor

//�Լ���
bool greater_f(int a, int b)
{
	return a > b;
}

bool less_f(int a, int b)
{
	return a < b;
}


//�Լ� ��ü��
struct functor_greater
{
	bool operator() (int a, int b)
	{
		return a > b;
	}
};

struct functor_less
{
	bool operator() (int a, int b)
	{
		return a < b;
	}
};


int main()
{
	functor_greater greater;

	functor_less less;

	int a = 10;
	int b = 20;

	cout << "���� �Լ� ȣ��" << endl;
	cout << less_f(a, b) << endl;
	cout << greater_f(a, b) << endl;
	cout << endl;

	cout << "�Լ� ��ü ȣ��" << endl;
	cout << less(a, b) << endl;
	cout << greater(a, b) << endl;
	cout << endl;

	//functor_less()�� func_greater(0)�� �����ڸ� ȣ���� ��.
	cout << "�ӽ� ��ü�� �̿��� �Լ� ��ü ȣ��" << endl;
	cout << functor_less() (a,b) << endl;
	cout << functor_greater() (a, b) << endl;
	cout << endl;

	cout << "����� �Լ� ȣ��" << endl;
	cout << less.operator()(a, b) << endl;
	cout << greater.operator()(a, b) << endl;
	cout << endl;
}

#endif

//STL�� less�� greater �Լ� ��ü ���

#ifdef fifth_stl

#include <functional>
using std::less;
using std::greater;

//Ŭ���� ���ø����� �Ǿ��ִ�.
typedef less<int> Less;
typedef greater<int> Greater;

int main()
{
	Less iLess;
	Greater iGreater;

	int a = 10;
	int b = 20;

	cout << "�Լ� ��ü ȣ��" << endl;
	cout << iLess(a, b) << endl;
	cout << iGreater(a, b) << endl;
	cout << endl;

	cout << "�ӽ� ��ü�� �̿��� �Լ� ��ü ȣ��" << endl;
	cout << Less() (a, b) << endl;
	cout << Greater() (a, b) << endl;
	cout << endl;

	cout << "����� �Լ� ȣ��" << endl;
	cout << iLess.operator()(a, b) << endl;
	cout << iGreater.operator()(a, b) << endl;
	cout << endl;

	cout << "�ӽ� ��ü�� �̿��� ����� �Լ� ȣ��" << endl;
	cout << Less().operator()(a, b) << endl;
	cout << Greater().operator()(a, b) << endl;
	cout << endl;
}

#endif

//plus(), minus()
//�Լ�, �Լ� ��ü, STL ��

#ifdef sixth

#include <functional>
using std::plus;
using std::minus;

int plus_f(int a, int b)
{
	return a + b;
}

int minus_f(int a, int b)
{
	return a - b;
}

struct functor_plus
{
	int operator() (int a, int b)
	{
		return a + b;
	}
};

struct functor_minus
{
	int operator() (int a, int b)
	{
		return a - b;
	}
};

int main()
{
	functor_plus Plus;
	functor_minus Minus;

	int a = 10;
	int b = 20;

	cout << "�Լ� ���" << endl;
	cout << plus_f(a, b) << endl;
	cout << minus_f(a, b) << endl;
	cout << endl;

	cout << "�Լ� ��ü ���" << endl;
	cout << Plus(a, b) << endl;
	cout << Minus(a, b) << endl;
	cout << endl;

	cout << "STL ���" << endl;
	cout << plus<int>() (a, b) << endl;
	cout << minus<int>() (a, b) << endl;
	cout << endl;
}
#endif

//�Լ� ��ü�� ���� ����� ������ �� �˾Ƶ���.

//����Ǯ��
#ifdef problem

//1. �Լ�ó�� ȣ�� ������ Ŭ���� ��ü�� ������ �Լ� ��ü�� �մϴ�.
//2. �Լ�ó�� ȣ�� ������ Ŭ���� ��ü�� operator()�� �������Ͽ� �����մϴ�.


struct equal
{
	bool operator() (int a, int b)
	{
		if (a == b) { return true; }
		else { return false; }
	}
};

struct Adder
{
	int operator() (int a, int b)
	{
		return a + b;
	}
};

int main()
{
	equal cmp;

	if (cmp(10, 20)) {
		cout << "����" << endl;
	}
	else {
		cout << "�ٸ���" << endl;
	}

	Adder add;

	int sum = add(10, 20);
	cout << "sum = " << sum << endl;
}

#endif