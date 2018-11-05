#pragma once

template <typename T>
class QueueList
{
	template <typename T>
	struct node {
		T data;
		node<T>* next;
	};

	node<T>* pFront;
	node<T>* pRear;

	int iCount;

public:
	int Add(T data);
	int Remove();
	T  Peek();
	int Count();

public:
	QueueList();
	virtual ~QueueList();
};

template <typename T>
QueueList<T>::QueueList()
{
	pFront = nullptr;
	pRear = nullptr;
	iCount = 0;
}


template <typename T>
int QueueList<T>::Add(T data)
{
	node<T>* newnode = new node<T>;
	newnode->data = data;
	newnode->next = nullptr;

	if (pRear != nullptr) {
		pRear->next = newnode;
	}
	else {
		pFront = newnode;
	}

	pRear = newnode;

	return ++iCount;
}

template <typename T>
int QueueList<T>::Remove()
{
	node<T>* pDel = pFront;
	pFront = pFront->next;
	delete pDel;

	return 	--iCount;
}

template <typename T>
T QueueList<T>::Peek()
{
	return pFront->data;
}

template <typename T>
int QueueList<T>::Count()
{
	return iCount;
}

template <typename T>
QueueList<T>::~QueueList()
{
	while (true) {
		if (!a.Remove()) {
			break;
		}
	}
}