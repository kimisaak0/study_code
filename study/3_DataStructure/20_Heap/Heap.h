#pragma once
#include <math.h>

template <typename T>
class Heap
{
	T* capacity;
	int size;

	int iLastIndex;

	T tRet;

private:
	int   ParentIndex(int index); // 지정한 노드의 부모 노드의 인덱스를 반환
	int   LeftIndex(int index);   // 지정한 노드의 왼쪽 노드의 인덱스를 반환
	int   RightIndex(int index);  // 지정한 노드의 오른쪽 노드의 인덱스를 반환

public:
	bool AddNode(T data);
	T&   DelNode();
	T&   CheckRoot();

	int  getCount();
	int  getSize();


public:
	Heap(int size);
	virtual ~Heap();
};

//------------------------>

//private Function
// 지정한 노드의 부모 노드의 인덱스를 반환, -1은 없음을 의미.
template <typename T>
int   Heap<T>::ParentIndex(int index)
{
	if (index == 0) {
		return -1;
	}

	return (index - 1) / 2;
}

// 지정한 노드의 왼쪽 노드의 인덱스를 반환, -1은 없음을 의미.
template <typename T>
int   Heap<T>::LeftIndex(int index)
{
	int iRet = index * 2 + 1;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}

// 지정한 노드의 오른쪽 노드의 인덱스를 반환, -1은 없음을 의미.
template <typename T>
int   Heap<T>::RightIndex(int index)
{
	int iRet = index * 2 + 2;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}


//---------------------------->
//Public Function
template <typename T>
Heap<T>::Heap(int _size)
{
	size = _size;
	capacity = new T[size];
	iLastIndex = 0;
}


template <typename T>
bool Heap<T>::AddNode(T data)
{
	if (iLastIndex == size) {
		return false;
	}

	capacity[iLastIndex++] = data;

	int nowIndex = iLastIndex;

	while (true) {
		if (capacity[ParentIndex(nowIndex)] > capacity[nowIndex]) {
			T temp = capacity[ParentIndex(nowIndex)];
			capacity[ParentIndex(nowIndex)] = capacity[nowIndex];
			capacity[nowIndex] = temp;
			nowIndex = ParentIndex(nowIndex);
		}
		else {
			break;
		}
			
	}

	return true;
}

template <typename T>
T& Heap<T>::DelNode()
{
	if (iLastIndex == 0) {
		tRet = nullptr;
	}

	iLastIndex--;

	tRet = capacity[0];
	capacity[0] = capacity[iLastIndex];

	int nowInedex = 0;
	

	while (true) {
		if (capacity[LeftIndex(nowInedex)] < capacity[RightIndex(nowInedex)) {
			if (capacity[nowInedex] > capacity[LeftIndex(nowInedex)]) {
				T temp = capacity[nowInedex];
				capacity[nowInedex] = capacity[LeftIndex(nowInedex)];
				capacity[LeftIndex(nowInedex)] = temp;
				nowInedex = LeftIndex(nowInedex);
			}
			else {
				break;
			}
		}
		else {
			if (capacity[nowInedex] > capacity[RightIndex(nowInedex)]) {
				T temp = capacity[nowInedex];
				capacity[nowInedex] = capacity[RightIndex(nowInedex)];
				capacity[RightIndex(nowInedex)] = temp;
				nowInedex = RightIndex(nowInedex);
			}
			else {
				break;
			}
		}
	
	}
	return tRet;
}


template <typename T>
T& Heap<T>::CheckRoot()
{

	tRet = capacity[0];

	return tRet;
}

template <typename T>
int  Heap<T>::getCount()
{
	return iLastIndex;
}

template <typename T>
int  Heap<T>::getSize()
{
	return Size;
}


template <typename T>
Heap<T>::~Heap()
{

}