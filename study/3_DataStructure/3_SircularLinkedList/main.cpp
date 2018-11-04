#include "SircularLinkedList.h"
#include <iostream>

int main()
{
	SircularLinkedList<int> a;

	a.AddData(a.getSize(), 1);
	a.AddData(a.getSize(), 2);
	a.AddData(a.getSize(), 3);
	a.AddData(a.getSize(), 4);
	a.AddData(a.getSize(), 5);

	while (true) {
		std::cout << a.Next() << std::endl;
	}
}