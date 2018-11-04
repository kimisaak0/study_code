#pragma once
#include "dList.h"

dList::dList()
{
	pHead = nullptr;
	pTail = nullptr;

	m_iCount = 0;
}

bool    dList::CreateData()
{
	DeleteList();

	srand((unsigned int)time(NULL));
	
	ofstream os;
	os.open("data.txt");

	int count = 5;

	if (os.is_open()) {
		os << count << endl;

		for (int iCnt = 0; iCnt < count; iCnt++) {
			string name = "";
			name += 65 + rand() % 26; //A(65), a(97)
			name += 65 + rand() % 26;
			name += 65 + rand() % 26;

			os << name << endl << 20 + rand() % 10 << endl;
		}

		return true;
	}
	else {
		cout << "���� ���� ����" << endl;
		return false;
	}

}// ���ο� �����͸� ����� ������ �����.
		
void    dList::AddLink_H(data* pStu) 
{
	pStu->pPrev = nullptr;
	pStu->pNext = nullptr;

	if (pHead == nullptr) {
		pTail = pStu;
	}
	else {
		pStu->pNext = pHead;
		pHead->pPrev = pStu;
	}

	pHead = pStu;
} // pHead ��� �տ� �߰��Ѵ�.

void    dList::AddLink_T(data* pStu) 
{
	pStu->pPrev = nullptr;
	pStu->pNext = nullptr;

	if (pHead == nullptr) {
		pHead = pStu;
	}
	else {
		pStu->pPrev = pTail;
		pTail->pNext = pStu;
	}
	pTail = pStu;
}
// pTail ��� �ڿ� �߰��Ѵ�.
		
void    dList::DeleteList()
{
	if (pHead == nullptr) {
		return;
	}
	else {
		data* pData = pHead;

		while (pData->pNext) { // == (pData->pNext != nullptr) 
			data* delData = pData->pNext;
			pData->pNext = delData->pNext;
			delete delData;
		}
		delete pHead;

		m_iCount = 0;
		pHead = nullptr;
		pTail = nullptr;
	}
}

bool    dList::DataRead_H()
{
	DeleteList();

	ifstream is;
	is.open("data.txt");

	if (is.is_open()) {
		is >> m_iCount;

		for (int iCnt = 0; iCnt < m_iCount; iCnt++) {

			data* pData = new data;

			is >> pData->m_strName;
			is >> pData->m_iAge;

			AddLink_H(pData);
		}
		return true;
	}
	else {
		cout << "���� ���� ����" << endl;
		return false;
	}

}// ���Ϸκ��� �����͸� �о� ���� ���Ḯ��Ʈ�� �����.

bool    dList::DataRead_T()
{
	DeleteList();

	ifstream is;
	is.open("data.txt");

	if (is.is_open()) {
		is >> m_iCount;

		for (int iCnt = 0; iCnt < m_iCount; iCnt++) {

			data* pData = new data;

			is >> pData->m_strName;
			is >> pData->m_iAge;

			AddLink_T(pData);
		}
		return true;
	}
	else {
		cout << "���� ���� ����" << endl;
		return false;
	}

}// ���Ϸκ��� �����͸� �о� ���� ���Ḯ��Ʈ�� �����.


bool    dList::PrintData(data* pStu)
{
	if (pStu == nullptr)
	{
		cout << "������ ����" << endl;
		return false;
	}
	else {
		cout << "�̸� : " << pStu->m_strName << ", ���� : " << pStu->m_iAge << endl;
		return true;
	}

}// Data* pStu�� ����Ѵ�.

bool    dList::PrintAllData()
{
	data* pData = pHead;

	while (pData) {
		PrintData(pData);
		pData = pData->pNext;
	}
	return true;
}// ��ü ���Ḯ��Ʈ�� ����Ѵ�.

void    dList::MenuClear()
{
	system("cls");
	printf("===================================\n");
	printf("====   ���� ���� ���α׷�      ====\n");
	printf("===================================\n");
}



dList::~dList()
{
	DeleteList();
}