#pragma once
#include "header.h"

class token;

class value // 문자열을 저장하는 리스트 구조 클래스
{
private:
	TCHAR*  m_szValue;	//문자열을 저장하는 변수
	value*  m_pNext;	//다음 노드를 가리키는 포인터.
	friend class token;

	//생성자도 private로 하면 token만이 사용할 수 있는 전용 클래스가 된다.
	value(TCHAR*);
	~value();
};


//템플릿 함수는 일단 패스.
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