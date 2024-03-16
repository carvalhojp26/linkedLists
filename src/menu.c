#include <stdio.h>
#include "logic.h"
#include "menu.h"
#include "utils.h"
#include <stdlib.h>

/**
 * @file menu.c
 * @brief Implementa a interface do usuário e as funções de solicitação para manipulação de matrizes.
 *
 * Este arquivo contém a lógica de interface do usuário necessária para interagir com o programa de manipulação
 * de matrizes. Inclui a exibição de um menu com várias opções, como alterar um valor na matriz, adicionar ou
 * remover linhas/colunas e calcular a soma máxima. Cada opção do menu é vinculada a uma função específica que
 * realiza a operação desejada, solicitando entradas adicionais do usuário quando necessário. As funções de
 * solicitação facilitam a coleta de dados de entrada do usuário para essas operações e chamam as funções lógicas
 * apropriadas definidas em outros arquivos do projeto para executar as ações requisitadas.
 *
 * Além das funções de solicitação, o arquivo define `clearScreen` e `waitForUserInput`, que melhoram a
 * experiência do usuário ao interagir com o menu e visualizar os resultados das operações executadas.
 *
 * Principais funções incluídas:
 * - `requestUpdateValue`: Solicita ao usuário para atualizar um valor específico na matriz.
 * - `requestAddRow`: Solicita ao usuário para adicionar uma nova linha na matriz.
 * - `requestAddColumn`: Solicita ao usuário para adicionar uma nova coluna na matriz.
 * - `requestRemoveRow`: Solicita ao usuário para remover uma linha específica da matriz.
 * - `requestRemoveColumn`: Solicita ao usuário para remover uma coluna específica da matriz.
 * - `requestCalculateMaxSum`: Solicita ao usuário para calcular e exibir a soma máxima conforme as condições definidas.
 * - `showMenuAndGetChoice`: Exibe o menu principal e coleta a escolha do usuário.
 * - `clearScreen`: Limpa o terminal para uma visualização clara do menu e resultados.
 * - `waitForUserInput`: Pausa a execução do programa até que o usuário pressione Enter, permitindo a visualização dos resultados.
 */

void requestUpdateValue(Node* head) {
    int oldValue, newValue;

    // Solicitar ao usuário o valor antigo a ser substituído
    printf("Digite o valor antigo a ser atualizado: ");
    scanf("%d", &oldValue);

    // Solicitar ao usuário o novo valor
    printf("Digite o novo valor: ");
    scanf("%d", &newValue);

    // Chamar updateValue com os valores fornecidos pelo usuário
    updateValue(head, oldValue, newValue);

    // Informar ao usuário que a operação foi concluída
    printf("Operação de atualização concluída.\n");
}

Node* requestAddRow(Node* head, const char* filename) {
    if (head == NULL) {
        printf("A lista está vazia.\n");
        return NULL;
    }

    int numRows, numCols;
    getDimensions(head, &numRows, &numCols); // Obtém o número atual de colunas da matriz

    int rowData[numCols]; // Cria um array para armazenar os dados da nova linha com base no número de colunas

    printf("Digite os valores para a nova linha (%d valores esperados): ", numCols);
    for (int i = 0; i < numCols; i++) {
        scanf("%d", &rowData[i]);
    }

    return addRow(head, rowData, numCols, filename); // Adiciona a nova linha à matriz e retorna a nova cabeça da lista
}

void requestAddColumn(Node* head, const char* filename) {
    if (head == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    int numRows, numCols;
    getDimensions(head, &numRows, &numCols); // Obtém o número atual de linhas da matriz

    int columnData[numRows]; // Cria um array para armazenar os dados da nova coluna com base no número de linhas

    printf("Digite os valores para a nova coluna (%d valores esperados): ", numRows);
    for (int i = 0; i < numRows; i++) {
        scanf("%d", &columnData[i]);
    }

    addColumn(head, columnData, filename); // Adiciona a nova coluna à matriz
    printf("Nova coluna adicionada.\n");
}

void requestRemoveRow(Node** head, const char* filename) {
    if (*head == NULL) {
        printf("A matriz está vazia. Não há linhas para remover.\n");
        return;
    }

    int numRows, numCols;
    getDimensions(*head, &numRows, &numCols); // Para informar ao usuário quantas linhas existem.

    int rowIndex;
    printf("Atualmente, existem %d linhas. Digite o índice da linha que deseja remover (começando de 0): ", numRows);
    scanf("%d", &rowIndex);

    // Verificar se o índice é válido
    if (rowIndex < 0 || rowIndex >= numRows) {
        printf("Índice fora dos limites. Nenhuma linha foi removida.\n");
        return;
    }

    *head = removeRow(*head, rowIndex, filename); // Remove a linha selecionada.

    printf("Linha %d removida com sucesso.\n", rowIndex);
}

void requestRemoveColumn(Node* head, const char* filename) {
    if (head == NULL) {
        printf("A matriz está vazia. Não há colunas para remover.\n");
        return;
    }

    int numRows, numCols;
    getDimensions(head, &numRows, &numCols); // Para informar ao usuário quantas colunas existem.

    int columnIndex;
    printf("Atualmente, existem %d colunas. Digite o índice da coluna que deseja remover (começando de 0): ", numCols);
    scanf("%d", &columnIndex);

    // Verificar se o índice é válido
    if (columnIndex < 0 || columnIndex >= numCols) {
        printf("Índice fora dos limites. Nenhuma coluna foi removida.\n");
        return;
    }

    removeColumn(head, columnIndex, filename); // Remove a coluna selecionada.

    printf("Coluna %d removida com sucesso.\n", columnIndex);
}

// Em menu.c ou onde quer que a função esteja definida
void requestCalculateMaxSum(Node* head, const char* filename) {
    if (!head) {
        printf("A matriz está vazia.\n");
        return;
    }
    // Garanta que a matriz é quadrada antes de calcular a soma máxima.
    makeSquare(&head); // Ajusta a matriz para ser quadrada, se necessário.

    int numRows, numCols;
    getDimensions(head, &numRows, &numCols); // Obtém as dimensões da matriz ajustada.
    if (numRows != numCols) {
        printf("Erro: A matriz ajustada ainda não é quadrada.\n");
        return;
    }

    int maxSum = calculateMaxSum(head, numRows);
    printf("A soma máxima é: %d\n", maxSum);

    // Se necessário, use 'filename' para operações de arquivo relacionadas.
}

int showMenuAndGetChoice() {
	int choice;
	
	clearScreen();

	printf("---------------MENU---------------\n");
	printf("1-Tabela de Valores\n");
	printf("2-Alterar Inteiro\n");
	printf("3-Adicionar Linha\n");
	printf("4-Adicionar Coluna\n");
	printf("5-Remover Linha\n");
    printf("6-Remover Coluna\n");
    printf("7-Calcular Soma Maxima\n");
	printf("0-Sair\n");
	printf("-----------------------------------\n");
	
	while (1) {
		if (scanf("%d", &choice) == 1) {
			return choice;
		} else {
			printf("Entrada inválida. Por favor, insira um número.\n");
			clearInputBuffer();
		}
	}
}

void clearScreen() {
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif
}

void waitForUserInput() {
	printf("\nPressione Enter para continuar...");
	// Limpa qualquer caractere residual no buffer de entrada
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	// Aguarda a nova entrada do utilizador
	while ((c = getchar()) != '\n' && c != EOF) { }
}