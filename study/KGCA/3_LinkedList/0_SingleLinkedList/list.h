#pragma once
#include "header.h"

//////////////////////////////////////////////////////////////
// 헤드노드(g_pNodeHead) Next부터 실제 데이터를 저장하는 연결리스트
// 사전에 헤드노드를 생성해 두고 처리한다.
// InsertLink_H : 새로운 노드가 헤드의 Next에 연결되는 전위 연결.
// InsertLink_T : 새로운 노드가 테일의 Next에 연결되는 후위 연결.
// 주) 단방향 연결리스트이므로 기준 노드의 앞쪽으로 연결하는 건 불가능하다.
//    (이전 노드 -> 기준 노드!  -> 신규 노드!! -> 다음 노드) <  가능!>
//    (이전 노드 -> 신규 노드!! -> 기준 노드!  -> 다음 노드) <불가능!> 
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

	void    NewLink(string name, int age);     // 신규 노드 생성 및 연결리스트 연결
	void    RandData();                        // 초기 연결리스트 구축

	void    FindName(string pFindName);        // pFindName이름의 노드를 반환한다.
	bool    PrintData();                       // pFindNode를 출력한다.
	bool    InsertLink_H();                      // g_pFindNode 노드 앞에 삽입한다.
	bool    InsertLink_T();                      // g_pFindNode 노드 뒤에 삽입한다.
	


	void    PrintAllData();                    // 전체 연결리스트를 출력한다.

	void    DelLink();                         // pDelNode를 연결리스트에서 삭제
	void    AllDeleteLink();                   // 전체 연결리스트 삭제

	void    LoadLink(string pFileName);       // 파일로부터 로드 및 연결리스트 구축
	void    SaveData(string pFileName);       // 연결리스트 전체를 파일로 저장.
	
	void    MenuClear();
};

