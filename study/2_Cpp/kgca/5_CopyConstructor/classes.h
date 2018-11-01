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

	//explicit�� ������ �տ� �ٿ��� �������� ȣ���� �����Ѵ�. 
	//�̴� ������� ȣ�⸸ ������� �Ѵ�.
	explicit class_E(int iValue) : m_iValue(iValue) {}
	
	//explicit�� ���� �����ڿ� ����ϸ� 
	//���� �����ڸ� ���Ͽ� ��ü�� ���� �� �ʱ�ȭ�� �� �� ����.
	explicit class_E(class_E& copy) : m_iValue(copy.m_iValue) {}
	
	~class_E() { }
};

class class_M
{
private:
	int m_iValue;

	//mutable�� ���� ������ const�Լ������� ������ �����ϴ�.
	//�� �̴� const�� ���� ���ܰ� �ȴ�.
	mutable int m_iData;

public:
	int Get() const
	{
		return m_iValue;
	}

	int Get(int iValue) const
	{
         m_iData = iValue;     //����
	   //m_iValue = iValue;    //�Ұ���
	     return m_iData;
	}

	explicit class_M(int iValue) : m_iValue(iValue)	{ }
	explicit class_M(class_M& copy) : m_iValue(copy.m_iValue) { }
	~class_M() { }
};