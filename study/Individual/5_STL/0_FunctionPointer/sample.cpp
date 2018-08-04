

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

//first, second, third, forth, fifth_call, fifth_callback, sixth_fp, sixth_stl

#define sixth_stl

//1. 함수의 이름은 함수가 시작하는 시작 주소를 의미한다.
//2. 함수 포인터는 함수의 시작 주소 즉 함수의 이름을 저장하는 포인터이다.
//3. 함수 포인터는 함수 시그니처가 같은 것끼리 짝을 이룬다.


#ifdef first

void print(int n) {
	cout << "정수 : " << n << endl;
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
	//void print(int n)의 함수 포인터 선언
	void(*pf)(int);
	//int print()의 함수 포인터 선언
	int(*ppf)();
	//int add(int a, int b)의 함수 포인터 선언
	int(*padd)(int, int);

	//함수의 이름은 함수의 시작 주소
	pf = print;
	ppf = print; 
	//오버로드된 함수는 시그니처에 맞게 알아서 구분되서 들어간다.

	//시그니처가 맞지 않은 함수는 넣을 수 없다.
	//pf = add;
	//ppf = add;
	padd = add;

	print(10);     //1. 함수 이름을 이용한 함수 호출
	pf(10);        //2. 함수 포인터를 이용한 함수 호출 - 1
	(*pf)(10);     //3. 함수 포인터를 이용한 함수 호출 - 2
	//모두 같은 결과
	 
	cout << endl;
	//함수의 시작 주소를 보고 싶지만 오버로드 되어 있어서 어떤걸 읽어와야 하는지 알 수 없는 상황
	//cout << print << endl;
	
	cout << add << endl;
	cout << padd << endl;
	cout << *padd << endl;
	//모두 같은 결과	
}


#endif

//C++의 함수 -> 1. 정적 함수, 2. 멤버 함수
//1. 정적 함수 -> 1-1. 전역 함수, 1-2. namespace내의 전역 함수, 1-3. static 멤버 함수
//2. 멤버 함수 -> 2-1. 객체로 호출, 2-2. 주소로 호출
//3. 멤버 함수 호출 방법 -> 3-1. 정적 함수 호출, 3-2. 객체로 멤버 함수 호출, 3-3. 객체의 주소로 멤버 함수 호출

#ifdef second

void print()
{
	cout << "정적 함수 print()" << endl;
}

class point
{
public:
	void print()
	{
		cout << "멤버함수 print" << endl;
	}
};

int main()
{
	point pt;
	point* ppt = &pt;

	print();        //1. 전역 함수 호출;
	pt.print();     //2. 객체로 멤버 함수 호출
	ppt->print();   //3. 주소로 멤버 함수 호출
}

#endif

//정적 함수 포인터는 함수 시그니처만 맞으면 쉽게 선언할 수 있으며
//전역 함수, namespace내의 전역 함수, static 멤버 함수는 모두 함수 호출 규약이 같아서 함수 포인터도 같다.

#ifdef third

void print()
{
	cout << "전역 함수" << endl;
}

namespace a
{
	void print()
	{
		cout << "namespace A 전역 함수" << endl;
	}
}

class b
{
public:
	static void print() {
		cout << "b 클래스의 정적 멤버 함수" << endl;
	}
};

int main()
{
	void(*pf)();               //정적 함수 포인터 선언
				            
	print();                   //1. namespace 없는 전역 함수 호출
	a::print();                //2. namespace a의 전역 함수 호출
	b::print();                //3. class b의 정적 멤버 함수 호출

	cout << endl;

	pf = print;      pf();     //1. 함수 포인터로 namespace 없는 전역 함수 호출
	pf = a::print;   pf();     //2. 함수 포인터로 namespace a의 전역 함수 호출
	pf = b::print;   pf();     //3. 함수 포인터로 class b의 정적 멤버 함수 호출
}

#endif

////C++에서 정적 함수에 대한 기본적인 함수 호출 규약은 cdecl이고, 멤버 함수는 thiscall을 사용한다.
//그래서 정적 함수 포인터와 멤버 함수 포인터를 선언하는 방법이 다르다.

//멤버 함수 포인터는 함수 포인터 선언에 어떤 클래스의 멤버 함수를 가리킬 것인지 클래스 이름을 지정해야 한다.

//시그니처가 void b::print(int n)인 멤버 함수 포인터는 void (b::*pf)(int)로 선언한다.

//함수를 호출할 때
//1. 객체로 멤버 함수 호출 시에는 .*  연산자를 이용. 
//2. 주소로 멤버 함수 호출 시에는 ->* 연산자를 이용.
//이때 연산자 우선순위에 의해 괄호를 필수로 사용해야한다.

#ifdef forth

class point
{
	int x;
	int y;

public:
	explicit point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	//explicit 암시적 생성자 호출을 금지하는 키워드
	void print() const { cout << x << ", " << y << endl; }
	void printInt(int n) { cout << "정수 : " << n << endl; }
};

