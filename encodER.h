#ifndef ENCODE_H
#define ENCODE_H

#include "rowNode.h"
#include "huffmanNode.h"
#include "generateCodes.h"

void sendFreqToFile(struct row *head, int outfile);

void writeBit(int outfile, int bit, int *bitBuffer, int *bitCount);

void generateFileBody(int infile, int outfile, struct huff *codeTable);

#endif
