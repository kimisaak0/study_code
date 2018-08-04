

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

//first, second, third, forth, fifth_call, fifth_callback, sixth_fp, sixth_stl

#define sixth_stl

//1. �Լ��� �̸��� �Լ��� �����ϴ� ���� �ּҸ� �ǹ��Ѵ�.
//2. �Լ� �����ʹ� �Լ��� ���� �ּ� �� �Լ��� �̸��� �����ϴ� �������̴�.
//3. �Լ� �����ʹ� �Լ� �ñ״�ó�� ���� �ͳ��� ¦�� �̷��.


#ifdef first

void print(int n) {
	cout << "���� : " << n << endl;
}

int print() {
	int iNum = 0;
	cout << "print" << endl;
	return iNum;
}

int add(int a, int b)
{
	return a + b;
}

int main()
{
	//void print(int n)�� �Լ� ������ ����
	void(*pf)(int);
	//int print()�� �Լ� ������ ����
	int(*ppf)();
	//int add(int a, int b)�� �Լ� ������ ����
	int(*padd)(int, int);

	//�Լ��� �̸��� �Լ��� ���� �ּ�
	pf = print;
	ppf = print; 
	//�����ε�� �Լ��� �ñ״�ó�� �°� �˾Ƽ� ���еǼ� ����.

	//�ñ״�ó�� ���� ���� �Լ��� ���� �� ����.
	//pf = add;
	//ppf = add;
	padd = add;

	print(10);     //1. �Լ� �̸��� �̿��� �Լ� ȣ��
	pf(10);        //2. �Լ� �����͸� �̿��� �Լ� ȣ�� - 1
	(*pf)(10);     //3. �Լ� �����͸� �̿��� �Լ� ȣ�� - 2
	//��� ���� ���
	 
	cout << endl;
	//�Լ��� ���� �ּҸ� ���� ������ �����ε� �Ǿ� �־ ��� �о�;� �ϴ��� �� �� ���� ��Ȳ
	//cout << print << endl;
	
	cout << add << endl;
	cout << padd << endl;
	cout << *padd << endl;
	//��� ���� ���	
}


#endif

//C++�� �Լ� -> 1. ���� �Լ�, 2. ��� �Լ�
//1. ���� �Լ� -> 1-1. ���� �Լ�, 1-2. namespace���� ���� �Լ�, 1-3. static ��� �Լ�
//2. ��� �Լ� -> 2-1. ��ü�� ȣ��, 2-2. �ּҷ� ȣ��
//3. ��� �Լ� ȣ�� ��� -> 3-1. ���� �Լ� ȣ��, 3-2. ��ü�� ��� �Լ� ȣ��, 3-3. ��ü�� �ּҷ� ��� �Լ� ȣ��

#ifdef second

void print()
{
	cout << "���� �Լ� print()" << endl;
}

class point
{
public:
	void print()
	{
		cout << "����Լ� print" << endl;
	}
};

int main()
{
	point pt;
	point* ppt = &pt;

	print();        //1. ���� �Լ� ȣ��;
	pt.print();     //2. ��ü�� ��� �Լ� ȣ��
	ppt->print();   //3. �ּҷ� ��� �Լ� ȣ��
}

#endif

//���� �Լ� �����ʹ� �Լ� �ñ״�ó�� ������ ���� ������ �� ������
//���� �Լ�, namespace���� ���� �Լ�, static ��� �Լ��� ��� �Լ� ȣ�� �Ծ��� ���Ƽ� �Լ� �����͵� ����.

#ifdef third

void print()
{
	cout << "���� �Լ�" << endl;
}

namespace a
{
	void print()
	{
		cout << "namespace A ���� �Լ�" << endl;
	}
}

class b
{
public:
	static void print() {
		cout << "b Ŭ������ ���� ��� �Լ�" << endl;
	}
};

