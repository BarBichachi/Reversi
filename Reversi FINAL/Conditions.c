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
bool isTopRow(ReversiPos pos) {
	if (pos.row == 'A')
		return true;
	else
		return false;
}
bool isBottomRow(ReversiPos pos) {
	if (pos.row == 'A' + BOARD_SIZE - 1)
		return true;
	else
		return false;
}
bool isLeftCol(ReversiPos pos) {
	if (pos.col == '1')
		return true;
	else
		return false;
}
bool isRightCol(ReversiPos pos) {
	if (pos.col == '1' + BOARD_SIZE - 1)
		return true;
	else
		return false;
}
bool isOccupiedByPlayer(Board board, ReversiPos* pos, Player player) {
	if (board[pos->row - 'A'][pos->col - '1'] == player)
		return true;
	else
		return false;
}
bool isNotOccupied(Board board, ReversiPos* pos)
{
	if (board[pos->row - 'A'][pos->col - '1'] == ' ')
		return true;
	else
		return false;
}
bool captureCondition(Board board, ReversiPos* playerPos, Player player,
	ReversiPos* rivalPos, ReversiPos* capturePos)
{

}
bool unableToCapture(Board board, ReversiPos* pos)
{

}

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

