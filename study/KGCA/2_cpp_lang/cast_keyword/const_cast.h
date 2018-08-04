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

		//const ��� ������ ������ �⺻ �����ڰ� �߰����� �ʴ´�.
		//�����ڿ��� const ��� ������ �ʱ�ȭ�ؾ��ϱ� �����̴�.
		cc_test() : cn(0) {}
		~cc_test() {}
	};

	void       cc_test::setNumber(int n)
	{
		
		//const_cast<int>cn = n;
		//const_cast�� ������ ��ü ���Ŀ� ���� ������, ���� �Ǵ� ��� �����Ϳ��� �մϴ�.

		number = n;
	}

	//����Լ��� const�� ������ �� �Լ� �������� Ŭ���� ��ü�� const class�� ��޵ȴ�.
	void       cc_test::printNumber() const
	{
		//const �Լ����� ��� ������ ���� �����ϱ�(..)
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