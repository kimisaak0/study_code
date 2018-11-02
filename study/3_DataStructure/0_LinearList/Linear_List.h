#pragma once
#include <assert.h>

template <typename T>
class LinearList
{
	T* arr;
	int iSize;
	int iEnd;
	int nowIndex;

private:
	//할당받은 메모리가 부족할 때 메모리를 더 할당받고 데이터를 그대로 복사.
	void moveData();
	

public:
	//get method
	int GetSize();
	int GetIndex();
	int GetEnd();

	//set method
	void SetIndex(int index);

	T& operator[](int index);             //인덱스로 접근, 수정이 가능.

	int addData(T data);                  //뒤에 데이터 추가
	int InsertData(int index, T data);    //중간에 데이터 삽입
	
	int DeleteData(int index);            //인덱스로 데이터 삭제
	int DeleteValue(T data);              //데이터 값으로 데이터 삭제.

	//순회용.
	T& prev();
	T& now();
	T& next();
	

public:
	LinearList();
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
		for (int i = 0; i < iEnd-1; i++) {
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

//[] 오버로딩
template <typename T>
T& LinearList<T>::operator[](int index)
{
	assert(0 <= index && index < iEnd);
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

//setMethod
template <typename T>
void  LinearList<T>::SetIndex(int index)
{
	nowIndex = index;
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
		arr[i] = arr[i - 1];
	}

	arr[index] = data;
	
	return iEnd;
}

//index로 삭제
template <typename T>
int LinearList<T>::DeleteData(int index)
{
	iEnd--;
	for (int i = index; i < iEnd; i++) {
		arr[i] = arr[i + 1];
	}

	arr[iEnd] = 0;

	return iEnd;
}

//값으로 삭제
template <typename T>
int LinearList<T>::DeleteValue(T data)
{
	for (int i = 0; i < iEnd; ) {
		if (arr[i] == data) {
			DeleteData(i);
			i = 0;
			continue;
		}
		i++;
	}
	return iEnd;
}

//순회용.
template <typename T>
T& LinearList<T>::prev()
{
	if (nowIndex > 0) {
		return arr[--nowIndex];
	}
	return arr[0];
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
	return arr[iEnd-1];
}

//소멸자
template <typename T>
LinearList<T>::~LinearList()
{
	delete[] arr;
	arr = nullptr;
}