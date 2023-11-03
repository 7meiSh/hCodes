#ifndef HUFF_H
#define HUFF_H

#define MAX_PATH_LENGTH 255

struct huff {
    char charType;
    struct huff *next;
    int code[MAX_PATH_LENGTH];
};

#endif
