#include "Card_deck.h"

int main()
{
	Card_deck deck;

	deck.Shuffle(100);
	deck.cardOpen();

	//���� �Լ��� �Ǿ����Ƿ� �� �� ����.
	//deck.CntChoice(deck, 42);

	CntChoice(deck,42);

	peep_deck pd;
	pd.peep_ok(deck);
}