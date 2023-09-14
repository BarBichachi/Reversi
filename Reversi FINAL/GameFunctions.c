#include <stdio.h>
#include "GameFunctions.h"

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
int CheckDirection(Board board, Player player, int rowDirection, int colDirection, ReversiPos* move, bool change)
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
				currentFlip = CheckDirection(board, player, i, j, move, false);

				// If 'change' is true, actually flip the pieces on the board
				if (currentFlip > 0 && change == true)
					currentFlip = CheckDirection(board, player, i, j, move, true);

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