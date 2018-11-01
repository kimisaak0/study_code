#include "studentMgr.h"



void CreateArray(Data* student); //����� ����
void PrintData(Data* student, int id); //������ ����ϱ�
void PrintArray(Data* student); //����� ����ϱ�
int  IdSearch(Data* student, int iSearchingValue); //id�� �˻�
int  NameSearch(Data* student, char* sSearchingName); //�̸����� �˻�
void DeleteData(Data* student, int iIndex); //������ �����ϱ�. �迭�� �ε��� ������ �����Ѵ�.
void  ChangeData(Data* student, int iIndex); //������ �����ϱ�. 
void AfterSearching(Data* student, int SearchingIndex); //�˻��� �۾�
void RandomInitialization(Data* student); //������ �ʱ�ȭ

int main()
{
	Data student[MAX_SIZE] = { 0, };

	while (1) {
		int iSelect = 0;
		system("cls");
		printf("�޴�\n");
		printf("1. ������ �߰� \n");
		printf("2. ��� ���\n");
		printf("3. ��Ͽ��� �˻�\n");
		printf("4. ������ �ʱ�ȭ \n");
		printf("5. ���� \n");
		printf("6. �ҷ����� \n");
		printf("9. ���α׷� ����\n");
		
		scanf_s("%d", &iSelect);

		switch (iSelect) {

			case 5:
				SaveData(student);
				printf("�����͸� �����߽��ϴ�. \n");
				_getch();

				break;

			case 6:
				LoadData(student);
				printf("�����͸� �ҷ��Խ��ϴ�. \n");
				_getch();

				break;

			case �����ʱ�ȭ:
				RandomInitialization(student);
				printf("���Ƿ� �����͸� ��� �ʱ�ȭ�߽��ϴ�. \n");
				_getch();

				break;

			case �߰�: {
				CreateArray(student);
				break;
			}

			case ���: {
				PrintArray(student);
				_getch();
				break;
			}

			case �˻�:
			{
				if (iCnt == 0) {
					printf("�Էµ� �����Ͱ� �����ϴ�. \n");
					continue;
				}

				int iSelectSearchingA = 0;
				printf("�˻� ����� �����ϼ��� \n");
				printf("1. ID�� �˻� \n");
				printf("2. �̸����� �˻� \n");
				printf("3. �ڷΰ��� \n");
				scanf_s("%d", &iSelectSearchingA);

				int SearchingIndex = 0;

				switch (iSelectSearchingA) {

				case ID��: {
					int iSearchingValue;
					printf("�˻��� ID�� �Է��ϼ��� : ");
					scanf_s("%d", &iSearchingValue);
					SearchingIndex = IdSearch(student, iSearchingValue);
					AfterSearching(student, SearchingIndex);
					break;
				}

				case �̸�����: {
					char NameBuff[10];
					printf("�˻��� �̸��� �Է��ϼ��� : ");
					scanf_s("%s", NameBuff, 10);
					SearchingIndex = NameSearch(student, NameBuff);
					AfterSearching(student, SearchingIndex);
					break;
				}

				case �ǵ��ư���:
					break;

				default:
					printf("�߸� �Է��ϼ̽��ϴ� \n");
					continue;
				}	
			}
			continue;

			case ����:
				printf("���α׷��� �����մϴ�. \n");
				return 0;

			default:
				printf("�߸��Է��ϼ̽��ϴ� \n");
				continue;
		}
	}
}