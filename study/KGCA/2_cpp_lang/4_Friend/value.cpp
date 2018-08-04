#include "value.h"


	value::value(TCHAR* pData)
	{
		//m_szValue에 메모리를 할당하고 자른 문자열 저장
		int iLength = (int)_tcslen(pData) + 1;
		int iSize = sizeof(TCHAR) * iLength;
		this->m_szValue = new TCHAR[iSize];
		_tcscpy_s(m_szValue, iSize, pData);
		//m_pNext에 nullptr 대입
		m_pNext = nullptr;
	}

	value::~value()
	{
		//할당된 메모리를 해제.
		delete m_szValue;
	}

