#pragma once
#include "Conditions.h"
void initializeBoard(Board board);
void printBoard(Board board);
void printSeperatingLine();
int CheckDirection(Board board, Player player, int rowDirection, int colDirection, ReversiPos* move);
int directionHelper(Board board, Player player, ReversiPos* move, bool change);