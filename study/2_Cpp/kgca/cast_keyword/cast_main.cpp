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

		// 부모 => 자식 (상속관계)
		// dA => dB => dC

		//자식의 자식을 동적할당
		dA* pa1 = new dC;  
		//가상 함수이므로 실제 자식의 것으로 실행됨.
		pa1->test(); 

		//자식을 동적할당
		dA* pa2 = new dB;  
		//부모에는 test2 함수가 없으므로 호출할 수 없다.
		//pa2->test2();


		//pa1에 들어있는 메모리는 C
		//그러므로 B(부모)의 포인터로 캐스팅 가능
		dB* pb = dynamic_cast<dB*>(pa1); 
		if (pb) { // == if(pb != nullptr) 
			pb->test();  //가상함수인 경우      : 메모리의 함수(class C의 함수) 호출
			pb->test2(); //가상함수가 아닌 경우 : 포인터의 함수(class B의 함수) 호출
		}

		//pa2에 들어있는 메모리는 B
		//그러므로 C(자식)의 포인터로 캐스팅 불가능
		dC* pc = dynamic_cast<dC*>(pa2); 
		if (pc != nullptr) { // == if(pc)  
			pc->test();
			pc->test2();
		}

		//A(부모)는 B(자식)을 알고 있지 않기 때문에 실패.
		dA AonStack;
		Globaltest(AonStack);

		//B(자신)은 B(자신)을 알고 있으므로 당연히 가능.
		dB BonStack;
		Globaltest(BonStack);

		//C(자식)은 B(부모)를 알고 있으므로 가능.
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
	//반환값이 const인 함수는 const 변수로 받아야 함.
	const int* iValue = X.GetConst();
	//*iValue = 20; //상수 에러

	//2
	int* iValue2 = const_cast<int*>(X.GetConst());
	*iValue2 = 20;
	X.printNumber();

	//이렇게 멤버 변수를 바꿀수도 있구나(...)
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

		//두 개의 값이 동일한 경우 주소를 사용하여 해시값을 얻을 수 있다.
		//주소를 인덱스에 매핑하는 해시함수에서 reinterpret_cast를 유용하게 사용할 수 있다.
		int a[3] = { 1,2,3 };
		for (int iCnt = 0; iCnt < 3; iCnt++) {
			cout << a[iCnt] << " " << hash_1(a + iCnt) << endl;
		}

		int iArray[100];

		//이부분을 왜 이렇게 해놨는지 모르겠음...(...)
		//여기서부터
		for (int iCnt = 0; iCnt < 10; iCnt++) {
			iArray[iCnt] = iCnt + 1;
			unsigned short iHash = hash_2(&iArray[iCnt]);
			set(iHash, iArray[iCnt]);
		}

		for (int iCnt = 0; iCnt < 10; iCnt++) {
			unsigned short iHash = hash_2(&iArray[iCnt]);
			cout << get(iHash, iArray[iCnt]) << " " << endl;
		}
		//여기까지
		

		//주소값을 수치로 바꿔서 주소에 접근하기.
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