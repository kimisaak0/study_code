#include <cstdio>
#include <cstdlib>
#include <cstring>

char* StringToAttach(const char* str1, const char* str2);

int main()
{
	char data[] = "K,G,C,A, game academy -33-";
	size_t iDataSize = strlen(data) + 1;

	char *str1 = (char*)malloc(sizeof(char) * iDataSize);
	char str2[30];

	{
		printf("========= ���ڿ� ����      ===========\n");
		strcpy_s(str1, iDataSize, data);

		strncpy_s(str2, data, 4); // �ڿ� �ι��ڸ� �ڵ����� �߰����� 
		//strncpy(str2, data, 4); // �ڿ� �ι��ڸ� �ڵ����� �߰������� ����.
		//str2[4] = 0; //5��° ĭ�� �ι��ڸ� �߰�����.
		//printf("str2 : %s\n", str2);

		printf("str1 : %s\n", str1);
		printf("str2 : %s\n", str2);

		printf("\n");
		printf("========= ���ڿ� ����/�� ===========\n");
		printf("strlen(str1) : %zu\n", strlen(str1));
		printf("strcmp(str1, str2) : %d\n", strcmp(str1, str2));
		printf("strcmp(str2, str1) : %d\n", strcmp(str2, str1));
		printf("strncmp(str1, str2, 4) : %d\n", strncmp(str1, str2, 4));
	}

	{
		printf("\n");
		printf("========= ���ڿ� ��ȯ      ===========\n");

		char* str_trans = (char*)malloc(sizeof(char) * (strlen(str1) + 1));

		strcpy_s(str_trans, strlen(str1) + 1, str1);
		_strupr_s(str_trans, strlen(str_trans) + 1);
		printf("str1 Capital Letter : %s\n", str_trans);
		//_strupr_s()���ڿ��� �ҹ��ڸ� �빮�ڷ� ��ȯ
		printf("str1 Default : %s\n", str1);

		strcpy_s(str_trans, strlen(str1) + 1, str1);
		_strlwr_s(str_trans, _msize(str_trans));
		printf("str1 Small Letter : %s\n", str_trans);
		//_strlwr_s()���ڿ��� �ҹ��ڸ� �빮�ڷ� ��ȯ
		printf("str1 Default : %s\n", str1);

		free(str_trans);
	}

	{
		printf("\n");
		printf("========= ���ڿ� ����      ===========\n");
		printf("str1 %s\n", strchr(str1, 'g'));
		//strchr()  str ������ ���� �տ� �ִ� ���� c�� ��ġ�� ��ȯ�Ѵ�.

		printf("\n");
		if (strchr(str1, 'A') != 0) { //���ڿ� �ȿ� 'A'�� ������ 
			printf("strchr : %s \n", strchr(str1, 'g')); //'g'������ ���ڿ��� ���
		}
		printf("strstr: %s\n", strstr(str1, "academy"));
		//str1���� str2�� ���ԵǾ� �ִٸ� str1�� �ִ� str2�� ù������ ��ġ�� ��ȯ�Ѵ�.
	}

	{
		printf("\n");
		printf("========= ���ڿ� �߰�      ===========\n");
		char buffer[100] = { 0, };
		strcpy_s(buffer, strlen(str1) + 1, str1);
		
		printf("str1        : %s\n", str1);
		printf("str2        : %s\n", str2);
		strcat_s(buffer, str2);
		printf("strcat_s	: %s\n", buffer);
		//strcat_s ù��° ���ڿ��� ���� �ι�° ���ڿ��� �����ϴ� �Լ�
		
		//�Լ������� �����Ҵ��� �ϴ� �Լ��̹Ƿ� �޾Ƽ� ��������� �Ѵ�.
		char *p = StringToAttach(str1, str2);
		printf("str1+str2 : %s\n", p);
	
		printf("\n");
		printf("========= ���ڿ� �и�      ===========\n");
		
		char* pch = NULL;
		pch = p;

		char tok[] = ",.-";
		printf("splitting [\"%s\"] into tokens: %s \n", p, tok);
		
		char** context = NULL;
		context = (char**)malloc(sizeof(char**));

		pch = strtok_s(pch, tok, context);
		while (pch != NULL)
		{
			printf("%s\n", pch);
			pch = strtok_s(*context, tok, context);
		}
		free(p);
	}
	free(str1);

	{
		char data[] = "k,g,c,a, game academy -33-";
		size_t iDataSize = strlen(data) + 1;

		char *str1 = (char*)malloc(sizeof(char) * iDataSize);
		char str2[30];

		printf("\n");
		printf("========= ���ڿ� ����/�� ===========\n");
		printf("strlen(str1) : %zu\n", strlen(str1));
		printf("strcmp(str1, str2) : %d\n", strcmp(str1, str2));
		printf("strcmp(str2, str1) : %d\n", strcmp(str2, str1));
		printf("strncmp(str1, str2, 4) : %d\n", strncmp(str1, str2, 4));
	}
}

//strcat�� �����غ� �Լ�
char* StringToAttach(const char* str1, const char* str2)
{
	int iDestSize = 0;
	while (str1[iDestSize++] != 0); 
	// == strlen(str1+1);

	int iSrcSize = 0;
	while (str2[iSrcSize++] != 0);
	// == strlen(str2+1);

	char* pStrReturn = (char*)malloc(iDestSize + iSrcSize);

	strcpy_s(pStrReturn, iDestSize, str1);
	pStrReturn += iDestSize - 1; 
	//ó�� ������ ������ ũ�⸸ŭ �����͸� �ڷ� ������.


	strcpy_s(pStrReturn, iSrcSize, str2);
	pStrReturn -= iDestSize - 1; 
	//�ٽ� ���ڿ��� �� ó������ �ǵ�����.

	return pStrReturn;

}