#pragma once
#include <math.h>

template <typename T>
class ABT_array
{
	T* capacity;
	int size;

	int iLastIndex;

	T tRet;

	int OrderIndex;

private:
	int   ParentIndex(int index); // ������ ����� �θ� ����� �ε����� ��ȯ
	int   LeftIndex(int index);   // ������ ����� ���� ����� �ε����� ��ȯ
	int   RightIndex(int index);  // ������ ����� ������ ����� �ε����� ��ȯ

	// �ε����� �޾� ���ȣ���� �ϸ� ��带 �����Ѵ�.
	bool     PreOrder(int index, T* tArray);
	bool     InOrder(int index, T* tArray);
	bool     PostOrder(int index, T* tArray);

public:
	bool AddNode(T data);
	bool DelNode();
	bool ChangeNode(int index, T data);

	T&   CheckNode(int index);

	int  Count();

	// Ʈ�� Ž�� �����
	//����� ���� �迭�� �μ��� �޴´�.
	void  LevelOrderTD(T* tArray); 
	void  LevelOrderBU(T* tArray);
	void  PreInPost(T* tArray, int select); //select ���� ���� pre, in, post order�� �����Ѵ�.

public:
	ABT_array(int size);
	virtual ~ABT_array();
};

//------------------------>

//private Function
// ������ ����� �θ� ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
template <typename T>
int   ABT_array<T>::ParentIndex(int index)
{
	if (index == 0) {
		return -1;
	}

	return (index - 1) / 2;
}

// ������ ����� ���� ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
template <typename T>
int   ABT_array<T>::LeftIndex(int index)
{
	int iRet = index * 2 + 1;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}

// ������ ����� ������ ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
template <typename T>
int   ABT_array<T>::RightIndex(int index)
{
	int iRet = index * 2 + 2;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}

// �ε����� �޾� ���ȣ���� �ϸ� ��带 �����Ѵ�.
template <typename T>
bool ABT_array<T>::PreOrder(int index, T* tArray)
{
	if (index != -1) {
		tArray[OrderIndex++] = capacity[index];
		PreOrder(LeftIndex(index), tArray);
		PreOrder(RightIndex(index), tArray);
		return true;
	}

	return false;
}

template <typename T>
bool ABT_array<T>::InOrder(int index, T* tArray)
{
	if (index != -1) {
		InOrder(LeftIndex(index), tArray);
		tArray[OrderIndex++] = capacity[index];
		InOrder(RightIndex(index), tArray);
	}

	return false;
}

template <typename T>
bool ABT_array<T>::PostOrder(int index, T* tArray)
{
	if (index != -1) {
		PostOrder(LeftIndex(index), tArray);
		PostOrder(RightIndex(index), tArray);
		tArray[OrderIndex++] = capacity[index];
	}

	return false;
}

//---------------------------->
//Public Function
template <typename T>
ABT_array<T>::ABT_array(int _size)
{
	size = _size;
	capacity = new T[size];
	iLastIndex = 0;
	OrderIndex = 0;
}


template <typename T>
bool ABT_array<T>::AddNode(T data)
{
	if (iLastIndex == size) {
		return false;
	}

	capacity[iLastIndex++] = data;

	return true;
}

template <typename T>
bool ABT_array<T>::DelNode()
{
	if (iLastIndex == 0) {
		return false;
	}

	iLastIndex--;

	return true;
}

template <typename T>
bool ABT_array<T>::ChangeNode(int index, T data)
{
	if (index < 0 && index >= iLastIndex) {
		return false;
	}

	capacity[index] = data;

	return true;
}



template <typename T>
T& ABT_array<T>::CheckNode(int index)
{
	if (index >= 0 && index < iLastIndex) {
		tRet = capacity[index];
		return tRet;
	}
	else {
		return nullptr;
	}
}

template <typename T>
int  ABT_array<T>::Count()
{
	return iLastIndex;
}



// ����� ���� �迭�� �μ��� �޴´�. 
template <typename T>
void ABT_array<T>::LevelOrderTD(T* tArray)
{
	for (int i = 0; i < iLastIndex; i++) {
		tArray[i] = capacity[i];
	}
}

template <typename T>
void ABT_array<T>::LevelOrderBU(T* tArray)
{
	int depth = 0;
	int depthCheck = 0;

	while (iLastIndex-1 > depthCheck) {
		depth++;
		depthCheck += pow(2, depth);
	}

	int tIndex = 0;
	for (int i = depth; i >= 0; i--) {
		depthCheck -= pow(2, i);
		for (int k = 1; k <= pow(2, i); k++) {
			tArray[tIndex] = capacity[depthCheck+k];
			tIndex++;
		}
	}

}

//select ���� ���� pre, in, post order�� �����Ѵ�.
template <typename T>
void  ABT_array<T>::PreInPost(T* tArray, int select)
{
	OrderIndex = 0;
	switch (select) {
		case 1: { PreOrder(0, tArray); } break;

		case 2: { InOrder(0, tArray); } break;

		case 3: { PostOrder(0, tArray);	} break;
	}
}


template <typename T>
ABT_array<T>::~ABT_array()
{

}