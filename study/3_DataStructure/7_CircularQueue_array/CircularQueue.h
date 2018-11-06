#pragma once
#include <DirectXMath.h>

template <typename T>
class CircularQueue
{
	T* capacity;

	int iCount;
	int iSize;

	int iFront;
	int iRear;

public:
	int Add(T data);
	int Remove();
	T   Peek();
	int Count();

public:
	CircularQueue(int size);
	virtual ~CircularQueue();
};


template <typename T>
CircularQueue<T>::CircularQueue(int size)
{
	capacity = new T[size];
	
	iSize = size;
	iCount = 0;

	iFront = 0;
	iRear  = 0;
}

template <typename T>
int CircularQueue<T>::Add(T data)
{
	if (iCount == iSize) {
		return iSize;
	}

	if (iRear == iSize) {
		iRear = 0;
	}

	capacity[iRear++] = data;
	
	return ++iCount;
}

template <typename T>
int CircularQueue<T>::Remove()
{
	if (iCount == 0) {
		return 0;
	}

	if (iFront == iSize) {
		iFront = 0;
	}

	iFront++;

	return --iCount;

}

template <typename T>
T CircularQueue<T>::Peek()
{
	return capacity[iFront];
}

template <typename T>
int CircularQueue<T>::Count()
{
	return iCount;
}

template <typename T>
CircularQueue<T>::~CircularQueue()
{
	delete[] capacity;
}