#pragma once

template <typename T>
class SingleLinkedList
{
	template <typename T>
	struct node {
		T data;
		node<T>* next;
	};

	node<T>* pHead;
	node<T>* pCursor;
	node<T>* pTail;

	int iSize;

public:
	int getSize();

	int AddData(T data);                  //����Ʈ ���� ������ �߰�
	int AddData(int index, T data);       //������ ��ġ�� ������ �߰�
	T& CheckData(int index);              //������ ��ġ�� �ִ� �����͸� Ȯ��.
	void ChangeData(int index, T data);   //������ ��ġ�� �ִ� �����͸� ����.
	int DeleteData(int index);            //������ ��ġ�� �ִ� ������ ����.
	int DeleteValue(T data);              //������ ���� ���� ���(��) ����.

	void SetCursor(int index);            //Ŀ�� �����͸� ������ ��ġ�� �̵�.
	T& Next(); //����Ʈ ��ȸ��

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


//����Ʈ ���� ������ �߰�
template <typename T>
int SingleLinkedList<T>::AddData(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
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
int SingleLinkedList<T>::AddData(int index, T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->next = nullptr;

	if (pHead == nullptr) {
		pHead = newnode;
		pTail = newnode;
	}
	else {
		if (index <= 0) {
			newnode->next = pHead;
			pHead = newnode;
		}
		else if (index >= iSize - 1) {
			pTail->next = newnode;
			pTail = newnode;
		}
		else {
			node<T>* pFind = pHead;
			for (int i = 0; i < index - 1; i++) {
				pFind = pFind->next;
			}
			newnode->next = pFind->next;
			pFind->next = newnode;
		}
	}
	pCursor = pHead;

	return ++iSize;
}

//������ ��ġ�� �ִ� �����͸� Ȯ��.
template <typename T>
T& SingleLinkedList<T>::CheckData(int index)
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
void SingleLinkedList<T>::ChangeData(int index, T data)
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
int SingleLinkedList<T>::DeleteData(int index)
{
	node<T>* pDel = nullptr;
	int iIndex = index;

	if (index <= 0) {
		pDel = pHead;
		pHead = pHead->next;
		delete pDel;
		pCursor = pHead;
	}
	else if (index >= iSize - 1) {
		iIndex = iSize - 1;
	}

	node<T>* pFind = pHead;
	for (int i = 0; i < iIndex -1; i++) {
		pFind = pFind->next;
	}

	if (pFind->next == pTail) {
		pTail = pFind;
	}

	pDel = pFind->next;
	pFind->next = pDel->next;
	delete pDel;

	return --iSize;
}

//Ư���� ���� ���� ���(��) ����
template <typename T>
int SingleLinkedList<T>::DeleteValue(T data)
{
	node<T>* pDel = nullptr;
	while (pHead != nullptr && pHead->data == data) {
		pDel = pHead;
		pHead = pHead->next;
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
			}
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

//Ŀ�� �����͸� ������ ��ġ�� �̵�.
template <typename T>
void SingleLinkedList<T>::SetCursor(int index)
{
	pCursor = pHead;
	int iIndex = index;

	if (index >= iSize-1) {
		iIndex = iSize-1;
	}

	for (int i = 0; i < iIndex; i++) {
		pCursor = pCursor->next;
	}
}

//����Ʈ ��ȸ��
template <typename T>
T& SingleLinkedList<T>::Next()
{
	T& ret = pCursor->data;

	if (pCursor != nullptr && pCursor->next != nullptr) {
		pCursor = pCursor->next;
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
	pCursor = nullptr;

	iSize = 0;
}