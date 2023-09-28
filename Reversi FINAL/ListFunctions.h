#pragma once
#include "Conditions.h"

void makeEmptyList(MovesList* lst);
MovesListNode* createNewListNode(ReversiPos pos, int flips, MovesListNode* next);
void insertDataToEndList(MovesList* lst, ReversiPos pos, int flips);
void insertNodeToEndList(MovesList* lst, MovesListNode* tail);
void freeList(MovesList* lst);
