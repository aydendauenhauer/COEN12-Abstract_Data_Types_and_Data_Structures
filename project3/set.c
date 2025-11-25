/*
 *	File:        set.c
 *
 *	Copyright:   2023, Ayden Dauenhauer
 *
 *	Description: Hashes items to assign to lists, then determines if the item is present in the list or not. If not, it is added.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct set{
	int count;
	int length;
	LIST **lists;
	int (*compare)();
	unsigned (*hash)();
} SET;

// Returns a value to insert values, depending on their properties via hashing
// Runtime: O(1) 
unsigned strhash(char *s)
{   
	unsigned hash = 0;
	while (*s != '\0')
		hash = 31 * hash + *s ++;
	return hash;
}

// Creates a set *sp
// Runtime: O(1)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
	printf("debug");

        SET *sp = malloc(sizeof(SET));
        assert(sp != NULL);

        sp->count = 0;
        sp->length = maxElts;

	LIST **lists = createList(sp->length);

//	LIST **lists = malloc(sizeof(*LIST) * sp->length);
	assert(lists != NULL);

	sp->compare = compare;
	sp->hash = hash;

	return sp;
}

// Destroys and frees memory associated with set *sp
// Runtime: O(n)
void destroySet(SET *sp) {
        assert(sp != NULL);

	int i;
        for (i = 0; i < sp->count; i++) {
                destroyList(sp->lists[i]);
        }

	free(sp->lists);
        free(sp);
}

// Returns the number of elements in a set, *sp
// Runtime: O(1)
int numElements(SET *sp) {
        assert(sp != NULL);
        return sp->count;
}

// Adds element *elt to set *sp if it's not already in it, in a specific list pointer *lp according to the hash table
// Runtime: O(n)
void addElement(SET *sp, void *elt) {
        assert (sp != NULL && elt != NULL);

	int *locn = findItem(sp->lists[strhash(elt)], elt);
        if (locn == NULL) {
                assert(sp->count < sp->length);
                addFirst(sp->lists[strhash(elt)], elt);
        }
}

// Removes element *elt from set *sp if it's in it, in a specific list pointer *lp according to the hash table
// Runtime: O(n)
void removeElement(SET *sp, void *elt) {
        assert(sp != NULL && elt != NULL);

	int *locn = findItem(sp->lists[strhash(elt)], elt);
        if (locn != NULL) {
                removeItem(sp->lists[strhash(elt)], elt);
        }
}

// Returns the index of *elt if it's in *sp, in a specific list pointer *lp according to the hash table
// Runtime: O(n)
void *findElement(SET *sp, void *elt) {
        assert(sp != NULL && elt != NULL);
	return findItem(sp->lists[strhash(elt)], elt);
}

// Returns all elements in *sp
// Runtime: O(n)
void *getElements(SET *sp) {
        assert(sp != NULL);

        char **list = malloc(sizeof(char *) * sp->count);

	int i;
	for (i = 0; i < sp->count; i++) {
		memcpy(list, getItems(sp->lists[i]), sizeof(char *) * sp->count);
	}

        return list;
}
