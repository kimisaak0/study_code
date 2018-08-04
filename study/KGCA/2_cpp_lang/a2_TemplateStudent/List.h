#pragma once
#include "node.h"

//���Ḯ��Ʈ Ŭ���� ���ø�
template <class T>
class list
{
public:
	int       m_iCount; //����Ʈ�� ����� ����� ���� �����ϴ� ���� 
	node<T>*  m_pHead;  //����Ʈ�� ���� ��带 ����Ű�� ������
	node<T>*  m_pTail;  //����Ʈ��   �� ��带 ����Ű�� ������

public:
	int       size();  //����Ʈ�� ����� ����� ���� ��ȯ

	bool      addLinkHead(T* pStud); //����Ʈ �տ� ��带 �߰�
	bool      addLinkTail(T* pStud); //����Ʈ �ڿ� ��带 �߰�
	bool      delLink(T* pStud); //����Ʈ���� ��带 ����

	void      delList(); //����Ʈ ��ü ����

	T*        getData(int iIndex);  //������ ��ġ�� �����͸� ��ȯ
	
	node<T>*  getHead();            //��� �����͸� ��ȯ
	node<T>*  getTail();            //���� �����͸� ��ȯ

	bool      sort(bool bUp);      //��带 ������

	list();
	~list();
};

//��� �Լ� ����
template <class T> int       list<T>::size() 
{
	return m_iCount; 
}

template <class T> bool      list<T>::addLinkHead(T* pData)
{
	node<T>* pNode = new node<T>();
	pNode->m_pData = pData;

	//����Ʈ�� �����Ͱ� ���� ���
	if (m_pHead == NULL) { 
		m_pHead = pNode;
		m_pTail = pNode;
	}
	//�̹� �����Ͱ� �ִ� ���
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

	//����Ʈ�� �����Ͱ� ���� ���
	if (m_pHead == NULL) {
		m_pHead = pNode;
		m_pTail = pNode;
	}
	//�̹� �����Ͱ� �ִ� ���
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
	//����
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