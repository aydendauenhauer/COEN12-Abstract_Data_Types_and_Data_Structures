/*
 * File:	unsorted.c
 *
 * Copyright:	2023, Ayden Dauenhauer
 *
 * Description:	To search, add, and remove from textfiles using an unsorted array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct set {
	char **elts;
	int count;
	int length;
};

// Searches for an element, *elt, in a set, *sp using a linear search
// Runtime: O(n)
static int search(SET *sp, char *elt) {
        assert(sp);
        assert(elt);

        int i;
        for (i = 0; i < sp->count; i++) {
                if (strcmp(sp->elts[i], elt) == 0) {
                        return i;
                }
        }
        return -1;
}

// Creates a set *sp
// Runtime: O(1)
SET *createSet(int maxElts) {
	SET *sp = malloc(sizeof(SET));
	assert(sp);

	sp->elts = malloc(sizeof(char*) *maxElts);
	assert(sp->elts);

	sp->count = 0;
	sp->length = maxElts;
	return sp;
}

// Destroys set *sp
// Runtime: O(1)
void destroySet(SET *sp) {
	free(sp);
}

// Returns the number of elements in a set, *sp
// Runtime: O(1)
int numElements(SET *sp) {
	assert(sp);
	return sp->count;
}

// Adds element *elt to set *sp if it's not already in it
// Runtime: O(n)
void addElement(SET *sp, char *elt) {
	assert(sp);
	assert(elt);

	if (search(sp, elt) == -1) {
		assert(sp->count < sp->length);
		elt = strdup(elt);
		assert(elt);
		sp->data[sp->count++] = elt;
	}
}

// Removes element *elt from set *sp if it's in it
// Runtime: O(n)
void removeElement(SET *sp, char *elt) {
	assert(sp);
	assert(elt);

	int i = search(sp, elt);
	if (i != -1) {
		sp->data[i] = sp->data[sp->count - 1];
		sp->count--;
	}
}

// Returns the index of *elt if it's found in *sp
// Runtime: O(n)
char *findElement(SET *sp, char *elt) {
	assert(sp);
	assert(elt);

	int i = search(sp, elt);
	if (i == -1) {
		return NULL;
	}

        return sp->data[i];
}

// Returns all elements in *sp
// Runtime: O(n)
char **getElements(SET *sp) {
	assert(sp);
	char **list;

	list = malloc(sizeof(char *) * sp->count);
	assert(list);

	memcpy(list, sp->data, sizeof(char *) * sp->count);
	return list;
}
