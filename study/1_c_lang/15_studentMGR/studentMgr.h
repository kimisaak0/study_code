#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


#define MAX_SIZE 10

int End_array = 0;
int iCnt = 0;

enum menu_number {
	추가 = 1,
	출력 = 2,
	검색 = 3,
	랜덤초기화 = 4,
	ID로 = 1,
	이름으로 = 2,
	되돌아가기 = 3,
	수정 = 1,
	삭제 = 2,
	종료 = 9
};


struct Data {
	int iID;
	char cpName[10];
	int iKor;
	int iEng;
	int iMath;
	int iSum_score;
	double dAvr;
};

//데이터 입력받기
void InputData(Data* student, int iIndex) 
{
	printf("학생의 이름을 입력하세요 : "); scanf_s("%s", student[iIndex].cpName, 10);

	printf("국어 성적을 입력하세요 : "); scanf_s("%d", &student[iIndex].iKor); while (getchar() != '\n');

	printf("영어 성적을 입력하세요 : "); scanf_s("%d", &student[iIndex].iEng); while (getchar() != '\n');
															
	printf("수학 성적을 입력하세요 : "); scanf_s("%d", &student[iIndex].iMath); while (getchar() != '\n');
	
	student[iIndex].iSum_score = student[iIndex].iKor + student[iIndex].iEng + student[iIndex].iMath;	//총점
	student[iIndex].dAvr = student[iIndex].iSum_score / 3.0;											//평균
}

//목록을 만듬
void CreateArray(Data* student)
{
	bool bOnoff = true;
	
	if (iCnt >= MAX_SIZE) {
		printf("더 만들 수 없습니다.\n");
	}

	while (bOnoff && iCnt < MAX_SIZE) {		
		student[iCnt].iID = iCnt;

		InputData(student,iCnt);

		End_array++;
		iCnt++;

		while (bOnoff) {
			printf("계속 입력하시겠습니까? (y,n)\n");
			char buff = _getch();
			_getch(); //그냥 버퍼를 비우기 위한 용도
			
			if (buff == 'y' || buff == 'Y') {
				break;
			}
			else if (buff == 'n' || buff == 'N') {
				bOnoff = false;
			}
		}
	}
}

//데이터 출력하기
void PrintData(Data* student, int id)
{
	printf("%d\t%s\t%3d\t%3d\t%3d\t%3d\t%5.2lf\n",
		student[id].iID, student[id].cpName, student[id].iKor, student[id].iEng, student[id].iMath, student[id].iSum_score, student[id].dAvr);

}

//목록을 출력하기
void PrintArray(Data* student) 
{
	if (End_array == 0) {
		printf("입력된 데이터가 없습니다.\n");
		return;
	}

	printf("ID\t이름\t국어\t영어\t수학\t총점\t평균\n");
	for (int iCnt = 0; iCnt < End_array; iCnt++) {
		PrintData(student, iCnt);
	}
}

//id로 검색
int IdSearch(Data* student, int iSearchingValue)
{
	for (int i = 0; i < End_array; i++) {
		if (iSearchingValue == student[i].iID) {
			printf("ID\t이름\t국어\t영어\t수학\t총점\t평균\n");
			PrintData(student, i);
			return i;
		}
	}
	printf("찾으시는 데이터가 없습니다. \n");
	return -1;
}

//이름으로 검색
int NameSearch(Data* student, char* sSearchingName)
{
	for (int i = 0; i < End_array; i++) {
		if (!strcmp(sSearchingName, student[i].cpName)) {
			printf("ID\t이름\t국어\t영어\t수학\t총점\t평균\n");
			PrintData(student, i);
			return i;
		}
	}
	printf("찾으시는 데이터가 없습니다. \n");
	return -1;
}

//데이터 삭제하기. 배열의 인덱스 값으로 삭제한다.
void DeleteData(Data* student,int iIndex)
{
	for (int i = iIndex; i < End_array-1; i++) {
		student[i] = student[i + 1];
	}
	End_array--;
}

//데이터 수정하기. 
void  ChangeData(Data* student, int iIndex)
{
	InputData(student, iIndex);
}

void AfterSearching(Data* student, int SearchingIndex)
{
	if (SearchingIndex == -1) {
		return;
	}
	while (1) {
		int iSelectSearchingB = 0;
		printf("검색 후 원하는 작업을 선택하세요. \n");
		printf("1. 값 수정 \n");
		printf("2. 값 삭제 \n");
		printf("3. 뒤로가기 \n");
		scanf_s("%d", &iSelectSearchingB);

		switch (iSelectSearchingB) {
		case 수정:
			ChangeData(student, SearchingIndex);
			return;

		case 삭제:
			DeleteData(student, SearchingIndex);
			return;

		case 되돌아가기:
			return;

		default:
			printf("잘못입력하셨습니다 \n");
			continue;
		}
	}
}

void RandomInitialization(Data* student)
{
	char RandomName[4];

	srand((unsigned)time(NULL));

	for (int i = End_array; i < MAX_SIZE; i++) {
		student[i].iID = iCnt;
		RandomName[0] = 'A' + (rand() % 26);
		RandomName[1] = 'A' + (rand() % 26);
		RandomName[2] = 'A' + (rand() % 26);
		RandomName[3] = '\0';

		strcpy_s(student[i].cpName, sizeof(char)*(strlen(RandomName) + 1), RandomName);
		student[i].iKor = rand() % 101;
		student[i].iEng = rand() % 101;
		student[i].iMath = rand() % 101;
		student[i].iSum_score = student[i].iKor + student[i].iEng + student[i].iMath;	//총점
		student[i].dAvr = student[i].iSum_score / 3.0;									//평균
		End_array++;
		iCnt++;
	}
}

void SaveData(Data* student)
{
	FILE* Datafp;

	fopen_s(&Datafp, "save.txt", "wt");
	fprintf(Datafp, "%2d\n", End_array);

	for (int i = 0; i < End_array; i++) {
		fprintf(Datafp, "%3d ", student[i].iID);	
		fprintf(Datafp, "%10s ", student[i].cpName);
		fprintf(Datafp, "%3d ", student[i].iKor);
		fprintf(Datafp, "%3d ", student[i].iEng);
		fprintf(Datafp, "%3d ", student[i].iMath);
		fprintf(Datafp, "%3d ", student[i].iSum_score);
		fprintf(Datafp, "%lf\n", student[i].dAvr);
	}

	fclose(Datafp);
}

void LoadData(Data* student) {
	FILE* Datafp;

	fopen_s(&Datafp, "save.txt", "r");

	fscanf_s(Datafp, "%2d", &End_array);

	for (int i = 0; i < End_array; i++) {
		
		fscanf_s(Datafp, "%3d", &student[i].iID);
		fscanf_s(Datafp, "%10s", student[i].cpName,10);
		fscanf_s(Datafp, "%3d", &student[i].iKor);
		fscanf_s(Datafp, "%3d", &student[i].iEng);
		fscanf_s(Datafp, "%3d", &student[i].iMath);
		fscanf_s(Datafp, "%3d", &student[i].iSum_score);
		fscanf_s(Datafp, "%lf\n", &student[i].dAvr);
	}	
	
	fclose(Datafp);
}