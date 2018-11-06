#include "CircularQueue.h"
#include <iostream>

int main()
{
	CircularQueue<int> a(5);

	for (int i = 0; i < 5; i++) {
		a.Add(i);
	}

	for (int i = 0; i < 6; i++) {
		std::cout << a.Peek() << std::endl;
		a.Remove();
	}
}