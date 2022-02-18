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

	printf("손님이 왔다면 0이 아닌 수를 입력하세요. \n0은 손님이 오지 않은 것으로 처리됩니다. \n종료하고 싶으시면 999를 입력하세요\n");

	printf("현재 %d 턴 \n", iCurrentTurn);
	
	if (CurCustomer == nullptr) {
		printf("창구 : 손님이 없습니다.\n");
	}
	else {
		int remainTurn = CurCustomer->iNeedTurn - (iCurrentTurn - CurCustomer->iStartTurn);
		printf("창구 : %d번 손님 처리중 [남은 턴 : %d] \n", CurCustomer->iNumid, remainTurn);
	}

	customerQueue.ResetCursor();
	node<customer*>* wait = nullptr;
	do {
		wait = customerQueue.Next();
		if (wait == nullptr) {
			printf("대기 : 손님이 없습니다.\n");
			return;
		}
		else {
			printf("대기 : 대기자 목록 : %d번 [%d턴] \n", wait->data->iNumid, wait->data->iNeedTurn);
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