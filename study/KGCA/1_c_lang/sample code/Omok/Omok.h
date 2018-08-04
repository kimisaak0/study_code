#pragma once

#include <windows.h>	// gotoxy(), SetConsoleCursorPosition()
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>		//kbhit(), _getch()

#define RIGHT		77
#define LEFT		75
#define UP			72
#define DOWN		80
#define ENTER		13
#define WHITEWIN	2
#define BLACKWIN	3

//�Լ� ������ ����
void(*game) ();

enum STATE { GAME_INIT = 0, KEY_CHECK, GAME_DRAW, GAME_CHECK };

void	keyCheck();
void	gotoxy(int x, int y);
void	DrawBoard();
void	InitOmokBoard();
void	judgment();

int		g_OmokBoard[19][19] = { 0 };
int		g_iCursorX = 19;
int		g_iCursorY = 9;
bool	g_bPlayer = true;	//���� �÷��̾�
int		g_iGameLoop = 1;	//���� ���� ����
int		g_iGameStage = GAME_INIT;
bool	g_bRestartGame = false;	//�ٸ� ���� ����

void Execute()
{
	game();
}

void	keyCheck() 
{
	//1�̸� 1p����, 0�̸� 2p����
	int iPlayTurn = 1;
	
	while (iPlayTurn) {
		switch (_getch()) {
			case RIGHT: {
				g_iCursorX += 2;
				if (g_iCursorX > 38) {
					g_iCursorX += 2;
				}
				gotoxy(g_iCursorX, g_iCursorY);
				break;
			}

			case LEFT: {
				g_iCursorX -= 2;
				if (g_iCursorX < 0) {
					g_iCursorX += 2;
				}
				gotoxy(g_iCursorX, g_iCursorY);
				break;
			}

			case UP: {
				g_iCursorY -= 1;
				if (g_iCursorY <= 0) {
					g_iCursorY -= 1;
				}
				gotoxy(g_iCursorX, g_iCursorY);
				break;
			}

			case DOWN: {
				g_iCursorY += 1;
				if (g_iCursorY < 19) {
					g_iCursorY += 1;
				}
				gotoxy(g_iCursorX, g_iCursorY);
				break;
			}

			case ENTER: {
				//ȭ�鿡 ��µ� �� �迭�� ��ġ�� ���߱� ���ؼ� 
				//g_iCursorX => g_iCursorX/2, g_iCursorY => g_iCursorY-1�� �����
				if (g_OmokBoard[g_iCursorX / 2][g_iCursorY - 1] != 0) {
					break;
				}

				if (g_bPlayer == true) {
					g_OmokBoard[g_iCursorX / 2][g_iCursorY - 1] = 1;
				}
				else {
					g_OmokBoard[g_iCursorX / 2][g_iCursorY - 1] = 2;
				}
				iPlayTurn = 0;
				break;
			}
		}
		gotoxy(2, 21);
		printf("ip=�� 2p=�� \n ������ǥ [%d][%d]", g_iCursorX / 2, g_iCursorY - 1);
		gotoxy(g_iCursorX, g_iCursorY);
	}
}

void	gotoxy(int x, int y)
{
	COORD Pos = {
		x - 1, 
		y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void	DrawBoard()
{
	system("cls");

	for (int i = 0; i < 19; i++) {
		for (int k = 0; k < 19; k++) {
			if (i == 0) {
				if (k == 0) {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
				else if (k == 18) {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
				else {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
			}
			else if (i == 18) {
				if (k == 0) {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
				else if (k == 18) {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
				else {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
			}
			else {
				if (k == 0) {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
				else if (k == 18) {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
				else {
					if (g_OmokBoard[k][i] == 1)			printf("��");
					else if (g_OmokBoard[k][i] == 2)	printf("��");
					else if (g_OmokBoard[k][i] == 0)	printf("��");
				}
			}
		}
		printf("\n");
	}
	gotoxy(2, 20);
	printf("����Ű�� ����Ű�� �̿��Ͽ� ���� �����ϴ�.");
	gotoxy(2, 21);//������� ���� ����
	printf("1p=��, 2p=�� \n ������ǥ [%d][%d]", g_iCursorX / 2, g_iCursorY - 1);
	gotoxy(g_iCursorX, g_iCursorY);
}

//������ �ʱ�ȭ (��/��)
void	InitOmokBoard()
{
	for (int iRowBoard = 0; iRowBoard < 19; iRowBoard++) {
		for (int iColBoard = 0; iColBoard < 19; iColBoard++) {
			g_OmokBoard[iRowBoard][iColBoard] = 0;
		}
	}
	DrawBoard();
}

void	judgment()
{
	g_bPlayer = !g_bPlayer;	//�÷��̾ �ٲ۴�.

	int cal[8][4] = { 0 };
	int total = 0;
	g_iGameLoop = 1;

	for (int iRowBoard = 0; iRowBoard < 19; iRowBoard++) {
		for (int iColBoard = 0; iColBoard < 19; iColBoard++) {
			//1:�鵹, 2:�浹
			for (int iStone = 1; iStone < 3; iStone++) {
				if (iStone == g_OmokBoard[iRowBoard][iColBoard]) {
					for (int k = 1; k < 5; k++) {

						if (iStone == g_OmokBoard[iRowBoard - (1 * k)][iColBoard - (1 * k)]) { cal[0][0 + k - 1] = 1; }
						if (iStone == g_OmokBoard[iRowBoard - (1 * k)][iColBoard + (0 * k)]) { cal[1][0 + k - 1] = 1; }
						if (iStone == g_OmokBoard[iRowBoard - (1 * k)][iColBoard + (1 * k)]) { cal[2][0 + k - 1] = 1; }
						if (iStone == g_OmokBoard[iRowBoard + (0 * k)][iColBoard + (1 * k)]) { cal[3][0 + k - 1] = 1; }
						if (iStone == g_OmokBoard[iRowBoard + (1 * k)][iColBoard + (1 * k)]) { cal[4][0 + k - 1] = 1; }
						if (iStone == g_OmokBoard[iRowBoard + (1 * k)][iColBoard + (0 * k)]) { cal[5][0 + k - 1] = 1; }
						if (iStone == g_OmokBoard[iRowBoard + (1 * k)][iColBoard - (1 * k)]) { cal[6][0 + k - 1] = 1; }
						if (iStone == g_OmokBoard[iRowBoard + (0 * k)][iColBoard - (1 * k)]) { cal[7][0 + k - 1] = 1; }
					}

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 4; j++) {
							total += cal[i][j];
						}

						if (total == 4) {
							if (1 == iStone) {
								g_iGameLoop = WHITEWIN;
							}
							else if (2 == iStone) {
								g_iGameLoop = BLACKWIN;
							}
						}
						else {
							total = 0;
						}
					}

					//�ʱ�ȭ
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 4; j++) {
							cal[i][j] = 0;
						}
					}
				}
			}
		}
	}
}

