#include "QueueList.h"
#include <iostream>

int main()
{
	QueueList<int> a;

	for (int i = 0; i < 10; i++) {
		a.Add(i);
	}

	while (true) {
		std::cout << a.Peek() << std::endl;
		if (!a.Remove()) {
			break;
		}
	}
}