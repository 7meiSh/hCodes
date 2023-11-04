#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "rowNode.h"
#include "freqTable.h"
#include "buildTree.h"

// Define a function to rebuild the frequency table from the input file
struct row* rebuildFreqTable(int infile) {
    // Set the file pointer to the beginning of the file
    if (lseek(infile, 0, SEEK_SET) == -1) {
        fprintf(stderr, "Error setting the file pointer to the beginning of the input file.\n");
        return NULL;
    }

    // Read the number of unique characters minus one from the input file
    char numMinusOne;
    if (read(infile, &numMinusOne, 1) != 1) {
        fprintf(stderr, "Error reading the number of unique characters from the input file.\n");
        return NULL;
    }

    // Calculate the actual number of unique characters
    int numUniqueChars = (int) numMinusOne + 1;

    // Initialize a pointer to the head of the linked list
    struct row* freqTable = NULL;

    // Read character type and frequency for each unique character
    int i = 0;
    while (i < numUniqueChars) {
        // Read the character type (one byte)
        char charType;
        if (read(infile, &charType, 1) != 1) {
            fprintf(stderr, "Error reading character type from the input file.\n");
            return NULL;
        }

        // Read the frequency (four bytes, little-endian)
        int frequency = 0;
        int j = 0;
        while (j < 4) {
            char byte;
            if (read(infile, &byte, 1) != 1) {
                fprintf(stderr, "Error reading frequency byte from the input file.\n");
                return NULL;
            }
            frequency |= ((int)byte & 0xFF) << (j * 8);
            j++;
        }

        // Create a new node for this character and frequency
        struct row* newNode = (struct row*)malloc(sizeof(struct row));
        newNode->charType = charType;
        newNode->freq = frequency;
        newNode->next = NULL;

        // Add the new node to the frequency table
        if (freqTable == NULL) {
            // This is the first node
            freqTable = newNode;
        } else {
            // Find the last node in the list and append the new node
            struct row* current = freqTable;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }

        i++;
    }

    return freqTable;
}

void cleanList(struct row* head) {
    struct row* current = head;
    while (current != NULL) {
        current->left = NULL;
        current->right = NULL;
        current = current->next;
    }

}

int decodeParser(int infile, int outfile) {
    // Create the tree
    struct row* freq = rebuildFreqTable(infile);
    //cleanList(freq);
    struct row* prioQueue = createMinHeap(freq);
    cleanList(prioQueue);
    struct row* tree = buildHuffman(prioQueue);

    // Set the file pointer to the beginning of the file
    if (lseek(infile, 1, SEEK_SET) == -1) {
        perror("Error setting the file pointer to the beginning of the input file");
        close(outfile); // Close the output file first
        close(infile);
        return 1;
    }

    // Read and process one bit at a time
    char buffer;
    int curByte;
    struct row* current = tree; // Initialize the current node outside the loop

    while ((curByte = read(infile, &buffer, 1)) > 0) {
        int i = 7;
        while (i >= 0) {
            if (current == NULL) {
                fprintf(stderr, "Current node is NULL. Aborting.\n");
                close(outfile);
                close(infile);
                return 1;
            }

            int bit = (buffer >> i) & 1;
            if (bit == 1) {
                current = current->right;
            } else if (bit == 0) {
                current = current->left;
            }

            if (current == NULL) {
                fprintf(stderr, "Current node became NULL. Bit: %d\n", bit);
                close(outfile);
                close(infile);
                return 1;
            }

            // If we reach a leaf node, write the found character to the output file
            if (current->left == NULL && current->right == NULL) {
                char foundChar = current->charType;
                if (write(outfile, &foundChar, 1) != 1) {
                    perror("Error writing character to the output file");
                    close(outfile);
                    close(infile);
                    return 1;
                }
                // Reset current to the root of the tree for the next bit
                current = tree;
            }

            i--;
        }

        if (curByte == -1) {
            perror("Error reading from input file");
            close(outfile);
            close(infile);
            return 1;
        }
    }


    // Close the output and input files in the correct order
    close(outfile);
    close(infile);

    return 0;
}

