#pragma once
#include "header.h"

namespace dyn
{
	//dynamic_cast는 vtable을 사용하기 떄문에 반드시 virtual 함수가 있어야 작동한다.

	class dA {
	public:
		virtual void test() {
			cout << "test in A" << endl;
		}
	};

	//상속시 접근지정자를 생략하면 class는 private로, struct와 union은 public으로 상속된다.
	class dB : public dA {
	public:
		virtual void test() {
			cout << "test in B" << endl;
		}

		void test2() {
			cout << "test2 in B" << endl;
		}

	};


	class dC : public dB {
	public:
		virtual void test() {
			cout << "test in C" << endl;
		}

		void test2() {
			cout << "test2 in C" << endl;
		}

	};

	//부모 클래스의 레퍼런스를 매개변수로 받는 함수
	void Globaltest(dA& da)
	{
		try {
			//매개변수로 받은 a를 B&로 캐스팅
			dB& b = dynamic_cast<dB&>(da);
			cout << "Success cast to B " << endl;
		}

		//캐스팅 실패시 dynamic_cast연산자는 예외 클래스 std::bad_cast를 던진다.
		catch (std::bad_cast) {
			cout << "Can't cast to B" << endl;
		}
	}
}