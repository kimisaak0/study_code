#include "LinkedList.h"


void LinkedList::addNodeTT()
{
	Node* newNode = new Node;

	newNode->m_iValue = m_iCount++;
	newNode->m_pNext = NULL;

	if (m_pHead == NULL) {
		m_pHead = newNode;
		m_pTail = newNode;
	}
	else {
		m_pTail->m_pNext = newNode;
		m_pTail = m_pTail->m_pNext;
	}
}

void LinkedList::deleteTail()
{
	Node* pNode = m_pHead;

	if (m_pHead == NULL) {
		return;
	}
	else if (m_pHead == m_pTail) {
		delete m_pTail;

		m_pHead = NULL;
		m_pTail = NULL;
	}
	else {
		for (;	pNode->m_pNext->m_pNext != NULL; pNode = pNode->m_pNext) {}
		
		pNode->m_pNext = NULL;
		m_pTail = pNode;

		delete m_pTail;
		
	}
}

void LinkedList::deleteNode(int dValue)
{
	Node* pNode = m_pHead;

	if (m_pHead == NULL) {
		return;
	}
	else if (m_pHead == m_pTail) {

		if (m_pTail->m_iValue == dValue) {
			delete m_pTail;

			m_pHead = NULL;
			m_pTail = NULL;
		}
	}
	else {
		for (; pNode->m_pNext->m_pNext != NULL; pNode = pNode->m_pNext) {
			if (pNode->m_pNext->m_iValue == dValue) { break; }
		}
		Node* delNode = pNode->m_pNext;

		pNode->m_pNext = pNode->m_pNext->m_pNext;
		
		if (delNode->m_pNext == NULL) {
			m_pTail = pNode;
		}

		delete delNode;
	}
}

void LinkedList::printList()
{
	Node* pNode = m_pHead;

	if (pNode == NULL) {
		return;
	}
	else {
		cout << pNode->m_iValue << endl;
		pNode = pNode->m_pNext;
	}
}

LinkedList::LinkedList()
{
	m_iCount = 0;

	Node* newNode = new Node;

	newNode->m_iValue = m_iCount++;
	newNode->m_pNext = NULL;

	m_pHead = newNode;
	m_pTail = newNode;
}


LinkedList::~LinkedList()
{
}
