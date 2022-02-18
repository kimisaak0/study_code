#pragma once
#include "QueueList.h"

#include <iostream>

struct customer
{
	int iNumid;

	int iArrivalTurn;
	int iNeedTurn;
	int iStartTurn;

	int iEndTurn;
};

class simulator
{
private:
	bool customerEmpty;
	
	int customerId;
	QueueList<customer*> customerQueue;

	int iCurrentTurn;
	customer* CurCustomer;
	
private:
	void CustomerChange();
	bool ComeCustomer(int nt);

public:
	void Display();
	void Work(int n);

public:
	simulator();
	~simulator();
};

//---------------->

simulator::simulator()
{
	iCurrentTurn = 0;
	customerId = 1;
	customerEmpty = true;
	CurCustomer = nullptr;
}

void simulator::Display()
{
	system("cls");

	printf("�մ��� �Դٸ� 0�� �ƴ� ���� �Է��ϼ���. \n0�� �մ��� ���� ���� ������ ó���˴ϴ�. \n�����ϰ� �����ø� 999�� �Է��ϼ���\n");

	printf("���� %d �� \n", iCurrentTurn);
	
	if (CurCustomer == nullptr) {
		printf("â�� : �մ��� �����ϴ�.\n");
	}
	else {
		int remainTurn = CurCustomer->iNeedTurn - (iCurrentTurn - CurCustomer->iStartTurn);
		printf("â�� : %d�� �մ� ó���� [���� �� : %d] \n", CurCustomer->iNumid, remainTurn);
	}

	customerQueue.ResetCursor();
	node<customer*>* wait = nullptr;
	do {
		wait = customerQueue.Next();
		if (wait == nullptr) {
			printf("��� : �մ��� �����ϴ�.\n");
			return;
		}
		else {
			printf("��� : ����� ��� : %d�� [%d��] \n", wait->data->iNumid, wait->data->iNeedTurn);
		}
	} while (wait->next != nullptr);
}

bool simulator::ComeCustomer(int nt)
{
	if (nt <= 0) {
		return false;
	}

	customer* nCustomer = new customer;
	nCustomer->iNumid = customerId++;
	nCustomer->iArrivalTurn = iCurrentTurn;
	nCustomer->iNeedTurn = nt;
	nCustomer->iStartTurn = 0;
	nCustomer->iEndTurn = 0;

	customerQueue.Add(nCustomer);

	return true;
}

void simulator::CustomerChange()
{
	if (customerQueue.Count() != 0) {
		CurCustomer = customerQueue.Peek();
		customerQueue.Remove();
		CurCustomer->iStartTurn = iCurrentTurn;
		CurCustomer->iEndTurn = iCurrentTurn + CurCustomer->iNeedTurn;
		customerEmpty = false;
	}
	else {
		CurCustomer = nullptr;
	}
}

void simulator::Work(int n)
{
	iCurrentTurn++;

	ComeCustomer(n);

	if (customerEmpty) {
		CustomerChange();
	}
	else {
		if (iCurrentTurn == CurCustomer->iEndTurn) {
			if (customerQueue.Count() != 0) {
				CustomerChange();
			}
			else {
				customerEmpty = true;
			}
		}
	}
}


simulator::~simulator()
{
	customerQueue.~QueueList();
}