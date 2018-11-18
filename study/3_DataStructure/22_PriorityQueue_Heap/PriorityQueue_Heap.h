#pragma once

class PQ_Heap
{
	int* capacity;
	int iSize;

	int iCount;

	int* tRet;

private:
	int   ParentIndex(int index); // 지정한 노드의 부모 노드의 인덱스를 반환
	int   LeftIndex(int index);   // 지정한 노드의 왼쪽 노드의 인덱스를 반환
	int   RightIndex(int index);  // 지정한 노드의 오른쪽 노드의 인덱스를 반환

public:
	bool   Add(int data);
	int    Remove();
	int    Retrive();

	int  getCount();
	int  getSize();


public:
	PQ_Heap(int size);
	virtual ~PQ_Heap();
};

//------------------------>

//private Function
// 지정한 노드의 부모 노드의 인덱스를 반환, -1은 없음을 의미.
int   PQ_Heap::ParentIndex(int index)
{
	if (index == 0) {
		return -1;
	}

	return (index - 1) / 2;
}

// 지정한 노드의 왼쪽 노드의 인덱스를 반환, -1은 없음을 의미.
int   PQ_Heap::LeftIndex(int index)
{
	int iRet = index * 2 + 1;

	if (iRet >= iCount) {
		return -1;
	}

	return iRet;
}

// 지정한 노드의 오른쪽 노드의 인덱스를 반환, -1은 없음을 의미.
int   PQ_Heap::RightIndex(int index)
{
	int iRet = index * 2 + 2;

	if (iRet >= iCount) {
		return -1;
	}

	return iRet;
}


//---------------------------->
//Public Function
PQ_Heap::PQ_Heap(int _size)
{
	iSize = _size;
	capacity = new int[iSize];
	iCount = 0;
	tRet = new int;
}

bool PQ_Heap::Add(int data)
{
	if (iCount == iSize) {
		return false;
	}

	capacity[iCount] = data;

	int nowIndex = iCount++;

	while (true) {

		if (capacity[ParentIndex(nowIndex)] > capacity[nowIndex]) {
			int temp = capacity[ParentIndex(nowIndex)];
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

int PQ_Heap::Remove()
{
	if (iCount == 0) {
		tRet = nullptr;
	}


	*tRet = capacity[0];
	capacity[0] = capacity[--iCount];

	int nowIndex = 0;
	bool whilesw = true;

	if (iCount == 0) {
		*tRet = capacity[0];
		return *tRet;
	}


	while (whilesw) {

		int left = LeftIndex(nowIndex);
		int right = RightIndex(nowIndex);

		if (iCount > 1) {
			if (left == -1 || right == -1) {
				whilesw = false;
				break;
			}
		}
		else {
			if (*tRet > capacity[0]) {
				capacity[1] = *tRet;
				*tRet = capacity[0];
				capacity[0] = capacity[1];
				whilesw = false;
				break;
			}
			else {
				whilesw = false;
				break;
			}
		}

		if (capacity[left] < capacity[right]) {

			if (capacity[nowIndex] > capacity[left]) {
				int temp = capacity[nowIndex];
				capacity[nowIndex] = capacity[left];
				capacity[left] = temp;
				nowIndex = left;
			}
			else {
				break;
			}

		}
		else {

			if (capacity[nowIndex] > capacity[right]) {
				int temp = capacity[nowIndex];
				capacity[nowIndex] = capacity[right];
				capacity[right] = temp;
				nowIndex = right;
			}
			else {
				break;
			}

		}

	}
	return *tRet;
}

int PQ_Heap::Retrive()
{
	*tRet = capacity[0];

	return *tRet;
}

int  PQ_Heap::getCount()
{
	return iCount;
}

int  PQ_Heap::getSize()
{
	return iSize;
}

PQ_Heap::~PQ_Heap()
{
	delete tRet;
}