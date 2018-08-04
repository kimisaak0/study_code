#include <stdio.h>

int main()
{
	int iSum = 0;
	int iInput;

	printf("0부터 더할 값을 입력하세요 : "); scanf_s("%d", &iInput);

	int i = 0;
	
	do{
		iSum += i;
		i++;
	}while (i <= 100);

	printf("0부터 %d까지의 합은 %d입니다. \n", iInput, iSum);
}