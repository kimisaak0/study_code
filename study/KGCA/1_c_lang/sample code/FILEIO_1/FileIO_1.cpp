#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


//파일을 읽어들여 16진수와 문자로 출력한다.
void DrawHexAscii(char* file) 
{
	unsigned char munja[10];
	FILE* fp;
	int i, j, n = 0;

	fopen_s(&fp, file, "rb");
	if (fp == NULL)
	{
		puts("파일이 존재하지 않습니다. \n");
		return;
	}

	while (!feof(fp)) {
		printf("\n%05d : ", ftell(fp));
		for (i = 0; i < 10; i++) {
			munja[i] = fgetc(fp);
			printf("%02X", munja[i]);
			if (feof(fp)) { break; }
		}
		printf("  ");

		for (j = 0; j < i; j++) {
			if (munja[j] == '\t' || munja[j] == '\n' || munja[j] == '\r') {
				munja[j] = '.';
			}
			putchar(munja[j]);
		}
		n++;
		if (n % 20 == 0) {
			puts("\n<아무키나 누르세요>\n");
			_getch();
		}
	}
}

//파일을 로딩하여 역순으로 출력한다.

void DrawInverse(char* file)
{
	FILE* fp;

	fopen_s(&fp, file, "rb");
	if (fp == NULL)
	{
		puts("파일이 존재하지 않습니다. \n");
		return;
	}

	fseek(fp, 0, SEEK_END);
	int iSize = ftell(fp);
	printf("%d 바이트입니다.\n", iSize);
	fseek(fp, 0, SEEK_SET);

	int n = 0;

	do {
		char* munja = 0;
		munja = (char*)calloc(256, sizeof(char));

		int i, j;

		for (i = 0; i < 256; i++) {
			if (!feof(fp)) {
				munja[i] = fgetc(fp);
			}
			else {
				free(munja);
				return;
			}

			//int iCnt = fseek(fp, 2, SEEK_CUR);
			if (munja[i] == '\n' || ftell(fp) <= 0) {
				break;
			}
		}
		for (j = i; j > 0; j--) {
			putchar(munja[j]);
		}
		n++;
		free(munja);

		if (n % 20 == 0) {
			puts("\n<아무키나 누르세요>\n");
			_getch();
		}

	} while (!feof(fp));
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf("\n 사용법 : fileIO_1.exe FilePath 0(inverse) or 1(Hex) \n");
		return 0;
	}

	int iValue = atoi(argv[2]);
	if (iValue == 1) {
		DrawHexAscii(argv[1]);
	}
	else {
		DrawInverse(argv[1]);
	}

}