#include <stdio.h>

int main()
{
	int iSum = 0;
	int iInput;

	printf("0���� ���� ���� �Է��ϼ��� : "); scanf_s("%d", &iInput);
	
	for (int i = 0; i <= 100; i++) {
		iSum += i;
	}

	printf("0���� %d������ ���� %d�Դϴ�. \n", iInput, iSum);
}