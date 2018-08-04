#include <iostream>

//(디폴트 매개 변수의 기본 문법)
void a(int i = 0) { std::cout << i << std::endl; }  //함수 1번
													//void a() { std::cout << 1 << std::endl; }         //함수 2번
													//void a(int d) { std::cout << d*10 << std::endl; } //함수 3번

void b(int i = 0) { std::cout << i << std::endl; }

void c(int a = 0, int b = 0, int c = 0) { std::cout << a + b + c << std::endl; }

//이런거 안 됨.
//void d(int a = 0, int b, int c) { std::cout << a + b + c << std::endl; }
//void d(int a = 0, int b , int c = 0) { std::cout << a + b + c << std::endl; }

//함수의 원형과 정의를 분리했을 경우 사용 전에 매개변수가 나타나야 한다.

//이렇게 하는건 되는데
void d(int a, int b, int c);

void d(int a = 0, int b = 0, int c = 0)
{
	std::cout << a + b + c << std::endl;
}

//이렇게 하는건 안된다.
void e(int a, int b, int c);

int main()
{
	/*
	a();    //함수 1번과 2번 중 어떤 것을 호출하는지 애매하다.
	a(1);   //함수 1번과 3번 중 어떤 것을 호출하는지 애매하다.
	*/

	b(10);  //b함수를 인수 주고 호출.
	b();    //b함수를 인수 없이 호출.

			//매개변수는 마지막 값부터 생략된다. 즉, 디폴트 매개 변수도 마지막 값부터 줄 수 있다.
	c(1, 2, 3);
	c(1, 2);
	c(1);
	c();

	//됨
	d();

	//이건 안됨.
	//e();
}

void e(int a = 0, int b = 0, int c = 0)
{
	std::cout << a + b + c << std::endl;
}

