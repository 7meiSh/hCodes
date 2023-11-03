#include <stdio.h>
#include <stdlib.h>
#include "rowNode.h"

#ifndef BUILDTREE_H
#define BUILDTREE_H

struct row *duplicate(struct row *subject);

struct row *createMinHeap(struct row *head);

struct row *kill(struct row *root);

struct row *buildHuffman(struct row *minChar);

void printTree(struct row *root);

#endif