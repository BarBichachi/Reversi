#pragma once
#include "types.h"
#include <stdbool.h>
bool isTopRow(ReversiPos pos);
bool isBottomRow(ReversiPos pos);
bool isLeftCol(ReversiPos pos);
bool isRightCol(ReversiPos pos);
bool isOccupiedByPlayer(Board board, ReversiPos* pos, Player player);
bool isNotOccupied(Board board, ReversiPos* pos);
bool captureCondition(Board board, ReversiPos* playerPos, Player player,
	ReversiPos* rivalPos, ReversiPos* capturePos);
bool unableToCapture(Board board, ReversiPos* pos);
bool winningCondition(Board board, Player player);


bool isInsideBoard(int currentRow, int currentCol);
