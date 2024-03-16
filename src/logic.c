#include "logic.h"
#include "utils.h"
#include "types.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @file logic.c
 * @brief Implementa as operações lógicas sobre a matriz representada por uma lista ligada bidimensional.
 *
 * Este arquivo contém as definições das funções responsáveis por manipular a matriz, incluindo atualização de valores,
 * adição e remoção de linhas e colunas, e o cálculo da soma máxima sob certas condições. As operações são aplicadas sobre
 * a estrutura de dados de lista ligada bidimensional, que permite a representação flexível de matrizes. As funções abordam:
 * 
 * - Atualização de um valor específico dentro da matriz (`updateValue`).
 * - Adição de novas linhas (`addRow`) e colunas (`addColumn`) à matriz com dados especificados pelo usuário.
 * - Remoção de linhas (`removeRow`) e colunas (`removeColumn`) selecionadas pelo usuário da matriz.
 * - Cálculo da soma máxima possível selecionando um elemento por linha e coluna sem repetições (`calculateMaxSum`).
 * 
 * Além disso, o arquivo lida com a escrita da matriz atualizada de volta ao arquivo após modificações, garantindo que as
 * alterações sejam persistidas.
 */

void updateValue(Node* head, int oldValue, int newValue) {
    Node* row = head;
    Node* col = NULL;
    int found = 0; // Adiciona um indicador para verificar se o valor foi encontrado

    // Percorrer cada linha
    while (row != NULL) {
        col = row; // Começar da primeira coluna
        // Percorrer cada coluna na linha atual
        while (col != NULL) {
            // Checar se o valor atual é o que queremos atualizar
            if (col->data == oldValue) {
                col->data = newValue; // Atualizar com o novo valor
                found = 1; // Marcar como encontrado
                break; // Pode remover este break se desejar atualizar todas as ocorrências
            }
            col = col->right; // Mover para o próximo nó na mesma linha
        }
        if (found) break; // Se o valor foi encontrado, não precisa continuar procurando
        row = row->down; // Mover para a próxima linha
    }

    writeToFile(head, "data.txt"); // Escrever no arquivo fora do loop

    if (!found) {
        printf("Value %d not found.\n", oldValue);
    }
}

Node* addRow(Node* head, int rowData[], int size, const char* filename) {
    // Primeiro, criamos a nova linha
    Node* newRowHead = NULL;
    Node* currentInNewRow = NULL;
    for (int i = 0; i < size; i++) {
        Node* newNode = createNode(rowData[i]);
        if (newRowHead == NULL) {
            newRowHead = newNode; // Primeiro nó da nova linha
        } else {
            currentInNewRow->right = newNode; // Conectar horizontalmente
        }
        currentInNewRow = newNode;
    }

    if (head == NULL) {
        // Se a lista estava vazia, a nova linha é agora a cabeça da lista
        head = newRowHead;
    } else {
        // Caso contrário, percorremos até o final da lista e adicionamos a nova linha
        Node* last = head;
        while (last->down != NULL) {
            last = last->down;
        }
        last->down = newRowHead;
    }

    // Após adicionar a nova linha, escrevemos a lista atualizada no arquivo
    writeToFile(head, filename);

    return head; // A cabeça da lista não muda
}

void addColumn(Node* head, int columnData[], const char* filename) {
    Node* currentRow = head;
    int rowIndex = 0;
    
    // Percorrer todas as linhas
    while (currentRow != NULL) {
        // Mover para o último nó da linha atual
        Node* lastNodeInRow = currentRow;
        while (lastNodeInRow->right != NULL) {
            lastNodeInRow = lastNodeInRow->right;
        }
        
        // Adicionar novo nó ao final da linha com os dados da coluna correspondente
        Node* newNode = createNode(columnData[rowIndex++]);
        lastNodeInRow->right = newNode;

        // Mover para a próxima linha
        currentRow = currentRow->down;
    }
    
    // Escrever a lista atualizada no arquivo
    writeToFile(head, filename);
}

Node* removeRow(Node* head, int rowIndex, const char* filename) {
    if (head == NULL || rowIndex < 0) {
        printf("Lista vazia ou índice inválido.\n");
        return head;
    }

    Node* temp = head;
    Node* toBeDeleted = NULL;

    if (rowIndex == 0) {
        // Remover a primeira linha
        head = temp->down; // Atualizar a cabeça da lista
        toBeDeleted = temp;
    } else {
        // Encontrar a linha imediatamente antes da que queremos remover
        for (int i = 0; temp != NULL && i < rowIndex - 1; i++) {
            temp = temp->down;
        }

        if (temp == NULL || temp->down == NULL) {
            printf("Índice fora dos limites.\n");
            return head;
        }

        // 'temp' agora aponta para o nó antes da linha a ser removida
        toBeDeleted = temp->down; // Linha a ser removida
        temp->down = temp->down->down; // Reconectar a lista sem a linha a ser removida
    }

    // Liberar os nós da linha removida
    while (toBeDeleted != NULL) {
        Node* next = toBeDeleted->right;
        free(toBeDeleted);
        toBeDeleted = next;
    }

    // Escrever a lista atualizada no arquivo
    writeToFile(head, filename);

    return head; // Retornar o novo ponteiro de cabeça da lista
}

void removeColumn(Node* head, int columnIndex, const char* filename) {
    if (head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Node* currentRow = head;
    
    // Percorrer todas as linhas
    while (currentRow != NULL) {
        Node* temp = currentRow;
        Node* toBeDeleted = NULL;

        if (columnIndex == 0) {
            // Remover a primeira coluna da linha
            toBeDeleted = temp;
            currentRow = temp->right; // Atualizar o início da linha atual
        } else {
            // Encontrar a coluna imediatamente antes da que queremos remover
            for (int i = 0; temp != NULL && i < columnIndex - 1; i++) {
                temp = temp->right;
            }

            if (temp == NULL || temp->right == NULL) {
                printf("Índice da coluna fora dos limites.\n");
            } else {
                // 'temp' agora aponta para o nó antes da coluna a ser removida
                toBeDeleted = temp->right; // Coluna a ser removida
                temp->right = temp->right->right; // Reconectar a lista sem a coluna a ser removida
            }
        }

        // Liberar o nó da coluna removida
        if (toBeDeleted != NULL) {
            free(toBeDeleted);
        }

        // Mover para a próxima linha
        if (currentRow != head || columnIndex == 0) { // Se estamos removendo a primeira coluna, já ajustamos `currentRow`
            currentRow = currentRow->down;
        } else { // Se não, precisamos ajustar manualmente para a próxima linha após manipulações
            currentRow = head->down; // Isto é necessário para continuar a iteração corretamente
        }
    }

    // Escrever a lista atualizada no arquivo
    writeToFile(head, filename);
}

int calculateMaxSum(Node* head, int numRows) {
    int* visited = (int*)calloc(numRows, sizeof(int));
    int maxSum = 0;
    calculateMaxSumUtil(head, visited, 0, &maxSum, numRows);
    free(visited);
    return maxSum;
}