#pragma once

template <typename T>
class Shelf
{
	template <typename T>
	struct node {
		T data;
		node<T>* prev;
		node<T>* next;
	};

	node<T>* pFirst;
	node<T>* pLast;

	T tRet;

	int iSize;

public:
	int getSize();

	int AddFirst(T data);
	int AddLast(T data);

	T& RemoveFirst();

public:
	Shelf();
	~Shelf();
};

template <typename T>
Shelf<T>::Shelf()
{
	pFirst = nullptr;
	pLast = nullptr;

	iSize = 0;
}

template <typename T>
int Shelf<T>::getSize()
{
	return iSize;
}

template <typename T>
int Shelf<T>::AddFirst(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->prev = nullptr;
	newnode->next = pFirst;

	if (pLast == nullptr) { pLast = newnode; }
	else { pFirst->prev = newnode; }
	pFirst = newnode;

	return ++iSize;
}

template <typename T>
int Shelf<T>::AddLast(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->prev = pLast;
	newnode->next = nullptr;

	if (pFirst == nullptr) { pFirst = newnode; }
	else { pLast->next = newnode; }
	pLast = newnode;

	return ++iSize;
}

template <typename T>
T& Shelf<T>::RemoveFirst()
{
	node<T>* pDel = nullptr;
	pDel = pFirst;
	tRet = pDel->data;

	pFirst = pFirst->next;
	pFirst->prev = nullptr;

	delete pDel;
	iSize--;

	return tRet;
}

template <typename T>
Shelf<T>::~Shelf()
{
	node<T>* pDel = nullptr;
	node<T>* pFind = pFirst;
	while (pFind != nullptr) {
		pDel = pFind;
		pFind = pFind->next;
		delete pDel;
	}

	pFirst = nullptr;
	pLast = nullptr;

	iSize = 0;
}