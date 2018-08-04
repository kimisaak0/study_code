#include <stdio.h>

int main()
{
	int iSum = 0;
	int iInput;

	printf("0부터 더할 값을 입력하세요 : "); scanf_s("%d", &iInput);
	
	for (int i = 0; i <= 100; i++) {
		iSum += i;
	}

	printf("0부터 %d까지의 합은 %d입니다. \n", iInput, iSum);
}