#include "dList.h"

int main()
{
	dList a;

	while (true) {
		int iSelect = 0;

		cout << "select number" << endl;
		cout << "0 : ���Ͽ� ������ ���� ����" << endl;
		cout << "1 : ���� ���� ����Ʈ �����" << endl;
		cout << "2 : ���� ���� ����Ʈ �����" << endl;
		cout << "3 : ����Ʈ ��ü ����ϱ�" << endl;
		cout << "�׿� : ����" << endl;
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

