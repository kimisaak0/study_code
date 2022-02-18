#include "StackList.h"
#include <iostream>

int main()
{
	StackList<int> a;

	for (int i = 0; i < 6; i++) {
		a.Push(i);
	}

	for (int i = 0; i < 10; i++) {
		if (a.Count() != 0) {
			std::cout << a.Pop();
		}
	}
}