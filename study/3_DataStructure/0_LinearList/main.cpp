#include "Linear_List.h"

#include <iostream>

int main()
{
	{
		LinearList<int> a;

		a.addData(1);
		a.addData(1);
		a.addData(1);

		a.DeleteValue(1);

		std::cout << std::endl;
		a.SetIndex(0);
		for (int i = 0; i < a.GetEnd(); i++) {
			std::cout << a.next() << std::endl;
		}
	}


}