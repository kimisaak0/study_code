#include <iostream>

//매개변수의 갯수가 다름
void a() { std::cout << 'a' << std::endl; }
void a(int i) { std::cout << i << std::endl; }

//매개변수의 타입이 다름
void b(int i) { std::cout << i << std::endl; }
void b(double i) { std::cout << i << std::endl; }

//매개변수의 순서가 다름
void c(int i, double d) { std::cout << i << std::endl; }
void c(double i, int d) { std::cout << i << std::endl; }


//리턴 타입만 다름 (구분 안 됨)
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
