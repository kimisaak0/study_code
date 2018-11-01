#pragma once
#include "sub.h"


//학생 정보를 저장하는 클래스
class stu
{
private:
	int      m_iIndex;
	wstring  m_strName;
	sub      m_sub;			//sub클래스를 멤버로 포함
	int      m_iTotal;
	double   m_dAverage;

public:
	void     setIndex(int iIndex);
	int      getIndex();
	
	void     setName(wstring name);
	wstring  getName();
	
	void     setSub(int m_iKor, int m_iEng, int m_iMat); //sub클래스를 세팅
	sub      getSub();                                   //sub클래스를 반환
	
	int      getTotal();
	double   getAverage();
public:
	stu();
	~stu();
};

//멤버 함수 정의
void     stu::setIndex(int iIndex)
{
	m_iIndex = iIndex;
}

int      stu::getIndex()
{
	return m_iIndex;
}

void     stu::setName(wstring name)
{
	m_strName = name;
}

wstring  stu::getName()
{
	
	if (this == nullptr) {	throw 0; }

	//try {
	//	if (this == nullptr) {
	//		ExceptB();
	//	}
	//}
	//catch (ExceptB& ex) {
	//	cout << "Catch Except A" << endl;
	//	ex.what();
	//}
	
	return m_strName;
}

void     stu::setSub(int m_iKor, int m_iEng, int m_iMat)
{
	m_sub.set(m_iKor, m_iEng, m_iMat);
	m_iTotal = m_iKor + m_iEng + m_iMat;
	m_dAverage = m_iTotal / 3.0;
}

sub      stu::getSub()
{
	return m_sub;
}

int      stu::getTotal()
{
	return m_iTotal;
}
double   stu::getAverage()
{
	return m_dAverage;
}

stu::stu()
{
	//cout << "stu" << endl;
	m_dAverage = 0.0;
	m_iTotal = 0;
	m_iIndex = -1;
	//m_pNext = nullptr;
	//m_pPrev = nullptr;
}

stu::~stu()
{
	
	//cout << "~stu" << endl;
}