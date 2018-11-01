#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define USE_ARRAY
#undef USE_ARRAY


#ifdef USE_ARRAY

int Data[20][20];

//ũ�Ⱑ iSize�� �������� �����.

void MagicSquare(int iSize);

int main()
{
	int iSize;

	//������ �Է�
	while (true) {
		printf("�������� ũ�⸦ 3~19������ Ȧ���� �Է��ϼ��� :"); 
		scanf_s("%d", &iSize);
		
		if (iSize >= 3 && iSize < 20) {
			break;
		}
	}

	//������ ���
	MagicSquare(iSize);

	//������ ���
	for (int iRow = 0; iRow < iSize; iRow++) {
		for (int jCol = 0; jCol < iSize; jCol++) {
			printf("%4d", Data[iRow][jCol]);
		}
		printf("\n\n");
	}	
}

void MagicSquare(int iSize)
{
	int iWidth, iHeight;

	if (iSize % 2 == 0) {
		printf("Ȧ���� �Է����ּ���. \n");
		return;
	}

	//0���� �߰��� 1�� ä���.
	int iRow = 0;
	int iCol = (iSize - 1) / 2;
	Data[iRow][iCol] = 1;


	//���� ���Ŀ� ���� ���� ä��������.
	for (int iNum = 2; iNum <= iSize * iSize; iNum++) {
		if (iRow == 0) {			//���� ���� ���� �����̸�
			iHeight = iSize - 1;	//���� �Ʒ�������
		}
		else {						//�ƴϸ�
			iHeight = iRow - 1;		//��ĭ �������� �̵�
		}

		////���1
		//if (iCol == iSize - 1) {	//���� ���� ���� ������ ���̸�
		//	iWidth = 0;				//���� ���� ����
		//}
		//else {						//�ƴϸ�
		//	iWidth = iCol + 1;		//��ĭ ������ ���� �̵�
		//}

		//���2
		if (iCol == 0) {			//���� ���� ���� ���� ���̸�
			iWidth = iSize - 1;		//���� ������ ����
		}
		else {						//�ƴϸ�
			iWidth = iCol - 1;		//�ϳ� ���� ���� �̵�
		}


		if (Data[iHeight][iWidth] == 0) {	//�̵��� ��ġ�� ��ĭ�̸�
			iRow = iHeight, iCol = iWidth;	//�� ��ġ�� ���ڸ� ä�� ��ġ�� �Ѵ�.
		}
		else {								//��ĭ�� �ƴϸ� 
			iRow++;							//�Ʒ������� �̵�
		}
		Data[iRow][iCol] = iNum;			//���ڸ� ä���.
	}
}

#else

//�Ʒ� �� �Լ��� �����Ҵ� ó���� ���
void Collision(int* x, int* y);
int DynamicAlloc(int iSize);
void Print(int* pData, int iSize);

int main()
{
	int iSize;

	//������ �Է�
	while (true) {
		printf("������ ũ�� (3~19 ������ Ȧ��)�� �Է��ϼ��� : ");
		scanf_s("%d", &iSize); 
		if (iSize >= 3 && iSize < 20) {
			break;
		}
	}

	DynamicAlloc(iSize);
}

void Print(int* pData, int iSize)
{
	system("cls");
	for (int iRow = 0; iRow < iSize; iRow++) {
		printf("\n");
		for (int iCol = 0; iCol < iSize; iCol++) {
			int iIndex = iCol + iSize * iRow;
			printf("%d\t", pData[iIndex]);
		}
	}
}

void Collision(int* x, int* y)
{
	*x = *x - 1;
	*y = *y + 2;
}

int DynamicAlloc(int iSize)
{
	int* pData = (int*)calloc(iSize*iSize, sizeof(int));
	
	int y = 0;
	int x = iSize / 2;

	int iIndex = x + iSize * y;

	int iCount = 1;

	pData[iIndex] = iCount++;

	while (iCount <= (iSize*iSize)) {
		x = x + 1;
		y = y - 1;

		if (x == iSize && y < 0) {
			Collision(&x, &y);
		}
		else {
			if (x == iSize) {
				x = 0;
			}

			if (y < 0) {
				y = iSize - 1;
			}
		}

		iIndex = x + y * iSize;
		if (pData[iIndex] != 0) {
			Collision(&x, &y);
			iIndex = x + iSize * y;
		}
		pData[iIndex] = iCount++;
	}

	Print(pData, iSize);
	free(pData);

	return 0;
}

#endif