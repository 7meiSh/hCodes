#ifndef ROW_H
#define ROW_H

#define MAX_PATH_LENGTH 255

struct row {
    char charType;
    int freq;
    struct row *next;
    struct row *left;
    struct row *right;
};

#endif