int main()
{
	void(*pf)();               //���� �Լ� ������ ����
				            
	print();                   //1. namespace ���� ���� �Լ� ȣ��
	a::print();                //2. namespace a�� ���� �Լ� ȣ��
	b::print();                //3. class b�� ���� ��� �Լ� ȣ��

	cout << endl;

	pf = print;      pf();     //1. �Լ� �����ͷ� namespace ���� ���� �Լ� ȣ��
	pf = a::print;   pf();     //2. �Լ� �����ͷ� namespace a�� ���� �Լ� ȣ��
	pf = b::print;   pf();     //3. �Լ� �����ͷ� class b�� ���� ��� �Լ� ȣ��
}

#endif

////C++���� ���� �Լ��� ���� �⺻���� �Լ� ȣ�� �Ծ��� cdecl�̰�, ��� �Լ��� thiscall�� ����Ѵ�.
//�׷��� ���� �Լ� �����Ϳ� ��� �Լ� �����͸� �����ϴ� ����� �ٸ���.

//��� �Լ� �����ʹ� �Լ� ������ ���� � Ŭ������ ��� �Լ��� ����ų ������ Ŭ���� �̸��� �����ؾ� �Ѵ�.

//�ñ״�ó�� void b::print(int n)�� ��� �Լ� �����ʹ� void (b::*pf)(int)�� �����Ѵ�.

//�Լ��� ȣ���� ��
//1. ��ü�� ��� �Լ� ȣ�� �ÿ��� .*  �����ڸ� �̿�. 
//2. �ּҷ� ��� �Լ� ȣ�� �ÿ��� ->* �����ڸ� �̿�.
//�̶� ������ �켱������ ���� ��ȣ�� �ʼ��� ����ؾ��Ѵ�.

#ifdef forth

class point
{
	int x;
	int y;

public:
	explicit point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	//explicit �Ͻ��� ������ ȣ���� �����ϴ� Ű����
	void print() const { cout << x << ", " << y << endl; }
	void printInt(int n) { cout << "���� : " << n << endl; }
};

int main()
{
	point pt(2, 3);
	point* ppt = &pt;

	void (point::*pf1)() const; // ��� �Լ� ������ ���� (const�� �ñ״�ó�� ���Ե�)
	void (point::*pf2)(int);    // ��� �Լ� ������ ����

	pf1 = &point::print;
	pf2 = &point::printInt;


	//�⺻���� ��� �Լ� ȣ����
	pt.print();
	pt.printInt(10);
	cout << endl;

	//��ü�� ���� ��� �Լ� �����͸� �̿�
	(pt.*pf1)();
	(pt.*pf2)(10);
	cout << endl;

	//��ü �����Ϳ� ���� ��� �Լ� �����͸� �̿�
	(ppt->*pf1)();
	(ppt->*pf2)(10);
	cout << endl;
}

#endif

//���� �ڵ�� Ŭ���̾�Ʈ �ڵ� 
//���� �ڵ� : ����� �����ϴ� �ڵ�
//Ŭ���̾�Ʈ �ڵ� : ����� �����޴� �ڵ�


// call(��)       : Ŭ���̾�Ʈ �ڵ尡 ���� �ڵ带 ȣ�� (�Լ��� ȣ�� ������ ���α׷��Ӱ� ������)
// callback(�ݹ�) : ���� �ڵ尡 Ŭ���̾�Ʈ �ڵ带 ȣ�� (�Լ��� ȣ�� ������ �ý��ۿ��� ������)

#ifdef fifth_call

//���� �ڵ�
void printHello()
{
	cout << "Hello" << endl;
}

//Ŭ���̾�Ʈ �ڵ�
int main()
{
	printHello();
}

#endif

