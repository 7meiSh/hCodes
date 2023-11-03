#include <stdio.h>
#include <stdlib.h>
#include "rowNode.h"
#include "huffmanNode.h"
#include "generateCodes.h"

void generateHuffmanCodes(struct row *root, int depth, int path[], struct huff *codeTable) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        path[depth] = 0;
        generateHuffmanCodes(root->left, depth + 1, path, codeTable);
    }

    if (root->right != NULL) {
        path[depth] = 1;
        generateHuffmanCodes(root->right, depth + 1, path, codeTable);
    }

    if (root->left == NULL && root->right == NULL && root->charType != '\0') {
        // Leaf node, store the Huffman code in the codeTable
        struct huff *newCode = (struct huff *) calloc(1, sizeof(struct huff));
        newCode->charType = root->charType;
        newCode->next = NULL;

        int i = 0;
        while (i <= depth) {
            newCode->code[i] = path[i];
            i++;
        }
        newCode->code[i] = -1;
        struct huff *current = codeTable;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCode;
    }
}

struct huff *charHeap(struct huff *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct huff *heap = NULL;

    while (head != NULL) {
        struct huff *node = head;
        head = head->next;
        node->next = NULL;

        if (heap == NULL) {
            heap = node;
        } else {
            if (node->charType < heap->charType) {
                node->next = heap;
                heap = node;
            } else {
                struct huff *current = heap;
                while (current->next != NULL && node->charType >= current->next->charType) {
                    current = current->next;
                }
                node->next = current->next;
                current->next = node;
            }
        }
    }

    return heap;
}

void printCodes(struct huff *head) {
    struct huff *current = head;
    while (current != NULL) {
        printf("%c:", current->charType);

        int i = 0;
        while (current->code[i] != -1) {
            printf("%d", current->code[i]);
            i++;
        }
        printf("\n");

        current = current->next;
    }
}