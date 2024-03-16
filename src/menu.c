#include <stdio.h>
#include "logic.h"
#include "menu.h"
#include "utils.h"
#include <stdlib.h>

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


/**
 * @brief Limpa o ecra do terminal. Verifica o sistema operativo para executar o comando correto.
 */
void clearScreen() {
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif
}


/**
 * @brief Aguarda até que o utilizador pressione Enter.
 */
void waitForUserInput() {
	printf("\nPressione Enter para continuar...");
	// Limpa qualquer caractere residual no buffer de entrada
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	// Aguarda a nova entrada do utilizador
	while ((c = getchar()) != '\n' && c != EOF) { }
}