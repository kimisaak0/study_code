#include "Card_one.h"

bool Card_one::showData()
{
	if (open == true) {
		switch (pattern) {
			case 0: cout << SPADE;   break;
			case 1: cout << DIAMOND; break;
			case 2: cout << HEART;   break;
			case 3: cout << CLUB;    break;
		}
		switch (number) {
			 case  1: cout << " A"; break;
			 case 11: cout << " J"; break;
			 case 12: cout << " Q"; break;
			 case 13: cout << " K"; break;
			 default: cout << " " << number; break;	}
		cout << endl;
		return true;
	}
	else {
		cout << "???" << endl;
		return false;
	}
}

bool Card_one::setOpen(bool onoff)
{
	open = onoff;
	return open;
}

bool Card_one::getOpen()
{
	return open;
}

Card_one::Card_one()
{
	pattern = 0;
	number = 0;
	open = false;
}

Card_one::Card_one(int p, int n)
{
	pattern = p;
	number = n;
	open = false;
}

Card_one::~Card_one()
{
}