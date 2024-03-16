#ifndef TYPES_H
#define TYPES_H

typedef struct Node {
    int data;
    struct Node *right;
    struct Node *down;
} Node;

#endif