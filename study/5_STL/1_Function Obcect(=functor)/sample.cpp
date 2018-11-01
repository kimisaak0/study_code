#include <iostream>
using std::cout;
using std::endl;
using std::cin;

//first, second, third, forth, fifth_functor, fifth_stl, sixth

#define problem

//a. 함수 객체는 함수처럼 호출 가능한 클래스 객체이다. 
//b. 함수 객체는 함수처럼 사용할 수 있으면서도 상태를 가질 수 있다.
//c. 객체가 함수처럼 동작하려면 '()'연산자를 재정의해야 한다.

#ifdef first

void print()
{
	cout << "전역 함수" << endl;
}

struct Functor
{
	void operator() ()
	{
		cout << "함수 객체" << endl;
	}
};

int main()
{
//	functor print;
//
//	//이름이 같으면 함수 객체가 우선시된다.
//	print();     //멤버 함수 호출 (functor.operator()와 같음)
//	::print();   //전역 함수 호출

	Functor functor;

	print();    //전역 함수 호출
	functor();  //멤버 함수 호출
}

#endif

//매개변수 리스트를 갖는 함수 객체 만들기

#ifdef second

void printAdd(int a, int b)
{
	cout << "전역 함수 : ";
	printf("%d+%d=%d\n", a, b, a + b);
}

struct Functor
{
	void operator() (int a, int b)
	{
		cout << "함수 객체 : ";
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

//함수 객체의 장점
//1. 일반 함수와는 다르게 다른 멤버 변수와 멤버 함수를 가질 수 있다.
//2. 함수 객체의 시그니처가 같아도 객체 타입이 다르면 전혀 다른 타입으로 인식한다.
//3. 일반 함수보다 함수 객체가 더 빠르다.
//4. 일반 함수의 함수 포인터는 인라인 될 수 없지만 함수 객체는 인라인 될 수 있고, 컴파일러가 쉽게 최적화 할 수 있다.

#ifdef third

class Adder
{
	int total;

public:
	explicit Adder(int n = 0) : total(n) {}
	
	//클래스 내부에 정의었으므로 인라인 함수.
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
	//멤버 변수를 갖는 함수 객체
	Adder add(0); // 초깃값 0
	
	cout << add(10) << endl;
	cout << add(20) << endl;
	cout << add(30) << endl;

	//(함수)객체끼리의 대입 
	Adder add_a(10); // 초깃값 0
	Miner min(0); // 초깃값 0

	add = add_a;
	cout << add(0) << endl;

	//시그니처는 같지만 객체 타입이 다르므로 (기본적으로) 대입이 안된다.
	//add = min;
}

#endif

//콜백 함수 예제를 함수 객체를 사용하여 변경한 것
//for_each() 알고리즘에 함수가 아닌 함수 객체를 전달할 수도 있다는 것을 보여준다.
//for_each() 알고리즘이 템플릿으로 구현되어 있기 때문이다.

#ifdef forth

#include <algorithm>
using std::for_each;

//클라이언트 함수 객체들
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
		cout << "정수 : " << c << endl;
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

//bool형을 반환하는 less와 greater함수 객체. 
//조건자(predicate)

#ifdef fifth_functor

//함수들
bool greater_f(int a, int b)
{
	return a > b;
}

bool less_f(int a, int b)
{
	return a < b;
}


//함수 객체들
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

	cout << "전역 함수 호출" << endl;
	cout << less_f(a, b) << endl;
	cout << greater_f(a, b) << endl;
	cout << endl;

	cout << "함수 객체 호출" << endl;
	cout << less(a, b) << endl;
	cout << greater(a, b) << endl;
	cout << endl;

	//functor_less()와 func_greater(0)은 생성자를 호출한 것.
	cout << "임시 객체를 이용해 함수 객체 호출" << endl;
	cout << functor_less() (a,b) << endl;
	cout << functor_greater() (a, b) << endl;
	cout << endl;

	cout << "명시적 함수 호출" << endl;
	cout << less.operator()(a, b) << endl;
	cout << greater.operator()(a, b) << endl;
	cout << endl;
}

#endif

//STL의 less와 greater 함수 객체 사용

#ifdef fifth_stl

#include <functional>
using std::less;
using std::greater;

//클래스 템플릿으로 되어있다.
typedef less<int> Less;
typedef greater<int> Greater;

int main()
{
	Less iLess;
	Greater iGreater;

	int a = 10;
	int b = 20;

	cout << "함수 객체 호출" << endl;
	cout << iLess(a, b) << endl;
	cout << iGreater(a, b) << endl;
	cout << endl;

	cout << "임시 객체를 이용해 함수 객체 호출" << endl;
	cout << Less() (a, b) << endl;
	cout << Greater() (a, b) << endl;
	cout << endl;

	cout << "명시적 함수 호출" << endl;
	cout << iLess.operator()(a, b) << endl;
	cout << iGreater.operator()(a, b) << endl;
	cout << endl;

	cout << "임시 객체를 이용한 명시적 함수 호출" << endl;
	cout << Less().operator()(a, b) << endl;
	cout << Greater().operator()(a, b) << endl;
	cout << endl;
}

#endif

//plus(), minus()
//함수, 함수 객체, STL 비교

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

	cout << "함수 사용" << endl;
	cout << plus_f(a, b) << endl;
	cout << minus_f(a, b) << endl;
	cout << endl;

	cout << "함수 객체 사용" << endl;
	cout << Plus(a, b) << endl;
	cout << Minus(a, b) << endl;
	cout << endl;

	cout << "STL 사용" << endl;
	cout << plus<int>() (a, b) << endl;
	cout << minus<int>() (a, b) << endl;
	cout << endl;
}
#endif

//함수 객체의 구현 방법과 사용법을 잘 알아두자.

//문제풀이
#ifdef problem

//1. 함수처럼 호출 가능한 클래스 객체를 가리켜 함수 객체라 합니다.
//2. 함수처럼 호출 가능한 클래스 객체는 operator()를 재정의하여 생성합니다.


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
		cout << "같다" << endl;
	}
	else {
		cout << "다르다" << endl;
	}

	Adder add;

	int sum = add(10, 20);
	cout << "sum = " << sum << endl;
}

#endif