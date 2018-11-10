#include "AVT.h"
#include <iostream>

int main()
{
	AVT_array<int> avt(7);

	for (int i = 0; i < 7; i++) {
		avt.AddNode(i);
	}
	
	int* arr = new int[avt.Count()];
	avt.LevelOrderTD(arr);

	for (int i = 0; i < 7; i++) {
		std::cout << arr[i] << std::endl;
	}
}