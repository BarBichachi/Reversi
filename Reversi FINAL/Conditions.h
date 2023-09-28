#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void checkAllocation(void* ptr);
bool isInsideBoard(int currentRow, int currentCol);
bool isEmptyList(MovesList* lst);
