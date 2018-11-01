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

	//접근자들
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

	//부모 클래스에 접근하기

	void AinB() const
	{
		cout << "AinB()에서 호출" << endl;

		cout << endl;
		cout << "A의 public 변수    : 접근 가능 "; cout <<    m_iPublicA << endl;
		cout << "A의 protected 변수 : 접근 가능 "; cout <<    m_iProtectedA << endl;
		cout << "A의 private 변수   : 접근 불가 "; cout /* << m_iPrivateA */ << endl; 
		cout << "A의 public 함수    : 접근 가능 ";            Apublic();
		cout << "A의 protected 함수 : 접근 가능 ";            Aprotected();
		cout << "A의 private 함수   : 접근 불가 ";          //Aprivate();
	
		cout << endl;
	}

	//오버라이딩용 함수

	int m_iID; //변수만 재정의 

	//void showID()
	//{
	//	cout << m_iID << endl;
	//}

	void overriding()
	{
		cout << "ClassB " << m_iID << "의 overriding" << endl;
	}

public:
	ClassB()
	{
		//A의 생성자를 지정하지 않음
		cout << "ClassB의 기본 생성자" << endl;

		m_iPrivateB = 'B' + 10000;
		m_iProtectedB = 'B' + 20000;
		m_iPublicB = 'B' + 30000;

		m_iID = 'B';
	}

	ClassB(int id)
	{
		// A의 생성자를 지정하지 않음
		cout << "ClassB의 생성자 ID : " << m_iID << endl;

		m_iPrivateB = 'B' + 10000;
		m_iProtectedB = 'B' + 20000;
		m_iPublicB = 'B' + 30000;

		m_iID = id;
	}

	ClassB(int Aid, int Bid) : ClassA(Aid)
	{
		// A의 생성자를 지정함
		cout << "ClassB의 생성자 ID : " << m_iID << endl;

		m_iPrivateB = 'B' + 10000;
		m_iProtectedB = 'B' + 20000;
		m_iPublicB = 'B' + 30000;

		m_iID = Bid;
	}

	virtual ~ClassB()
	{
		cout << "자식의 소멸자" << endl;
	}

};

