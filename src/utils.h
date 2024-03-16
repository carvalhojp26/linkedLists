#ifndef UTILS_H
#define UTILS_H

#include "types.h"

Node* createNode(int data);
Node* readFile(char* filename);

void writeToFile(Node* head, const char* filename);
void printList(Node* head);
void getDimensions(Node *head, int *numRows, int *numCols);
void makeSquare(Node **head);
void calculateMaxSumUtil(Node* row, int* visited, int currentSum, int* maxSum, int numRows);
void clearInputBuffer();

#endif