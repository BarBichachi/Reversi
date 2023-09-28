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
	expandMoveHelper(tr->board, p, move, height, tr->root);

	return tr;
}
// This function expands the game tree based on available moves
void expandMoveHelper(Board b, Player p, ReversiPos* move, int height, MovesTreeNode* root)
{	
	// Copy the current board state for recursive calls
	Board tmpBoard;
	memcpy(tmpBoard, b, sizeof(Board));

	
	// Populate the root node with the current move & player and then makes the move
	root->pos = *move;
	root->player = p;
	root->flips = CheckMove(tmpBoard, p, move);
	MakeMove(tmpBoard, p, move);

	Player enemyPlayer = getEnemy(p);
	MovesList enemyLst = FindMoves(tmpBoard, enemyPlayer);
	// If there are no moves for the enemy player or height reaches 0
	if (isEmptyList(&enemyLst) || height == 0)
	{
		root->num_moves = 0;
		root->next_moves = NULL;
		return;
	}

	// calculate the required memory and allocate it for the next_moves array in the root
	root->num_moves = countMoves(&enemyLst);
	root->next_moves = (MovesTreeNode**)malloc((root->num_moves) * sizeof(MovesTreeNode*));
	checkAllocation(root->next_moves);

	// Recursively build the game tree for enemy player's moves
	MovesListNode* curr = enemyLst.head;
		for (int i = 0; i < root->num_moves; i++)
		{
			root->next_moves[i] = (MovesTreeNode*)malloc(sizeof(MovesTreeNode));
			checkAllocation(root->next_moves[i]);
			expandMoveHelper(tmpBoard, enemyPlayer, &curr->pos, height - 1, root->next_moves[i]);
			curr = curr->next;
		}

}

//Q4
// This function calculates the score by calling the ScoreTreeHelper function
int ScoreTree(MovesTree* movesTree)
{
	Player rootPlayer = movesTree->root->player;
	//  in case the tree's root is the last move in the game (no next moves),
	//  the scoring of the move is simply how many flips it did.
	if (movesTree->root->num_moves == 0)
		return movesTree->root->flips;

	// otherwise, find the branch with the minimal score, and output it's score.
	int minPoints = scoreTreeHelper(movesTree->root->next_moves[0], rootPlayer, movesTree->root->flips);
	for (int i = 1; i < movesTree->root->num_moves; i++)
	{
		int tmpPoints = scoreTreeHelper(movesTree->root->next_moves[i], rootPlayer, movesTree->root->flips);
		if (tmpPoints < minPoints)
			minPoints = tmpPoints;
	}
	return minPoints;
}
// This function recursively evaluates the score of a moves tree by traversing the tree,
// the score is based on the flips value and wether the node is a leaf or parent node
int scoreTreeHelper(MovesTreeNode* root, Player rootPlayer, int points)
{
	int currPoints = 0;
	int tmpPoints = 0;
	Player currPlayer = root->player;

	// In case it's a leaf
	if (root->num_moves == 0)
	{
		if (currPlayer == rootPlayer)
			points += root->flips;
		else
			points -= root->flips;
		return points;
	}

	// In case it's a parent
	else
	{

		// In case it's the same player as the root, calculate the minimum of his childs
		if (currPlayer == rootPlayer)
		{
			currPoints = scoreTreeHelper(root->next_moves[0], rootPlayer, points + root->flips);
			for (int i = 1; i < root->num_moves; i++)
			{
				tmpPoints = scoreTreeHelper(root->next_moves[i], rootPlayer, points + root->flips);
				if (tmpPoints < currPoints)
					currPoints = tmpPoints;
			}
		}

		// In case it's the enemy player's node, calculate the maximum of his childs
		else
		{
			currPoints = scoreTreeHelper(root->next_moves[0], rootPlayer, points - root->flips);
			for (int i = 1; i < root->num_moves; i++)
			{
				tmpPoints = scoreTreeHelper(root->next_moves[i], rootPlayer, points - root->flips);
				if (tmpPoints > currPoints)
					currPoints = tmpPoints;
			}
		}
	}
	return currPoints;
}

//Q5
// get a current board, the player and the height of his tree,
// then make's a move ,updates the board and returns 1,
// if there are no moves available, returns 0.
int PlayOneTurn(Board board, Player player, int height)
{
	// create a possible move's list, or return 0 if there are no moves.
	MovesList movesList = FindMoves(board, player);
	if (isEmptyList(&movesList))
		return 0;
	
	// find the maximum score:
	// create a tree for each possible move and calculate it's score.
	MovesListNode* currMove = movesList.head;
	MovesTree* currTree = ExpandMove(board, player, &(currMove->pos), height);
	int bestScore = ScoreTree(currTree);
	ReversiPos bestMove = currMove->pos;
	currMove = currMove->next;
	while (currMove != NULL)
	{
		currTree = ExpandMove(board, player, &(currMove->pos), height);
		int currScore = ScoreTree(currTree);
		if (currScore > bestScore)
		{
			bestMove = currMove->pos;
			bestScore = currScore;
		}
		currMove = currMove->next;
	}

	// make the best move and return 1.
	MakeMove(board, player, &bestMove);
	printf("\n%c's turn: %c%c\n", player, bestMove.col, bestMove.row);
	return 1;
}

//Q6
// this function gets a board, a first player, and a height of the tree for each of the players. 
void PlayGame(Board board, Player first, int h1, int h2)
{
	// call getEnemy to get the second player.
	Player second = getEnemy(first);

	// as long as both players can play - play one turn for each player and print the board.
	int canPlay = 1;
	while (canPlay == 1)
	{
		canPlay = PlayOneTurn(board, first, h1);
		if (canPlay == 0)
			break;
		printBoard(board);
		canPlay = PlayOneTurn(board, second, h2);
		if (canPlay == 0)
			break;
		printBoard(board);
	}

	// finally, print the winner.
	printWinner(board);
}