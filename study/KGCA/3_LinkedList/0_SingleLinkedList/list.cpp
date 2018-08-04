#include "list.h"

node::node()
{
	pHead = new data;
	memset(pHead, 0, sizeof(node));
	pTail = pHead;

	pHead->pNext = nullptr;
	pFind = pHead;

	m_iCount = 0;
}

void  node::NewLink(string name, int age)
{
	data*   pNewData = new data;
	{
		pNewData->m_strName = name;
		pNewData->m_iAge = age;
		pNewData->pNext = nullptr;
	}

	pTail -> pNext = pNewData;
	pTail = pNewData;

	m_iCount++;

}// �ű� ��� ���� �� ���Ḯ��Ʈ ����

void  node::RandData()
{
	srand(time(NULL));
	for (int iStd = 0; iStd < RandStd; iStd++) {
		string name ="";
		name += 65 + rand() % 26; //A(65), a(97)
		name += 65 + rand() % 26;
		name += 65 + rand() % 26;
	
		NewLink(name, 20 + rand() % 10);
	}

}// �ʱ� ���Ḯ��Ʈ ����

void  node::FindName(string pFindName)
{
	for (data* nodeWrite = pHead; nodeWrite != nullptr; nodeWrite = nodeWrite->pNext) {
		if(nodeWrite->pNext != nullptr && nodeWrite->pNext->m_strName == pFindName) {
			pFind = nodeWrite->pNext;
			return;
		}
	}
	pFind = nullptr;
	return;

}// pFindName�̸��� ��带 ��ȯ�Ѵ�.

bool  node::PrintData()
{
	if (pFind == nullptr) {
		cout << "�˻� ����!" << endl;
		return false;
	}
	cout << "�̸� : " << pFind->m_strName << " ���� : " << pFind->m_iAge << endl;

	return true;
}// pFindNode�� ����Ѵ�.

bool   node::InsertLink_H()
{
	string name = "";
	name += 65 + rand() % 26; //A(65), a(97)
	name += 65 + rand() % 26;
	name += 65 + rand() % 26;

	data* pNewData = new data;

	pNewData->m_strName = name;
	pNewData->m_iAge = 20 + rand() % 10;

	pNewData->pNext = pHead->pNext;
	pHead->pNext = pNewData;

	return true;
}// pHead ��� �ڿ� �����Ѵ�. (�� �տ� �����͸� �߰��Ѵ�.)

bool   node::InsertLink_T()
{

	if (pFind == nullptr) {
		cout << "�˻� ����!" << endl;
		return false;
	}

	string name = "";
	name += 65 + rand() % 26; //A(65), a(97)
	name += 65 + rand() % 26;
	name += 65 + rand() % 26;

	data* pNewData = new data;

	pNewData->m_strName = name;
	pNewData->m_iAge = 20 + rand() % 10;
	pNewData->pNext = pFind->pNext;
	pFind->pNext = pNewData;

	return true;
}// pFind ��� �ڿ� �����Ѵ�.

void   node::PrintAllData()
{
	pFind = pHead->pNext;
	if (pFind == nullptr) {
		cout << "������ ����!!!" << endl;
		return;
	}

	while (pFind != nullptr) {
		PrintData();
		pFind = pFind->pNext;

	}
}// ��ü ���Ḯ��Ʈ�� ����Ѵ�.

void   node::DelLink()
{
	data* pPrevNode = pFind;

	data* pDelNode = pPrevNode->pNext;
	if (pHead->pNext == pTail && pTail == pDelNode) {
		pTail = pHead;
		pHead->pNext = nullptr;
	}

	if (pHead == pTail) {
		return;
	}

	data* pNextNode = pDelNode->pNext;
	delete pDelNode;
	m_iCount--;

	pPrevNode->pNext = pNextNode;

	return;
}
// pDelNode�� ���Ḯ��Ʈ���� ����

void   node::AllDeleteLink()
{
	pFind = pHead;
	while (pHead->pNext != nullptr) {
		if (pHead == pTail) {
			return;
		}
		DelLink();
	}
	pTail = pHead;
}// ��ü ���Ḯ��Ʈ ����

void   node::SaveData(string pFileName)
{
	ofstream os;
	os.open(pFileName);

	for (data* nodeWrite = pHead; nodeWrite->pNext != nullptr; nodeWrite = nodeWrite->pNext) {
		os << nodeWrite->pNext->m_strName << endl;
		os << nodeWrite->pNext->m_iAge << endl;
	}
	os.close();

}// ���Ḯ��Ʈ ��ü�� ���Ϸ� ����.


void   node::LoadLink(string pFileName)
{
	ifstream is;
	is.open(pFileName);

	AllDeleteLink();
	
	string ch;

	data* nodeWrite = pHead;
	pFind = pHead;

	while (true) {
		nodeWrite->pNext = new data;
		is >> nodeWrite->pNext->m_strName;
		is >> nodeWrite->pNext->m_iAge;
		
		if (is.eof()) {
			pTail = nodeWrite;
			pTail->pNext = nullptr;
			break;
		}
		nodeWrite = nodeWrite->pNext;
	}
	is.close();

}// ���Ϸ� ���� �ε� �� ���Ḯ��Ʈ ����


void   node::MenuClear()
{
	system("cls");
	printf("\n=========================================");
	printf("\n============ �����������α׷�============");
	printf("\n=========================================");
	cout << endl;
}