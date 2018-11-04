#pragma once
#include "header.h"

//////////////////////////////////////////////////////////////
// �����(g_pNodeHead)���� ���� �����͸� �����ϴ� ���߿��Ḯ��Ʈ
// ����Ʈ�� ��������� ���ο� �����͸� ���� �����Ѵ�.
// InsertLink_H : ���ο� ��尡 ����� Next�� ����Ǵ� ���� ����.
// InsertLink_T : ���ο� ��尡 ������ Next�� ����Ǵ� ���� ����.
//////////////////////////////////////////////////////////////

class dList
{
	struct data {
		string	m_strName;
		int		m_iAge;

		data*   pPrev;
		data*   pNext;
	};

	data*   pHead;
	data*   pTail;

	int     m_iCount;

public:

	//bool(*process) ();
	//bool    Excute();

	dList();

	bool    CreateData();            // ���ο� �����͸� ����� ������ �����.

	void    AddLink_H(data* pStu);            // pHead ��� �տ� �����Ѵ�.
	void    AddLink_T(data* pStu);            // pTail ��� �ڿ� �����Ѵ�.

	void    DeleteList();                     // ��ü ���Ḯ��Ʈ ����

	bool    DataRead_H();                     // ���Ϸκ��� �����͸� �о� ���� ���Ḯ��Ʈ�� �����.
	bool    DataRead_T();                     // ���Ϸκ��� �����͸� �о� ���� ���Ḯ��Ʈ�� �����.

	bool    PrintData(data* pStu);            // data* pStu�� ����Ѵ�.
	bool    PrintAllData();                   // ��ü ���Ḯ��Ʈ�� ����Ѵ�.

	void    MenuClear();

	~dList();
};
