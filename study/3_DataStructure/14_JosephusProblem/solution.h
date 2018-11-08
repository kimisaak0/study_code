#pragma once
#include <iostream>

class CircularList
{
	struct node
	{
		int id;
		bool exist;
	};

	node* capacity;
	int iIndex;

	int iSize;
	int iCount;

private:
	int next(int d);

public:
	void LastN(int live, int die);

public:
	CircularList(int size);
	virtual ~CircularList();
};

CircularList::CircularList(int size)
{
	capacity = new node[size];
	iIndex = 0;

	iSize = iCount = size;

	for (int i = 0; i < size; i++) {
		capacity[i].id = i + 1;
		capacity[i].exist = true;
	}
}

int CircularList::next(int d)
{
	iIndex += d;
	iIndex %= iSize;

	while (!capacity[iIndex].exist) {
		iIndex += 1;
		if (iIndex == iSize) {
			iIndex = 0;
		}
	}

	return iIndex;
}

void CircularList::LastN(int live, int die)
{
	while (iCount != live) {
		capacity[next(die)].exist = false;
		iCount--;
	}

	printf("생존자 %d명\n", live);
	for (int i = 0; i < iSize; i++) {
		if (capacity[i].exist) {
			printf("%d번 ", capacity[i].id);
		}
	}
}

CircularList::~CircularList()
{
	delete[] capacity;
}