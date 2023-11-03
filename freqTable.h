#include <stdio.h>
#include <stdlib.h>
#include "rowNode.h"

#ifndef FREQTABLE_H
#define FREQTABLE_H


struct row *buildFreqTable(FILE *stream);

void addRow(struct row *current, char c, int f);

void printTable(struct row *head);

int tableIndex(struct row *head, char find);

#endif
