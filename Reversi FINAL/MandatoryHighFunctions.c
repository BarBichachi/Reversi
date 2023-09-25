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

//Q2
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

//Q3
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

// This function expands the game tree based on available moves
void expandMoveHelper(Board b, Player p, ReversiPos* move, int height, MovesTreeNode* root)
{
	Board tmpBoard;
	int i = 0;
	Player enemyPlayer = getEnemy(p);
	MovesList lst = FindMoves(b, enemyPlayer);

	// Populate the root node with the current move & player and then makes the move
	root->pos = *move;
	root->player = p;
	root->flips = CheckMove(b, p, move);
	MakeMove(b, p, move);

	// If there are no moves for the enemy player or height reaches 0
	if (isEmptyList(&lst) || height == 0)
	{
		root->num_moves = 0;
		root->next_moves = NULL;
		return;
	}

	// Initialize the next_moves array in the root
	MovesListNode* curr = lst.head;
	root->num_moves = countMoves(&lst);
	root->next_moves = (MovesTreeNode**)malloc((root->num_moves) * sizeof(MovesTreeNode*));
	checkAllocation(root->next_moves);

	// Copy the current board state for recursive calls
	memcpy(tmpBoard, b, sizeof(Board));

	// Recursively build the game tree for enemy player's moves
	while (curr != NULL)
	{
		root->next_moves[i] = (MovesTreeNode*)malloc(sizeof(MovesTreeNode));
		checkAllocation(root->next_moves[i]);
		expandMoveHelper(tmpBoard, enemyPlayer, &curr->pos, height - 1, root->next_moves[i]);
		curr = curr->next;
		i++;
	}
}

//Q4
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
	MovesList movesList = FindMoves(board, player);
	if (isEmptyList(&movesList))
		return 0;
	
	MovesListNode* currMove = movesList.head;


	int bestScore = 0;
	ReversiPos bestMove = currMove->pos;

	while (currMove != NULL)
	{
		MovesTree* currTree = ExpandMove(board, player, &(currMove->pos), height);
		int currScore = ScoreTree(currTree);
		if (currScore > bestScore)
		{
			bestMove = currMove->pos;
			bestScore = currScore;
		}
		currMove = currMove->next;
	}

	MakeMove(board, player, &bestMove);
	return 1;
}

//Q6
void PlayGame(Board board, Player first, int h1, int h2)
{
	Player second = getEnemy(first);
	int canMove = 1;

	while (canMove == 1)
	{
		canMove = PlayOneTurn(board, first, h1);
		if (canMove == 0)
			break;
		canMove = PlayOneTurn(board, second, h1);
	}

	printWinner(board);
}