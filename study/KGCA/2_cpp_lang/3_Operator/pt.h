#pragma once
#include <iostream>
using namespace std;

//const char& operator []() const;
//char& operator [] ();
//두 함수는 별개의 함수가 된다. ... const 함수냐 아니냐의 차이.

class pt
{
	static int dynamic;
	int x, y;
public:
	void SetPosition(int _x, int _y);
	void Move(int _x, int _y);
	void Show();

	//포인터 연산자 재정의
	pt* operator->();
	pt& operator* ();

	//증가 연산자 재정의
	pt operator++();      // ++p1(전위)
	pt operator++(int);  // p1++;(후위)

	// 이항연산자 p3 = p1 + p2
	pt operator+(const pt& np) const;

	// 이항연산자 p3 = p1 + 2, p3 = 2 + p1
	pt operator+(int n) const; // p2=p1*2;
	friend pt operator+(int n, const pt& np); // p2= 2 * p1;
	

	pt &operator=(const pt &pt);

	pt &operator+=(const pt &pt);
	pt &operator+=(int n);

	//의미 없는 장난질
	friend int operator+= (int& n, const pt& np);
	//friend pt& operator+= (int& n, pt& np);

	bool operator==(const pt &pt) const;
	bool operator!=(const pt &pt) const;

	int &operator[](int index);
	void *operator new(size_t size);
	void operator delete(void *p);

	//std::cout << *pFindA << *pFindB;
	friend ostream &operator<<(ostream &os, const pt &pt);
	friend istream &operator>>(istream &is, pt &pt);

	void (pt::*m_fp) ();	//함수 포인터 선언

	void Execute() {		//함수 포인터 실행
		if (m_fp != NULL)
		{
			(this->*m_fp)();
		}
	}
	void operator > (pt* the)
	{
		if (m_fp != NULL)
		{
			(the->*m_fp)();
		}
	}
public:
	pt();
	pt(int x, int y);
	pt(const pt& obj);

	~pt();

};

