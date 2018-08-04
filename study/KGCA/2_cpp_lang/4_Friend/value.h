#pragma once
#include "header.h"

class token;

class value // ���ڿ��� �����ϴ� ����Ʈ ���� Ŭ����
{
private:
	TCHAR*  m_szValue;	//���ڿ��� �����ϴ� ����
	value*  m_pNext;	//���� ��带 ����Ű�� ������.
	friend class token;

	//�����ڵ� private�� �ϸ� token���� ����� �� �ִ� ���� Ŭ������ �ȴ�.
	value(TCHAR*);
	~value();
};


//���ø� �Լ��� �ϴ� �н�.
static vector<string>& split(const string &s, char delim, vector<string>& elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

static vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}