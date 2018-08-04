#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

using std::pair;


//first, second, third, forth, fifth_basic, fifth_default, sixth, seventh, eighth, nineth, problem_1, problem_2, problem_3
#define problem_3

//함수 템플릿 : 타입이 다른 함수를 만들어내는 틀
//클래스 템플릿 : 타입이 다른 클래스를 만들어내는 틀

//기본적인 자료형에 대한 함수는 함수 오버로딩으로 대응할 수 있지만 사용자 정의 자료형에 대해서는 대응할 수 없다.
//이때 함수 템플릿을 사용하면 사용자 정의 자료형에도 대응하는 함수를 만들어낼 수 있다.

//함수 템플릿은 실제로 사용될 때의 인자값에 따라 실제 함수를 만들어낸다.
//이렇게 만들어진 실제 함수를 템플릿의 인스턴스라고 한다.



//template <typename T>와 template<class T>는 같은 의미를 갖는다.
#ifdef first
template <typename T>
void print(T a, T b)
{
	cout << a << ", " << b << endl;
}

//반환형에도 사용할 수 있다.
template <typename A, class B>
A print_a(A a, B b)
{
	cout << b << endl;
	return a;
}

int main()
{
	print(1, 2);
	print(0.12, 3.45);
	print("abc", "def");

	//템플릿 인스턴스의 타입을 명시한 경우
	print<int>('a', 'b');

	//서로 다른 타입을 매개변수로 받는 템플릿의 인스턴스
	cout << print_a(2, "b") << endl;
}
#endif


//템플릿의 타입으로 포인터나 레퍼런스가 넘어가진 않는다.
#ifdef second

//이 템플릿 함수에는 복사 생성자와 대입 연산자를 지원하는 모든 타입이 올 수 있다.
template <typename T>
void Swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

int main()
{
	int n1 = 10, n2 = 20;
	double d1 = 0.1, d2 = 0.2;

	cout << n1 << ", " << n2 << endl;
	Swap(n1, n2);
	cout << n1 << ", " << n2 << endl;

	cout << d1 << ", " << d2 << endl;
	Swap(d1, d2);
	cout << d1 << ", " << d2 << endl;
}

#endif


//템플릿의 매개변수로는 타입이름뿐 아니라 기본 자료형도 가능하다.
//이때는 템플릿 매개변수의 인자를 명시적으로 전달해줘야한다. 
#ifdef third

template <typename T, int size>
void printArr(T* arr)
{
	for (int i = 0; i < size; i++) {
		cout << "[" << i << "] : " << arr[i] << endl;
	}
	cout << endl;
}

int main()
{
	int arr1[5] = { 1,2,3,4,5 };
	printArr<int, 5>(arr1);

	double arr2[3] = { 0.1, 0.2, 0.3 };
	printArr<double, 3>(arr2);
}

#endif


//함수 템플릿 특수화
#ifdef forth

class point
{
	int x;
	int y;

public:
	explicit point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	void print() const 
	{ 
		printf("(%d,%d)", x, y);
	}
};

//일반화 함수 템플릿
template <typename T>
void print(T a)
{
	cout << a << endl;
}


//특수화 함수 템플릿
//template <point>
//void print(point a) 
//가 더 명시적인 코드이다.

template <>
void print(point a)
{
	cout << "print 특수화 버전: ";
	a.print();
}

int main()
{
	int n = 10;
	double d = 2.5;
	point pt(2, 3);

	print(n);   // print<int>(n)    일반화 버전
	print(d);   // print<double>(d) 일반화 버전
	print(pt);  // print<point>(pt) 특수화 버전

	//하지만 함수 템플릿은 특수화가 아닌 오버로딩이 더 우선시된다.
	//즉 오버로딩으로 처리할 수 있다.
}
#endif


//클래스 템플릿
#ifdef fifth_basic

