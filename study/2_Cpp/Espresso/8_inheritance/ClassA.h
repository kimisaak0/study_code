#pragma once
#include "header.h"

class ClassA
{
private:
	int m_iPrivateA;

	void Aprivate() const
	{
		cout << "Aprivate" << endl;
	}


protected:
	int m_iProtectedA;

	void Aprotected() const
	{
		cout << "Aprotected" << endl;
	}

public:
	int m_iPublicA;

	void Apublic() const  
	{
		cout << "Apublic" << endl;
	}

	//�����ڵ�
	int getPrivateInt() const
	{
		return m_iPrivateA;
	}

	int getProtected() const
	{
		return m_iProtectedA;
	}

	int getPublic() const
	{
		return m_iPublicA;
	}

	//�������̵��� �Լ�

	int m_iID;

	void showID()
	{
		cout << m_iID << endl;
	}

	void overriding()
	{
		cout << "ClassA" << m_iID << "�� overriding" << endl;
	}

public:
	ClassA()
	{
		cout << "ClassA�� �⺻ ������" << endl;

		m_iPrivateA = 'A' + 10000;
		m_iProtectedA = 'A' + 20000;
		m_iPublicA = 'A' + 30000;

		m_iID = 'A';
	}

	ClassA(int id)
	{
		cout << "ClassA�� ������ ID : " << m_iID << endl;

		m_iPrivateA = 'A' + 10000;
		m_iProtectedA = 'A' + 20000;
		m_iPublicA = 'A' + 30000;

		m_iID = id;
	}

	virtual ~ClassA()
	{
		cout << "ClassA�� �Ҹ���" << endl;
	}
};

