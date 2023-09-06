#include "Conditions.h"
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
bool winningCondition(Board board, Player player)
{

}

bool isInsideBoard(int currentRow, int currentCol)
{
	if (currentRow >= 0 && currentCol >= 0 && currentRow < BOARD_SIZE && currentCol < BOARD_SIZE)
		return true;
	return false;
}