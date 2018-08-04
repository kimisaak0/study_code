#include <stdio.h>

int main()
{
	int		iValue = 50;
	float	fValue = 3.141592f;
	FILE*	fp;
	fopen_s(&fp, "demo.txt", "w");
	{
		fprintf(fp, "%s", "========= KGCA =========");
		fprintf(fp, "\n%s", "홍길동");
		fprintf(fp, " %d %f", iValue, fValue);
	}
	fclose(fp);


	iValue = 99;
	fValue = 6.26f;
	fopen_s(&fp, "demo.txt", "a");
	{
		fprintf(fp, "\n%s ", "개통이");
		fprintf(fp, "%d %f", iValue, fValue);
	}
	fclose(fp);


	char	buffer[256] = { 0, };
	int		iValueRead;
	float	fValueRead;
	FILE*	fpRead;

	fopen_s(&fpRead, "demo.txt", "r");
	{
		fgets(buffer, 256, fpRead);
		fscanf_s(fpRead, "%s %d %f", buffer, 256, &iValueRead, &fValueRead);
		printf("\n%s %d %f", buffer, iValueRead, fValueRead);
		fscanf_s(fpRead, "%s %d %f", buffer, 256, &iValueRead, &fValueRead);
		printf("\n%s %d %f", buffer, iValueRead, fValueRead);
	}
	fclose(fpRead);

	return 0;
}