#include <stdio.h>

int main()
{
	int iSum = 0;
	int iInput;

	printf("0���� ���� ���� �Է��ϼ��� : "); scanf_s("%d", &iInput);

	int i = 0;
	
	do{
		iSum += i;
		i++;
	}while (i <= 100);

	printf("0���� %d������ ���� %d�Դϴ�. \n", iInput, iSum);
}