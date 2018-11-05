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
	T&  Remove();
	T&  Peek();
	int Count();

public:
	QueueList();
	virtual ~QueueList();
};

template <typename T>
QueueList<T>::QueueList()
{

}


template <typename T>
int QueueList<T>::Add(T data)
{

}

template <typename T>
T& QueueList<T>::Remove()
{

}

template <typename T>
T& QueueList<T>::Peek()
{

}

template <typename T>
int QueueList<T>::Count()
{

}

template <typename T>
QueueList<T>::~QueueList()
{

}