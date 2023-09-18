#pragma once
#include "ListFunctions.h"

void initializeBoard(Board board);
void printBoard(Board board);
void printList(MovesList* lst);
void printSeperatingLine();
int directionHelper(Board board, Player player, ReversiPos* move, bool change);
int checkDirection(Board board, Player player, int rowDirection, int colDirection, ReversiPos* move);
Player getEnemy(Player p);
int countMoves(MovesList* lst);
void freeTree(MovesTreeNode* root);
int scoreTreeHelper(MovesTreeNode* root, Player rootPlayer, int points);
