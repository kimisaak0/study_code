#include "odbc.h"



int main()
{
	int iRet = Init();

	while (true) {
		int iSelect = 0;

		std::cout << "\n1. ȸ����� ���, 2. ȸ������ 3. Ż�� 4. ��й�ȣ����";
		std::cin >> iSelect;

		switch (iSelect) {
			case 1: { 
				Select(); 
			} break;

			case 2: { 
				char name[26] = { 0, };
				char pass[26] = { 0, };
				std::cout << "ID�� �Է��ϼ��� : "; scanf("%s", name);
				std::cout << "PASS�� �Է��ϼ��� : "; scanf("%s", pass);
				Add(name, pass);
			} break;

			case 3: {
				char name[26];
				std::cout << "�ʵ���� �Է��ϼ��� : "; scanf("%s", name);
				Delete(name);
			} break;

			case 4: {
				char name[26];
				std::cout << "�ʵ���� �Է��ϼ��� : "; scanf("%s", name);
				Update(name);
			} break;

			case 5: {
				char name[26];
				std::cout << "�ʵ���� �Է��ϼ��� : "; scanf("%s", name);
				Select_2(name);

			}
		}
	}

	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLDisconnect(g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
	SQLDisconnect(g_hEnv);
}