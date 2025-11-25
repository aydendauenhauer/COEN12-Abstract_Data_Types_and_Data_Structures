/*	File: list.c
 *
 *	Copyright: Ayden Dauenhauer, 2023
 *
 *	Description: Implements a Maze game using stakcs and queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct list {
	int count;
	struct node *head;
	int (*compare)();
};

struct node {
	void *data;
	struct node *next;
	struct node *prev;
};

// Creates a list which can be used to implement stacks and queues
// Runtime: O(1)
LIST *createList(int (*compare)()) {
	struct list *lp;

	lp = malloc(sizeof(struct list));
	assert(lp != NULL);

	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);

	lp->head->next = lp->head;
	lp->head->prev = lp->head;

	return lp;
}

// Deletes all elements in a list and frees the memory associated
// Runtime: O(1)
void destroyList(LIST *lp) {
	assert(lp != NULL);
	struct node *np;
	np = lp->head->next;

	while (np != lp->head) {
		free(np);
		np = np->next;
	}
	free(lp->head);
	free(lp);
}

// Returns the number of elements in a list, *lp
// Runtime: O(1)
int numItems(LIST *lp) {
	assert(lp != NULL);
	return lp->count;
}

// Adds an item to the list in its first position (stack)
// Runtime: O(1)
void addFirst(LIST *lp, void *item) {
	assert(lp != NULL);

	struct node *np;
	np = malloc(sizeof(struct node));
	assert(np != NULL);
	np->data = item;

	np->prev = lp->head;
	np->next = lp->head->next;

	lp->head->next->prev = np;
	lp->head->next = np;

	lp->count++;
}

// Adds an item to the list in its last position (queue)
// Runtime: O(1)
void addLast(LIST *lp, void *item) {
	assert(lp != NULL);

	struct node *np;
	np = malloc(sizeof(struct node));
        assert(np != NULL);
        np->data = item;

        np->prev = lp->head->prev;
        np->next = lp->head;

        lp->head->prev->next = np;
        lp->head->prev = np;

	lp->count++;
}

// Removes an item from the list in its first position (queue)
// Runtime: O(1)
void *removeFirst(LIST *lp) {
	assert(lp != NULL && lp->count > 0);

	void *item;
        struct node *np, *sentinel;
        sentinel = lp->head;

        np = sentinel->next;
        sentinel->next = np->next;
        np->next->prev = sentinel;

        item = np->data;
        free(np);

	lp->count--;
        return item;
}

// Removes an item from the list in its last position (stack)
// Runtime: O(1)
void *removeLast(LIST *lp) {
	assert(lp != NULL && lp->count > 0);

	void *item;
	struct node *np, *sentinel;
	sentinel = lp->head;

	np = sentinel->prev;
	sentinel->prev = np->prev;
	np->prev->next = sentinel;

	item = np->data;
	free(np);

	lp->count--;
	return item;
}

// Returns the first element in the list
// Runtime: O(1)
void *getFirst(LIST *lp) {
	assert(lp != NULL);
	return lp->head->next->data;
}

// Returns the last element in the list
// Runtime: O(1)
void *getLast(LIST *lp) {
	assert(lp != NULL);
	return lp->head->prev->data;
}

// Removes the node that contains the given item
// Runtime: O(n)
void removeItem(LIST *lp, void *item) {
	assert(lp != NULL && lp->count > 0);

        struct node *np;
        np = lp->head->next;

	for (np; np != lp->head; np = np->next) {
		if ((*lp->compare)(np->data, item) == 0) {
			np->prev->next = np->next;
			np->next->prev = np->prev;
			free(np);
			lp->count--;
		}
	}
}

// Finds the node that contains the given item
// Runtime: O(n)
void *findItem(LIST *lp, void *item) {
	assert(lp != NULL);

	struct node *np;
	np = lp->head;

	int i;
	for (i = 0; i < lp->count; i++) {
		if ((*lp->compare)(np->data, item) == 0) {
			return np->data;
		}
	}
	return NULL;
}

// Returns the items in a list *lp
// Runtime: O(n)
void *getItems(LIST *lp) {
	assert(lp != NULL);

	struct node *np;
	np = lp->head;

	int *items = malloc(sizeof(np->data));

	int i;
	for (i = 0; i < lp->count; i++) {
		items[i] = np->data;
		np = np->next;
	}
	return items;
}
