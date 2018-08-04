#pragma once

#include "header.h"

namespace sta
{

	using BYTE = unsigned char;
	// == typedef unsigned char BYTE ;

	//static_cast : �ǹ̾��� ����ȯ ����



	class sA
	{
	public:
		virtual void Test() {}
	};

	class sB : public sA 
	{
		//������ ����(..)
	};
	
	class sD
	{
	public:
		float m_fValue;


		//operator sC()
		//{
		//	//��� �ʱ�ȭ
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
			//��� �ʱ�ȭ
			sD fRet = { static_cast<float>(m_iValue) };
			return fRet;
		}
	};


	//�Լ���
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

		//�̷����� ����ȯ�� �����Ϸ��� ����� �𸣹Ƿ� �Ұ����ϴ�. 
		//sA aaa = static_cast<sA>(ch);
	}

	void func(sA* pa, sB* pb)
	{
		//sA(�θ�)�� �����͸� sB(�ڽ�)�� �����ͷ� ����ȯ �õ�
		//�������� �ʴ�. (unsafe conversion)
		sB* pb1 = dynamic_cast<sB*>(pa);
		sB* pb2 = static_cast<sB*>(pa);

		if (pb1 == nullptr) {
			cout << "pb1 == nullptr ĳ���� ����" << endl;
		}
		else {
			cout << "pb1 != nullptr ĳ���� ����" << endl;
		}

		if (pb2) {
			cout << "pb2 != nullptr ĳ���� ����" << endl;
		}
		else {
			cout << "pb2 == nullptr ĳ���� ����" << endl;
		}

		//sB(�ڽ�)�� �����͸� sA(�θ�)�� �����ͷ� ����ȯ �õ�
		//�����ϴ�.      (safe conversion);
		sA* pa1 = dynamic_cast<sA*>(pb);
		sA* pa2 = static_cast<sA*>(pb);

		if (pa1 == nullptr) {
			cout << "pa1 == nullptr ĳ���� ����" << endl;
		}
		else {
			cout << "pa1 != nullptr ĳ���� ����" << endl;
		}

		if (pa2) {
			cout << "pa2 != nullptr ĳ���� ����" << endl;
		}
		else {
			cout << "pa2 == nullptr ĳ���� ����" << endl;
		}
	}

	void func(sC& pc, sD& pd)
	{
		//��� ���谡 �ƴ� Ŭ���������� ����ȯ�� Dynamic_cast�� ������� �ʴ´�.	
		// sC* pc1 = dynamic_cast<sC*>(pd);
		// sD* pd1 = dynamic_cast<sD*>(pc);

		//static_cast�� �����Ϸ��� ����ȯ ����� �˸� ��ȯ���ش�.
		//�׷��� �����Ϸ��� ����ȯ ����� �𸣸� �˷���� �Ѵ�.
		//sC pc2 = static_cast<sC>(pd); //����ȯ ��� ���� ����
		sD pd2 = static_cast<sD>(pc); //����ȯ ��� ���� ��

		cout << "pc.m_iValue : " << pc.m_iValue << endl;
		cout << "pd.m_fValue : " << pd.m_fValue << endl;
		cout << "pd2.m_fValue : " << pd2.m_fValue << endl;
		
	}
}