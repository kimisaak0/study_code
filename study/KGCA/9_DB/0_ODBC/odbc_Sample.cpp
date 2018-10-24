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
	// �����Ǵ� ���ڿ��� ũ�Ⱑ ��ȯ�ȴ�.
	int iLength = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
	int iRet = MultiByteToWideChar(CP_ACP, 0,
		data, -1,  //  �ҽ�
		retData, iLength); // ���
	return retData;
}

void Select()
{
	SQLCHAR cName[20] = { 0, };
	int iPrice = 0;
	BOOL bKorean;
	SQLLEN lName, lPrice, lKorean;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, cName, sizeof(cName), &lName);
	SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &iPrice, 0, &lPrice);
	SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &bKorean, 0, &lKorean);


	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)_T("select name,price,korean from tblCigar"), SQL_NTS) != SQL_SUCCESS) {
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA) {
		printf("%s : %d�� ���� : %d  \n", cName, iPrice, bKorean);
	}

	SQLCloseCursor(g_hStmt);
}


void Add(const char* name, int price)
{
	const wchar_t* cName = GetMtW(name);
	int iPrice = price;
	TCHAR buffer[256] = { 0, };

	wsprintf((LPTSTR)buffer, _T("Insert into tblCigar (name, price, korean) VALUES ('%s', %d, TRUE)"), cName, iPrice);

	if (SQLExecDirect(g_hStmt, buffer, SQL_NTS) == SQL_SUCCESS) {
		SQLCloseCursor(g_hStmt);
		Select();
	}
	SQLCloseCursor(g_hStmt);
}

void Delete(const char* name)
{
	const wchar_t* cName = GetMtW(name);
	TCHAR buffer[256] = { 0, };

	wsprintf((LPTSTR)buffer, _T("Delete from tblCigar where name = '%s'"), cName);

	if (SQLExecDirect(g_hStmt, buffer, SQL_NTS) == SQL_SUCCESS) {
		SQLCloseCursor(g_hStmt);
		Select();
	}
	SQLCloseCursor(g_hStmt);
}

void Update(const char* name)
{
	const wchar_t* cName = GetMtW(name);

	wchar_t* UpdateName = new wchar_t;
	std::cout << "�ٲ� �̸��� �Է��ϼ���.";
	wscanf(L"%s", UpdateName);

	getc(stdin);

	int UpdatePrice = 0;
	std::cout << "�ٲ� ������ �Է��ϼ���.";
	scanf("%d", &UpdatePrice);

	TCHAR buffer[256] = { 0, };

	wsprintf((LPTSTR)buffer, _T("Update tblCigar set name = '%s', price = %d where name = '%s'"), UpdateName, UpdatePrice, cName);

	SQLCloseCursor(g_hStmt);
	if (SQLExecDirect(g_hStmt, buffer, SQL_NTS) == SQL_SUCCESS) {
		SQLCloseCursor(g_hStmt);
		Select();
	}
	SQLCloseCursor(g_hStmt);
}

int main()
{
	//ȯ�� �ڵ�
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv) != SQL_SUCCESS) {
		return -1;
	}

	if (SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) {
		return -1;
	}

	//���� �ڵ�
	SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc);

	SQLTCHAR szInCon[256] = _T("FileDsn=.\\cigarette.mdb.dsn");
	//_stprintf(szInCon, _T("DRIVER={Microsoft Access Driver (*.mdb)}; DBQ=cigarette.mdb; "));
	SQLTCHAR szOutCon[256] = { 0, };
	SQLSMALLINT cbCon = 0;

	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, szInCon, _countof(szInCon), szOutCon, _countof(szOutCon), &cbCon, SQL_DRIVER_NOPROMPT);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return -1;
	}

	//��� �ڵ�
	SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);

	while (true) {
		int iSelect = 0;

		std::cout << "\n1. ���, 2. ���� 3. ���� 4. ����";
		std::cin >> iSelect;

		switch (iSelect) {
			case 1: { 
				Select(); 
			} break;

			case 2: { 
				char name[26];
				int price;
				std::cout << "�ʵ���� �Է��ϼ��� : "; scanf("%s", name);
				std::cout << "������ �Է��ϼ��� : "; std::cin >> price;
				Add(name, price); 
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