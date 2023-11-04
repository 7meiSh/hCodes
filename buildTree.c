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
                if(current->next != NULL && node->freq >= current->next->freq){
                    struct row* temp = current->next;
                    current->next = node;
                    node->next = temp;
                }
                else {
                    node->next = current->next;
                    current->next = node;
                }
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
struct row *insert(struct row *root, struct row *newNode) {
    if (newNode == NULL) {
        // Handle invalid input
        fprintf(stderr, "Cannot insert a NULL row into the priority queue.\n");
        return root;
    }

    // If the root is empty or the new row's frequency is smaller than the root's frequency,
    // make the new row the new root.
    if (root == NULL || newNode->freq < root->freq) {
        newNode->next = root;
        return newNode;
    }

    // Otherwise, find the appropriate position to insert the new row
    struct row *current = root;
    struct row *prev = NULL;
    while (current != NULL && newNode->freq >= current->freq) {
        prev = current;
        current = current->next;
    }

    // Insert the new row between prev and current
    prev->next = newNode;
    newNode->next = current;

    return root;
}

struct row *buildHuffman(struct row *minChar) {

    //grab the first two
    while(minChar->next!=NULL) {
        struct row *left = duplicate(minChar);
        minChar = kill(minChar);
        struct row *right = duplicate(minChar);
        minChar = kill(minChar);

        //create a parents with children are left and right
        struct row* parent = (struct row *)calloc(1, sizeof(struct row));
        parent->freq = left->freq+right->freq;
        parent->left = left;
        parent->right = right;
        parent->charType = '\0';//to indicate that this is not a leaf;
        minChar = insert(minChar, parent);
    }
    return minChar;
}