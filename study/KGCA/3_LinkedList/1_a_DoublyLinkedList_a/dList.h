#pragma once
#include "header.h"

//////////////////////////////////////////////////////////////
// 헤드노드(g_pNodeHead)부터 실제 데이터를 저장하는 이중연결리스트
// 리스트가 비어있으면 새로운 데이터를 헤드로 저장한다.
// InsertLink_H : 새로운 노드가 헤드의 Next에 연결되는 전위 연결.
// InsertLink_T : 새로운 노드가 테일의 Next에 연결되는 후위 연결.
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

	bool    CreateData();            // 새로운 데이터를 기록한 파일을 만든다.

	void    AddLink_H(data* pStu);            // pHead 노드 앞에 삽입한다.
	void    AddLink_T(data* pStu);            // pTail 노드 뒤에 삽입한다.

	void    DeleteList();                     // 전체 연결리스트 삭제

	bool    DataRead_H();                     // 파일로부터 데이터를 읽어 전위 연결리스트를 만든다.
	bool    DataRead_T();                     // 파일로부터 데이터를 읽어 후위 연결리스트를 만든다.

	bool    PrintData(data* pStu);            // data* pStu를 출력한다.
	bool    PrintAllData();                   // 전체 연결리스트를 출력한다.

	void    MenuClear();

	~dList();
};
