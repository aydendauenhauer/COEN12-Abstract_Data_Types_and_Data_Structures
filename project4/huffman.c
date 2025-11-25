// File:	huffman.c
//
// Copyright:	Ayden Dauenhauer, 2023
//
// Description:	To encode and decode data which can be exactly reconstructed through lossless compression

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

struct node {
	struct node *parent;
	int count;
};

int counts[256 + 1];
struct node *nodes[257] = NULL;

// Count the number of occurences of each chareacter in a file
// Runtime: O(n)
FILE *fp = argv[1];
int value;

while (value = getc(fp)) {
	if (value == EOF) {
		break;
	}

	count[value] += 1;
}

// Create and allocate memory for a new node
// Runtime: O(1)
node mknode(data, left_node, right_node) {
	struct node *new_node = malloc(sizeof(node));

	new_node->count = data;
	new_node->parent = NULL;

	if (left_node != NULL) {
		left_node->parent = new_node;
	}

	if (right_node != NULL) {
		right_node->parent = new_node;
	}

	return new_node;
}

// To compare values for createQueue(cmp)
// Runtime: O(1)
int compare(t1, t2) {
	return (t1->count < t2->count) ? -1 : (t1->count > t2->count);
}


// To create a priority queue to build a huffman tree
// Runtime: O(n)
pq[0] = mknode(0, NULL, pq[1]);

int i;
for (i = 0; i < 257; i++) {
	if (counts[i] != 0) {
		pq[i] = mknode(i, pq[i-1], pq[i+1]);
	}
}

// To count the number of bits for each character
// Runtime: O(1)
int depth(node) {
	
}

// To print out occurences of each character
// Runtime: O(1)
if (isprint(c) = False) {
	printf("%03o", c);
}

printf("%d %d %d", counts[c], depth(nodes[c]), counts[c] * depth[nodes[c]]);

// To generare the compressed file
// Runtime: O(1)
pack(fp, new_file, *nodes);
