#include <stdio.h>

int main()
{
	int iSum = 0;
	int iInput;

	printf("0���� ���� ���� �Է��ϼ��� : "); scanf_s("%d", &iInput);

	int i = 0;
	while ( i <= 100 ) {
		iSum += i;
		i++;
	}

	printf("0���� %d������ ���� %d�Դϴ�. \n", iInput, iSum);
}