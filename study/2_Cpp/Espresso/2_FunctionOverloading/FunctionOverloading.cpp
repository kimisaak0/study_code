#include <iostream>

//�Ű������� ������ �ٸ�
void a() { std::cout << 'a' << std::endl; }
void a(int i) { std::cout << i << std::endl; }

//�Ű������� Ÿ���� �ٸ�
void b(int i) { std::cout << i << std::endl; }
void b(double i) { std::cout << i << std::endl; }

//�Ű������� ������ �ٸ�
void c(int i, double d) { std::cout << i << std::endl; }
void c(double i, int d) { std::cout << i << std::endl; }


//���� Ÿ�Ը� �ٸ� (���� �� ��)
void d() { std::cout << 0 << std::endl; }
//int d() { std::cout << 'c' << std::endl; }

int main()
{
	a();
	a(1);

	b(2);
	b(2.5);

	c(3, 3.5);
	c(4.5, 4);

	d();
}
