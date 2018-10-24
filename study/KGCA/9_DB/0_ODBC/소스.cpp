//#define _CRT_SECURE_NO_WARNINGS
//#include <Windows.h>
//#include <sql.h>
//#include <sqlext.h>
//#include <tchar.h>
//#include <iostream>
//
//SQLHENV      hEnv;
//SQLHDBC      hDbc;
//SQLHSTMT   hStmt;
//SQLRETURN ret;
//void main()
//{
//
//
//
//	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
//	if (ret != SQL_SUCCESS)
//	{
//		return;
//	}
//
//	ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
//	if (ret != SQL_SUCCESS)
//	{
//		return;
//	}
//
//	ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
//	if (ret != SQL_SUCCESS)
//	{
//		return;
//	}
//
//	SQLTCHAR InCon[255];
//	SQLTCHAR OutCon[255];
//	SQLSMALLINT cbOutCon;
//	TCHAR ConStr[MAX_PATH];
//	GetCurrentDirectory(MAX_PATH, ConStr);
//	wsprintf((TCHAR*)InCon, _T("DRIVER={Microsoft Access Driver (*.mdb)}; DBQ=%s\\cigarette.mdb;"), ConStr);
//
//	ret = SQLDriverConnect(hDbc, NULL, InCon, sizeof(InCon), OutCon, sizeof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);
//	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//	{
//		return;
//	}
//
//	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
//	if (ret != SQL_SUCCESS)
//	{
//		return;
//	}
//
//	SQLTCHAR Name[20] = { 0, };
//	int iPrice = 0;
//	BOOL korean;
//	SQLLEN IName, IPrice, IKorean;
//
//	SQLBindCol(hStmt, 1, SQL_C_CHAR, &Name, sizeof(Name), &IName);
//	SQLBindCol(hStmt, 2, SQL_C_ULONG, &iPrice, sizeof(iPrice), &IPrice);
//	SQLBindCol(hStmt, 3, SQL_C_ULONG, &korean, sizeof(korean), &IKorean);
//
//	SQLTCHAR query[255];
//
//	wsprintf((LPTSTR)query, _T("select * from tblCigar"));
//
//	if (SQLExecDirect(hStmt, query, SQL_NTS) != SQL_SUCCESS)
//	{
//		return;
//	}
//
//	while (SQLFetch(hStmt) != SQL_NO_DATA)
//	{
//		printf("\n%s:[%d]:[%d]", Name, iPrice, korean);
//	}
//	SQLCloseCursor(hStmt);
//
//	wsprintf((LPTSTR)query, _T("insert into tblCigar (name, price, korean) values('¾È³ç', 2000, 0)"));
//
//	if (SQLExecDirect(hStmt, query, SQL_NTS) != SQL_SUCCESS)
//	{
//		return;
//	}
//	wsprintf((LPTSTR)query, _T("select * from tblCigar"));
//
//	if (SQLExecDirect(hStmt, query, SQL_NTS) != SQL_SUCCESS)
//	{
//		return;
//	}
//	while (SQLFetch(hStmt) != SQL_NO_DATA)
//	{
//		printf("\n%s:[%d]", Name, iPrice, korean);
//	}
//
//	SQLCloseCursor(hStmt);
//
//	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//	SQLDisconnect(hStmt);
//	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
//	SQLDisconnect(hDbc);
//	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
//	SQLDisconnect(hEnv);
//}