#include "Linear_List.h"

#include <iostream>

int main()
{
	LinearList<int> a(2);

	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	std::cout << a[0] << std::endl;
	std::cout << a[1] << std::endl;
	std::cout << a[2] << std::endl;
	std::cout << a[3] << std::endl;


}