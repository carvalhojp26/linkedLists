#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"  
#include <stdbool.h>
#include "utils.h"
#include <stddef.h>
#include "logic.h"

/**
 * @file utils.c
 * @brief Fornece funções utilitárias para a manipulação de uma matriz representada como uma lista ligada bidimensional.
 *
 * Este arquivo contém a implementação de várias funções utilitárias que apoiam a manipulação e visualização da matriz,
 * incluindo a criação de novos nós, leitura e escrita de matrizes em arquivos, impressão da matriz no console, obtenção
 * das dimensões da matriz, ajuste da matriz para garantir que seja quadrada e cálculo auxiliar para a soma máxima.
 * Estas funções são essenciais para o funcionamento das funcionalidades oferecidas pelo programa, permitindo uma interação
 * eficiente e eficaz com a estrutura de dados da matriz e com a persistência dos dados em arquivos.
 *
 * Principais funcionalidades incluídas:
 * - `createNode`: Aloca e inicializa um novo nó para a lista ligada.
 * - `readFile`: Lê uma matriz de um arquivo e constrói uma representação de lista ligada bidimensional.
 * - `writeToFile`: Escreve a matriz atualizada em um arquivo, preservando as alterações feitas pelo usuário.
 * - `printList`: Exibe a matriz atual no console em um formato de tabela fácil de ler.
 * - `getDimensions`: Calcula e retorna as dimensões atuais da matriz.
 * - `makeSquare`: Ajusta a matriz para ser quadrada, adicionando linhas ou colunas de zeros conforme necessário.
 * - `calculateMaxSumUtil`: Função auxiliar utilizada para calcular a soma máxima de valores selecionados da matriz.
 * - `clearInputBuffer`: Limpa o buffer de entrada para evitar leituras indesejadas durante a coleta de entrada do usuário.
 *
 * Estas funções proporcionam uma base sólida para a realização de operações complexas sobre a matriz de maneira simples e direta.
 */

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); //aloca a memoria para o novo no
    if (!newNode) {
        perror("Fail to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->right = NULL;
    newNode->down = NULL;
    return newNode;
}

Node* readFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    Node* mainHead = NULL;
    Node* lastHead = NULL; // Usado para manter o rastro do último head de cada linha para conectar com down.
    char line[1024];
    char* token;
    int data;

    while (fgets(line, sizeof(line), file)) {
        Node* head = NULL; // Head da linha atual
        Node* current = NULL; // Nó atual na linha
        token = strtok(line, ";");
        while (token != NULL) {
            data = atoi(token); // Convertendo token para inteiro
            Node* newNode = createNode(data);

            if (head == NULL) {
                head = newNode; // Primeiro nó da linha
                if (mainHead == NULL) {
                    mainHead = head; // Definindo o mainHead se for a primeira linha
                }
            } else {
                current->right = newNode; // Conectando nós horizontalmente
            }
            current = newNode;

            token = strtok(NULL, ";");
        }
        if (lastHead != NULL) {
            lastHead->down = head; // Conectando a última linha com a atual verticalmente
        }
        lastHead = head; // Atualizando lastHead para a linha atual
    }

    fclose(file);
    return mainHead;
}

void writeToFile(Node* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    Node* row = head;
    Node* col = NULL;

    // Percorrer cada linha
    while (row != NULL) {
        col = row;
        // Percorrer cada coluna na linha atual
        while (col != NULL) {
            fprintf(file, "%d", col->data); // Escrever o valor no arquivo
            if (col->right != NULL) {
                fprintf(file, ";"); // Separar valores na mesma linha
            }
            col = col->right; // Mover para o próximo nó na mesma linha
        }
        if (row->down != NULL) {
            fprintf(file, "\n"); // Nova linha para linhas subsequentes
        }
        row = row->down; // Mover para a próxima linha
    }

    fclose(file);
}

void printList(Node* head) {
    Node* row = head;
    
    while (row) {
        Node* column = row;
        
        // Imprime a linha superior da tabela ou divisória entre as linhas
        while (column) {
            printf("+-----");
            column = column->right;
        }
        printf("+\n"); // Fecha a linha superior/divisória com o canto da tabela
        
        column = row; // Reset para o início da linha para imprimir os dados
        printf("|"); // Início da linha de dados
        while (column) {
            printf(" %3d |", column->data); // Assume que os números têm até 3 dígitos
            column = column->right;
        }
        printf("\n"); // Quebra de linha após imprimir todos os dados da linha atual
        
        row = row->down; // Move para a próxima linha da lista ligada
    }

    // Após imprimir todas as linhas, imprime a linha inferior da tabela
    if (head) { // Verifica se a lista não está vazia antes de imprimir a linha inferior
        Node* bottomLine = head;
        while (bottomLine) {
            printf("+-----");
            bottomLine = bottomLine->right;
        }
        printf("+\n"); // Fecha a linha inferior da tabela
    }
}


void getDimensions(Node *head, int *numRows, int *numCols) {
    *numRows = 0;
    *numCols = 0;
    Node *row = head, *col = head;
    while (row) {
        (*numRows)++;
        row = row->down;
    }
    while (col) {
        (*numCols)++;
        col = col->right;
    }
}

void makeSquare(Node **head) {
    int numRows, numCols;
    getDimensions(*head, &numRows, &numCols);

    int diff = abs(numRows - numCols);
    if (diff == 0) {
        // A matriz já é quadrada.
        return;
    }

    int *zeroData = (int *)calloc(diff, sizeof(int));
    const char* filename = "data.txt"; // Definindo o nome do arquivo para uso
    if (numRows < numCols) {
        // Adiciona linhas de zeros.
        for (int i = 0; i < diff; i++) {
            *head = addRow(*head, zeroData, numCols, filename);
        }
    } else {
        // Adiciona colunas de zeros.
        for (int i = 0; i < diff; i++) {
            addColumn(*head, zeroData, filename);
        }
    }

    free(zeroData);
}

int maxSum = 0;

void calculateMaxSumUtil(Node* row, int* visited, int currentSum, int* maxSum, int numRows) {
    if (row == NULL) {
        if (currentSum > *maxSum) {
            *maxSum = currentSum;
        }
        return;
    }

    Node* col = row;
    int colIndex = 0;
    while (col != NULL) {
        if (!visited[colIndex]) {
            visited[colIndex] = 1;
            calculateMaxSumUtil(row->down, visited, currentSum + col->data, maxSum, numRows);
            visited[colIndex] = 0;
        }
        col = col->right;
        colIndex++;
    }
}

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}