#include "Card_deck.h"

int main()
{
	Card_deck deck;

	deck.Shuffle(100);
	deck.cardOpen();

	//전역 함수가 되었으므로 볼 수 없다.
	//deck.CntChoice(deck, 42);

	CntChoice(deck,42);

	peep_deck pd;
	pd.peep_ok(deck);
}