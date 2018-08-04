#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


//������ �о�鿩 16������ ���ڷ� ����Ѵ�.
void DrawHexAscii(char* file) 
{
	unsigned char munja[10];
	FILE* fp;
	int i, j, n = 0;

	fopen_s(&fp, file, "rb");
	if (fp == NULL)
	{
		puts("������ �������� �ʽ��ϴ�. \n");
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
			puts("\n<�ƹ�Ű�� ��������>\n");
			_getch();
		}
	}
}

//������ �ε��Ͽ� �������� ����Ѵ�.

void DrawInverse(char* file)
{
	FILE* fp;

	fopen_s(&fp, file, "rb");
	if (fp == NULL)
	{
		puts("������ �������� �ʽ��ϴ�. \n");
		return;
	}

	fseek(fp, 0, SEEK_END);
	int iSize = ftell(fp);
	printf("%d ����Ʈ�Դϴ�.\n", iSize);
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
			puts("\n<�ƹ�Ű�� ��������>\n");
			_getch();
		}

	} while (!feof(fp));
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf("\n ���� : fileIO_1.exe FilePath 0(inverse) or 1(Hex) \n");
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