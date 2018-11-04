#include "SingleLinkedList.h"
#include <iostream>

int main()
{
	SingleLinkedList<int> a;
	for (int i = 0; i < 10; i++) {
		a.AddData(i);
	}

	//a.SetCursor(15);
	for (int i = 0; i < 6; i++) {
		std::cout << a.Next() << std::endl;
	}

	for (int i = 0; i < 6; i++) {
		std::cout << a.Next() << std::endl;
	}
}