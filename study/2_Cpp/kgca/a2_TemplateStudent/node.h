#pragma once
#include "Header.h"

//listŬ�������� ����� node Ŭ���� ���ø�
template <class T>
class node
{
	//����� public���� �� ����
public:
	T*     m_pData;   //������ Ŭ������ �����ͷ� ����ų �� �ִ�.
	node*  m_pNext;   //���� ��带 ����Ű�� ������
	node*  m_pPrev;   //���� ��带 ����Ű�� ������

public:
	void del() 
	{
		delete m_pData;
	}

	node()
	{
		m_pData = nullptr;            //����Ű�� �ִ� �����Ͱ� ����
		m_pNext = m_pPrev = nullptr;  //�̾��� �ִ� ��尡 ����.
	}

	~node()
	{
		delete m_pData;
		//cout << "node end" << endl;
	}
};