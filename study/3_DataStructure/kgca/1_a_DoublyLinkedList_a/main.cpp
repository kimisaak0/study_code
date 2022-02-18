#include "dList.h"

int main()
{
	dList a;

	while (true) {
		int iSelect = 0;

		cout << "select number" << endl;
		cout << "0 : 파일에 데이터 새로 쓰기" << endl;
		cout << "1 : 전위 연결 리스트 만들기" << endl;
		cout << "2 : 후위 연결 리스트 만들기" << endl;
		cout << "3 : 리스트 전체 출력하기" << endl;
		cout << "그외 : 종료" << endl;
		cin >> iSelect;

		bool (dList::*process)();

		switch (iSelect) {
		case 0:
			process = &dList::CreateData;
			break;

		case 1:
			process = &dList::DataRead_H;
			break;

		case 2:
			process = &dList::DataRead_T;
			break;

		case 3:
			process = &dList::PrintAllData;
			break;

		default:
			return 0;
		}

		a.MenuClear();
		(a.*process)();
	}

}

