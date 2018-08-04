#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <conio.h>

int Compute(int* iValueX, int* iValueY);
void ComputeArray(int* iList, int n);
char* StringToUpper(char strList[]);

int main()
{
	int iX = 10;
	int iY = 20;
	int iArr[] = { 10,20,0,40,50,60 };

	printf("iX + iY : %d \n", Compute(&iX, &iY));
	printf("iX : %d, iY : %d \n", iX, iY);

	int iMaxCnt = sizeof(iArr) / sizeof(iArr[0]);
	int iTotalSize = sizeof(iArr);

	ComputeArray(iArr, iMaxCnt);

	for (int iCnt = 0; iCnt < iMaxCnt; iCnt++) {
		printf("%5d \n", iArr[iCnt]);
	}

//	char* p = StringToUpper("Kgca Game Acamemy");
	
	char cArr[] = "abcd";

	char* p = StringToUpper(cArr);
	puts(p);

	free(p);
}

int Compute(int* iValueX, int* iValueY)
{
	int iAdd = 0;
	iAdd = *iValueX + *iValueY;
	*iValueX = iAdd;

	return iAdd;
}
 
void ComputeArray(int* iList, int n)
{
	for (int iCnt = 0; iCnt < n; iCnt++) {
		iList[iCnt] += 3;
	}
}

char* StringToUpper(char strList[])
{
	int iCount = 0;
	while (strList[iCount++] != 0);
	//�Ѱܹ��� ���ڿ��� ���̸� ���Ѵ�.

	//int iCount = sizeof(strList) ;
	//strList�� �Լ��� ���ڷ� ���޵� ���ο� ������ �����̱� ������ sizeof�����ڷ� ����ϸ� ������ ������ ũ�Ⱑ ��������.
	//�׷��Ƿ� ���� �ڵ�δ� �Ѱܹ��� �迭�� ũ�⸦ ���� �� ����.


	char* pString = NULL;
	pString = (char*)malloc(sizeof(char) * iCount);

	for (int iCnt = 0; iCnt < iCount - 1; iCnt++) {
		pString[iCnt] = toupper(strList[iCnt]);
	}
	//strList�� �ִ� ������ �ϳ��ϳ� �빮�ڷ� �ٲ۴�.

	pString[iCount - 1] = 0;

	return pString;
}