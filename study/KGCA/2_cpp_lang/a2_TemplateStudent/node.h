#pragma once
#include "Header.h"

//list클래스에서 사용할 node 클래스 템플릿
template <class T>
class node
{
	//멤버를 public으로 둔 상태
public:
	T*     m_pData;   //임의의 클래스를 데이터로 가리킬 수 있다.
	node*  m_pNext;   //다음 노드를 가리키는 포인터
	node*  m_pPrev;   //다음 노드를 가리키는 포인터

public:
	void del() 
	{
		delete m_pData;
	}

	node()
	{
		m_pData = nullptr;            //가리키고 있는 데이터가 없음
		m_pNext = m_pPrev = nullptr;  //이어져 있는 노드가 없음.
	}

	~node()
	{
		delete m_pData;
		//cout << "node end" << endl;
	}
};