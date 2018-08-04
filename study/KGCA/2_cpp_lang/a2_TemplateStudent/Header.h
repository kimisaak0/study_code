#pragma once
#include <iostream>
#include <string>
#include <tchar.h>
#include <new>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::wstring;
using std::wcout;
using std::bad_alloc;

//예외 클래스 A
//사용하진 않음
class ExceptA
{
public:
	void What()
	{
		cout << "ExceptA" << endl;
	}
};

//예외 클래스 B
//사용하진 않음
class ExceptB
{
public:
	void what() {
		cout << "stu::GetName() this==NULL" << endl;
	}
};

template<typename T> void swapP(T* a, T* b)
{
	a->m_pNext = b;
	b->m_pPrev = a;
}