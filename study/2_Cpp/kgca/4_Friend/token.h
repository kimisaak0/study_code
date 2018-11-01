#pragma once
#include "value.h"

//예외 클래스 인듯.
class EXP
{
public:
	void show(TCHAR* pData)
	{
		wcout << pData;
	}
public:
	EXP() {};
	~EXP() {};
};


//value의 문자열을 잘라서 리스트로 만드는 클래스
class token
{
private:
	value* m_pToken;
	int    m_iSize;
public:
	void   Show();
	void   Show(value* pValue);
	TCHAR* nth_token(int num);

public:
	token();
	token(TCHAR* pData);
	~token();
};

