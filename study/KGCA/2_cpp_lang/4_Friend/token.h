#pragma once
#include "value.h"

//���� Ŭ���� �ε�.
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


//value�� ���ڿ��� �߶� ����Ʈ�� ����� Ŭ����
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

