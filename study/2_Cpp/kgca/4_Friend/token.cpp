#include "token.h"

void   token::Show()
{
	// ���ڿ��� ������� ����Ѵ�.
	value* pData = m_pToken;
	for (int iCnt = 0; iCnt < m_iSize; iCnt++) {
		wcout << pData->m_szValue << endl;
		pData = pData->m_pNext;
	}
}

void   token::Show(value* pValue)
{
	//�Ű������� ���� ���ڿ��� �ڸ���.
	TCHAR* pszNextToken = 0;
	TCHAR* temp = _tcstok_s(pValue->m_szValue, SPA, &pszNextToken);
	if (temp != NULL) {
		m_pToken = new value(temp);
		value* pLink = m_pToken;
		for (m_iSize = 1; temp = _tcstok_s(0, SPA, &pszNextToken); m_iSize++) {
			pLink->m_pNext = new value(temp);
			pLink = pLink->m_pNext;
		}
	}
	//�ڸ��� ������� ����Ѵ�.
	Show();
}


TCHAR* token::nth_token(int num)
{//������ ������ ���ڿ��� ����Ѵ�.
	value* cursor = m_pToken;

	for (int iCnt = 1; iCnt < num; iCnt++) {
		if (cursor != 0) {	cursor = cursor->m_pNext; 	}
		else             {	return 0; }
	}

	return cursor->m_szValue;
}

token::token(TCHAR* pData) 
{//�Ű������� ���� ���ڿ��� �߶� ����Ʈ ������ �����Ѵ�.
	m_iSize = 0;
	TCHAR* temp;
	TCHAR* pszNextToken = 0;

	try {
		//int iNum = 100;
		//int iId = 1;
		//if (iId = 0) { throw(iId); }
		//if (pszNextToken == 0) { //throw (pszNextToken); 
		//	throw EXP(); //exit(1);
		//}
		//iNum /= iId;

		temp = _tcstok_s(pData, SPA, &pszNextToken);
		if (temp != NULL) {
			m_pToken = new value(temp);
			value* pLink = m_pToken;
			for (m_iSize = 1; temp = _tcstok_s(0, SPA, &pszNextToken); m_iSize++) {
				pLink->m_pNext = new value(temp);
				pLink = pLink->m_pNext;
			}
		}
	}

	catch (int iNum) {
		wcout << _T("Error!");
	}
	catch (TCHAR* pszNextToken) {
		wcout << _T("Error!");
		throw(pszNextToken);
	}
	catch (EXP& exp) {
		exp.show((TCHAR*)_T("Error!"));
	}
}

token::token()
{
	m_iSize = 0;
}


token::~token()
{//����Ʈ�� �����Ѵ�.
	value* pDel;
	value* pLink = m_pToken;
	while (pLink != 0) {
		pDel  = pLink;
		pLink = pLink->m_pNext;
		delete pDel;
	}
}
