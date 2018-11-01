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
	�߰� = 1,
	��� = 2,
	�˻� = 3,
	�����ʱ�ȭ = 4,
	ID�� = 1,
	�̸����� = 2,
	�ǵ��ư��� = 3,
	���� = 1,
	���� = 2,
	���� = 9
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

//������ �Է¹ޱ�
void InputData(Data* student, int iIndex) 
{
	printf("�л��� �̸��� �Է��ϼ��� : "); scanf_s("%s", student[iIndex].cpName, 10);

	printf("���� ������ �Է��ϼ��� : "); scanf_s("%d", &student[iIndex].iKor); while (getchar() != '\n');

	printf("���� ������ �Է��ϼ��� : "); scanf_s("%d", &student[iIndex].iEng); while (getchar() != '\n');
															
	printf("���� ������ �Է��ϼ��� : "); scanf_s("%d", &student[iIndex].iMath); while (getchar() != '\n');
	
	student[iIndex].iSum_score = student[iIndex].iKor + student[iIndex].iEng + student[iIndex].iMath;	//����
	student[iIndex].dAvr = student[iIndex].iSum_score / 3.0;											//���
}

//����� ����
void CreateArray(Data* student)
{
	bool bOnoff = true;
	
	if (iCnt >= MAX_SIZE) {
		printf("�� ���� �� �����ϴ�.\n");
	}

	while (bOnoff && iCnt < MAX_SIZE) {		
		student[iCnt].iID = iCnt;

		InputData(student,iCnt);

		End_array++;
		iCnt++;

		while (bOnoff) {
			printf("��� �Է��Ͻðڽ��ϱ�? (y,n)\n");
			char buff = _getch();
			_getch(); //�׳� ���۸� ���� ���� �뵵
			
			if (buff == 'y' || buff == 'Y') {
				break;
			}
			else if (buff == 'n' || buff == 'N') {
				bOnoff = false;
			}
		}
	}
}

//������ ����ϱ�
void PrintData(Data* student, int id)
{
	printf("%d\t%s\t%3d\t%3d\t%3d\t%3d\t%5.2lf\n",
		student[id].iID, student[id].cpName, student[id].iKor, student[id].iEng, student[id].iMath, student[id].iSum_score, student[id].dAvr);

}

//����� ����ϱ�
void PrintArray(Data* student) 
{
	if (End_array == 0) {
		printf("�Էµ� �����Ͱ� �����ϴ�.\n");
		return;
	}

	printf("ID\t�̸�\t����\t����\t����\t����\t���\n");
	for (int iCnt = 0; iCnt < End_array; iCnt++) {
		PrintData(student, iCnt);
	}
}

//id�� �˻�
int IdSearch(Data* student, int iSearchingValue)
{
	for (int i = 0; i < End_array; i++) {
		if (iSearchingValue == student[i].iID) {
			printf("ID\t�̸�\t����\t����\t����\t����\t���\n");
			PrintData(student, i);
			return i;
		}
	}
	printf("ã���ô� �����Ͱ� �����ϴ�. \n");
	return -1;
}

//�̸����� �˻�
int NameSearch(Data* student, char* sSearchingName)
{
	for (int i = 0; i < End_array; i++) {
		if (!strcmp(sSearchingName, student[i].cpName)) {
			printf("ID\t�̸�\t����\t����\t����\t����\t���\n");
			PrintData(student, i);
			return i;
		}
	}
	printf("ã���ô� �����Ͱ� �����ϴ�. \n");
	return -1;
}

//������ �����ϱ�. �迭�� �ε��� ������ �����Ѵ�.
void DeleteData(Data* student,int iIndex)
{
	for (int i = iIndex; i < End_array-1; i++) {
		student[i] = student[i + 1];
	}
	End_array--;
}

//������ �����ϱ�. 
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
		printf("�˻� �� ���ϴ� �۾��� �����ϼ���. \n");
		printf("1. �� ���� \n");
		printf("2. �� ���� \n");
		printf("3. �ڷΰ��� \n");
		scanf_s("%d", &iSelectSearchingB);

		switch (iSelectSearchingB) {
		case ����:
			ChangeData(student, SearchingIndex);
			return;

		case ����:
			DeleteData(student, SearchingIndex);
			return;

		case �ǵ��ư���:
			return;

		default:
			printf("�߸��Է��ϼ̽��ϴ� \n");
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
		student[i].iSum_score = student[i].iKor + student[i].iEng + student[i].iMath;	//����
		student[i].dAvr = student[i].iSum_score / 3.0;									//���
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