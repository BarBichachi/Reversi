#include "Conditions.h"

// This function checks if the memory allocation was successful.
void checkAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!");
		exit(1);
	}
}

// Checks if the given position is on the board.
bool isInsideBoard(int currentRow, int currentCol)
{
	if (currentRow >= 0 && currentCol >= 0 && currentRow < BOARD_SIZE && currentCol < BOARD_SIZE)
		return true;
	return false;
}

bool isEmptyList(MovesList* lst)
{
	if (lst->head == NULL && lst->tail == NULL)
		return true;
	return false;
}

