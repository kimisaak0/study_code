#pragma once
#include "List.h"


//해쉬테이블
//무슨 역할인지 1도 모르겠음
template <class T>
class hashTable
{
public:
	list<T>*  m_pArray;
	int       m_iLength;

public:
	int       hash(const wchar_t* pName);
	void      insert(T* newitem);
              hashTable(int iLength = 20);
              ~hashTable();
};


//멤버 함수 정의
template <class T> int   hashTable<T>::hash(const wchar_t* pName)
{
	int iKey = 5381;
	int c;
	size_t hash = 0x811c9dc5;

	while (c = *pName++) {
		hash ^= c;
		hash *= 0x01000193;
	}

	//int c;
	//while (c = *pName++) {
	//	iKey = ((iKey << 5) + iKey) + c;
	//}

	//int iValue = 0;
	//int iLen = _tcslen(pName);
	//for (int iCnt = 0; iCnt < iLen; iCnt++) {
	//	iValue += pName[iCnt];
	//}
	//int iKey = (iValue * iValue) % m_iLength;

	return hash % m_iLength;
}

template <class T> void  hashTable<T>::insert(T* newitem)
{
	int iIndex = hash((newitem->getName().c_str()));
	m_pArray[iIndex].addLinkTail(newitem);
}

template <class T>       hashTable<T>::hashTable(int iLength)
{
	m_pArray = new list<T>[iLength];
	m_iLength = iLength;
}

template <class T>       hashTable<T>::~hashTable()
{
	delete[] m_pArray;
}