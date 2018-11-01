#include <stdio.h>

void DrawChar(char cValue);
void DrawStar(int iMaxRow, int iMaxColumn, int iStartColumn, int iDir);
void DrawDiamond(int iNunRow, int iNumCol);

int main()
{
	int iNumColumn = 3;				//행(가로줄,위에서 아래로 셈) = Column
	int iNumRow = iNumColumn;		//열(세로줄,좌에서 우로 셈 ) = Row

	//1)직접 제어문을 사용하여 출력
	for (int row = 0; row < iNumRow; row++) {				

		for (int col = 0; col < iNumColumn - row; col++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * row + 1; k++) {
			printf("*");
		}
		printf("\n");
	}

	for (int row = 0; row < iNumRow; row++) {

		for (int col = 0; col < row; col++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * (iNumColumn - row +1) +1; k++) {
			printf("*");
		}
		printf("\n");
	}

	printf("\n\n");


	//2) 함수를 사용하여 출력
	DrawDiamond(iNumRow, iNumColumn);
}

void DrawChar(char cValue)
{
	fprintf(stdout, "%c", cValue);
}

void DrawStar(int iMaxRow, int iMaxColumn, int iStartColumn, int iDir)
{
	for (int iRow = 0; iRow < iMaxRow; iRow++) {

		int iNumCol = iMaxColumn - (iRow * iDir);
		for (int iCol = 0; iCol < iNumCol; iCol++) {
			DrawChar(' ');
		}

		iNumCol = (iStartColumn - (iRow * -iDir)) * 2 + 1;
		for (int iCol = 0; iCol < iNumCol; iCol++) {
			DrawChar('=');
		}
		printf("\n");
	}
}

void DrawDiamond(int iNumRow, int iNumCol)
{
	//iDir=1 아래로 갯수 증가, iDir = -1 아래로 갯수 감소
	DrawStar(iNumRow,	 iNumCol,  0,		1);
	DrawStar(iNumRow +1, 0		, iNumCol,  -1);
}