#pragma once

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// const char& operator []() const {}
// char& operator [] () 두 함수는 별개의 함수가 된다.

//재정의가 금지된 연산자
//1) 선택 연산자 : .
//2) 포인터 선택 연산자 : .*
//3) 영역 연산자 : ::
//4) 조건 연산자 : ? :
//5) 크기 연산자 : sizeof


//재정의가 가능한 연산자는 다 적어두고 실제 구현은 생략했다.
//리턴형이 정해진 것이 아니라면 다 point클래스를 반환하도록 했다.

class point
{


public:
	//왜 재정의하는지 잘 모르겠는 연산자(..)
	point * operator-> () { return this; } // 멤버 선택 연산자
	point& operator* () { return *this; } // 포인터 역참조 연산자
	point operator->* (const point& p);	  // 멤버 포인터 선택 연산자

	point operator() (...); //함수 호출 연산자
	point& operator, (point& p) const; //쉼표 연산자
									   // void operatorR() const; //캐스트 연산자 ???

									   //할당 및 할당 취소 연산자
	void* operator new (size_t i);
	void* operator delete (size_t i);
	void operator new[](size_t i);
	void operator delete[](size_t i);

	point operator[] (point& p); // 배열 연산자

								 //[]는 인덱싱을 구현하는데 더 많이 쓰인다.
	int operator[] (int i);

	//단항 증감연산자, 매개변수는 전위와 후위를 나누는데만 쓰인다.
	point operator++ (); // 전위 증가 연산자
	point operator-- (); // 전위 감소 연산자
	point operator++ (int); //후위 증가 연산자
	point operator-- (int); //후위 감소 연산자

							//단항 부호연산자.
	point operator+ () const;
	point operator- () const;

	//이항 사칙 연산자. 같은 클래스끼리 연산
	point operator+ (const point& p) const;
	point operator- (const point& p) const;
	point operator* (const point& p) const;
	point operator/ (const point& p) const;
	point operator% (const point& p) const;

	//이항 사칙 연산자. 서로 다른 타입과의 연산
	//int형과의 연산만 정의했으며 다른 타입과의 연산이 필요하면 따로 정의해야한다.
	//교환 법칙도 따로 만들어 주지 않으면 성립하지 않는다.
	point operator+ (int i);
	friend point operator+ (int i, const point& p);

	point operator- (int i);
	friend point operator- (int i, const point& p);

	point operator* (int i);
	friend point operator* (int i, const point& p);

	point operator/ (int i);
	friend point operator/ (int i, const point& p);

	friend point operator% (const point& p, int i); //그냥 이렇게 해도 되긴 한다.
	friend point operator% (int i, const point& p);



	//비교 연산자
	bool operator== (const point& p);
	bool operator!= (const point& p);
	bool operator>  (const point& p);
	bool operator<  (const point& p);
	bool operator>= (const point& p);
	bool operator<= (const point& p);


	//논리 연산자
	bool operator! () const; //부정
	bool operator&& (const point& p) const; //그리고
	bool operator|| (const point& p) const; //또는


											//비트 연산자
	point operator~ () const; //비트 부정
	point operator& (const point& p); //비트 and;
	point operator| (const point& p); //비트 or;
	point operator^ (const point& p); //비트 xor;
	point operator<< (const point& p); // 비트 왼쪽 시프트
	point operator>> (const point& p); // 비트 오른쪽 시프트


									   //대입 연산자, 복합 대입 연산자
	point& operator=  (const point& p);
	point& operator+= (const point& p);
	point& operator-= (const point& p);
	point& operator*= (const point& p);
	point& operator/= (const point& p);
	point& operator%= (const point& p);
	point& operator&= (const point& p);
	point& operator|= (const point& p);
	point& operator^= (const point& p);
	point& operator>>= (const point& p);
	point& operator<<= (const point& p);


	//입출력 연산자 재정의
	friend std::ostream& operator<<(std::ostream &os, const point& pt);
	friend std::istream& operator>>(std::istream &is, point& pt);

	//다른 타입과의 복합 대입도 재정의 가능하다.
	point& operator+= (int i);

	//이런것도 가능하긴 하다
	bool operator== (int i);
	friend bool operator== (int i, const point& p);

	bool operator&& (int i);
	friend bool operator&& (int i, const point& p);

	point operator^ (int i);
	friend bool operator^ (int i, const point& p);



	//진짜 별개 다 된다(..)
};

