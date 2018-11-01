#pragma once
#include <assert.h>
#include <vector>

template <typename T>
class LinearList
{
	T* arr;
	int iSize;
	int iEnd;
	int nowIndex;

	//std::vector<int> vi;

private:
	void moveData();
	

public:
	//인덱스로 접근, 수정이 가능.
	T& operator[](int index);

	int GetSize();
	int GetIndex();
	int GetEnd();

	int addData(T data);

	int InsertData(int index, T data);

	T& prev();
	T& now();
	T& next();

	

public:
	LinearList();
	LinearList(int size);
	~LinearList();
};

//내부 함수
template <typename T>
void LinearList<T>::moveData()
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
}

//생성자
template <typename T>
LinearList<T>::LinearList()
{
	arr = nullptr;
	iSize = 0;
	iEnd = 0;
	nowIndex = 0;
}

template <typename T>
LinearList<T>::LinearList(int size)
{
	arr = new T[size];
	iSize = size;
	iEnd = size;
	nowIndex = 0;
}

//[] 오버로딩
template <typename T>
T& LinearList<T>::operator[](int index)
{
	assert(0 <= index);
	return arr[index];
}

//getMethod
template <typename T>
int LinearList<T>::GetSize()
{
	return iSize;
}

template <typename T>
int  LinearList<T>::GetIndex()
{
	return nowIndex;
}

template <typename T>
int  LinearList<T>::GetEnd()
{
	return iEnd;
}

//뒤에 추가
template <typename T>
int LinearList<T>::addData(T data)
{
	moveData();

	arr[iEnd++] = data;

	return iEnd;
}

//중간에 삽입
template <typename T>
int LinearList<T>::InsertData(int index, T data)
{
	iEnd++;
	moveData();
	for (int i = iEnd; i > index; i--) {
		arr[iEnd] = arr[iENd-1]
	}

	arr[index] = data;
	
	return iEnd;
}


//순회용.
template <typename T>
T& LinearList<T>::prev()
{
	if (nowIndex > 0) {
		return arr[--nowIndex];
	}
}


template <typename T>
T& LinearList<T>::now()
{
	return arr[nowIndex];
}


template <typename T>
T& LinearList<T>::next()
{
	if (nowIndex < iEnd) {
		return arr[nowIndex++];
	}
}

//소멸자
template <typename T>
LinearList<T>::~LinearList()
{
	//남아있는 arr의 모든 요소를 순회하며 딜리트 해줘야 함.
	delete arr;
}