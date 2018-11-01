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
		printf("========= 문자열 복사      ===========\n");
		strcpy_s(str1, iDataSize, data);

		strncpy_s(str2, data, 4); // 뒤에 널문자를 자동으로 추가해줌 
		//strncpy(str2, data, 4); // 뒤에 널문자를 자동으로 추가해주지 않음.
		//str2[4] = 0; //5번째 칸에 널문자를 추가해줌.
		//printf("str2 : %s\n", str2);

		printf("str1 : %s\n", str1);
		printf("str2 : %s\n", str2);

		printf("\n");
		printf("========= 문자열 길이/비교 ===========\n");
		printf("strlen(str1) : %zu\n", strlen(str1));
		printf("strcmp(str1, str2) : %d\n", strcmp(str1, str2));
		printf("strcmp(str2, str1) : %d\n", strcmp(str2, str1));
		printf("strncmp(str1, str2, 4) : %d\n", strncmp(str1, str2, 4));
	}

	{
		printf("\n");
		printf("========= 문자열 변환      ===========\n");

		char* str_trans = (char*)malloc(sizeof(char) * (strlen(str1) + 1));

		strcpy_s(str_trans, strlen(str1) + 1, str1);
		_strupr_s(str_trans, strlen(str_trans) + 1);
		printf("str1 Capital Letter : %s\n", str_trans);
		//_strupr_s()문자열의 소문자를 대문자로 변환
		printf("str1 Default : %s\n", str1);

		strcpy_s(str_trans, strlen(str1) + 1, str1);
		_strlwr_s(str_trans, _msize(str_trans));
		printf("str1 Small Letter : %s\n", str_trans);
		//_strlwr_s()문자열의 소문자를 대문자로 변환
		printf("str1 Default : %s\n", str1);

		free(str_trans);
	}

	{
		printf("\n");
		printf("========= 문자열 조사      ===========\n");
		printf("str1 %s\n", strchr(str1, 'g'));
		//strchr()  str 내에서 가장 앞에 있는 문자 c의 위치를 반환한다.

		printf("\n");
		if (strchr(str1, 'A') != 0) { //문자열 안에 'A'가 있으면 
			printf("strchr : %s \n", strchr(str1, 'g')); //'g'부터의 문자열을 출력
		}
		printf("strstr: %s\n", strstr(str1, "academy"));
		//str1내에 str2가 포함되어 있다면 str1에 있는 str2의 첫글자의 위치를 반환한다.
	}

	{
		printf("\n");
		printf("========= 문자열 추가      ===========\n");
		char buffer[100] = { 0, };
		strcpy_s(buffer, strlen(str1) + 1, str1);
		
		printf("str1        : %s\n", str1);
		printf("str2        : %s\n", str2);
		strcat_s(buffer, str2);
		printf("strcat_s	: %s\n", buffer);
		//strcat_s 첫번째 문자열의 끝에 두번째 문자열을 연결하는 함수
		
		//함수내에서 동적할당을 하는 함수이므로 받아서 해제해줘야 한다.
		char *p = StringToAttach(str1, str2);
		printf("str1+str2 : %s\n", p);
	
		printf("\n");
		printf("========= 문자열 분리      ===========\n");
		
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
		printf("========= 문자열 길이/비교 ===========\n");
		printf("strlen(str1) : %zu\n", strlen(str1));
		printf("strcmp(str1, str2) : %d\n", strcmp(str1, str2));
		printf("strcmp(str2, str1) : %d\n", strcmp(str2, str1));
		printf("strncmp(str1, str2, 4) : %d\n", strncmp(str1, str2, 4));
	}
}

//strcat을 구현해본 함수
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
	//처음 복사한 문자의 크기만큼 포인터를 뒤로 보낸다.


	strcpy_s(pStrReturn, iSrcSize, str2);
	pStrReturn -= iDestSize - 1; 
	//다시 문자열의 맨 처음으로 되돌린다.

	return pStrReturn;

}