template <typename T>
class Array
{
	T*  buf;
	int size;      // 원소의 개수
	int capacity;  // 저장 가능한 메모리 크기

public:
	explicit Array(int cap = 100) 
		: buf(0), size(0), capacity(cap) 	
	    { buf = new T[capacity]; }
	virtual  ~Array()
	    { delete[] buf; }

	void   insert(T data)                  { buf[size++] = data; }
	T      operator[] (int idx) const      { return buf[idx]; }
	int    GetSize() const                 { return size; }
};

int main()
{
	Array<int> iarr;
	iarr.insert(1);
	iarr.insert(2);
	iarr.insert(3);

	for (int i = 0; i < iarr.GetSize(); i++) {
		cout << iarr[i] << " ";
	}
	cout << endl;

	Array<double> darr;
	darr.insert(0.1);
	darr.insert(0.2);
	darr.insert(0.3);

	for (int i = 0; i < darr.GetSize(); i++) {
		cout << darr[i] << " ";
	}
	cout << endl;

	Array<string> sarr;
	sarr.insert("ABC");
	sarr.insert("DEF");
	sarr.insert("GHI");

	for (int i = 0; i < sarr.GetSize(); i++) {
		cout << sarr[i] << " ";
	}
	cout << endl;
}
#endif


//디폴트 매개변수 값을 갖는 클래스 템플릿
#ifdef fifth_default

template<typename T = int, int capT = 100>
class Array
{
	T*   buf;
	int  size;
	int  capacity;

public:
	explicit Array(int cap = capT)
		: buf(0), size(0), capacity(cap)
	{
		buf = new T[capacity];
	}
	virtual  ~Array()
	{
		delete[] buf;
	}

	void   insert(T data) { buf[size++] = data; }
	T      operator[] (int idx) const { return buf[idx]; }
	int    GetSize() const { return size; }
};

int main()
{
	Array<> iarr; //디폴트 매개변수 값 사용.
	iarr.insert(1);
	iarr.insert(2);
	iarr.insert(3);

	for (int i = 0; i < iarr.GetSize(); i++) {
		cout << iarr[i] << " ";
	}
	cout << endl;

	Array<double> darr; //디폴트 매개변수 값 사용.
	darr.insert(0.1);
	darr.insert(0.2);
	darr.insert(0.3);

	for (int i = 0; i < darr.GetSize(); i++) {
		cout << darr[i] << " ";
	}
	cout << endl;

	Array<string, 10> sarr; //디폴트 매개변수 값 사용.
	sarr.insert("a");
	sarr.insert("b");
	sarr.insert("c");

	for (int i = 0; i < sarr.GetSize(); i++) {
		cout << sarr[i] << " ";
	}
	cout << endl;
}
#endif


//클래스 템플릿 특수화
#ifdef sixth
template <typename T>
class ObjectInfo
{
	T data;

public:
	ObjectInfo(const T& d)
	{
		data = d;
	}

	void print()
	{
		cout << "타입 : " << typeid(data).name() << endl;
		cout << "크기 : " << sizeof(data) << endl;
		cout << " 값  : " << data << endl;
		cout << endl;
	}
};

template <>
class ObjectInfo<string>
{
	string data;

public:
	ObjectInfo(const string& d)
	{
		data = d;
	}

	void print()
	{
		cout << "타입 : " << "string" << endl;
		cout << "크기 : " << data.size() << endl;
		cout << " 값  : " << data << endl;
		cout << endl;
	}
};

int main()
{
	ObjectInfo<int> d1(10);
	d1.print();

	ObjectInfo<double> d2(5.5);
	d2.print();

	ObjectInfo<string> d3("h");
	d3.print();
}

#endif

//stl을 위한 템플릿 예제
//매개변수로 전달된 함수 포인터의 타입을 컴파일러가 유추할 수 없으므로
//함수 템플릿으로 만들어진 함수의 타입은 명시적으로 지정해줘야 한다.
#ifdef seventh
//begin은 배열의 시작 주소, end는 배열의 끝 주소, pf는 클라이언트 함수 포인터를 의미.
template <typename IterT, typename Func>
void For_each(IterT begin, IterT end, Func pf)
{
	while (begin != end) {
		pf(*begin++);
	}
}

