#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define USE_ARRAY
#undef USE_ARRAY


#ifdef USE_ARRAY

int Data[20][20];

//크기가 iSize인 마방진을 만든다.

void MagicSquare(int iSize);

int main()
{
	int iSize;

	//마방진 입력
	while (true) {
		printf("마방진의 크기를 3~19사이의 홀수로 입력하세요 :"); 
		scanf_s("%d", &iSize);
		
		if (iSize >= 3 && iSize < 20) {
			break;
		}
	}

	//마방진 계산
	MagicSquare(iSize);

	//마방진 출력
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
		printf("홀수를 입력해주세요. \n");
		return;
	}

	//0행의 중간에 1을 채운다.
	int iRow = 0;
	int iCol = (iSize - 1) / 2;
	Data[iRow][iCol] = 1;


	//이후 공식에 따라 수를 채워나간다.
	for (int iNum = 2; iNum <= iSize * iSize; iNum++) {
		if (iRow == 0) {			//현재 행이 제일 위행이면
			iHeight = iSize - 1;	//제일 아래행으로
		}
		else {						//아니면
			iHeight = iRow - 1;		//한칸 위행으로 이동
		}

		////방법1
		//if (iCol == iSize - 1) {	//현재 행이 제일 오른쪽 열이면
		//	iWidth = 0;				//제일 왼쪽 열로
		//}
		//else {						//아니면
		//	iWidth = iCol + 1;		//한칸 오른쪽 열로 이동
		//}

		//방법2
		if (iCol == 0) {			//현재 행이 제일 왼쪽 열이면
			iWidth = iSize - 1;		//제일 오른쪽 열로
		}
		else {						//아니면
			iWidth = iCol - 1;		//하나 왼쪽 열로 이동
		}


		if (Data[iHeight][iWidth] == 0) {	//이동한 위치가 빈칸이면
			iRow = iHeight, iCol = iWidth;	//이 위치를 숫자를 채울 위치로 한다.
		}
		else {								//빈칸이 아니면 
			iRow++;							//아래행으로 이동
		}
		Data[iRow][iCol] = iNum;			//숫자를 채운다.
	}
}

#else

//아래 두 함수는 동적할당 처리에 사용
void Collision(int* x, int* y);
int DynamicAlloc(int iSize);
void Print(int* pData, int iSize);

int main()
{
	int iSize;

	//마방진 입력
	while (true) {
		printf("마방진 크기 (3~19 사이의 홀수)를 입력하세요 : ");
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