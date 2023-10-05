#include "MandatoryHighFunctions.h"

void main()
{	
	// A generated "centered" board
	Board board;
	initializeBoard(board);

	// Prints the board and starts the game
	printBoard(board);
	PlayGame(board, PLAYER_X, 1, 1);
}