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

//���� Ŭ���� A
//������� ����
class ExceptA
{
public:
	void What()
	{
		cout << "ExceptA" << endl;
	}
};

//���� Ŭ���� B
//������� ����
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