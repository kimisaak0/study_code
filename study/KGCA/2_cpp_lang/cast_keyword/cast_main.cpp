#include "dynamic_cast.h"
#include "static_cast.h"
#include "const_cast.h"
#include "reinterpret_cast.h"

int main()
{

#pragma region dynamic_cast
	{
#define define_dynamic
#ifdef define_dynamic
		using namespace dyn;
#endif
		cout << "dynamic_cast Start" << endl;

		// �θ� => �ڽ� (��Ӱ���)
		// dA => dB => dC

		//�ڽ��� �ڽ��� �����Ҵ�
		dA* pa1 = new dC;  
		//���� �Լ��̹Ƿ� ���� �ڽ��� ������ �����.
		pa1->test(); 

		//�ڽ��� �����Ҵ�
		dA* pa2 = new dB;  
		//�θ𿡴� test2 �Լ��� �����Ƿ� ȣ���� �� ����.
		//pa2->test2();


		//pa1�� ����ִ� �޸𸮴� C
		//�׷��Ƿ� B(�θ�)�� �����ͷ� ĳ���� ����
		dB* pb = dynamic_cast<dB*>(pa1); 
		if (pb) { // == if(pb != nullptr) 
			pb->test();  //�����Լ��� ���      : �޸��� �Լ�(class C�� �Լ�) ȣ��
			pb->test2(); //�����Լ��� �ƴ� ��� : �������� �Լ�(class B�� �Լ�) ȣ��
		}

		//pa2�� ����ִ� �޸𸮴� B
		//�׷��Ƿ� C(�ڽ�)�� �����ͷ� ĳ���� �Ұ���
		dC* pc = dynamic_cast<dC*>(pa2); 
		if (pc != nullptr) { // == if(pc)  
			pc->test();
			pc->test2();
		}

		//A(�θ�)�� B(�ڽ�)�� �˰� ���� �ʱ� ������ ����.
		dA AonStack;
		Globaltest(AonStack);

		//B(�ڽ�)�� B(�ڽ�)�� �˰� �����Ƿ� �翬�� ����.
		dB BonStack;
		Globaltest(BonStack);

		//C(�ڽ�)�� B(�θ�)�� �˰� �����Ƿ� ����.
		dC ConStack;
		Globaltest(ConStack);

		cout << "dynamic_cast End" << endl << endl;

#undef define_dynamic
	}
#pragma endregion

#pragma region static_cast
	{
#define define_static
#ifdef define_static
		using namespace sta;
#endif
		cout << "static_cast Start" << endl;

		func();

		sA a;
		sB b;
		func(&a, &b);


		sC c;
		sD d;
		c.m_iValue = 99;
		d.m_fValue = 0.99f;

		func(c, d);

		cout << "static_cast End" << endl << endl;

#undef define_static
	}
#pragma endregion

#pragma region const_cast
	{
#define define_const
#ifdef define_const
	using namespace con;
#endif

	cout << "const_cast Start" << endl;

	cc_test X;
	X.setNumber(8);
	X.printNumber();

	//1 
	//int* iValue = X.GetConst();
	//��ȯ���� const�� �Լ��� const ������ �޾ƾ� ��.
	const int* iValue = X.GetConst();
	//*iValue = 20; //��� ����

	//2
	int* iValue2 = const_cast<int*>(X.GetConst());
	*iValue2 = 20;
	X.printNumber();

	//�̷��� ��� ������ �ٲܼ��� �ֱ���(...)
	int* iValue3 = X.GetNumberPointer();
	*iValue3 = 30;
	X.printNumber();

	cout << "const_cast End" << endl << endl;


#undef define_const
	}
#pragma endregion

#pragma region reinterpret_cast
	{
#define define_reinterpret
#ifdef define_reinterpret
		using namespace rei;
#endif
		cout << "reinterpret_cast Start" << endl;

		//�� ���� ���� ������ ��� �ּҸ� ����Ͽ� �ؽð��� ���� �� �ִ�.
		//�ּҸ� �ε����� �����ϴ� �ؽ��Լ����� reinterpret_cast�� �����ϰ� ����� �� �ִ�.
		int a[3] = { 1,2,3 };
		for (int iCnt = 0; iCnt < 3; iCnt++) {
			cout << a[iCnt] << " " << hash_1(a + iCnt) << endl;
		}

		int iArray[100];

		//�̺κ��� �� �̷��� �س����� �𸣰���...(...)
		//���⼭����
		for (int iCnt = 0; iCnt < 10; iCnt++) {
			iArray[iCnt] = iCnt + 1;
			unsigned short iHash = hash_2(&iArray[iCnt]);
			set(iHash, iArray[iCnt]);
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			unsigned short iHash = hash_2(&iArray[iCnt]);
			cout << get(iHash, iArray[iCnt]) << " " << endl;
		}
		//�������
		

		//�ּҰ��� ��ġ�� �ٲ㼭 �ּҿ� �����ϱ�.
		__int64 aa = 7;

		__int64 aaa = reinterpret_cast<__int64>(&aa);
		__int64* pAAA;

		cout << aa << endl;

		pAAA = reinterpret_cast<__int64*>(aaa);
		*pAAA = 111;

		cout << aa << endl;

		cout << "reinterpret_cast End" << endl << endl;


#undef define_reinterpret
	}
#pragma endregion
}