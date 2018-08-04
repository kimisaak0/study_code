#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
using std::string;

using std::pair;


//first, second, third, forth, fifth_basic, fifth_default, sixth, seventh, eighth, nineth, problem_1, problem_2, problem_3
#define problem_3

//�Լ� ���ø� : Ÿ���� �ٸ� �Լ��� ������ Ʋ
//Ŭ���� ���ø� : Ÿ���� �ٸ� Ŭ������ ������ Ʋ

//�⺻���� �ڷ����� ���� �Լ��� �Լ� �����ε����� ������ �� ������ ����� ���� �ڷ����� ���ؼ��� ������ �� ����.
//�̶� �Լ� ���ø��� ����ϸ� ����� ���� �ڷ������� �����ϴ� �Լ��� ���� �� �ִ�.

//�Լ� ���ø��� ������ ���� ���� ���ڰ��� ���� ���� �Լ��� ������.
//�̷��� ������� ���� �Լ��� ���ø��� �ν��Ͻ���� �Ѵ�.



//template <typename T>�� template<class T>�� ���� �ǹ̸� ���´�.
#ifdef first
template <typename T>
void print(T a, T b)
{
	cout << a << ", " << b << endl;
}

//��ȯ������ ����� �� �ִ�.
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

	//���ø� �ν��Ͻ��� Ÿ���� ����� ���
	print<int>('a', 'b');

	//���� �ٸ� Ÿ���� �Ű������� �޴� ���ø��� �ν��Ͻ�
	cout << print_a(2, "b") << endl;
}
#endif


//���ø��� Ÿ������ �����ͳ� ���۷����� �Ѿ�� �ʴ´�.
#ifdef second

//�� ���ø� �Լ����� ���� �����ڿ� ���� �����ڸ� �����ϴ� ��� Ÿ���� �� �� �ִ�.
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


//���ø��� �Ű������δ� Ÿ���̸��� �ƴ϶� �⺻ �ڷ����� �����ϴ�.
//�̶��� ���ø� �Ű������� ���ڸ� ��������� ����������Ѵ�. 
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


//�Լ� ���ø� Ư��ȭ
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

//�Ϲ�ȭ �Լ� ���ø�
template <typename T>
void print(T a)
{
	cout << a << endl;
}


//Ư��ȭ �Լ� ���ø�
//template <point>
//void print(point a) 
//�� �� ������� �ڵ��̴�.

template <>
void print(point a)
{
	cout << "print Ư��ȭ ����: ";
	a.print();
}

int main()
{
	int n = 10;
	double d = 2.5;
	point pt(2, 3);

	print(n);   // print<int>(n)    �Ϲ�ȭ ����
	print(d);   // print<double>(d) �Ϲ�ȭ ����
	print(pt);  // print<point>(pt) Ư��ȭ ����

	//������ �Լ� ���ø��� Ư��ȭ�� �ƴ� �����ε��� �� �켱�õȴ�.
	//�� �����ε����� ó���� �� �ִ�.
}
#endif


//Ŭ���� ���ø�
#ifdef fifth_basic

template <typename T>
class Array
{
	T*  buf;
	int size;      // ������ ����
	int capacity;  // ���� ������ �޸� ũ��

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


//����Ʈ �Ű����� ���� ���� Ŭ���� ���ø�
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
	Array<> iarr; //����Ʈ �Ű����� �� ���.
	iarr.insert(1);
	iarr.insert(2);
	iarr.insert(3);

	for (int i = 0; i < iarr.GetSize(); i++) {
		cout << iarr[i] << " ";
	}
	cout << endl;

	Array<double> darr; //����Ʈ �Ű����� �� ���.
	darr.insert(0.1);
	darr.insert(0.2);
	darr.insert(0.3);

	for (int i = 0; i < darr.GetSize(); i++) {
		cout << darr[i] << " ";
	}
	cout << endl;

	Array<string, 10> sarr; //����Ʈ �Ű����� �� ���.
	sarr.insert("a");
	sarr.insert("b");
	sarr.insert("c");

	for (int i = 0; i < sarr.GetSize(); i++) {
		cout << sarr[i] << " ";
	}
	cout << endl;
}
#endif


//Ŭ���� ���ø� Ư��ȭ
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
		cout << "Ÿ�� : " << typeid(data).name() << endl;
		cout << "ũ�� : " << sizeof(data) << endl;
		cout << " ��  : " << data << endl;
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
		cout << "Ÿ�� : " << "string" << endl;
		cout << "ũ�� : " << data.size() << endl;
		cout << " ��  : " << data << endl;
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

//stl�� ���� ���ø� ����
//�Ű������� ���޵� �Լ� �������� Ÿ���� �����Ϸ��� ������ �� �����Ƿ�
//�Լ� ���ø����� ������� �Լ��� Ÿ���� ��������� ��������� �Ѵ�.
#ifdef seventh
//begin�� �迭�� ���� �ּ�, end�� �迭�� �� �ּ�, pf�� Ŭ���̾�Ʈ �Լ� �����͸� �ǹ�.
template <typename IterT, typename Func>
void For_each(IterT begin, IterT end, Func pf)
{
	while (begin != end) {
		pf(*begin++);
	}
}

//�Լ� ��ü�� ����
template <typename T>
struct print
{
	string sep; //��� ������ ����
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
	For_each(iarr, iarr + 5, print<int>()); //���� ���
	cout << endl;

	string sarr[3] = { "a","b","c" };
	For_each(sarr, sarr + 3, print<string>()); //���� ���
	cout << endl;
}
#endif

//��ȯ Ÿ�԰� �Ű����� Ÿ���� Ŭ���̾�Ʈ�� ������ �� �ִ� �Լ� ��ü
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

//stl�� Pair Ŭ���� ���ø� ����
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

	//���� ������ Pair Ŭ���� ���ø�
	Pair<int, int> p1(10, 20);
	cout << p1.first << ", " << p1.second << endl;
	cout << endl;

	Pair<int, string> p2(1, "one");
	cout << p2.first << ", " << p2.second << endl;
	cout << endl;

	//STL�� pair
	pair<int, int> p3(10, 20); 
	cout << p3.first << ", " << p3.second << endl;
	cout << endl;

	pair<int, string> p4(1, "one");
	cout << p4.first << ", " << p4.second << endl;
}
#endif

//���� Ǯ��_1 (�Լ� ���ø� �ۼ��ϱ�)
#ifdef problem_1
//�迭�� ���Ҹ� �����ϴ� �Լ� ���ø� copy()�� �ۼ��ϼ���.

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

//���� Ǯ��_2 (���� Ŭ���� �����ϱ�)
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

//���� Ǯ��_3 (ť Ŭ���� �����ϱ�)
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