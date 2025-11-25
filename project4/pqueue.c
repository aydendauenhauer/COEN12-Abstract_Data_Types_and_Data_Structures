// File:	pqueue.c
//
// Copyright:	2023, Ayden Dauenhauer
//
// Description:	To add and remove elements in a binary heap, for better efficiency

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"
# define p(x) ((x - 1) / 2)
# define l(x) (x * 2 + 1)
# define r(x) (x * 2 + 2)

typedef struct pqueue {
	int count;
	int length;
	void **data;
	int (*compare)();
} PQ;

// To create a priority queue
// Runtime: O(1)
PQ *createQueue(int (*compare)()) {
	PQ *pq = malloc(sizeof(PQ));
	assert(pq != NULL);

	pq->count = 0;
	pq->length = 10;

	pq->data = malloc(sizeof(void *) * pq->length);
	assert(pq->data != NULL);

	pq->compare = compare;

	return pq;
}

// To remove all data associated with a priority queue
// Runtime: O(1)
void destroyQueue(PQ *pq) {
	assert(pq != NULL);
    	free(pq->data);
	free(pq);
}

// To return the number of elements in the priority queue
// Runtime: O(1)
int numEntries(PQ *pq) {
	assert(pq != NULL);
	return pq->count;
}

// To add an item to an array in a binary heap
// Runtime: O(logn)
void addEntry(PQ *pq, void *entry) {
	assert(pq != NULL);

// fix reallocation
	if (pq->count == pq->length) {
		pq = realloc(pq, sizeof(PQ) * 2);
	}

	int index = pq->count++;
	int parent = ((index - 1) / 2);

	while (index > 0 && (*pq->compare) (pq->data[parent], entry) > 0) {
		pq->data[index] = pq->data[parent];
		index = parent;
	}

	pq->data[index] = entry;
}

// To remove the smallest element in the priority queue
// Runtime: O(logn)
void *removeEntry(PQ *pq) {
	assert(pq != NULL);

	void *low, *entry;
    	low = pq->data[0];

	int child;
	int current = 0;
	int lchild = ((current) * 2 + 1);
	int rchild = ((current) * 2 + 2);

    	entry = pq->data[-- pq->count];

	while (lchild < pq->count) {
		child = lchild;

		if (rchild < pq->count)
			if ((*pq->compare)(pq->data[lchild], pq->data[rchild]) > 0) {
			child = rchild;
		}

		if ((*pq->compare) (entry, pq->data[child]) > 0) {
			pq->data[current] = pq->data[child];
			current = child;
		} else
			break;
	}

	pq->data[current] = entry;
	return low;

}
