#include "PriorityQueue_Heap.h"
#include <iostream>

int main()
{
	PQ_Heap a(20);

	a.Add(3);
	a.Add(18);
	a.Add(4);
	a.Add(1119);
	a.Add(10);
	a.Add(1);
	a.Add(112);
	a.Add(0);
	a.Add(70);
	a.Add(5);
	a.Add(12);
	a.Add(80);
	a.Add(50);
	a.Add(29);

	int range = a.getCount();

	for (int i = 0; i < range; i++) {
		std::cout << a.Remove() << std::endl;
	}
}