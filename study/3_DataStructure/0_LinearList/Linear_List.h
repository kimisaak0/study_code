#pragma once
#include <assert.h>
#include <vector>

template <typename T>
class LinearList
{
	T* arr;
	int iSize;
	int iEnd;

	//std::vector<int> vi;

public:
	T& operator[](int index);

	int GetSize();
	void insert(T data);

public:
	LinearList();
	LinearList(int size);
	~LinearList();
};

//생성자
template <typename T>
LinearList<T>::LinearList()
{
	arr = nullptr;
	iSize = 0;
	iEnd = 0;
}

template <typename T>
LinearList<T>::LinearList(int size)
{
	arr = new T[size];
	iSize = size;
	iEnd = 0;
}

//[] 오버로딩
template <typename T>
T& LinearList<T>::operator[](int index)
{
	assert(0 <= index);
	return arr[index];
}

template <typename T>
int LinearList<T>::GetSize()
{
	return iSize;
}

template <typename T>
void LinearList<T>::insert(T data)
{
	if (iEnd >= iSize) {
		T* backup = new T[iSize];
		for (int i = 0; i < iSize; i++) {
			backup[i] = arr[i];
		}
		arr = new T[iSize + 5];
		for (int i = 0; i < iSize; i++) {
			arr[i] = backup[i];
		}
		iSize = iSize + 5;
	} 

	arr[iEnd++] = data;
}

//소멸자
template <typename T>
LinearList<T>::~LinearList()
{
	//남아있는 arr의 모든 요소를 순회하며 딜리트 해줘야 함.
	delete arr;
}