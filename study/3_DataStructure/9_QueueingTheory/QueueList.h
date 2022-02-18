#pragma once

template <typename T>
struct node {
	T data;
	node<T>* next;
};

template <typename T>
class QueueList
{
	node<T>* pFront;
	node<T>* pRear;
	node<T>* pCursor;

	int iCount;

public:
	int Add(T data);
	int Remove();
	T  Peek();
	int Count();

	//대기 목록 보여주기용
	void ResetCursor();
	node<T>* Next(); 

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
		if (pFront == nullptr) {
			pFront = pRear;
		}
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
	if (--iCount == 0) {
		pRear = nullptr;
	}
	delete pDel;

	return 	iCount;
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

//리스트 순회용 (대기자 리스트 보여주기 용)
template <typename T>
void QueueList<T>::ResetCursor()
{
	pCursor = pFront;
}

template <typename T>
node<T>* QueueList<T>::Next()
{
	node<T>* ret = pCursor;

	if (pCursor != nullptr && pCursor->next != nullptr) {
		pCursor = pCursor->next;
	}

	return ret;
}

template <typename T>
QueueList<T>::~QueueList()
{

}