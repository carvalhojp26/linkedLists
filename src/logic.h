#ifndef LOGIC_H
#define LOGIC_H

#include "types.h"

void updateValue(Node* head, int oldValue, int newValue);
void addColumn(Node* head, int columnData[], const char* filename);
void removeColumn(Node* head, int columnIndex, const char* filename);

Node* addRow(Node* head, int rowData[], int size, const char* filename);
Node* removeRow(Node* head, int rowIndex, const char* filename);

int calculateMaxSum(Node* head, int numRows);

#endif