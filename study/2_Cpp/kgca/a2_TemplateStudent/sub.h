#pragma once
#include "Header.h"

//점수를 저장하는 클래스
class sub
{
private:
	int  m_iKor;
	int  m_iEng;
	int  m_iMat;
public:
	//생성자에만 멤버 초기화 목록을 사용할 수 있다. (...몰랐다)
	void set(int kor, int eng, int mat) 
	{
		m_iKor = kor;
		m_iEng = eng;
		m_iMat = mat;
	}
	int  getKor() { return m_iKor; }
	int  getEng() { return m_iEng; }
	int  getMat() { return m_iMat; }
public:
	sub() : m_iKor(0), m_iEng(0), m_iMat(0) {}
	~sub() {}
};
