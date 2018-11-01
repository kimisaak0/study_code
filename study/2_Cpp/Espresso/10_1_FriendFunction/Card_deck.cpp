#include "Card_deck.h"


Card_deck::Card_deck()
{
	//ī�� ����
	for (int iCnt = 0; iCnt < 52; iCnt++) {
		switch (iCnt / 13) {
		case 0: Deck[iCnt] = Card_one(0, iCnt % 13 + 1); break;
		case 1: Deck[iCnt] = Card_one(1, iCnt % 13 + 1); break;
		case 2: Deck[iCnt] = Card_one(2, iCnt % 13 + 1); break;
		case 3: Deck[iCnt] = Card_one(3, iCnt % 13 + 1); break;
		}
		//Ư�����ڴ� char���� ǥ�������� ����� ������ ��� �߻��Ѵ�.
		//C���� Ư�����ڳ� �ٱ��� ó���� ����� ��ٷο� �κ�.
		//�ϴ� ���⼭�� char�� wchar_t�� �ٲٴ� ������ �ذ��ߴ�.
		//���� : ��Ƽ����Ʈ, �����ڵ�, ICU(International Components for Unicode)
	}

	currentCnt = 0;
}

void Card_deck::swapCard(Card_one& srcCard, Card_one& dstCard)
{
	Card_one temp = srcCard;
	srcCard = dstCard;
	dstCard = temp;
}

void Card_deck::Shuffle(int cnt)
{
	srand((unsigned)time(NULL));

	cout << "���� " << cnt << "�� �����ϴ�." << endl;
	
	for (int iCnt = 0; iCnt < cnt; iCnt++) {
		int src = rand() % 52;
		int dst = rand() % 52;

		swapCard(Deck[src], Deck[dst]);
	}

	cout << "���� �������ϴ�." << endl;
}

void Card_deck::cardOpen()
{
	Deck[currentCnt].open = true;
	Deck[currentCnt].showData();
	currentCnt++;
}


Card_deck::~Card_deck()
{
}



void  peep_deck::peep_ok(Card_deck& D)
{
	D.cardOpen();
	D.currentCnt--;
}

//friend ���� ���� �Լ������� ���� �Ұ�.
//void peep_deck::peep_no(Card_deck& D)
//{
//	D.cardOpen();
//	D.currentCnt--;
//}
