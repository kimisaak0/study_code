#pragma once

template <typename T>
class SircularLinkedList
{
	template <typename T>
	struct node {
		T data;
		node<T>* prev;
		node<T>* next;
	};

	node<T>* pHead;
	node<T>* pCursor;

	int iSize;

public:
	int getSize();

	int AddData(int index, T data);       //지정한 위치에 데이터 추가.
	T& CheckData(int index);              //지정한 위치에 있는 데이터를 확인.
	void ChangeData(int index, T data);   //지정한 위치에 있는 데이터를 수정.
	int DeleteData(int index);            //지정한 위치에 있는 데이터 삭제.
	int DeleteValue(T data);              //지정한 값을 가진 노드(들) 삭제.


	void SetCursor(int index);            //커서 포인터를 지정한 위치로 이동.
	//리스트 순회용
	T& Next();
	T& Prev();

public:
	SircularLinkedList();
	~SircularLinkedList();
};

template <typename T>
SircularLinkedList<T>::SircularLinkedList()
{
	pHead = nullptr;
	iSize = 0;
}

//getMethod
template <typename T>
int SircularLinkedList<T>::getSize()
{
	return iSize;
}

//원하는 위치에 데이터 추가 (맨 앞에 추가하고 싶다면 -1을, 맨 끝에 추가하고 싶다면 getSize()사용)
template <typename T>
int SircularLinkedList<T>::AddData(int index, T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;

	if (pHead == nullptr) {
		newnode->prev = newnode;
		newnode->next = newnode;
		pCursor = pHead = newnode;
	}
	else {
		if (index <= 0 || index >= iSize - 1) {
			newnode->prev = pHead->prev;
			newnode->next = pHead;
			pHead->prev->next = newnode;
			pHead->prev = newnode;
			if (index <= 0) {
				pCursor = pHead = newnode;
			}
		}
		else {
			node<T>* pFind = pHead;
			if (index <= iSize / 2) {
				for (int i = 0; i < index - 1; i++) {
					pFind = pFind->next;
				}
			}
			else {
				for (int i = 0; i < iSize - index + 1; i++) {
					pFind = pFind->prev;
				}
			}
			newnode->prev = pFind;
			newnode->next = pFind->next;
			pFind->next->prev = newnode;
			pFind->next = newnode;
		}
	}

	return ++iSize;
}

//지정한 위치에 있는 데이터를 확인.
template <typename T>
T& SircularLinkedList<T>::CheckData(int index)
{
	int iIndex = index;
	if (index >= iSize) {
		iIndex = iSize - 1;
	}

	node<T>* pFind = pHead;
	if (iIndex <= iSize / 2) {
		for (int i = 0; i < iIndex; i++) {
			pFind = pFind->next;
		}
	}
	else {
		for (int i = 0; i < iSize - iIndex; i++) {
			pFind = pFind->prev;
		}
	}

	return pFind->data;
}

//지정한 위치에 있는 데이터를 수정.
template <typename T>
void SircularLinkedList<T>::ChangeData(int index, T data)
{
	int iIndex = index;
	if (index >= iSize) {
		iIndex = iSize - 1;
	}

	node<T>* pFind = pHead;
	if (iIndex <= iSize / 2) {
		for (int i = 0; i < iIndex; i++) {
			pFind = pFind->next;
		}
	}
	else {
		for (int i = 0; i < iSize - iIndex; i++) {
			pFind = pFind->prev;
		}
	}

	pFind->data = data;
}

//지정한 위치에 있는 데이터를 삭제
template <typename T>
int SircularLinkedList<T>::DeleteData(int index)
{
	if (pHead == nullptr) {
		return 0;
	}

	node<T>* pDel = nullptr;
	int iIndex = index;

	if (index <= 0) {
		pDel = pHead;
		pHead = pHead->next;
		pDel->prev->next = pHead;
		pHead->prev = pDel->prev;
		delete pDel;
		pCursor = pHead;
		return --iSize;
	}

	if (index >= iSize - 1) {
		pDel = pHead->prev;
		pDel->prev->next = pHead;
		pHead->prev = pDel->prev;
		delete pDel;
		return --iSize;
	}
	
	if (index > iSize - 1) {
		iIndex = iSize - 1;
	}

	node<T>* pFind = pHead;
	if (iIndex <= iSize / 2) {
		for (int i = 0; i < iIndex - 1; i++) {
			pFind = pFind->next;
		}
	}
	else {
		for (int i = 0; i < iSize - iIndex + 1; i++) {
			pFind = pFind->prev;
		}
	}

	pDel = pFind->next;
	pFind->next = pDel->next;
	pDel->next->prev = pFind;
	delete pDel;
	
	return --iSize;
}

//특정한 값을 가진 노드(들) 삭제
template <typename T>
int SircularLinkedList<T>::DeleteValue(T data)
{
	if (pHead == nullptr) {
		return 0;
	}

	node<T>* pDel = nullptr;
	while (pHead->data == data) {
		pDel = pHead;
		pHead = pHead->next;
		pDel->prev->next = pHead;
		pHead->prev = pDel->prev;
		delete pDel;
		pCursor = pHead;
		iSize--;
		if (iSize == 0) {
			pHead = nullptr;
			return 0;
		}
	} 


	node<T>* pFind = pHead;
	while (pFind->next != pHead) {
		if (pFind->next->data == data) {
			pDel = pFind->next;
			pFind->next = pDel->next;
			pDel->next->prev = pFind;
			delete pDel;
			iSize--;
		}
		else {
			pFind = pFind->next;
		}
	}
	return iSize;
}

//커서 포인터를 지정한 위치로 이동.
template <typename T>
void SircularLinkedList<T>::SetCursor(int index)
{
	pCursor = pHead;
	int iIndex = index;

	if (index > iSize - 1) {
		iIndex = iSize - 1;
	}

	if (iIndex <= iSize / 2) {
		for (int i = 0; i < iIndex; i++) {
			pCursor = pCursor->next;
		}
	}
	else {
		for (int i = 0; i < iSize - iIndex; i++) {
			pCursor = pCursor->prev;
		}
	}
}

//리스트 순회용
template <typename T>
T& SircularLinkedList<T>::Next()
{
	T& ret = pCursor->data;

	if (pCursor->next != nullptr) {
		pCursor = pCursor->next;
	}

	return ret;
}

template <typename T>
T& SircularLinkedList<T>::Prev()
{
	T& ret = pCursor->data;

	if (pCursor->prev != nullptr) {
		pCursor = pThis->prev;
	}

	return ret;
}


template <typename T>
SircularLinkedList<T>::~SircularLinkedList()
{
	node<T>* pDel = nullptr;
	node<T>* pFind = pHead;
	while (pFind != nullptr) {
		pDel = pFind;
		pFind = pFind->next;
		delete pDel;
	}

	pHead = nullptr;
	pCursor = nullptr;

	iSize = 0;
}