//함수 객체로 변경
template <typename T>
struct print
{
	string sep; //출력 구분자 정보
public:
	explicit print(const string& s = " ") : sep(s) { }
	void operator() (T data) const
	{
		cout << data << sep;
	}
};

int main()
{
	int iarr[5] = { 1,2,3,4,5 };
	For_each(iarr, iarr + 5, print<int>()); //정수 출력
	cout << endl;

	string sarr[3] = { "a","b","c" };
	For_each(sarr, sarr + 3, print<string>()); //정수 출력
	cout << endl;
}
#endif

//반환 타입과 매개변수 타입을 클라이언트가 결정할 수 있는 함수 객체
#ifdef eighth
template <typename RetType, typename ArgType>
class Functor
{
public:
	RetType operator() (ArgType data)
	{
		cout << data << endl;
		return RetType();
	}
};

int main()
{
	Functor<void, int> functor_a;
	functor_a(10);

	Functor<bool, string> functor_b;
	functor_b("Hello");
}

#endif

//stl의 Pair 클래스 템플릿 구현
#ifdef nineth
template <typename T1, typename T2>
struct Pair
{
	T1 first;
	T2 second;
	Pair(const T1& ft, const T2& sd) : first(ft), second(sd) {};
};

int main()
{

	//직접 구현한 Pair 클래스 템플릿
	Pair<int, int> p1(10, 20);
	cout << p1.first << ", " << p1.second << endl;
	cout << endl;

	Pair<int, string> p2(1, "one");
	cout << p2.first << ", " << p2.second << endl;
	cout << endl;

	//STL의 pair
	pair<int, int> p3(10, 20); 
	cout << p3.first << ", " << p3.second << endl;
	cout << endl;

	pair<int, string> p4(1, "one");
	cout << p4.first << ", " << p4.second << endl;
}
#endif

//문제 풀이_1 (함수 템플릿 작성하기)
#ifdef problem_1
//배열의 원소를 복사하는 함수 템플릿 copy()를 작성하세요.

template<typename T>
void copy(T* dst, T* src, int size )
{
	for (int i = 0; i < size; i++) {
		dst[i] = src[i];
	}
};

int main()
{
	int arr1[5] = { 1,2,3,4,5 };
	int arr2[5] = { 0, };

	copy(arr2, arr1, 5);

	cout << arr2[3] << endl;
}

#endif

//문제 풀이_2 (스택 클래스 구현하기)
#ifdef problem_2

template <typename T>
class Stack
{
	T arr[100];
	int door;

public:
	Stack()
	{
		door = -1;
	}

	void Push(T data)
	{
		arr[++door] = data;
	}

	T Pop()
	{
		return arr[door--];
	}

	bool Empty()
	{
		if (door == -1) {
			return true;
		}
		else {
			return false;
		}
	}
};

int main()
{
	Stack<int> st;

	st.Push(10);
	st.Push(20);
	st.Push(30);

	if (!st.Empty()) { cout << st.Pop() << endl; }
	if (!st.Empty()) { cout << st.Pop() << endl; }
	if (!st.Empty()) { cout << st.Pop() << endl; }
}
#endif

//문제 풀이_3 (큐 클래스 구현하기)
#ifdef problem_3

template <typename T>
class Queue
{
	T arr[100];
	int in;
	int out;

public:
	Queue()
	{
		in = -1;
		out = -1;
	}

	void Push(T data)
	{
		arr[++in] = data;
	}

	T Pop()
	{
		return arr[++out];
	}

	bool Empty()
	{
		if (in == out) {
			return true;
		}
		else {
			return false;
		}
	}
};

int main()
{
	Queue<int> q;

	q.Push(10);
	q.Push(20);
	q.Push(30);

	if (!q.Empty()) { cout << q.Pop() << endl; }
	if (!q.Empty()) { cout << q.Pop() << endl; }
	if (!q.Empty()) { cout << q.Pop() << endl; }
}
#endif