#pragma once

template <typename T>
class Scroll
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

	int AddLast(T data);

	T& RemoveFirst();
	T& RemoveLast();

public:
	Scroll();
	~Scroll();
};

template <typename T>
Scroll<T>::Scroll()
{
	pFirst = nullptr;
	pLast = nullptr;

	iSize = 0;
}

template <typename T>
int Scroll<T>::getSize()
{
	return iSize;
}

template <typename T>
int Scroll<T>::AddLast(T data)
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
T& Scroll<T>::RemoveFirst()
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
T& Scroll<T>::RemoveLast()
{
	node<T>* pDel = nullptr;
	pDel = pLast;
	tRet = pDel->data;

	pLast = pLast->prev;
	pLast->next = nullptr;

	delete pDel;
	iSize--;

	return tRet;
}


template <typename T>
Scroll<T>::~Scroll()
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