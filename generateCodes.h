#include <stdio.h>
#include <stdlib.h>

#include "rowNode.h"
#include "huffmanNode.h"

#ifndef GENERATECODES_H
#define GENERATECODES_H

void generateHuffmanCodes(struct row *root, int depth, int path[], struct huff *codeTable);

struct huff *charHeap(struct huff *head);

void printCodes(struct huff *head);

#endif
