#include "studentMgr.h"



void CreateArray(Data* student); //목록을 만듬
void PrintData(Data* student, int id); //데이터 출력하기
void PrintArray(Data* student); //목록을 출력하기
int  IdSearch(Data* student, int iSearchingValue); //id로 검색
int  NameSearch(Data* student, char* sSearchingName); //이름으로 검색
void DeleteData(Data* student, int iIndex); //데이터 삭제하기. 배열의 인덱스 값으로 삭제한다.
void  ChangeData(Data* student, int iIndex); //데이터 수정하기. 
void AfterSearching(Data* student, int SearchingIndex); //검색후 작업
void RandomInitialization(Data* student); //무작위 초기화

int main()
{
	Data student[MAX_SIZE] = { 0, };

	while (1) {
		int iSelect = 0;
		system("cls");
		printf("메뉴\n");
		printf("1. 데이터 추가 \n");
		printf("2. 목록 출력\n");
		printf("3. 목록에서 검색\n");
		printf("4. 무작위 초기화 \n");
		printf("5. 저장 \n");
		printf("6. 불러오기 \n");
		printf("9. 프로그램 종료\n");
		
		scanf_s("%d", &iSelect);

		switch (iSelect) {

			case 5:
				SaveData(student);
				printf("데이터를 저장했습니다. \n");
				_getch();

				break;

			case 6:
				LoadData(student);
				printf("데이터를 불러왔습니다. \n");
				_getch();

				break;

			case 랜덤초기화:
				RandomInitialization(student);
				printf("임의로 데이터를 모두 초기화했습니다. \n");
				_getch();

				break;

			case 추가: {
				CreateArray(student);
				break;
			}

			case 출력: {
				PrintArray(student);
				_getch();
				break;
			}

			case 검색:
			{
				if (iCnt == 0) {
					printf("입력된 데이터가 없습니다. \n");
					continue;
				}

				int iSelectSearchingA = 0;
				printf("검색 방법을 선택하세요 \n");
				printf("1. ID로 검색 \n");
				printf("2. 이름으로 검색 \n");
				printf("3. 뒤로가기 \n");
				scanf_s("%d", &iSelectSearchingA);

				int SearchingIndex = 0;

				switch (iSelectSearchingA) {

				case ID로: {
					int iSearchingValue;
					printf("검색할 ID를 입력하세요 : ");
					scanf_s("%d", &iSearchingValue);
					SearchingIndex = IdSearch(student, iSearchingValue);
					AfterSearching(student, SearchingIndex);
					break;
				}

				case 이름으로: {
					char NameBuff[10];
					printf("검색할 이름을 입력하세요 : ");
					scanf_s("%s", NameBuff, 10);
					SearchingIndex = NameSearch(student, NameBuff);
					AfterSearching(student, SearchingIndex);
					break;
				}

				case 되돌아가기:
					break;

				default:
					printf("잘못 입력하셨습니다 \n");
					continue;
				}	
			}
			continue;

			case 종료:
				printf("프로그램을 종료합니다. \n");
				return 0;

			default:
				printf("잘못입력하셨습니다 \n");
				continue;
		}
	}
}