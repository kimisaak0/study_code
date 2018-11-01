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

	//접근자들
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

	//오버라이딩용 함수

	int m_iID;

	void showID()
	{
		cout << m_iID << endl;
	}

	void overriding()
	{
		cout << "ClassA" << m_iID << "의 overriding" << endl;
	}

public:
	ClassA()
	{
		cout << "ClassA의 기본 생성자" << endl;

		m_iPrivateA = 'A' + 10000;
		m_iProtectedA = 'A' + 20000;
		m_iPublicA = 'A' + 30000;

		m_iID = 'A';
	}

	ClassA(int id)
	{
		cout << "ClassA의 생성자 ID : " << m_iID << endl;

		m_iPrivateA = 'A' + 10000;
		m_iProtectedA = 'A' + 20000;
		m_iPublicA = 'A' + 30000;

		m_iID = id;
	}

	virtual ~ClassA()
	{
		cout << "ClassA의 소멸자" << endl;
	}
};

