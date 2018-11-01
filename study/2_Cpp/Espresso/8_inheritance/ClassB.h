#pragma once
#include "ClassA.h"

class ClassB :public ClassA
{
private:
	int m_iPrivateB;

	void Bprivate() const
	{
		cout << "Bprivate" << endl;
	}


protected:
	int m_iProtectedB;

	void Bprotected() const
	{
		cout << "Bprotected" << endl;
	}

public:
	int m_iPublicB;

	void Bpublic() const
	{
		cout << "Bpublic" << endl;
	}

	//�����ڵ�
	int getPrivateInt() const
	{
		return m_iPrivateB;
	}

	int getProtected() const
	{
		return m_iProtectedB;
	}

	int getPublic() const
	{
		return m_iPublicB;
	}

	//�θ� Ŭ������ �����ϱ�

	void AinB() const
	{
		cout << "AinB()���� ȣ��" << endl;

		cout << endl;
		cout << "A�� public ����    : ���� ���� "; cout <<    m_iPublicA << endl;
		cout << "A�� protected ���� : ���� ���� "; cout <<    m_iProtectedA << endl;
		cout << "A�� private ����   : ���� �Ұ� "; cout /* << m_iPrivateA */ << endl; 
		cout << "A�� public �Լ�    : ���� ���� ";            Apublic();
		cout << "A�� protected �Լ� : ���� ���� ";            Aprotected();
		cout << "A�� private �Լ�   : ���� �Ұ� ";          //Aprivate();
	
		cout << endl;
	}

	//�������̵��� �Լ�

	int m_iID; //������ ������ 

	//void showID()
	//{
	//	cout << m_iID << endl;
	//}

	void overriding()
	{
		cout << "ClassB " << m_iID << "�� overriding" << endl;
	}

public:
	ClassB()
	{
		//A�� �����ڸ� �������� ����
		cout << "ClassB�� �⺻ ������" << endl;

		m_iPrivateB = 'B' + 10000;
		m_iProtectedB = 'B' + 20000;
		m_iPublicB = 'B' + 30000;

		m_iID = 'B';
	}

	ClassB(int id)
	{
		// A�� �����ڸ� �������� ����
		cout << "ClassB�� ������ ID : " << m_iID << endl;

		m_iPrivateB = 'B' + 10000;
		m_iProtectedB = 'B' + 20000;
		m_iPublicB = 'B' + 30000;

		m_iID = id;
	}

	ClassB(int Aid, int Bid) : ClassA(Aid)
	{
		// A�� �����ڸ� ������
		cout << "ClassB�� ������ ID : " << m_iID << endl;

		m_iPrivateB = 'B' + 10000;
		m_iProtectedB = 'B' + 20000;
		m_iPublicB = 'B' + 30000;

		m_iID = Bid;
	}

	virtual ~ClassB()
	{
		cout << "�ڽ��� �Ҹ���" << endl;
	}

};

