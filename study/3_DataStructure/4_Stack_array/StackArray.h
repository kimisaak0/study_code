#pragma once

template <typename T>
class StackArray
{
	int size;
	T* capacity;
	int top;

public:
	bool Push(T data);
	bool Pop();
	T& Peek();
	int Count();
	int CapacitySize();

public:
	StackArray(int size);
	virtual ~StackArray();
};

template <typename T>
StackArray<T>::StackArray(int _size)
{
	size = _size;
	capacity = new T[size];
	top = -1;
}

template <typename T>
bool StackArray<T>::Push(T data)
{
	if (top == size - 1) {
		return false;
	}

	capacity[++top] = data;
	return true;
}

template <typename T>
bool StackArray<T>::Pop()
{
	if (top == -1) {
		return false;
	}

	top--;
	return true;
}

template <typename T>
T& StackArray<T>::Peek()
{
	return capacity[top];
}

template <typename T>
int StackArray<T>::Count()
{
	return top + 1;
}

template <typename T>
int StackArray<T>::CapacitySize()
{
	return size;
}

template <typename T>
StackArray<T>::~StackArray()
{
	delete[] capacity;
}