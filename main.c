#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "freqTable.h"
#include "buildTree.h"
#include "rowNode.h"
#include "huffmanNode.h"
#include "generateCodes.h"

#define MAX_PATH_LENGTH 255

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file> [output_file]\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    const char *output_filename;

    if (argc >= 3) {
        output_filename = argv[2];
    } else {
        output_filename = "noNewlineOut.txt";
    }

    int infile = open(input_filename, O_RDONLY);
    if (infile == -1) {
        fprintf(stderr, "Error: Unable to open input file '%s'\n", input_filename);
        return 1;
    }

    int outfile = open(output_filename, O_WRONLY | O_CREAT);
    if (outfile == -1) {
        fprintf(stderr, "Error: Unable to open or create output file '%s'\n", output_filename);
        close(infile);
        return 1;
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
