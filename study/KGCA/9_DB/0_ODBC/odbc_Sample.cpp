#define  _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>


SQLHENV  g_hEnv;
SQLHDBC  g_hDbc;
SQLHSTMT g_hStmt;


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

	SQLTCHAR szInCon[256] = { 0, };
	_stprintf(szInCon, _T("DRIVER={Microsoft Access Driver (*.mdb)}; DBQ=cigarette.mdb; "));
	SQLTCHAR szOutCon[256] = { 0, };
	SQLSMALLINT cbCon = 0;

	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, szInCon, _countof(szInCon), szOutCon, _countof(szOutCon), &cbCon, SQL_DRIVER_NOPROMPT);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return -1;
	}

	//명령 핸들
	SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);

	SQLCHAR cName[20] = { 0, };
	int iPrice = 0;
	BOOL bKorean;
	SQLLEN lName, lPrice, lKorean;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, cName, sizeof(cName), &lName);
	SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &iPrice, 0, &lPrice);
	SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &bKorean, 0, &lKorean);
	

	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)_T("select name,price,korean from tblCigar"), SQL_NTS) != SQL_SUCCESS) {
		return -1;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA) {
		printf("%s : %d원 국산 : %d  \n", cName, iPrice, bKorean);
	}

	SQLCloseCursor(g_hStmt);


	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLDisconnect(g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
	SQLDisconnect(g_hEnv);
}