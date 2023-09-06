#pragma once
#include "Constants.h"
typedef struct _reversiPos {
	char row, col;
}ReversiPos;
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef struct _movesListNode {
	ReversiPos pos;
	int flips;
	struct _movesListNode* next;
} MovesListNode;
typedef struct _movesList {
	MovesListNode* head;
	MovesListNode* tail;
} MovesList;
typedef struct _movesTreeNode {
	ReversiPos pos;
	Player player;
	int flips;
	struct _movesTreeNode** next_moves;
	int num_moves;
} MovesTreeNode;
typedef struct _movesTree {
	Board board;
	MovesTreeNode* root;
} MovesTree;