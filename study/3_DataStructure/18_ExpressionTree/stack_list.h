#pragma once

template <typename T>
class StackList
{
	template <typename T>
	struct node {
		T data;
		node<T>* next;
	};

	node<T>* pTop;

	int iCount;

public:
	int Push(T data);
	T& Pop();
	T& Peek();
	int Count();

public:
	StackList();
	virtual ~StackList();
};

template <typename T>
StackList<T>::StackList()
{
	pTop = nullptr;
	int iCount = 0;
}

template <typename T>
int StackList<T>::Push(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->next = nullptr;

	if (pTop != nullptr) {
		newnode->next = pTop;
	}

	pTop = newnode;
	return ++iCount;
}

template <typename T>
T& StackList<T>::Pop()
{
	T tRet = pTop->data;

	if (pTop != nullptr) {
		node<T>* pDel = pTop;
		pTop = pTop->next;
		delete pDel;
	}

	iCount--;
	return tRet;
}

template <typename T>
T& StackList<T>::Peek()
{
	T tRet = pTop->data;
	return tRet;
}

template <typename T>
int StackList<T>::Count()
{
	return iCount;
}

template <typename T>
StackList<T>::~StackList()
{
	while (pTop != nullptr) {
		node<T>* pDel = pTop;
		pTop = pTop->next;
		delete pDel;
	}
}