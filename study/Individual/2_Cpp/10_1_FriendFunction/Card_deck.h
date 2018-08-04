#pragma once

//friend ������ Ŭ���������� �ش� Ŭ������ ���� ������ ������ �ʿ��ϴ�.
#include "Card_one.h"

class peep_deck
{
public:
	void peep_ok(Card_deck& D);
	//void peep_no(Card_deck& D);

	peep_deck() {}
	~peep_deck() {}
};

class Card_deck
{
private:
	Card_one Deck[52];
	int currentCnt;

public:
	void swapCard(Card_one& srcCard, Card_one& dstCard);
	void Shuffle(int cnt);
	void cardOpen();

	Card_deck();
	virtual ~Card_deck();

	//friend ���� �Լ� ����. 
	//CntChoice �Լ��� ���� �Լ��� �ǹǷ� Card_deckŬ������ ����� �ƴϰ� �ȴ�.
	friend void CntChoice(Card_deck&p, int n)
	{
		p.currentCnt = n;
	}

	//peep_deck Ŭ������ peep_ok()�޼ҵ常 friend ����
	//Ư�� Ŭ������ ����� friend�� �����Ϸ��� �� Ŭ������ ������ �� Ŭ������ �տ� �ְ�, ��� �Լ��� ��ü�� �ڿ� �־�� �Ѵ�. 
	friend void peep_deck::peep_ok(Card_deck& D);

};

