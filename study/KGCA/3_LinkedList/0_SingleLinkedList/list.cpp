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

}// 신규 노드 생성 및 연결리스트 연결

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

}// 초기 연결리스트 구축

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

}// pFindName이름의 노드를 반환한다.

bool  node::PrintData()
{
	if (pFind == nullptr) {
		cout << "검색 오류!" << endl;
		return false;
	}
	cout << "이름 : " << pFind->m_strName << " 나이 : " << pFind->m_iAge << endl;

	return true;
}// pFindNode를 출력한다.

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
}// pHead 노드 뒤에 삽입한다. (맨 앞에 데이터를 추가한다.)

bool   node::InsertLink_T()
{

	if (pFind == nullptr) {
		cout << "검색 오류!" << endl;
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
}// pFind 노드 뒤에 삽입한다.

void   node::PrintAllData()
{
	pFind = pHead->pNext;
	if (pFind == nullptr) {
		cout << "데이터 없음!!!" << endl;
		return;
	}

	while (pFind != nullptr) {
		PrintData();
		pFind = pFind->pNext;

	}
}// 전체 연결리스트를 출력한다.

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
// pDelNode를 연결리스트에서 삭제

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
}// 전체 연결리스트 삭제

void   node::SaveData(string pFileName)
{
	ofstream os;
	os.open(pFileName);

	for (data* nodeWrite = pHead; nodeWrite->pNext != nullptr; nodeWrite = nodeWrite->pNext) {
		os << nodeWrite->pNext->m_strName << endl;
		os << nodeWrite->pNext->m_iAge << endl;
	}
	os.close();

}// 연결리스트 전체를 파일로 저장.


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

}// 파일로 부터 로드 및 연결리스트 구축


void   node::MenuClear()
{
	system("cls");
	printf("\n=========================================");
	printf("\n============ 성적관리프로그램============");
	printf("\n=========================================");
	cout << endl;
}