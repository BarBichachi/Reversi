#include <stdlib.h>
#include <stdio.h>

#include "MandatoryHighFunctions.h"

//Q1
// This function checks if a move is valid and calculates the number of pieces to flip
int CheckMove(Board board, Player player, ReversiPos* move)
{
	int row = move->row - '1';
	int col = move->col - 'a';

	if (board[row][col] != ' ')
		return 0; 

	return directionHelper(board, player, move, false);
}

// This function makes a move and flips the necessary pieces
void MakeMove(Board board, Player player, ReversiPos* move)
{
	int row = move->row - '1';
	int col = move->col - 'a';

	// Performs the necessary piece flips for the move
	int totalFlips = directionHelper(board, player, move, true);
}

// This function takes a board and a player and returns a list of valid moves for that player
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
				currFlips = CheckMove(board, player, &currPos);

				// In case there's a possible move
				if (currFlips > 0)
					insertDataToEndList(&lst, currPos, currFlips);
			}
	return lst;
}

// This function creates and initializes a MovesTree representing the game for a given move
MovesTree* ExpandMove(Board b, Player p, ReversiPos* move, int height)
{
	MovesTree* tr = (MovesTree*)malloc(sizeof(MovesTree));
	checkAllocation(tr);

	tr->root = (MovesTreeNode*)malloc(sizeof(MovesTreeNode));
	checkAllocation(tr->root);

	memcpy(tr->board, b, sizeof(Board));
	expandMoveHelper(b, p, move, height, tr->root);

	return tr;
}

// This function calculates the score by calling the ScoreTreeHelper function
int ScoreTree(MovesTree* movesTree)
{
	int tmpPoints = 0;
	int currPoints = scoreTreeHelper(movesTree->root->next_moves[0], movesTree->root->player, movesTree->root->flips);

	for (int i = 1; i < movesTree->root->num_moves; i++)
	{
		tmpPoints = scoreTreeHelper(movesTree->root->next_moves[i], movesTree->root->player, movesTree->root->flips);
		if (tmpPoints < currPoints)
			currPoints = tmpPoints;
	}
	return currPoints;
}

//Q5
int PlayOneTurn(Board board, Player player, int height)
{

}

//Q6
void PlayGame(Board board, Player first, int h1, int h2)
{

}