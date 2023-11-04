#ifndef FREQ_TABLE_H
#define FREQ_TABLE_H

// Define a structure for a row in the frequency table

// Function to rebuild the frequency table from the input file
struct row* rebuildFreqTable(int infile);
void cleanList(struct row* head);
void decodeParser(int infile, int outfile);
#endif // FREQ_TABLE_H
