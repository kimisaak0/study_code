#pragma once
#include "Header.h"

//���漱��. �̷� Ŭ������ ���ðŶ�� �˷��ִ� �ǹ�.
class Card_deck;

const char SPADE[3] = "��";
const char DIAMOND[3] = "��";
const char HEART[3] = "��";
const char CLUB[3] = "��";

class Card_one
{
	int     pattern;
	int     number;
	bool    open;

	bool    showData();
	bool    setOpen(bool onoff);
	bool    getOpen();

	//�����ڵ� private�̹Ƿ� �Ϲ����� ������δ� ��ü ������ �ȵǴ� Ŭ����.
	Card_one();
	Card_one(int p, int n);
	~Card_one();

	//ī�� �� Ŭ������ friend ����.
	friend class Card_deck;

};

