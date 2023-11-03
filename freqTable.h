#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "rowNode.h"

#ifndef FREQTABLE_H
#define FREQTABLE_H


struct row *buildFreqTable(int infile);

void addRow(struct row *current, char c, int f);

void printTable(struct row *head);

int tableIndex(struct row *head, char find);

#endif
