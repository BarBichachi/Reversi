#pragma once
#include "Conditions.h"
void initializeBoard(Board board);
void printBoard(Board board);
void printSeperatingLine();
int CheckDirection(Board board, Player player, int rowDirection, int colDirection, ReversiPos* move);
int directionHelper(Board board, Player player, ReversiPos* move, bool change);
void makeEmptyList(MovesList* lst);
MovesListNode* createNewListNode(ReversiPos pos, int flips, MovesListNode* next);
void insertDataToStartList(MovesList* lst, ReversiPos pos, int flips);
void insertNodeToStartList(MovesList* lst, MovesListNode* head);
void insertDataToEndList(MovesList* lst, ReversiPos pos, int flips);
void insertNodeToEndList(MovesList* lst, MovesListNode* tail);
void freeList(MovesList* lst);
void checkAllocation(void* ptr);