//�Լ� �����͸� ���� �ʰ� ���� ���� ������ ����
//�����δ� ���� �ڵ忡�� �ڽ��� ȣ���� Ŭ���̾�Ʈ �ڵ带 �̸� �˰����� ����� ����.
//������ Ŭ���̾�Ʈ�� ������ �����ϴ� ������δ� 
//1. �Լ� ������ �Ű������� �̿��� �ݹ� �Լ��� �ּҸ� �����ϴ� ���
//2. �Լ� ��ü�� �̿��ϴ� ��� 
//3. �븮��(Proxy) ������ �̿��ϴ� ���
//4. ����(Strategy) ������ �̿��ϴ� ���
//���� �ִ�.

#ifdef fifth_callback

void client();

//���� �ڵ�
void server()
{
	cout << "�� ������" << endl;
	client(); //���� �ڵ忡�� Ŭ���̾�Ʈ �ڵ� ȣ��
}

//Ŭ���̾�Ʈ �ڵ�
void client()
{
	cout << "�� Ŭ���̾�Ʈ��" << endl;
}

int main()
{
	server(); //���� �ڵ� ȣ��

	return 0;
}
#endif

//�Լ� �����͸� �̿��� �ݹ� ��Ŀ������ ������ ����

#ifdef sixth_fp

//���� �Լ�
void For_each(int* begin, int* end, void(*pf)(int))
{
	while (begin != end) {
		//Ŭ���̾�Ʈ �Լ� ȣ��(�ݹ�)
		pf(*begin++); 
	}
}

//Ŭ���̾�Ʈ �Լ���
void print_a(int a) { 
	cout << a << ' ';
}

void print_b(int b) {
	cout << b * b << ' ';
}

void print_c(int c) {
	cout << "���� : " << c << endl;
}

int main()
{
	int arr[5] = { 10, 20, 30, 40, 50 };

	//�ݹ� �Լ��� �ּҸ� ����
	For_each(arr, arr + 5, print_a);
	cout << endl << endl;
	For_each(arr, arr + 5, print_b);
	cout << endl << endl;
	For_each(arr, arr + 5, print_c);
	cout << endl << endl;
}
#endif

//STL�� for_each�˰����� �̿��� ��

#ifdef sixth_stl

#include <algorithm>
using std::for_each;

//Ŭ���̾�Ʈ �Լ���
void print_a(int a) {
	cout << a << ' ';
}

void print_b(int b) {
	cout << b * b << ' ';
}

void print_c(int c) {
	cout << "���� : " << c << endl;
}

int main()
{
	int arr[5] = { 10, 20, 30, 40, 50 };

	//�ݹ� �Լ��� �ּҸ� ����
	for_each(arr, arr + 5, print_a);
	cout << endl << endl;
	for_each(arr, arr + 5, print_b);
	cout << endl << endl;
	for_each(arr, arr + 5, print_c);
	cout << endl << endl;

	//����� ���� ������ ������
	//STL�� for_each�� ���ø����� ������� �ڷ����� �����Ӵ�.
}

#endif


//���� Ǯ�� 

//�־��� �Լ� : void print(int data) {...}
//1. print() �Լ��� ���� �Լ��� �����Լ���� �Լ� �����ʹ� void(*pf)(int);�� ���� �����մϴ�.
//2. print() �Լ��� class a�� ��� �Լ���� �Լ� �����ʹ� void(a::*pf)(int);�� ���� �����մϴ�.
//3. �Լ� ������ pf�� ���� �Լ� print()�� �ּҶ�� pf(10)ó�� ���� �Լ��� ȣ���մϴ�.
//4. �Լ� ������ pf�� class a�� ��� �Լ� print()�� �ּҰ�, ��ü�� obj��� obj.pf1(10);ó�� ��� �Լ��� ȣ���մϴ�.

//������ Ŭ���̾�Ʈ�� ��å�� �ݿ��Ϸ��� ���� �� �ڵ忡�� Ŭ���̾�Ʈ �� �Լ��� ȣ���մϴ�.
//�� �� ������ ȣ���ϴ� Ŭ���̾�Ʈ �Լ��� ������ �ݹ� �Լ��� �մϴ�. 