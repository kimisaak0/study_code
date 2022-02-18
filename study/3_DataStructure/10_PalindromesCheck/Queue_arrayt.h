#pragma once

template <typename T>
class QueueArray
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
	QueueArray(int size);
	virtual ~QueueArray();
};


template <typename T>
QueueArray<T>::QueueArray(int size)
{
	capacity = new T[size];

	iSize = size;
	iCount = 0;

	iFront = 0;
	iRear = 0;
}

template <typename T>
int QueueArray<T>::Add(T data)
{
	if (iCount == iSize) {
		return iSize;
	}

	capacity[iRear++] = data;

	return ++iCount;
}

template <typename T>
int QueueArray<T>::Remove()
{
	if (iCount == 0) {
		return 0;
	}

	iFront++;

	return --iCount;

}

template <typename T>
T QueueArray<T>::Peek()
{
	return capacity[iFront];
}

template <typename T>
int QueueArray<T>::Count()
{
	return iCount;
}

template <typename T>
QueueArray<T>::~QueueArray()
{
	delete[] capacity;
}