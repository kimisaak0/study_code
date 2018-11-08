#include "Deque.h"
#include <iostream>

int main()
{
	Deque<int> a;

	a.AddFirst(4);
	a.AddFirst(3);
	a.AddLast(5);
	a.AddLast(2);

	std::cout << a.RemoveFirst() << std::endl;
	std::cout << a.RemoveLast() << std::endl;
}