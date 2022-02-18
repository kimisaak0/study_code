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
		wsprintf(str, _T("SQLSTATE:%s, 진단정보:%s"), (LPCTSTR)SqlState, (LPCTSTR)Msg);
		::MessageBox(NULL, str, _T("진단 정보"), 0);
		ii++;
	}
	return Ret;
}

int Init()
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
	SQLTCHAR InCon[256];
	SQLTCHAR OutCon[1024];
	SQLSMALLINT cbOutCon;

	_stprintf(InCon, _T("%s"), _T("Driver={SQL Server};Server=shader.kr;Address=192.168.0.104,1433;Network=dbmssocn;Database=KGCA_SAMPLE;Uid=sa;Pwd=kgca!@34;"));
	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, (SQLTCHAR*)InCon, _countof(InCon), OutCon,	_countof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);

	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		return -1;
	}

	//명령 핸들
	SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt);
}

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

	//이게 실행되어야지 결과값 확인이 가능함.
	SQLMoreResults(g_hStmt);
	// SQLMoreResults는 결과 세트을 리턴하는 저장된 프로시듀어와 연관된 명령문 핸들에서 사용할 수 있는 추가 정보가 더 있는지 판별합니다.
	// 모든 결과 세트가 처리되었으면 SQLMoreResults()는 SQL_NO_DATA_FOUND를 리턴합니다.
	// SQL_CLOSE 또는 SQL_DROP 옵션으로 SQLFreeStmt()를 호출하면 이 명령문 핸들 가운데 지연 중인 모든 집합이 삭제됩니다.

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
