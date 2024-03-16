#include <stdio.h>
#include "logic.h"
#include "menu.h"
#include "utils.h"

/**
 * @file main.c
 * @brief Ponto de entrada principal para a aplicação de manipulação de matrizes.
 *
 * Este arquivo contém a função `main`, que serve como o ponto de entrada para uma aplicação que
 * manipula uma matriz armazenada em um arquivo de texto ("data.txt"). A matriz é representada internamente
 * como uma lista ligada bidimensional. O programa oferece ao usuário um menu de opções para visualizar a matriz,
 * alterar elementos, adicionar ou remover linhas/colunas, e calcular a soma máxima sob certas condições.
 * 
 * As operações disponíveis são:
 * - Visualizar a matriz atual.
 * - Atualizar um valor específico dentro da matriz.
 * - Adicionar uma nova linha com valores especificados pelo usuário.
 * - Adicionar uma nova coluna com valores especificados pelo usuário.
 * - Remover uma linha selecionada pelo usuário.
 * - Remover uma coluna selecionada pelo usuário.
 * - Calcular e exibir a soma máxima de uma seleção de valores da matriz.
 * 
 * O loop principal do programa apresenta essas opções em um menu, executa a escolha do usuário e
 * repete até que a opção de sair seja selecionada. Após a execução de cada operação, o usuário é solicitado
 * a pressionar Enter para continuar, permitindo a visualização dos resultados ou mensagens de status.
 *
 */


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

