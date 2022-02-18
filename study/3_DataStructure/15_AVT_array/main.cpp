#include "ABT.h"
#include <iostream>

int main()
{
	ABT_array<int> abt(14);

	for (int i = 0; i < 14; i++) {
		abt.AddNode(i);
	}
	
	int* arr = new int[abt.Count()];
	abt.PreInPost(arr,3);

	for (int i = 0; i < 14; i++) {
		std::cout << arr[i] << std::endl;
	}
}