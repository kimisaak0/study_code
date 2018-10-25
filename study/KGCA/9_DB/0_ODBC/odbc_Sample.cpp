#define  _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>

SQLHENV  g_hEnv;
SQLHDBC  g_hDbc;
SQLHSTMT g_hStmt;

static WCHAR* GetMtW(const char* data)
{
	WCHAR retData[4096] = { 0 };
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		data, -1,  //  소스
		retData, iLength); // 대상
	return retData;
}

void Select()
{
	SQLCHAR cID[20] = { 0, };
	SQLCHAR cPASS[20] = { 0, };
	SQLLEN lID, lPASS;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, cID, sizeof(cID), &lID);
	SQLBindCol(g_hStmt, 2, SQL_C_CHAR, cPASS, sizeof(cPASS), &lPASS);


	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)_T("select Client_ID, Client_pass from user_list"), SQL_NTS) != SQL_SUCCESS) {
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA) {
		printf("ID : %s, PASS : %s  \n", cID, cPASS);
	}

	SQLCloseCursor(g_hStmt);
}


void Add(const char* name, const char* pass)
{
	wchar_t cID[26] = { 0, };
	_tcscpy_s(cID, GetMtW(name));
	wchar_t cPASS[26] = { 0, };
	_tcscpy_s(cPASS, GetMtW(pass));

	TCHAR buffer[256] = { 0, };

	wsprintf((LPTSTR)buffer, _T("Insert into user_list (Client_ID, Client_pass) VALUES ('%s', '%s')"), cID, cPASS);

	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)buffer, SQL_NTS) == SQL_SUCCESS) {
		SQLCloseCursor(g_hStmt);
		Select();
	}
	SQLCloseCursor(g_hStmt);
}

void Delete(const char* name)
{
	wchar_t cID[26] = { 0, };
	_tcscpy_s(cID, GetMtW(name));
	TCHAR buffer[256] = { 0, };

	wsprintf((LPTSTR)buffer, _T("Delete from user_list where Client_ID = '%s'"), cID);

	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)buffer, SQL_NTS) == SQL_SUCCESS) {
		SQLCloseCursor(g_hStmt);
		Select();
	}
	SQLCloseCursor(g_hStmt);
}

void Update(const char* name)
{
	const wchar_t* cID = GetMtW(name);

	wchar_t* UpdatePASS = new wchar_t;
	std::cout << "바꿀 패스워드를 입력하세요. \n";
	wscanf(L"%s", UpdatePASS);

	getc(stdin);

	TCHAR buffer[256] = { 0, };

	wsprintf((LPTSTR)buffer, _T("Update user_list set Client_PASS = '%s' where Client_ID = '%s'"), UpdatePASS, cID);

	SQLCloseCursor(g_hStmt);
	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)buffer, SQL_NTS) == SQL_SUCCESS) {
		SQLCloseCursor(g_hStmt);
		Select();
	}
	SQLCloseCursor(g_hStmt);
}

int main()
{
	//환경 핸들
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv) != SQL_SUCCESS) {
		return -1;
	}

	if (SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) {
		return -1;
	}

	//연결 핸들
	SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc);
	SQLTCHAR dsn[256] = _T("Sample_db");

	SQLRETURN ret = SQLConnect(g_hDbc, (SQLTCHAR*)dsn, SQL_NTS, (SQLTCHAR*)L"sa", SQL_NTS, (SQLTCHAR*)L"kgca!@34", SQL_NTS);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return -1;
	}


	//명령 핸들
	SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);

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