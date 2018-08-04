#include <stdio.h>

int main()
{
	int iMax;
	printf("줄 수를 입력하세요 : "); scanf_s("%d", &iMax);

	for (int i = 0; i < iMax; i++) {
		int k = 0;
		for (k = 0; k < iMax-i; k++) {
			printf(" ");
		}
		for (; k < iMax+ i + 1; k++) {
			if(i%2 == 1) {
				if(k%2 == 1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			else {
				if (k % 2 == 1) {
					printf(" ");
				}
				else {
					printf("*");
				}
			}
			
		}
		for (; k < i; i++) {
			printf(" ");
		}
		printf("\n");
	}

	for (int i = iMax; i >= 0; i--) {
		int k = 0;
		for (k = 0; k < iMax-i; k++) {
			printf(" ");

		}
		for (; k < iMax+i+1; k++) {
			if (i % 2 == 1) {
				if (k % 2 == 1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			else {
				if (k % 2 == 1) {
					printf(" ");
				}
				else {
					printf("*");
				}
			}
		}
		for (; k < i; i++) {
			printf(" ");
		}
		printf("\n");
	}
}
