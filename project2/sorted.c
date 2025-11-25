/*
 * File:	sorted.c
 *
 * Copyright:	2023, Ayden Dauenhauer
 *
 * Description:	To search, add, and remove from text files in a sorted array. In theory, should be faster than unsorted.
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

// Searches for an element, *elt, in a set, *sp using a binary search
// Runtime: O(log(n))
static int search(SET *sp, char *elt, bool *found) {
        assert(sp);
        assert(elt);

        int min, mid, max, x;
        max = sp->count - 1;

        while (max >= min) {
                mid = (min + max) / 2;
                x = strcmp(elt, sp->elts[mid]);

                if (x == 0) {
                        *found = true;
                        return mid;
                }

                if (x > 0) {
                        min = mid + 1;
                }

                if (x < 0) {
                        max = mid - 1;
                }
        }

        *found = false;
        return min;
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

// Destroys and frees memory associated with set *sp
// Runtime: O(n)
void destroySet(SET *sp) {
	assert(sp);

	int i;
	for (i = 0; i < sp->count; i++) {
		free(sp->elts[i]);
	}

	free(sp->elts);
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
        assert(sp->count < sp->length);

        bool found = false;
        int i = search(sp, elt, &found);
        if (!found) {
		elt = strdup(elt);
		assert(elt);

		int j;
		for (j = sp->count; j > i; j--) {
			sp->elts[j] = sp->elts[j - 1];
		}

		sp->elts[i] = elt;
		sp->count++;
		
	}
}

// Removes element *elt from set *sp if it's in it
// Runtime: O(n)
void removeElement(SET *sp, char *elt) {
	assert(sp);
	assert(elt);

	bool found = false;
	int i = search(sp, elt, &found);
	if (found) {
		int j;
		for (j = i; j < sp->count - 1; j++) {
			sp->elts[j] = sp->elts[j + 1];
		}

		sp->elts[sp->count - 1] = NULL;
		sp->count--;
	}
}

// Returns the index of *elt if it's in *sp
// Runtime: O(log(n))
char *findElement(SET *sp, char *elt) {
	assert(sp);
	assert(elt);

	bool found = false;
	int i = search(sp, elt, &found);
	if (found) {
		return sp->elts[i];
	}

        return NULL;
}

// Returns all elements in *sp
// Runtime: O(n)
char **getElements(SET *sp) {
	assert(sp);

	char **list = malloc(sizeof(char *) * sp->count);
	assert(list);

	memcpy(list, sp->elts, sizeof(char *) * sp->count);
	return list;
}
