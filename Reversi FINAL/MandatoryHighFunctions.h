#pragma once
#include "GameFunctions.h"

//Q1
int CheckMove(Board board, Player player, ReversiPos* move);
void MakeMove(Board board, Player player, ReversiPos* move);
//Q2
MovesList FindMoves(Board board, Player player);
//Q3
MovesTree* ExpandMove(Board b, Player p, ReversiPos* move, int height);
void expandMoveHelper(Board b, Player p, ReversiPos* move, int height, MovesTreeNode* root);
//Q4
int ScoreTree(MovesTree* movesTree);
int scoreTreeHelper(MovesTreeNode* root, Player rootPlayer, int points);
//Q5
int PlayOneTurn(Board board, Player player, int height);
//Q6
void PlayGame(Board board, Player first, int h1, int h2);