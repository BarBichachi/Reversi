#include <stdio.h>
#include <stdlib.h>

#include "MandatoryHighFunctions.h"

// This function initializes the game board
void initializeBoard(Board board)
{
	int startPos = BOARD_SIZE / 2;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (i == startPos - 1)
			{
				if (j == startPos - 1)
					board[i][j] = 'X';
				else if (j == startPos)
					board[i][j] = 'O';
				else
					board[i][j] = ' ';
			}
			else if (i == startPos)
			{
				if (j == startPos - 1)
					board[i][j] = 'O';
				else if (j == startPos)
					board[i][j] = 'X';
				else
					board[i][j] = ' ';
			}
			else
				board[i][j] = ' ';
		}
}

// This function prints the game board
void printBoard(Board board) {
	printSeperatingLine();
	printf("| |");
	for (int i = 0; i < BOARD_SIZE; i++)
		printf("%c|", 'a' + i);
	printf("\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		printSeperatingLine();
		printf("|%d|", i + 1);
		for (int j = 0; j < BOARD_SIZE; j++)
			printf("%c|", board[i][j]);
		printf("\n");
	}
	printSeperatingLine();
}

// This function prints the given moves list
void printList(MovesList* lst)
{
	MovesListNode* curr = lst->head;

	while (curr != NULL)
	{
		printf("Position: (%c, %c)\n", curr->pos.row, curr->pos.col);
		printf("Flips: %d\n", curr->flips);
		printf("\n");

		curr = curr->next;
	}
}

// This function prints a separating line to visually separate rows and columns on the game board
void printSeperatingLine() {
	for (int j = 0; j < 2 * (BOARD_SIZE + 1); j++)
		if (j % 2 == 0)
			printf("+");
		else
			printf("-");
	printf("\n");
}

// Function to check and calculate the number of pieces to flip in a specific direction
int checkDirection(Board board, Player player, int rowDirection, int colDirection, ReversiPos* move, bool change)
{
	// If 'change' is true, place the player's piece on the initial cell
	if (change == true)
		board[move->row - '1'][move->col - 'a'] = player;

	int flips = 0;
	int currentRow = (move->row - '1') + rowDirection;
	int currentCol = (move->col - 'a') + colDirection;

	// Keep moving in the direction until the end of the board is reached or a condition is met
	while (isInsideBoard(currentRow, currentCol))
	{
		if (board[currentRow][currentCol] == ' ')
			return NO_MOVE;
		else if (board[currentRow][currentCol] == player)
			return flips;

		// If 'change' is true, flip the opponent's piece to the player's piece
		if (change == true)
			board[currentRow][currentCol] = player;

		flips++;
		currentRow += rowDirection;
		currentCol += colDirection;
	}
	return NO_MOVE;
}

// Helper function to check and calculate the number of pieces to flip in all directions
int directionHelper(Board board, Player player, ReversiPos* move, bool change)
{
	int currentFlip = 0;
	int totalFlips = 0;

	// Loop through all possible movement directions
	for (int i = UP; i <= DOWN; i++)
		for (int j = LEFT; j <= RIGHT; j++)
		{
			// Skip the case when we're looking at the same position of the ReversiPos
			if (i == NO_MOVE && j == NO_MOVE)
				continue;
			else
			{
				// Check and calculate the number of pieces to flip in the current direction
				currentFlip = checkDirection(board, player, i, j, move, false);

				// If 'change' is true, actually flip the pieces on the board
				if (currentFlip > 0 && change == true)
					currentFlip = checkDirection(board, player, i, j, move, true);

				totalFlips += currentFlip;
			}
		}
	return totalFlips;
}

// This function initializes a MovesList
void makeEmptyList(MovesList* lst)
{
	lst->head = lst->tail = NULL;
}

// This function creates and returns a new MovesListNode
MovesListNode* createNewListNode(ReversiPos pos, int flips, MovesListNode* next)
{
	MovesListNode* res = (MovesListNode*)malloc(sizeof(MovesListNode));
	checkAllocation(res);

	res->pos = pos;
	res->flips = flips;
	res->next = next;
	return res;
}

// This function creates a new MovesListNode with the provided pos and flips values and inserts it at the start of the MovesList
void insertDataToStartList(MovesList* lst, ReversiPos pos, int flips)
{
	MovesListNode* newHead = createNewListNode(pos, flips, NULL);
	insertNodeToStartList(lst, newHead);
}

// This function inserts the provided head node at the start of the MovesList
void insertNodeToStartList(MovesList* lst, MovesListNode* head)
{
	if (isEmptyList(lst))
		lst->head = lst->tail = head;
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}

// This function creates a new MovesListNode with the provided pos and flips values and inserts it at the end of the MovesList
void insertDataToEndList(MovesList* lst, ReversiPos pos, int flips)
{
	MovesListNode* newTail = createNewListNode(pos, flips, NULL);
	insertNodeToEndList(lst, newTail);
}

// This function inserts the provided tail node at the end of the MovesList
void insertNodeToEndList(MovesList* lst, MovesListNode* tail)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = tail;
	}
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
}

// This function frees the memory allocated for the MovesList
void freeList(MovesList* lst)
{
	MovesListNode* curr = lst->head;
	MovesListNode* tmp;

	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	free(lst);
}

// This function checks if the memory allocation was successful.
void checkAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!");
		exit(1);
	}
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

// This function returns the enemy player
Player getEnemy(Player p)
{
	if (p == PLAYER_O)
		return PLAYER_X;
	return PLAYER_O;
}

// This function counts the number of nodes in the list
int countMoves(MovesList* lst)
{
	MovesListNode* curr = lst->head;
	int count = 0;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

// This function recursively frees the tree
void freeTree(MovesTreeNode* root)
{
	if (root == NULL) 
		return;

	for (int i = 0; i < root->num_moves; i++) 
		freeTree(root->next_moves[i]);
	
	free(root->next_moves);
	free(root);
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
		currPoints = scoreTreeHelper(root->next_moves[0], rootPlayer, points - root->flips);

		// In case it's the same node as the root, calculate the minimum of his childs
		if (currPlayer == rootPlayer)
			for (int i = 1; i < root->num_moves; i++)
			{
				tmpPoints = scoreTreeHelper(root->next_moves[i], rootPlayer, points + root->flips);
				if (tmpPoints < currPoints)
					currPoints = tmpPoints;
			}

		// In case it's the enemy node of the root, calculate the maximum of his childs
		else
			for (int i = 1; i < root->num_moves; i++)
			{
				tmpPoints = scoreTreeHelper(root->next_moves[i], rootPlayer, points - root->flips);
				if (tmpPoints > currPoints)
					currPoints = tmpPoints;
			}
	}
	return currPoints;
}