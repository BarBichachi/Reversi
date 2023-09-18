#include "ListFunctions.h"

// This function initializes a MovesList
void makeEmptyList(MovesList* lst)
{
	lst->head = lst->tail = NULL;
}

// This function creates and returns a new MovesListNode
MovesListNode* createNewListNode(ReversiPos pos, int flips, MovesListNode* next)
{
	MovesListNode* res = (MovesListNode*)malloc(sizeof(MovesListNode));
	checkAllocation(res);

	res->pos = pos;
	res->flips = flips;
	res->next = next;
	return res;
}

// This function creates a new MovesListNode with the provided pos and flips values and inserts it at the start of the MovesList
void insertDataToStartList(MovesList* lst, ReversiPos pos, int flips)
{
	MovesListNode* newHead = createNewListNode(pos, flips, NULL);
	insertNodeToStartList(lst, newHead);
}

// This function inserts the provided head node at the start of the MovesList
void insertNodeToStartList(MovesList* lst, MovesListNode* head)
{
	if (isEmptyList(lst))
		lst->head = lst->tail = head;
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}

// This function creates a new MovesListNode with the provided pos and flips values and inserts it at the end of the MovesList
void insertDataToEndList(MovesList* lst, ReversiPos pos, int flips)
{
	MovesListNode* newTail = createNewListNode(pos, flips, NULL);
	insertNodeToEndList(lst, newTail);
}

// This function inserts the provided tail node at the end of the MovesList
void insertNodeToEndList(MovesList* lst, MovesListNode* tail)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = tail;
	}
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
}

// This function frees the memory allocated for the MovesList
void freeList(MovesList* lst)
{
	MovesListNode* curr = lst->head;
	MovesListNode* tmp;

	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	free(lst);
}