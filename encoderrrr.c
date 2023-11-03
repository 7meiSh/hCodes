#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "rowNode.h"
#include "huffmanNode.h"
#include "generateCodes.h"
#include "encoderrrr.h"

void sendFreqToFile(struct row *head, int outfile) {
    // Count the number of unique characters in the frequency table
    int numUniqueChars = 0;
    struct row *current = head;
    while (current != NULL) {
        numUniqueChars++;
        current = current->next;
    }

    // Write the number of unique characters minus one to the output file
    char numMinusOne = (char)(numUniqueChars - 1);
    write(outfile, &numMinusOne, 1);


    // Write the sorted frequency table to the output file
    current = head;
    while (current != NULL) {
        // Write the character type (one byte)
        write(outfile, &(current->charType), 1);
        // Write the frequency (four bytes, little-endian)
        int frequency = current->freq;
        int i = 0;
        while (i < 4) {
            char byte = (char)(frequency & 0xFF);
            write(outfile, &byte, 1);
            frequency >>= 8;
            i++;
        }
        current = current->next;
    }
}

void writeBit(int outfile, int bit, int *bitBuffer, int *bitCount) {
    // Add the bit to the bit buffer (0 or 1)
    *bitBuffer <<= 1;
    *bitBuffer |= bit;

    // Increment the bit count
    (*bitCount)++;

    // If the bit buffer is full (8 bits), write it to the output file
    if (*bitCount == 8) {
        char byte = (char)(*bitBuffer);
        write(outfile, &byte, 1);
        *bitBuffer = 0;
        *bitCount = 0;
    }
}

void generateFileBody(int infile, int outfile, struct huff *codeTable) {
    int bitBuffer = 0;
    int bitCount = 0;
    char charType;

    while (read(infile, &charType, sizeof(charType)) == sizeof(charType)) {
        struct huff *code = codeTable;

        // Find the Huffman code for the current character
        while (code != NULL && code->charType != charType) {
            code = code->next;
        }

        if (code != NULL) {
            int i = 0;
            while (code->code[i] != -1) {
                int bit = code->code[i];

                // Write the bit (0 or 1) to the output file
                writeBit(outfile, bit, &bitBuffer, &bitCount);
                i++;
            }
        }
    }

    // Flush any remaining bits in the bit buffer to the output file
    while (bitCount > 0) {
        writeBit(outfile, 0, &bitBuffer, &bitCount);
    }
}

