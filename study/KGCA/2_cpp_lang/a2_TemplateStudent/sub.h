#pragma once
#include "Header.h"

//������ �����ϴ� Ŭ����
class sub
{
private:
	int  m_iKor;
	int  m_iEng;
	int  m_iMat;
public:
	//�����ڿ��� ��� �ʱ�ȭ ����� ����� �� �ִ�. (...������)
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
