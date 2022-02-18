#include "SircularLinkedList.h"
#include <iostream>

int main()
{
	SircularLinkedList<int> a;

	a.AddData(6, 1);
	a.AddData(6, 2);
	a.AddData(6, 3);
	a.AddData(6, 4);
	a.AddData(6, 5);

	a.SetCursor(0);

	std::cout << a.Next();


}