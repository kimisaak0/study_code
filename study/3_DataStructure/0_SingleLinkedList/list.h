#pragma once
#include "header.h"

//////////////////////////////////////////////////////////////
// �����(g_pNodeHead) Next���� ���� �����͸� �����ϴ� ���Ḯ��Ʈ
// ������ ����带 ������ �ΰ� ó���Ѵ�.
// InsertLink_H : ���ο� ��尡 ����� Next�� ����Ǵ� ���� ����.
// InsertLink_T : ���ο� ��尡 ������ Next�� ����Ǵ� ���� ����.
// ��) �ܹ��� ���Ḯ��Ʈ�̹Ƿ� ���� ����� �������� �����ϴ� �� �Ұ����ϴ�.
//    (���� ��� -> ���� ���!  -> �ű� ���!! -> ���� ���) <  ����!>
//    (���� ��� -> �ű� ���!! -> ���� ���!  -> ���� ���) <�Ұ���!> 
//////////////////////////////////////////////////////////////

class node
{
	struct data {
		string	m_strName;
		int		m_iAge;

		data*   pNext;
	};

	data*   pHead;
	data*   pTail;
	data*   pFind;

	int     m_iCount;

public:
	node();

	void    NewLink(string name, int age);     // �ű� ��� ���� �� ���Ḯ��Ʈ ����
	void    RandData();                        // �ʱ� ���Ḯ��Ʈ ����

	void    FindName(string pFindName);        // pFindName�̸��� ��带 ��ȯ�Ѵ�.
	bool    PrintData();                       // pFindNode�� ����Ѵ�.
	bool    InsertLink_H();                      // g_pFindNode ��� �տ� �����Ѵ�.
	bool    InsertLink_T();                      // g_pFindNode ��� �ڿ� �����Ѵ�.
	


	void    PrintAllData();                    // ��ü ���Ḯ��Ʈ�� ����Ѵ�.

	void    DelLink();                         // pDelNode�� ���Ḯ��Ʈ���� ����
	void    AllDeleteLink();                   // ��ü ���Ḯ��Ʈ ����

	void    LoadLink(string pFileName);       // ���Ϸκ��� �ε� �� ���Ḯ��Ʈ ����
	void    SaveData(string pFileName);       // ���Ḯ��Ʈ ��ü�� ���Ϸ� ����.
	
	void    MenuClear();
};

