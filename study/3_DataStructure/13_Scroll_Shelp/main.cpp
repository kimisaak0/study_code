#include "Scroll.h"
#include "Shelf.h"

#include <iostream>

int main()
{
	Scroll<int> sc;

	sc.AddLast(1);
	sc.AddLast(2);
	sc.AddLast(3);
	sc.AddLast(4);

	std::cout << sc.RemoveFirst() << std::endl;
	std::cout << sc.RemoveLast() << std::endl;


	Shelf<int> sh;

	sh.AddFirst(1);
	sh.AddFirst(2);
	sh.AddLast(3);
	sh.AddLast(4);

	std::cout << sh.RemoveFirst() << std::endl;
}