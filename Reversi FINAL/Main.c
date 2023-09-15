#define _CRT_SECURE_NO_WARNINGS
#include "MandatoryHighFunctions.h"

void main()
{						//      a    b    c    d    e    f    g    h
	Board manualBoard = {/*1*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						/*2*/  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						/*3*/  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						/*4*/  ' ', ' ', ' ', 'X', 'O', ' ', ' ', ' ',
						/*5*/  ' ', ' ', ' ', 'O', 'X', ' ', ' ', ' ',
						/*6*/  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						/*7*/  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						/*8*/  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	};

	//printBoard(manualBoard);
	Board board;

	ReversiPos move;
	move.col = 'd';
	move.row = '6';
	initializeBoard(board);
	int flips = CheckMove(manualBoard, PLAYER_X, &move);
	//MakeMove(manualBoard, PLAYER_X, &move);
	printBoard(manualBoard);

	MovesList moves = FindMoves(manualBoard, PLAYER_X);
	MovesTree* tr = ExpandMove(manualBoard, PLAYER_X, &move, 5);
	printList(&moves);

	//FreeTree(tr->root);
	//free(tr);
}
