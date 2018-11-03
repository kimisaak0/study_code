#pragma once
#include <assert.h>

template <typename T>
class SingleLinkedList
{
	template <typename T>
	struct node {
		T data;
		node<T>* next;
	};

	node<T>* pHead;
	node<T>* pThis;
	node<T>* pTail;

	int iSize;

public:
	int getSize();

	int AddData(T data); //리스트 끝에 데이터 추가
	int AddData(int index, T data); //리스트 끝에 데이터 추가
	T& CheckData(int index); //지정한 위치에 있는 데이터를 확인.
	void ChangeData(int index, T data); //지정한 위치에 있는 데이터를 수정.
	int DeleteData(int index); //지정한 위치에 있는 데이터 삭제.
	int DeleteValue(T data); //지정한 값을 가진 노드(들) 삭제.

	T Next(); //리스트 순회용

public:
	SingleLinkedList();
	~SingleLinkedList();
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList()
{
	pHead = nullptr;
	pTail = nullptr;
	
	iSize = 0;
}

//getMethod
template <typename T>
int SingleLinkedList<T>::getSize()
{
	return iSize;
}


//리스트 끝에 데이터 추가
template <typename T>
int SingleLinkedList<T>::AddData(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->next = nullptr;

	if (pHead == nullptr) {
		pHead = newnode;
		pThis = pHead;
	}
	else {
		pTail->next = newnode;
	}
	pTail = newnode;
	
	return ++iSize;
}

//원하는 위치에 데이터 추가
template <typename T>
int SingleLinkedList<T>::AddData(int index, T data)
{
	assert(index >= 0);

	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->next = nullptr;

	if (index == 0) {
		if (pHead == nullptr) {
			pHead = newnode;
			pTail = newnode;
		}
		else {
			newnode->next = pHead;
			pHead = newnode;
		}
		pThis = pHead;
	}
	else if(index >= iSize-1) {
		pTail->next = newnode;
		pTail = newnode;
	}
	else {
		node<T>* pFind = pHead;
		for (int i = 0; i < index-1; i++) {
			pFind = pFind->next;
		}
		newnode->next = pFind->next;
		pFind->next = newnode;
	}

	return ++iSize;
}

//지정한 위치에 있는 데이터를 확인.
template <typename T>
T& SingleLinkedList<T>::CheckData(int index)
{
	assert(index >= 0);
	node<T>* pFind = pHead;
	for (int i = 0; i < index; i++) {
		pFind = pFind->next;
	}
	
	return pFind->data;
}

//지정한 위치에 있는 데이터를 수정.
template <typename T>
void SingleLinkedList<T>::ChangeData(int index, T data)
{
	assert(index >= 0);
	node<T>* pFind = pHead;
	for (int i = 0; i < index; i++) {
		pFind = pFind->next;
	}

	pFind->data = data;
}

//지정한 위치에 있는 데이터를 삭제
template <typename T>
int SingleLinkedList<T>::DeleteData(int index)
{
	assert(index >= 0);

	node<T>* pDel = nullptr;
	int iIndex = index;

	if (index == 0) {
		pDel = pHead;
		pHead = pHead->next;
		delete pDel;
		pThis = pHead;
	}
	else if (index >= iSize - 1) {
		iIndex = iSize - 1;
	}

	node<T>* pFind = pHead;
	for (int i = 0; i < iIndex -1; i++) {
		pFind = pFind->next;
	}

	pDel = pFind->next;
	pFind->next = pDel->next;
	delete pDel;

	return --iSize;
}

//특정한 값을 가진 노드(들) 삭제
template <typename T>
int SingleLinkedList<T>::DeleteValue(T data)
{
	node<T>* pDel = nullptr;
	while (pHead != nullptr && pHead->data == data) {
		pDel = pHead;
		pHead = pHead->next;
		delete pDel;
		pThis = pHead;
		iSize--;
	}

	if (pHead == nullptr) {
		return 0;
	}

	node<T>* pFind = pHead;
	while (pFind->next != nullptr) {
		if (pFind->next->data == data) {
			pDel = pFind->next;
			pFind->next = pFind->next->next;
			delete pDel;
			iSize--;
		}
		else {
			pFind = pFind->next;
		}
	}

	return iSize;

}

//리스트 순회용
template <typename T>
T SingleLinkedList<T>::Next()
{
	T ret = pThis->data;

	if (pThis->next != nullptr) {
		pThis = pThis->next;
	}

	return ret;
}


template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
	node<T>* pDel = nullptr;
	node<T>* pFind = pHead;
	while (pFind != nullptr) {
		pDel = pFind;
		pFind = pFind->next;
		delete pDel;
	}
	
	pHead = nullptr;
	pTail = nullptr;
	pThis = nullptr;

	iSize = 0;
}