#pragma once

#include "header.h"

namespace sta
{

	using BYTE = unsigned char;
	// == typedef unsigned char BYTE ;

	//static_cast : 의미없는 형변환 방지



	class sA
	{
	public:
		virtual void Test() {}
	};

	class sB : public sA 
	{
		//내용이 없다(..)
	};
	
	class sD
	{
	public:
		float m_fValue;


		//operator sC()
		//{
		//	//멤버 초기화
		//	sD fRet = { static_cast<int>(m_fValue) };
		//	return fRet;
		//}
	};

	class sC
	{
	public:
		int m_iValue;

		operator sD()
		{
			//멤버 초기화
			sD fRet = { static_cast<float>(m_iValue) };
			return fRet;
		}
	};


	//함수들
	void func() {

		BYTE ch = 'a';
		int i = 75;
		float f = 2.5f;
		double db = 3.14;

		cout << ch << " " << i << " " << f << " " << db << endl;

		BYTE chi = static_cast<BYTE>(i);    //int to BYTE(unsigned char);
		int ich = static_cast<int>(ch);    //BYTE(unsigned char) to int
		float fdb = static_cast<float>(db);   //double to float;
		double dbf = static_cast<double>(f); //float to double;

		cout << chi << " " << ich << " " << fdb << " " << dbf << endl;

		//이런식의 형변환은 컴파일러가 방법을 모르므로 불가능하다. 
		//sA aaa = static_cast<sA>(ch);
	}

	void func(sA* pa, sB* pb)
	{
		//sA(부모)의 포인터를 sB(자식)의 포인터로 형변환 시도
		//안전하지 않다. (unsafe conversion)
		sB* pb1 = dynamic_cast<sB*>(pa);
		sB* pb2 = static_cast<sB*>(pa);

		if (pb1 == nullptr) {
			cout << "pb1 == nullptr 캐스팅 실패" << endl;
		}
		else {
			cout << "pb1 != nullptr 캐스팅 성공" << endl;
		}

		if (pb2) {
			cout << "pb2 != nullptr 캐스팅 성공" << endl;
		}
		else {
			cout << "pb2 == nullptr 캐스팅 실패" << endl;
		}

		//sB(자식)의 포인터를 sA(부모)의 포인터로 형변환 시도
		//안전하다.      (safe conversion);
		sA* pa1 = dynamic_cast<sA*>(pb);
		sA* pa2 = static_cast<sA*>(pb);

		if (pa1 == nullptr) {
			cout << "pa1 == nullptr 캐스팅 실패" << endl;
		}
		else {
			cout << "pa1 != nullptr 캐스팅 성공" << endl;
		}

		if (pa2) {
			cout << "pa2 != nullptr 캐스팅 성공" << endl;
		}
		else {
			cout << "pa2 == nullptr 캐스팅 실패" << endl;
		}
	}

	void func(sC& pc, sD& pd)
	{
		//상속 관계가 아닌 클래스끼리의 형변환은 Dynamic_cast가 허락하지 않는다.	
		// sC* pc1 = dynamic_cast<sC*>(pd);
		// sD* pd1 = dynamic_cast<sD*>(pc);

		//static_cast는 컴파일러가 형변환 방법을 알면 변환해준다.
		//그러나 컴파일러가 형변환 방법을 모르면 알려줘야 한다.
		//sC pc2 = static_cast<sC>(pd); //형변환 방법 지정 안함
		sD pd2 = static_cast<sD>(pc); //형변환 방법 지정 함

		cout << "pc.m_iValue : " << pc.m_iValue << endl;
		cout << "pd.m_fValue : " << pd.m_fValue << endl;
		cout << "pd2.m_fValue : " << pd2.m_fValue << endl;
		
	}
}