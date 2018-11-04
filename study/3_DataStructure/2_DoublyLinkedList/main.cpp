#include "DoublyLinkedList.h"
#include <iostream>

int main()
{
	DoublyLinkedList<int> a;

	a.AddBack(1);
	a.AddBack(2);
	a.AddBack(3);

	a.AddFront(0);
	a.AddFront(-1);

	a.DeleteValue(0);

	a.SetCursor(-1);
	for (int i = 0; i < a.getSize(); i++) {
		std::cout << a.Next() << std::endl;
	}

	std::cout << std::endl;

	a.AddData(0, 50);
	
	a.AddData(10, 100);

	//a.DeleteData(0);
	a.DeleteValue(100);

	a.SetCursor(a.getSize());
	for (int i = 0; i < a.getSize(); i++) {
		std::cout << a.Prev() << std::endl;
	}
}