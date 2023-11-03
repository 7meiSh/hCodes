#include <stdio.h>
#include <stdlib.h>
#include "rowNode.h"
#include "buildTree.h"

struct row *duplicate(struct row *subject) {
    struct row *new = (struct row *) calloc(1, sizeof(struct row));
    if (new == NULL) {
        return NULL;
    }
    if (subject == NULL) {
        return NULL;
    }
    new->charType = subject->charType;
    new->freq = subject->freq;
    new->next = NULL;
    new->right = subject->right;
    new->left = subject->left;
    return new;
}

struct row *createMinHeap(struct row *head) {
    /*guard against short/empty queues*/
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct row *heap = NULL;//new empty row

    while (head != NULL) {//until the end of the list
        struct row *node = head;//get the first element
        head = head->next;
        node->next = NULL;

        if (heap == NULL) {//if the heap is empty add the node to it
            heap = node;
        } else {//otherwise compare current freq with first freq
            if (node->freq < heap->freq) {//if current is smaller "bubble up"
                node->next = heap;
                heap = node;
            } else {//otherwise put it in the next open "largest" spot
                struct row *current = heap;
                while (current->next != NULL && node->freq >= current->next->freq) {
                    current = current->next;
                }
                node->next = current->next;
                current->next = node;
            }
        }
    }

    return heap;
}

struct row *kill(struct row *root) {
    if (root == NULL) {
        return NULL; // Return NULL if the list is empty
    }

    struct row *temp = root;
    root = root->next;
    free(temp);
    root = createMinHeap(root); // Recreate the min-heap
    return root;
}

struct row *buildHuffman(struct row *minChar) {
    while (minChar->next != NULL) {//until the end of the queue
        struct row *parent = (struct row *) calloc(1, sizeof(struct row));//empty node to manipulate

        //grab the two smallest characters
        struct row *left = duplicate(minChar);
        minChar = kill(minChar);
        struct row *right = duplicate(minChar);
        minChar = kill(minChar);

        //sum the frequencies and fill the parent
        parent->freq = left->freq + right->freq;
        parent->left = left;
        parent->right = right;
        if (minChar != NULL) {//as long as the queue still has things in it
            parent->next = minChar;//put the parent somewhere in the queue it doesn't matter where
            minChar = createMinHeap(parent);//re-sort
        } else {
            minChar = parent;//if its empty you're done
        }
    }
    return minChar;
}