int main()
{
	point pt(2, 3);
	point* ppt = &pt;

	void (point::*pf1)() const; // 멤버 함수 포인터 선언 (const도 시그니처에 포함됨)
	void (point::*pf2)(int);    // 멤버 함수 포인터 선언

	pf1 = &point::print;
	pf2 = &point::printInt;


	//기본적인 멤버 함수 호출방법
	pt.print();
	pt.printInt(10);
	cout << endl;

	//객체에 대한 멤버 함수 포인터를 이용
	(pt.*pf1)();
	(pt.*pf2)(10);
	cout << endl;

	//객체 포인터에 대한 멤버 함수 포인터를 이용
	(ppt->*pf1)();
	(ppt->*pf2)(10);
	cout << endl;
}

#endif

//서버 코드와 클라이언트 코드 
//서버 코드 : 기능을 제공하는 코드
//클라이언트 코드 : 기능을 제공받는 코드


// call(콜)       : 클라이언트 코드가 서버 코드를 호출 (함수의 호출 시점을 프로그래머가 결정함)
// callback(콜백) : 서버 코드가 클라이언트 코드를 호출 (함수의 호출 시점이 시스템에서 결정됨)

#ifdef fifth_call

//서버 코드
void printHello()
{
	cout << "Hello" << endl;
}

//클라이언트 코드
int main()
{
	printHello();
}

#endif

//함수 포인터를 쓰지 않고 만든 아주 간단한 예시
//실제로는 서버 코드에서 자신을 호출한 클라이언트 코드를 미리 알고있을 방법은 없다.
//서버에 클라이언트의 정보를 전달하는 방법으로는 
//1. 함수 포인터 매개변수를 이용해 콜백 함수의 주소를 전달하는 방법
//2. 함수 객체를 이용하는 방법 
//3. 대리자(Proxy) 패턴을 이용하는 방법
//4. 전략(Strategy) 패턴을 이용하는 방법
//등이 있다.

#ifdef fifth_callback

void client();

//서버 코드
void server()
{
	cout << "난 서버야" << endl;
	client(); //서버 코드에서 클라이언트 코드 호출
}

//클라이언트 코드
void client()
{
	cout << "난 클라이언트야" << endl;
}

int main()
{
	server(); //서버 코드 호출

	return 0;
}
#endif

//함수 포인터를 이용해 콜백 메커니즘을 구현한 예제

#ifdef sixth_fp

//서버 함수
void For_each(int* begin, int* end, void(*pf)(int))
{
	while (begin != end) {
		//클라이언트 함수 호출(콜백)
		pf(*begin++); 
	}
}

//클라이언트 함수들
void print_a(int a) { 
	cout << a << ' ';
}

void print_b(int b) {
	cout << b * b << ' ';
}

void print_c(int c) {
	cout << "정수 : " << c << endl;
}

int main()
{
	int arr[5] = { 10, 20, 30, 40, 50 };

	//콜백 함수의 주소를 전달
	For_each(arr, arr + 5, print_a);
	cout << endl << endl;
	For_each(arr, arr + 5, print_b);
	cout << endl << endl;
	For_each(arr, arr + 5, print_c);
	cout << endl << endl;
}
#endif

//STL의 for_each알고리즘을 이용한 예

#ifdef sixth_stl

#include <algorithm>
using std::for_each;

//클라이언트 함수들
void print_a(int a) {
	cout << a << ' ';
}

void print_b(int b) {
	cout << b * b << ' ';
}

void print_c(int c) {
	cout << "정수 : " << c << endl;
}

int main()
{
	int arr[5] = { 10, 20, 30, 40, 50 };

	//콜백 함수의 주소를 전달
	for_each(arr, arr + 5, print_a);
	cout << endl << endl;
	for_each(arr, arr + 5, print_b);
	cout << endl << endl;
	for_each(arr, arr + 5, print_c);
	cout << endl << endl;

	//결과는 위의 예제와 같지만
	//STL의 for_each는 템플릿으로 만들어져 자료형에 자유롭다.
}

#endif


//문제 풀이 

//주어진 함수 : void print(int data) {...}
//1. print() 함수가 정적 함수나 전역함수라면 함수 포인터는 void(*pf)(int);와 같이 선언합니다.
//2. print() 함수가 class a의 멤버 함수라면 함수 포인터는 void(a::*pf)(int);와 같이 선언합니다.
//3. 함수 포인터 pf가 전역 함수 print()의 주소라면 pf(10)처럼 전역 함수를 호출합니다.
//4. 함수 포인터 pf가 class a의 멤버 함수 print()의 주소고, 객체가 obj라면 obj.pf1(10);처럼 멤버 함수를 호출합니다.

//서버는 클라이언트의 정책을 반영하려고 서버 측 코드에서 클라이언트 측 함수를 호출합니다.
//이 때 서버가 호출하는 클라이언트 함수를 가리켜 콜백 함수라 합니다. 