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
	ExpandMoveHelper(b, p, move, height, tr->root);

	return tr;
}

//Q4
int ScoreTree(MovesTree* movesTree)
{
	// Implement here a call to use ScoreTreeHelper
}

int ScoreTreeHelper(MovesTreeNode* root, Player rootPlayer)
{


	// Implement here a recursive call of ScoreTreeHelper




	int movesMinMax = 0;
	int playerXFlips = 0;
	int playerOFlips = 0;
	Player currPlayer = root->player;

	// In case it's a leaf
	if (root->num_moves == 0)
	{
		if (currPlayer == PLAYER_X)
			playerXFlips += root->flips;
		else
			playerOFlips += root->flips;
	}
	// In case it's a parent
	else
	{
		// In case it's the same node as the root, calculate the minimum of his childs
		if (currPlayer == rootPlayer)
		{
			movesMinMax = root->next_moves[0]->num_moves;
			for (int i = 1; i < root->num_moves; i++)
			{
				if (movesMinMax > root->next_moves[i]->num_moves)
					movesMinMax = root->next_moves[i]->num_moves;
			}
		}
		// In case it's the enemy node of the root, calculate the maximum of his childs
		else
		{
			movesMinMax = root->next_moves[0]->num_moves;
			for (int i = 1; i < root->num_moves; i++)
			{
				if (movesMinMax < root->next_moves[i]->num_moves)
					movesMinMax = root->next_moves[i]->num_moves;
			}
		}
	}
}

//Q5
int PlayOneTurn(Board board, Player player, int height)
{

}

//Q6
void PlayGame(Board board, Player first, int h1, int h2)
{

}