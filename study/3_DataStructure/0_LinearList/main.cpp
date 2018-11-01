#include "Linear_List.h"

#include <iostream>

int main()
{
	LinearList<int> a;

	for (int i = 0; i < 4; i++) {
		a.addData(i);
	}

	for (int i = 0; i < a.GetEnd(); i++) {
		std::cout << a.next() << std::endl;
	}

}