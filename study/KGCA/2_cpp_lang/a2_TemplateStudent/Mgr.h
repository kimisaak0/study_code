#pragma once
#include "HashTable.h"
#include "stu.h"

class mgr
{
private:
	list<stu> m_InitList;

public:
	list<stu> m_List;
	//hashTable<stu> m_hash;

public:
	bool inputDataHead(int iCnt = 10);
	bool inputDataTail(int iCnt = 10);


	void showData();
	void showData(stu* pStd);

	void release();

	void sortTotal(bool bUp = true);
	void sortIndex(bool bUp = true);

	stu* find(int iCnt);
	node<stu>* swap(node<stu>* a, node<stu>* b);

	mgr() {}
	~mgr() { release(); }

};


bool mgr::inputDataHead(int iCnt) {
	for (int iSt = 0; iSt < iCnt; iSt++) {
		stu* pStu = new stu;
		wstring name;
		for (int iname = 0; iname < 3; iname++) {
			char iNmae = 65 + rand() % 26;
			name += iNmae;
		}
		pStu->setIndex(iSt);
		pStu->setName(name);
		pStu->setSub(rand() % 100, rand() % 100, rand() % 100);

		//m_hash.insert(pStu);
		m_List.addLinkTail(pStu);
	}
	return true;
}


bool mgr::inputDataTail(int iCnt) {
	for (int iSt = 0; iSt < iCnt; iSt++) {
		stu* pStu = new stu;
		wstring name;
		for (int iname = 0; iname < 3; iname++) {
			char iNmae = 65 + rand() % 26;
			name += iNmae;
		}
		pStu->setIndex(iSt);
		pStu->setName(name);
		pStu->setSub(rand() % 100, rand() % 100, rand() % 100);

		//m_hash.insert(pStu);
		m_List.addLinkTail(pStu);
	}
	return true;
}

void mgr::showData()
{
	for (node<stu>* pNode = m_List.getHead(); 
		pNode != nullptr; 
		pNode = pNode->m_pNext) {
		stu* pData = pNode->m_pData;
		if (pData) {
			wcout << pData->getIndex() << L" " << pData->getName() << L" " << pData->getTotal() << endl;
		}
	}
}
void mgr::showData(stu* pStd)
{
	if (pStd == nullptr) { return; }
	wcout << " ======= "
		<< pStd->getIndex() << L" "
		<< pStd->getName().c_str() << L" "
		<< pStd->getSub().getKor() << L" "
		<< pStd->getSub().getEng() << L" "
		<< pStd->getSub().getMat() << L" "
		<< pStd->getTotal() << L" "
		<< endl;
}

void mgr::release()
{
	m_List.delList();
}

void mgr::sortTotal(bool bUp)
{
	//m_List.Sort(bUp);
	//정렬
	node<stu>* pNodeSrc = m_List.getHead();
	//가장 작은 것을 앞으로 이동시킨다.
	while (pNodeSrc && pNodeSrc->m_pNext) {
		node<stu>* pNodeSwap = pNodeSrc;
		stu* pStd = pNodeSwap->m_pData;

		for (node<stu>* pNodeDesk = pNodeSrc->m_pNext;
			pNodeDesk != nullptr;
			pNodeDesk = pNodeDesk->m_pNext)
		{
			stu* pDesk = pNodeDesk->m_pData;
			if (pNodeSwap->m_pData->getTotal() > pDesk->getTotal())
			{
				pNodeSwap = pNodeDesk;
			}
		}
		// pNodeSrc보다 크거나 작은 것이 있다.
		if (pNodeSrc != pNodeSwap) 	{
			pNodeSrc = swap(pNodeSrc, pNodeSwap);
		} 
		else {
			//pNodeSrc보다 크거나 작은 것이 없다.
			pNodeSrc = pNodeSrc->m_pNext;
		}
	}
	m_List.m_pTail = pNodeSrc;
}

void mgr::sortIndex(bool bUp)
{
	//m_List.Sort(bUp);
	//정렬
	node<stu>* pNodeSrc = m_List.getHead();
	//가장 작은 것을 앞으로 이동시킨다.
	while (pNodeSrc && pNodeSrc->m_pNext) {
		node<stu>* pNodeSwap = pNodeSrc;
		stu* pStd = pNodeSwap->m_pData;

		for (node<stu>* pNodeDesk = pNodeSrc->m_pNext;
			pNodeDesk != nullptr;
			pNodeDesk = pNodeDesk->m_pNext)
		{
			stu* pDesk = pNodeDesk->m_pData;
			if (pNodeSwap->m_pData->getIndex() > pDesk->getIndex())
			{
				pNodeSwap = pNodeDesk;
			}
		}
		// pNodeSrc보다 크거나 작은 것이 있다.
		if (pNodeSrc != pNodeSwap) {
			pNodeSrc = swap(pNodeSrc, pNodeSwap);
		}
		else {
			//pNodeSrc보다 크거나 작은 것이 없다.
			pNodeSrc = pNodeSrc->m_pNext;
		}
	}
	m_List.m_pTail = pNodeSrc;
}


stu* mgr::find(int iCnt)
{
	stu* pData = m_List.getData(iCnt);
	return pData;
}


node<stu>* mgr::swap(node<stu>* a, node<stu>* b)
{
	//NULL
	node<stu>* aprev = a->m_pPrev;
	node<stu>* anext = a->m_pNext;
	node<stu>* bprev = b->m_pPrev;
	node<stu>* bnext = b->m_pNext;

	//Head <-> b
	if (aprev != nullptr) {
		swapP<node<stu>>(aprev, b);
#pragma region KGCA
		//aprev->m_pNext = b;
		//b->m_pPrev = aprev;
#pragma endregion
	}
	else {
		m_List.m_pHead = b;
		b->m_pPrev = nullptr;
	}
	// b <-> c anext(c)
	if (anext != b) {
		swapP<node<stu>>(b, anext);
#pragma region KGCA
		//b->m_pNext = anext; // b -> c
		//anext->m_pPrev = b; // b <- c
#pragma endregion
	//초기 a -> c -> b 경우
		if (anext->m_pNext == b) {
			swapP<node<stu>>(anext, a);
#pragma region KGCA
			//anext->m_pNext = a; // c -> a
			//a->m_pPrev = anext; // c <- a
#pragma endregion
		}
		else {
			swapP<node<stu>>(bprev, a);
#pragma region KGCA
			//bprev->m_pNext = a;
			//a->m_pPrev = bprev;
#pragma endregion
		}
	}
	else  // b <-> a
	{
		b->m_pNext = a;     // b -> a
		a->m_pPrev = b;     // b <- a
		a->m_pNext = bnext; // a -> d
		if (bnext != nullptr) {
			bnext->m_pPrev = a; // a <- d
		}
	}
	// a <-> d anext(d) // 초기 a -> c -> b -> d 경우
	if (bnext != nullptr) {
		swapP<node<stu>>(a, bnext);
#pragma region KGCA
		//aprev->m_pNext = b;
		//b->m_pPrev = aprev;
#pragma endregion
	} 
	else {
		a->m_pNext = nullptr; // a -> d
	}

	if (anext == b) {
		return a;
	}
	return anext;
}

