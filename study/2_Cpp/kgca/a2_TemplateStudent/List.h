#pragma once
#include "node.h"

//연결리스트 클래스 템플릿
template <class T>
class list
{
public:
	int       m_iCount; //리스트에 저장된 노드의 수를 저장하는 변수 
	node<T>*  m_pHead;  //리스트의 시작 노드를 가리키는 포인터
	node<T>*  m_pTail;  //리스트의   끝 노드를 가리키는 포인터

public:
	int       size();  //리스트에 저장된 노드의 수를 반환

	bool      addLinkHead(T* pStud); //리스트 앞에 노드를 추가
	bool      addLinkTail(T* pStud); //리스트 뒤에 노드를 추가
	bool      delLink(T* pStud); //리스트에서 노드를 삭제

	void      delList(); //리스트 전체 삭제

	T*        getData(int iIndex);  //선택한 위치의 데이터를 반환
	
	node<T>*  getHead();            //헤드 포인터를 반환
	node<T>*  getTail();            //테일 포인터를 반환

	bool      sort(bool bUp);      //노드를 정렬함

	list();
	~list();
};

//멤버 함수 정의
template <class T> int       list<T>::size() 
{
	return m_iCount; 
}

template <class T> bool      list<T>::addLinkHead(T* pData)
{
	node<T>* pNode = new node<T>();
	pNode->m_pData = pData;

	//리스트에 데이터가 없는 경우
	if (m_pHead == NULL) { 
		m_pHead = pNode;
		m_pTail = pNode;
	}
	//이미 데이터가 있는 경우
	else
	{
		node<T>* pFirst = m_pHead;
		m_pHead = pNode;

		pNode -> m_pNext = pFirst;
		pFirst  -> m_pPrev = pNode;
	}
	m_iCount++;
	return true;
}

template <class T> bool      list<T>::addLinkTail(T* pData)
{
	node<T>* pNode = new node<T>();
	pNode->m_pData = pData;

	//리스트에 데이터가 없는 경우
	if (m_pHead == NULL) {
		m_pHead = pNode;
		m_pTail = pNode;
	}
	//이미 데이터가 있는 경우
	else
	{
		node<T>* pLast = m_pTail;
		m_pTail = pNode;

		pNode -> m_pPrev = pLast;
		pLast   -> m_pNext = pNode;
	}
	m_iCount++;
	return true;
}

template <class T> bool      list<T>::delLink(T* pStud)
{
	return true;
}

template <class T> void      list<T>::delList()
{
	node<T>* pDelNode = nullptr;
	node<T>* pNode = m_pHead;
	
	while (pNode != NULL) 
	{
		pDelNode = pNode;
		pNode = pNode->m_pNext;
		delete pDelNode;
	}

	m_pHead = nullptr;
	m_pTail = nullptr;
}

template <class T> T*        list<T>::getData(int iIndex)
{
	node<T>* pNode = m_pHead;
	while (pNode != nullptr) {
		if (pNode->m_pData->getIndex() == iIndex) {
			T* pData = pNode->m_pData;
			return pData;
		}
		pNode = pNode->m_pNext;
	}
	return NULL;
}

template <class T> node<T>*  list<T>::getHead() 
{
	return m_pHead; 
}

template <class T> node<T>*  list<T>::getTail()
{
	return m_pTail;
}


template <class T> bool      list<T>::sort(bool bUp)
{
	//정렬
}

template <class T>           list<T>::list()
{
	m_pHead = nullptr;
	m_pTail = nullptr;
	m_iCount = 0;
}

template <class T>           list<T>::~list()
{
	delList();
	//cout << "linkedlist end" << endl;
}