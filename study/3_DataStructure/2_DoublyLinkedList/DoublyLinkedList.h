#pragma once

template <typename T>
class DoublyLinkedList
{
	template <typename T>
	struct node {
		T data;
		node<T>* prev;
		node<T>* next;
	};

	node<T>* pHead;
	node<T>* pCursor;
	node<T>* pTail;

	int iSize;

public:
	int getSize();

	int AddFront(T data);                 //����Ʈ �տ� ������ �߰�
	int AddBack(T data);                  //����Ʈ ���� ������ �߰�
	int AddData(int index, T data);       //������ ��ġ�� ������ �߰�.
	T& CheckData(int index);              //������ ��ġ�� �ִ� �����͸� Ȯ��.
	void ChangeData(int index, T data);   //������ ��ġ�� �ִ� �����͸� ����.
	int DeleteData(int index);            //������ ��ġ�� �ִ� ������ ����.
	int DeleteValue(T data);              //������ ���� ���� ���(��) ����.

	void SetCursor(int index);            //Ŀ�� �����͸� ������ ��ġ�� �̵�.
	//����Ʈ ��ȸ��
	T Next(); 
	T Prev();

public:
	DoublyLinkedList();
	~DoublyLinkedList();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	pHead = nullptr;
	pTail = nullptr;

	iSize = 0;
}

//getMethod
template <typename T>
int DoublyLinkedList<T>::getSize()
{
	return iSize;
}

//����Ʈ �տ� ������ �߰�
template <typename T>
int DoublyLinkedList<T>::AddFront(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->prev = nullptr;
	newnode->next = pHead;

	if (pTail == nullptr) {
		pTail = newnode;
		pCursor = pTail;
	}
	else {
		pHead->prev = newnode;
	}
	pHead= newnode;

	return ++iSize;
}

//����Ʈ ���� ������ �߰�
template <typename T>
int DoublyLinkedList<T>::AddBack(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->prev = pTail;
	newnode->next = nullptr;

	if (pHead == nullptr) {
		pHead = newnode;
		pCursor = pHead;
	}
	else {
		pTail->next = newnode;
	}
	pTail = newnode;

	return ++iSize;
}

//���ϴ� ��ġ�� ������ �߰�
template <typename T>
int DoublyLinkedList<T>::AddData(int index, T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->prev = nullptr;
	newnode->next = nullptr;

	if (pHead == nullptr) {
		pHead = newnode;
		pTail = newnode;
	}
	else {
		if (index <= 0) {
			newnode->next = pHead;
			pHead->prev = newnode;
			pHead = newnode;
		}
		else if (index >= iSize - 1) {
			newnode->prev = pTail;
			pTail->next = newnode;
			pTail = newnode;
		}
		else {
			node<T>* pFind = pHead;
			for (int i = 0; i < index - 1; i++) {
				pFind = pFind->next;
			}
			newnode->next = pFind->next;
			newnode->prev = pFind;
			pFind->next = newnode;
		}
	}

	pCursor = pHead;

	return ++iSize;
}

//������ ��ġ�� �ִ� �����͸� Ȯ��.
template <typename T>
T& DoublyLinkedList<T>::CheckData(int index)
{
	int iIndex = index;
	if (index <= 0) {
		iIndex = 0;
	}
	node<T>* pFind = pHead;
	for (int i = 0; i < iIndex; i++) {
		pFind = pFind->next;
	}

	return pFind->data;
}

//������ ��ġ�� �ִ� �����͸� ����.
template <typename T>
void DoublyLinkedList<T>::ChangeData(int index, T data)
{
	int iIndex = index;
	if (index <= 0) {
		iIndex = 0;
	}
	node<T>* pFind = pHead;
	for (int i = 0; i < iIndex; i++) {
		pFind = pFind->next;
	}

	pFind->data = data;
}

//������ ��ġ�� �ִ� �����͸� ����
template <typename T>
int DoublyLinkedList<T>::DeleteData(int index)
{
	node<T>* pDel = nullptr;
	int iIndex = index;

	if (index <= 0) {
		pDel = pHead;
		pHead = pHead->next;
		pHead->prev = nullptr;
		delete pDel;
		pCursor = pHead;
	}
	else if (index >= iSize - 1) {
		iIndex = iSize - 1;
	}

	node<T>* pFind = pHead;
	for (int i = 0; i < iIndex - 1; i++) {
		pFind = pFind->next;
	}

	if (pFind->next == pTail) {
		pTail = pFind;
		pDel = pFind->next;
		pFind->next = nullptr;
		delete pDel;
	}
	else {

		pDel = pFind->next;
		pFind->next = pDel->next;
		pDel->next->prev = pFind;
		delete pDel;
	}
	return --iSize;
}

//Ư���� ���� ���� ���(��) ����
template <typename T>
int DoublyLinkedList<T>::DeleteValue(T data)
{
	node<T>* pDel = nullptr;
	while (pHead != nullptr && pHead->data == data) {
		pDel = pHead;
		pHead = pHead->next;
		pHead->prev = nullptr;
		delete pDel;
		pCursor = pHead;
		iSize--;
	}

	if (pHead == nullptr) {
		return 0;
	}

	node<T>* pFind = pHead;
	while (pFind->next != nullptr) {
		if (pFind->next->data == data) {
			if (pFind->next == pTail) {
				pTail = pFind;
				pDel = pFind->next;
				pFind->next = nullptr;
				delete pDel;
				iSize--;
			}
			else {
				pDel = pFind->next;
				pFind->next = pDel->next;
				pDel->next->prev = pFind;
				delete pDel;
				iSize--;
			}
		}
		else {
			pFind = pFind->next;
		}
	}

	return iSize;

}

//Ŀ�� �����͸� ������ ��ġ�� �̵�.
template <typename T>
void DoublyLinkedList<T>::SetCursor(int index)
{
	pCursor = pHead;
	int iIndex = index;

	if (index >= iSize - 1) {
		iIndex = iSize - 1;
	}

	for (int i = 0; i < iIndex; i++) {
		pCursor = pCursor->next;
	}
}

//����Ʈ ��ȸ��
template <typename T>
T DoublyLinkedList<T>::Next()
{
	T ret = pCursor->data;

	if (pCursor->next != nullptr) {
		pCursor = pCursor->next;
	}

	return ret;
}


template <typename T>
T DoublyLinkedList<T>::Prev()
{
	T ret = pCursor->data;

	if (pCursor->prev != nullptr) {
		pCursor = pCursor->prev;
	}

	return ret;
}


template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
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
	pCursor = nullptr;

	iSize = 0;
}