#include "odbc.h"



int main()
{
	int iRet = Init();

	while (true) {
		int iSelect = 0;

		std::cout << "\n1. 회원목록 출력, 2. 회원가입 3. 탈퇴 4. 비밀번호수정";
		std::cin >> iSelect;

		switch (iSelect) {
			case 1: { 
				Select(); 
			} break;

			case 2: { 
				char name[26] = { 0, };
				char pass[26] = { 0, };
				std::cout << "ID를 입력하세요 : "; scanf("%s", name);
				std::cout << "PASS를 입력하세요 : "; scanf("%s", pass);
				Add(name, pass);
			} break;

			case 3: {
				char name[26];
				std::cout << "필드명을 입력하세요 : "; scanf("%s", name);
				Delete(name);
			} break;

			case 4: {
				char name[26];
				std::cout << "필드명을 입력하세요 : "; scanf("%s", name);
				Update(name);
			} break;

			case 5: {
				char name[26];
				std::cout << "필드명을 입력하세요 : "; scanf("%s", name);
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