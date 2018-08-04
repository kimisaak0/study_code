#pragma once
#include <iostream>

class class_A
{
private:
	int m_iValue;

public:

	int Get() const { return m_iValue; }

	class_A(int iValue) : m_iValue(iValue) {}
	class_A(class_A& copy) : m_iValue(copy.m_iValue) {}
	~class_A() { }
};

class class_E
{
private:
	int m_iValue;

public:
	int Get() const	{ return m_iValue; }

	//explicit는 생성자 앞에 붙여서 묵시적인 호출을 방지한다. 
	//이는 명시적인 호출만 가능토록 한다.
	explicit class_E(int iValue) : m_iValue(iValue) {}
	
	//explicit를 복사 생성자에 사용하면 
	//대입 연산자를 통하여 객체의 생성 및 초기화를 할 수 없다.
	explicit class_E(class_E& copy) : m_iValue(copy.m_iValue) {}
	
	~class_E() { }
};

class class_M
{
private:
	int m_iValue;

	//mutable이 붙은 변수는 const함수에서도 변경이 가능하다.
	//즉 이는 const에 대한 예외가 된다.
	mutable int m_iData;

public:
	int Get() const
	{
		return m_iValue;
	}

	int Get(int iValue) const
	{
         m_iData = iValue;     //가능
	   //m_iValue = iValue;    //불가능
	     return m_iData;
	}

	explicit class_M(int iValue) : m_iValue(iValue)	{ }
	explicit class_M(class_M& copy) : m_iValue(copy.m_iValue) { }
	~class_M() { }
};