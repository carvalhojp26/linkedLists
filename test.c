#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"  
#include <stdbool.h>
 
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

int calculateMaxSum(Node* head, int numRows) {
    int* visited = (int*)calloc(numRows, sizeof(int));
    int maxSum = 0;
    calculateMaxSumUtil(head, visited, 0, &maxSum, numRows);
    free(visited);
    return maxSum;
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

int main() {
    char* filename = "data.txt";
    Node* list = readFile(filename); // Leia a matriz do arquivo.

    printf("Matriz original:\n");
    printList(list); // Imprime a matriz original lida do arquivo.

    makeSquare(&list); // Ajusta a matriz para ser quadrada, se necessário.

    printf("\nMatriz após ajuste para ser quadrada (se necessário):\n");
    printList(list); // Imprime a matriz após ajuste para ser quadrada.

    // Calcula a soma máxima na matriz ajustada para ser quadrada.
    int numRows, numCols;
    getDimensions(list, &numRows, &numCols); // Obtém as dimensões da matriz ajustada.
    int maxSum = calculateMaxSum(list, numRows); // Assume que a matriz agora é quadrada.

    printf("\nSoma máxima: %d\n", maxSum); // Exibe a soma máxima calculada.

    // Lembre-se de liberar a memória alocada para a lista ligada no final.
    // freeMatrix(list); // Esta função deve ser implementada para liberar toda a memória alocada.

    return 0;
}
