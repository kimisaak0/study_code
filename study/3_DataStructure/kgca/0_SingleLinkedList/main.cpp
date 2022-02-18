#include "list.h"

int main()
{
	node a;
	
	bool bRunning = true;

	while (bRunning) {

		int iWork = 0;
		cout << "생성(0),출력(1),검색(2),맨 앞에 데이터 추가(3), 저장(4),불러오기(5),종료(그외) : " << endl;
		cin >> iWork;

		string FName = "";
		int iWork_2 = 0;

		switch (iWork)
		{
		case 0: //초기데이터 생성 
			a.MenuClear();
			a.RandData();
		break;
		
		case 1: //화면 출력
			a.MenuClear();
			a.PrintAllData();
		break;

		case 2: // 검색
			a.MenuClear();

			cout << "이름을 입력하세요 " << endl;
			cin >> FName;

			a.FindName(FName);

			if(a.PrintData()) {
				cout << "검색한 데이터 뒤에 새로운 데이터 추가(1), 데이터 삭제(2), 돌아가기(그외) : " << endl;
				cin >> iWork_2;

				switch (iWork_2)
				{
				case 1:
					a.MenuClear();
					a.InsertLink_T();
				break;

				case 2:
					a.MenuClear();
					a.DelLink();
				break;

				default:
				break;
				}
			}
		break;

		case 3:
			a.MenuClear();
			a.InsertLink_H();
		break;

		case 4:
			a.MenuClear();
			a.SaveData("save.txt");
		break;

		case 5:
			a.MenuClear();
			a.LoadLink("save.txt");
		break;

		default:
			cout << "아무키나 누르시면 종료합니다" << endl;
			_getch();
			return 0;
		break;
		}
	}
}