#pragma once
#include "Conditions.h"

void initializeBoard(Board board);
void printBoard(Board board);
void printList(MovesList* lst);
void printSeperatingLine();
int checkDirection(Board board, Player player, int rowDirection, int colDirection, ReversiPos* move);
int directionHelper(Board board, Player player, ReversiPos* move, bool change);
void makeEmptyList(MovesList* lst);
MovesListNode* createNewListNode(ReversiPos pos, int flips, MovesListNode* next);
void insertDataToStartList(MovesList* lst, ReversiPos pos, int flips);
void insertNodeToStartList(MovesList* lst, MovesListNode* head);
void insertDataToEndList(MovesList* lst, ReversiPos pos, int flips);
void insertNodeToEndList(MovesList* lst, MovesListNode* tail);
void freeList(MovesList* lst);
void checkAllocation(void* ptr);
void expandMoveHelper(Board b, Player p, ReversiPos* move, int height, MovesTreeNode* root);
Player getEnemy(Player p);
int countMoves(MovesList* lst);
void freeTree(MovesTreeNode* root);
int scoreTreeHelper(MovesTreeNode* root, Player rootPlayer, int points);
