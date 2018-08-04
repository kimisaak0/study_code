#include "Omok.h"

void	keyCheck();
void	gotoxy(int x, int y);
void	DrawBoard();
void	judgment();

int main()
{
	g_iGameStage = GAME_INIT;

	//게임 루프
	while (g_iGameLoop != WHITEWIN && g_iGameLoop != BLACKWIN) {
		switch (g_iGameStage) {
			case GAME_INIT: {
				game = InitOmokBoard;//	오목판 초기화 (행/열)
				g_iGameStage = KEY_CHECK;	//오목판을 그린다.
				g_bRestartGame = false;
				g_bPlayer = true;
			} break;

			case KEY_CHECK: {
				game = keyCheck;
				g_iGameStage = GAME_DRAW;
			}break;

			case GAME_DRAW: {
				game = DrawBoard;
				g_iGameStage = GAME_CHECK;
			}break;

			case GAME_CHECK: {
				game = judgment;
				g_iGameStage = KEY_CHECK;
			}break;
		}
		Execute();
	}

	system("cls");
	gotoxy(2, 20);
	if (g_iGameLoop == WHITEWIN) {
		printf("백이 승리!!");
	}
	if (g_iGameLoop == BLACKWIN) {
		printf("흑이 승리!!");
	}
}