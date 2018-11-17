#include "Heap.h"
#include <iostream>

int main()
{
	Heap a(20);

	a.AddNode(3);
	a.AddNode(18);
	a.AddNode(4);
	a.AddNode(1119);
	a.AddNode(10);
	a.AddNode(1);

	a.AddNode(112);
	a.AddNode(0);
	a.AddNode(70);
	a.AddNode(5);
	a.AddNode(12);
	
	a.AddNode(80);
	a.AddNode(50);
	a.AddNode(29);

	int range = a.getCount();

	for (int i = 0; i < range; i++){
		std::cout << a.DelNode() << std::endl;
	}
}