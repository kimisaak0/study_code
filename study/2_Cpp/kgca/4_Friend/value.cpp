#include "value.h"


	value::value(TCHAR* pData)
	{
		//m_szValue�� �޸𸮸� �Ҵ��ϰ� �ڸ� ���ڿ� ����
		int iLength = (int)_tcslen(pData) + 1;
		int iSize = sizeof(TCHAR) * iLength;
		this->m_szValue = new TCHAR[iSize];
		_tcscpy_s(m_szValue, iSize, pData);
		//m_pNext�� nullptr ����
		m_pNext = nullptr;
	}

	value::~value()
	{
		//�Ҵ�� �޸𸮸� ����.
		delete m_szValue;
	}

