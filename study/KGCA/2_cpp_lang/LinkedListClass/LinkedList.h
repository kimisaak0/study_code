#pragma once
#include "Header.h"

class LinkedList
{
	struct Node {
		int		m_iValue;
		Node*	m_pNext;
	};

	Node* m_pHead;
	Node* m_pTail;

	int m_iCount;

public:
	void addNodeTT();
	void deleteTail();
	void deleteNode(int dValue);
	void printList();

	LinkedList();
	virtual ~LinkedList();
};

