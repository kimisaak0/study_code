#pragma once
#include "header.h"

namespace con
{
	class cc_test {
		      int number;
		const int cn;

	public:
		void       setNumber(int n);
		void       printNumber() const;
		const int* GetConst();
		int*       GetNumberPointer();

		//const 멤버 변수가 있으면 기본 생성자가 추가되지 않는다.
		//생성자에서 const 멤버 변수를 초기화해야하기 때문이다.
		cc_test() : cn(0) {}
		~cc_test() {}
	};

	void       cc_test::setNumber(int n)
	{
		
		//const_cast<int>cn = n;
		//const_cast의 형식은 개체 형식에 대한 포인터, 참조 또는 멤버 포인터여야 합니다.

		number = n;
	}

	//멤버함수에 const가 붙으면 그 함수 내에서는 클래스 자체가 const class로 취급된다.
	void       cc_test::printNumber() const
	{
		//const 함수에서 멤버 변수의 값을 변경하기(..)
		cout << "\nBefore : " << number;
		const_cast<cc_test *>(this)->number--;
		cout << "\nAfter : " << number << endl;
	}

	const int* cc_test::GetConst()
	{
		return &number;
	}

	int*       cc_test::GetNumberPointer()
	{
		return &number;
	}

}