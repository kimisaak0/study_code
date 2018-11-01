#include "Card_deck.h"


Card_deck::Card_deck()
{
	//카드 세팅
	for (int iCnt = 0; iCnt < 52; iCnt++) {
		switch (iCnt / 13) {
		case 0: Deck[iCnt] = Card_one(0, iCnt % 13 + 1); break;
		case 1: Deck[iCnt] = Card_one(1, iCnt % 13 + 1); break;
		case 2: Deck[iCnt] = Card_one(2, iCnt % 13 + 1); break;
		case 3: Deck[iCnt] = Card_one(3, iCnt % 13 + 1); break;
		}
		//특수문자는 char형의 표현범위를 벗어나기 때문에 경고가 발생한다.
		//C언어에서 특수문자나 다국어 처리는 상당히 까다로운 부분.
		//일단 여기서는 char를 wchar_t로 바꾸는 것으로 해결했다.
		//참고 : 멀티바이트, 유니코드, ICU(International Components for Unicode)
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

	cout << "덱을 " << cnt << "번 섞습니다." << endl;
	
	for (int iCnt = 0; iCnt < cnt; iCnt++) {
		int src = rand() % 52;
		int dst = rand() % 52;

		swapCard(Deck[src], Deck[dst]);
	}

	cout << "덱을 섞었습니다." << endl;
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

//friend 선언 안한 함수에서는 접근 불가.
//void peep_deck::peep_no(Card_deck& D)
//{
//	D.cardOpen();
//	D.currentCnt--;
//}
