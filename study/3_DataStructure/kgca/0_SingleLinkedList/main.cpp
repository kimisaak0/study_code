#include "list.h"

int main()
{
	node a;
	
	bool bRunning = true;

	while (bRunning) {

		int iWork = 0;
		cout << "����(0),���(1),�˻�(2),�� �տ� ������ �߰�(3), ����(4),�ҷ�����(5),����(�׿�) : " << endl;
		cin >> iWork;

		string FName = "";
		int iWork_2 = 0;

		switch (iWork)
		{
		case 0: //�ʱⵥ���� ���� 
			a.MenuClear();
			a.RandData();
		break;
		
		case 1: //ȭ�� ���
			a.MenuClear();
			a.PrintAllData();
		break;

		case 2: // �˻�
			a.MenuClear();

			cout << "�̸��� �Է��ϼ��� " << endl;
			cin >> FName;

			a.FindName(FName);

			if(a.PrintData()) {
				cout << "�˻��� ������ �ڿ� ���ο� ������ �߰�(1), ������ ����(2), ���ư���(�׿�) : " << endl;
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
			cout << "�ƹ�Ű�� �����ø� �����մϴ�" << endl;
			_getch();
			return 0;
		break;
		}
	}
}