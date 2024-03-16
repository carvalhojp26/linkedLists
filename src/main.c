#include <stdio.h>
#include "logic.h"
#include "menu.h"
#include "utils.h"

int main() {
    char* filename = "data.txt";
    Node* list = readFile(filename);
    int choice;

    if (!list) {
        printf("Falha ao carregar a matriz do arquivo ou arquivo vazio.\n");
        return 1;
    }

    do {
        choice = showMenuAndGetChoice();

        switch (choice) {
            case 1:
                printList(list);
                waitForUserInput();
                break;
            case 2:
                requestUpdateValue(list);
                waitForUserInput();
                break;
            case 3:
                list = requestAddRow(list, filename);
                waitForUserInput();
                break;
            case 4:
                requestAddColumn(list, filename);
                waitForUserInput();
                break;
            case 5:
                requestRemoveRow(&list, filename);
                waitForUserInput();
                break;
            case 6:
                requestRemoveColumn(list, filename);
                waitForUserInput();
                break;
            case 7:
                requestCalculateMaxSum(list, filename);
                waitForUserInput();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Escolha indisponível. Por favor, tente novamente.\n");
                break;
        }
    } while (choice != 0);

    // Lembre-se de liberar a memória alocada para a lista ligada antes de sair
    // freeMatrix(list); // Esta função deve ser implementada para liberar a memória

    return 0;
}

