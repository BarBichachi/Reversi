#include "MandatoryHighFunctions.h"

void main()
{	
	//a custom "shifted" board (to check the assignment's requested output).	
	Board manualBoard = {//     a    b    c    d    e    f    g    h
						 /*1*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				 		 /*2*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						 /*3*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						 /*4*/ ' ', ' ', 'X', 'O', ' ', ' ', ' ', ' ',
						 /*5*/ ' ', ' ', 'O', 'X', ' ', ' ', ' ', ' ',
						 /*6*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						 /*7*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
						 /*8*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	};

	// a generated "centered" board.
	Board board;
	initializeBoard(board);

	// print the board and start the game.
	printBoard(manualBoard);
	PlayGame(manualBoard, PLAYER_X, 1, 1);
}