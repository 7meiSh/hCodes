#include <stdio.h>
#include "freqTable.h"
#include "buildTree.h"
#include "rowNode.h"
#include "huffmanNode.h"
#include "generateCodes.h"

#define MAX_PATH_LENGTH 255

int main() {

    /*grab the infile*/
    FILE *infile = fopen("noNewline", "r");
    if (infile == NULL) {
        printf(stderr,"input file invalid");
    }

    /*creating and printing frequency table*/
    struct row *freqTable = buildFreqTable(infile);
    printTable(freqTable);

    /*creating a priority queue and converting it into a huffman tree*/
    struct row *pQueue = createMinHeap(freqTable);
    struct row *codes = buildHuffman(pQueue);

    /*creating the space for the code table
     * then creating an empty array of -1 to store the path*/
    struct huff *codeTable = (struct huff *) calloc(1, sizeof(struct huff));
    int path[MAX_PATH_LENGTH];
    int i = 0;
    while (i <= MAX_PATH_LENGTH) {
        path[i] = -1;
        i++;
    }

    /*make your codes and print them*/
    generateHuffmanCodes(codes, 0, path, codeTable);
    struct huff* temp = codeTable;
    codeTable = codeTable->next;
    printCodes(charHeap(codeTable));

    /*teardown*/
    free(temp);
    free(pQueue);
    free(codes);
    free(codeTable);
    return 0;
}
