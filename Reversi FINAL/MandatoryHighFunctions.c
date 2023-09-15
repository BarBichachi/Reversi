#include <stdlib.h>
#include <stdio.h>
#include "MandatoryHighFunctions.h"

//Q1
// Function to check if a move is valid and calculate the number of pieces to flip
int CheckMove(Board board, Player player, ReversiPos* move)
{
	int row = move->row - '1';
	int col = move->col - 'a';

	if (board[row][col] != ' ')
		return 0; 

	return directionHelper(board, player, move, false);
}

// Function to make a move and flip the necessary pieces
void MakeMove(Board board, Player player, ReversiPos* move)
{
	int row = move->row - '1';
	int col = move->col - 'a';

	// Performs the necessary piece flips for the move
	int totalFlips = directionHelper(board, player, move, true);
}

//Function takes a board and a player and returns a list of valid moves for that player
MovesList FindMoves(Board board, Player player)
{
	MovesList lst;
	makeEmptyList(&lst);

	ReversiPos currPos;
	int currFlips = 0;

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			// Checks if the board is empty
			if (board[i][j] == ' ')
			{
				currPos.row = '1' + i;
				currPos.col = 'a' + j;
				currFlips = CheckMove(board, PLAYER_X, &currPos);

				// In case there's a possible move
				if (currFlips > 0)
					insertDataToEndList(&lst, currPos, currFlips);
			}
	return lst;
}

//Q3
MovesTree* ExpandMove(Board b, Player p, ReversiPos* move, int height)
{

}
//Q4
int ScoreTree(MovesTree* movesTree)
{

}
//Q5
int PlayOneTurn(Board board, Player player, int height)
{

}
//Q6
void PlayGame(Board board, Player first, int h1, int h2)
{

}