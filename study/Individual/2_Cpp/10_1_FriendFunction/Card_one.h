#pragma once
#include "Header.h"

//전방선언. 이런 클래스가 나올거라고 알려주는 의미.
class Card_deck;

const char SPADE[3] = "♠";
const char DIAMOND[3] = "◆";
const char HEART[3] = "♥";
const char CLUB[3] = "♣";

class Card_one
{
	int     pattern;
	int     number;
	bool    open;

	bool    showData();
	bool    setOpen(bool onoff);
	bool    getOpen();

	//생성자도 private이므로 일반적인 방법으로는 객체 생성이 안되는 클래스.
	Card_one();
	Card_one(int p, int n);
	~Card_one();

	//카드 덱 클래스를 friend 지정.
	friend class Card_deck;

};

