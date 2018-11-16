#pragma once
#include <math.h>

class Heap
{
	int* capacity;
	int iSize;

	int iCount;

	int* tRet;

private:
	int   ParentIndex(int index); // ������ ����� �θ� ����� �ε����� ��ȯ
	int   LeftIndex(int index);   // ������ ����� ���� ����� �ε����� ��ȯ
	int   RightIndex(int index);  // ������ ����� ������ ����� �ε����� ��ȯ

public:
	bool   AddNode(int data);
	int    DelNode();
	int    CheckRoot();

	int  getCount();
	int  getSize();


public:
	Heap(int size);
	virtual ~Heap();
};

//------------------------>

//private Function
// ������ ����� �θ� ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
int   Heap::ParentIndex(int index)
{
	if (index == 0) {
		return -1;
	}

	return (index - 1) / 2;
}

// ������ ����� ���� ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
int   Heap::LeftIndex(int index)
{
	int iRet = index * 2 + 1;

	if (iRet >= iCount) {
		return -1;
	}

	return iRet;
}

// ������ ����� ������ ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
int   Heap::RightIndex(int index)
{
	int iRet = index * 2 + 2;

	if (iRet >= iCount) {
		return -1;
	}

	return iRet;
}


//---------------------------->
//Public Function
Heap::Heap(int _size)
{
	iSize = _size;
	capacity = new int[iSize];
	iCount = 0;
	tRet = new int;
}

bool Heap::AddNode(int data)
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

int Heap::DelNode()
{
	if (iCount == 0) {
		tRet = nullptr;
	}

	iCount--;


	*tRet = capacity[0];
	capacity[0] = capacity[iCount];

	int nowIndex = 0;
	bool whilesw = true;

	while (whilesw) {

		int left = LeftIndex(nowIndex);
		int right = RightIndex(nowIndex);


		if (left == -1) {
			left = iCount;
			whilesw = false;
		} 

		if (right == -1) {
			right = iCount;
			whilesw = false;
		}


		if (capacity[left] < capacity[right]) {
	
			if (capacity[nowIndex] > capacity[left]) {
				int temp = capacity[nowIndex];
				capacity[nowIndex] = capacity[left];
				capacity[left] = temp;
				nowIndex = left;
			}
			else {
				whilesw = false;
			}
	
		}
		else {

			if (capacity[nowIndex] > capacity[right]) {
				int temp = capacity[right];
				capacity[nowIndex] = capacity[right];
				capacity[right] = temp;
				nowIndex = right;
			}
			else {
				whilesw = false;
			}
		}

	}
	return *tRet;
}

int Heap::CheckRoot()
{
	*tRet = capacity[0];

	return *tRet;
}

int  Heap::getCount()
{
	return iCount;
}

int  Heap::getSize()
{
	return iSize;
}

Heap::~Heap()
{

}