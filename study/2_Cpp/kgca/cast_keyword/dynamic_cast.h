#pragma once
#include "header.h"

namespace dyn
{
	//dynamic_cast�� vtable�� ����ϱ� ������ �ݵ�� virtual �Լ��� �־�� �۵��Ѵ�.

	class dA {
	public:
		virtual void test() {
			cout << "test in A" << endl;
		}
	};

	//��ӽ� ���������ڸ� �����ϸ� class�� private��, struct�� union�� public���� ��ӵȴ�.
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

	//�θ� Ŭ������ ���۷����� �Ű������� �޴� �Լ�
	void Globaltest(dA& da)
	{
		try {
			//�Ű������� ���� a�� B&�� ĳ����
			dB& b = dynamic_cast<dB&>(da);
			cout << "Success cast to B " << endl;
		}

		//ĳ���� ���н� dynamic_cast�����ڴ� ���� Ŭ���� std::bad_cast�� ������.
		catch (std::bad_cast) {
			cout << "Can't cast to B" << endl;
		}
	}
}