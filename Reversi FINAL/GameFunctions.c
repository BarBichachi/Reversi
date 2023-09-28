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

//prints the winner of the game.
void printWinner(Board board)
{
	int x, o;
	x = o = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == PLAYER_X)
				x++;
			else if (board[i][j] == PLAYER_O)
				o++;
		}

	if (x == o)
		printf("It's a tie!\n");
	else if (x > o)
		printf("%c won! %d vs %d\n", PLAYER_X, x, o);
	else
		printf("%c won! %d vs %d\n", PLAYER_O, o, x);
}
