#pragma once

//friend 지정된 클래스에서는 해당 클래스에 대한 완전한 정보가 필요하다.
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

	//friend 전역 함수 선언. 
	//CntChoice 함수는 전역 함수가 되므로 Card_deck클래스의 멤버가 아니게 된다.
	friend void CntChoice(Card_deck&p, int n)
	{
		p.currentCnt = n;
	}

	//peep_deck 클래스의 peep_ok()메소드만 friend 지정
	//특정 클래스의 멤버를 friend로 선언하려면 그 클래스의 선언이 이 클래스의 앞에 있고, 멤버 함수의 몸체는 뒤에 있어야 한다. 
	friend void peep_deck::peep_ok(Card_deck& D);

};

