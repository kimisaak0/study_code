#include <iostream>

//(����Ʈ �Ű� ������ �⺻ ����)
void a(int i = 0) { std::cout << i << std::endl; }  //�Լ� 1��
													//void a() { std::cout << 1 << std::endl; }         //�Լ� 2��
													//void a(int d) { std::cout << d*10 << std::endl; } //�Լ� 3��

void b(int i = 0) { std::cout << i << std::endl; }

void c(int a = 0, int b = 0, int c = 0) { std::cout << a + b + c << std::endl; }

//�̷��� �� ��.
//void d(int a = 0, int b, int c) { std::cout << a + b + c << std::endl; }
//void d(int a = 0, int b , int c = 0) { std::cout << a + b + c << std::endl; }

//�Լ��� ������ ���Ǹ� �и����� ��� ��� ���� �Ű������� ��Ÿ���� �Ѵ�.

//�̷��� �ϴ°� �Ǵµ�
void d(int a, int b, int c);

void d(int a = 0, int b = 0, int c = 0)
{
	std::cout << a + b + c << std::endl;
}

//�̷��� �ϴ°� �ȵȴ�.
void e(int a, int b, int c);

int main()
{
	/*
	a();    //�Լ� 1���� 2�� �� � ���� ȣ���ϴ��� �ָ��ϴ�.
	a(1);   //�Լ� 1���� 3�� �� � ���� ȣ���ϴ��� �ָ��ϴ�.
	*/

	b(10);  //b�Լ��� �μ� �ְ� ȣ��.
	b();    //b�Լ��� �μ� ���� ȣ��.

			//�Ű������� ������ ������ �����ȴ�. ��, ����Ʈ �Ű� ������ ������ ������ �� �� �ִ�.
	c(1, 2, 3);
	c(1, 2);
	c(1);
	c();

	//��
	d();

	//�̰� �ȵ�.
	//e();
}

void e(int a = 0, int b = 0, int c = 0)
{
	std::cout << a + b + c << std::endl;
}

