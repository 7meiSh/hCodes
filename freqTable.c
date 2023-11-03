#include <stdio.h>
#include <stdlib.h>
#include "freqtable.h"

int tableIndex(struct row *head, char find) {
    struct row *current = head;
    int index = 0;
    while (current != NULL) {
        if (current->charType == find) {
            return index;
        }
        index++;
        current = current->next;
    }
    return -1;
}

void addRow(struct row *current, char c, int f) {
    struct row *new = NULL;
    new = (struct row *) calloc(1, sizeof(struct row));
    new->charType = c;
    new->freq = f;
    new->next = NULL;
    if (current == NULL) {
        current = new;
    };
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
}

struct row *buildFreqTable(FILE *stream) {
    struct row *head = NULL; // Initialize the frequency table as an empty list

    int thisChar;
    while ((thisChar = fgetc(stream)) != EOF) {
        int cIndex = tableIndex(head, thisChar);

        if (cIndex == -1) {
            // If the character is not found, add it to the frequency table
            if (head == NULL) {
                head = (struct row *) calloc(1, sizeof(struct row));
                head->freq = 1;
                head->charType = thisChar;
            } else {
                addRow(head, thisChar, 1);
            }
        } else {
            // If the character is found, increase its frequency
            struct row *tIndex = head;
            while (tIndex->charType != thisChar) {
                tIndex = tIndex->next;
            }
            tIndex->freq += 1;
        }
    }

    return head;
}

void printTable(struct row *head) {
    struct row *current = head;
    while (current != NULL) {
        printf("%c", current->charType);
        printf("%c", ':');
        printf("%i\n", current->freq);
        current = current->next;
    }
}
