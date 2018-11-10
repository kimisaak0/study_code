#pragma once

template <typename T>
class AVT_array
{
	T* capacity;
	int size;

	int iLastIndex;

	T tRet;

public:
	bool AddNode(T data);
	bool DelNode();
	bool ChangeNode(int index, T data);

	T&   CheckNode(int index);

	int  Count();

	int   ParentIndex(int index); // ������ ����� �θ� ����� �ε����� ��ȯ
	int   LeftIndex(int index);   // ������ ����� ���� ����� �ε����� ��ȯ
	int   RightIndex(int index);  // ������ ����� ������ ����� �ε����� ��ȯ

	void  LevelOrderTD(T* tArray); // ����� ���� �迭�� �μ��� �޴´�.

public:
	AVT_array(int size);
	virtual ~AVT_array();
};

//------------------------>

template <typename T>
AVT_array<T>::AVT_array(int _size)
{
	size = _size;
	capacity = new T[size];
	iLastIndex = 0;
}



template <typename T>
bool AVT_array<T>::AddNode(T data)
{
	if (iLastIndex == size) {
		return false;
	}

	capacity[iLastIndex++] = data;

	return true;
}

template <typename T>
bool AVT_array<T>::DelNode()
{
	if (iLastIndex == 0) {
		return false;
	}

	iLastIndex--;

	return true;
}

template <typename T>
bool AVT_array<T>::ChangeNode(int index, T data)
{
	if (index < 0 && index >= iLastIndex) {
		return false;
	}

	capacity[index] = data;

	return true;
}



template <typename T>
T& AVT_array<T>::CheckNode(int index)
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
int  AVT_array<T>::Count()
{
	return iLastIndex;
}

// ������ ����� �θ� ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
template <typename T>
int   AVT_array<T>::ParentIndex(int index)
{
	if (index == 0) {
		return -1;
	}

	return (index - 1) / 2;
}

// ������ ����� ���� ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
template <typename T>
int   AVT_array<T>::LeftIndex(int index)
{
	int iRet = index * 2 + 1;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}

// ������ ����� ������ ����� �ε����� ��ȯ, -1�� ������ �ǹ�.
template <typename T>
int   AVT_array<T>::RightIndex(int index)
{
	int iRet = index * 2 + 2;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}


// ����� ���� �迭�� �μ��� �޴´�. 
template <typename T>
void AVT_array<T>::LevelOrderTD(T* tArray)
{
	for (int i = 0; i < iLastIndex; i++) {
		tArray[i] = capacity[i];
	}
}



template <typename T>
AVT_array<T>::~AVT_array()
{

}