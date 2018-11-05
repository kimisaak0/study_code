#include "StackArray.h"
#include <iostream>

int main()
{
	StackArray<int> a(10);
	
	for (int i = 0; i < 6; i++) {
		a.Push(i);
	}

	StackArray<int> b(a);

	for (int i = 0; i < 10; i++) {
		std::cout << b.Peek() << " " << b.Count() << "/" << b.CapacitySize() << std::endl;
		b.Pop();
	}
}