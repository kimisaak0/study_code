#define  _CRT_SECURE_NO_WARNINGS

#pragma once

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>

SQLHENV  g_hEnv;
SQLHDBC  g_hDbc;
SQLHSTMT g_hStmt;


SQLRETURN HandleDiagnosticRecord()
{
	int ii;
	SQLRETURN Ret;
	SQLINTEGER NativeError;
	SQLTCHAR SqlState[6], Msg[255];
	SQLSMALLINT MsgLen;
	TCHAR str[256];

	ii = 1;
	while (Ret = SQLGetDiagRec(SQL_HANDLE_STMT, g_hStmt, ii, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen) != SQL_NO_DATA)
	{
		wsprintf(str, _T("SQLSTATE:%s, ��������:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("���� ����"), 0);
		ii++;
	}
	return Ret;
}

int Init()
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
	SQLTCHAR InCon[256];
	SQLTCHAR OutCon[1024];
	SQLSMALLINT cbOutCon;

	_stprintf(InCon, _T("%s"), _T("Driver={SQL Server};Server=shader.kr;Address=192.168.0.104,1433;Network=dbmssocn;Database=KGCA_SAMPLE;Uid=sa;Pwd=kgca!@34;"));
	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, (SQLTCHAR*)InCon, _countof(InCon), OutCon,	_countof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return -1;
	}

	//��� �ڵ�
	SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);
}

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
	SQLCHAR cID[20] = { 0, };
	SQLCHAR cPASS[20] = { 0, };
	SQLLEN lID, lPASS;
	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, cID, sizeof(cID), &lID);
	SQLBindCol(g_hStmt, 2, SQL_C_CHAR, cPASS, sizeof(cPASS), &lPASS);


	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)_T("{CALL usp_Test}"), SQL_NTS) != SQL_SUCCESS) {
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA) {
		printf("ID : %s, PASS : %s  \n", cID, cPASS);
	}

	SQLCloseCursor(g_hStmt);
}

void Select_2(const char* name)
{
	wchar_t cSearchID[20] = { 0, };
	_tcscpy_s(cSearchID, GetMtW(name));

	int sRet = 0;
	SQLCHAR cID[20] = { 0, };
	SQLCHAR cPASS[20] = { 0, };
	SQLLEN lID, lPASS;
	
	TCHAR buffer[256] = { 0, };

	SQLBindCol(g_hStmt, 1, SQL_C_CHAR, cID, sizeof(cID), &lID);
	SQLBindCol(g_hStmt, 2, SQL_C_CHAR, cPASS, sizeof(cPASS), &lPASS);

	SQLBindParameter(g_hStmt, 1, SQL_PARAM_OUTPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &sRet, 0 , 0);
	SQLBindParameter(g_hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, (SQLTCHAR*)&cSearchID, 0, 0);

	wsprintf((LPTSTR)buffer, _T("{? = CALL usp_Select(?)}"));

	if (SQLExecDirect(g_hStmt, (SQLTCHAR*)buffer, SQL_NTS) != SQL_SUCCESS) {
		HandleDiagnosticRecord();
		return;
	}

	while (SQLFetch(g_hStmt) != SQL_NO_DATA) {
		printf("ID : %s, PASS : %s  \n", cID, cPASS);
	}

	//�̰� ����Ǿ���� ����� Ȯ���� ������.
	SQLMoreResults(g_hStmt);
	// SQLMoreResults�� ��� ��Ʈ�� �����ϴ� ����� ���νõ��� ������ ��ɹ� �ڵ鿡�� ����� �� �ִ� �߰� ������ �� �ִ��� �Ǻ��մϴ�.
	// ��� ��� ��Ʈ�� ó���Ǿ����� SQLMoreResults()�� SQL_NO_DATA_FOUND�� �����մϴ�.
	// SQL_CLOSE �Ǵ� SQL_DROP �ɼ����� SQLFreeStmt()�� ȣ���ϸ� �� ��ɹ� �ڵ� ��� ���� ���� ��� ������ �����˴ϴ�.

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
	std::cout << "�ٲ� �н����带 �Է��ϼ���. \n";
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
