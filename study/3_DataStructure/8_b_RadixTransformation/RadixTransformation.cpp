#include "StackList.h"
#include <iostream>

int main()
{
	int decimal = 0;
	std::cout << "2������ ��ȯ�� 10������ �Է��ϼ���." << std::endl;
	std::cin >> decimal;

	StackList<int> binary;

	do {
		binary.Push(decimal%2);
		decimal /= 2;
	} while (decimal != 0);

	while (binary.Count() != 0) {
		std::cout << binary.Pop();
	}
}