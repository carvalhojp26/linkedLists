#ifndef LOGIC_H
#define LOGIC_H

#include "types.h"

/**
 * @brief Atualiza o primeiro nó encontrado com um valor específico na matriz 2D ligada.
 * 
 * Esta função percorre a matriz 2D ligada, linha por linha e coluna por coluna, em busca do primeiro
 * nó que contém o valor especificado em `oldValue`. Quando encontrado, o valor desse nó é atualizado
 * para `newValue`. Após a atualização, a matriz modificada é escrita de volta ao arquivo especificado.
 * Se o valor `oldValue` não for encontrado na matriz, uma mensagem será exibida para informar o usuário.
 * 
 * @param head Ponteiro para o nó cabeça da matriz 2D ligada.
 * @param oldValue O valor a ser procurado na matriz para atualização.
 * @param newValue O novo valor para substituir o `oldValue`.
 * 
 * @note Esta função atualiza apenas a primeira ocorrência de `oldValue`. Se houver múltiplas
 * ocorrências de `oldValue` na matriz, apenas a primeira será atualizada para `newValue`.
 * 
 * @note A função assume que o arquivo para gravação é "data.txt". Se necessário usar outro arquivo,
 * o nome do arquivo precisa ser ajustado dentro da função `writeToFile`.
 */
void updateValue(Node* head, int oldValue, int newValue);

/**
 * @brief Adiciona uma nova linha à matriz representada por uma lista ligada 2D.
 * 
 * Esta função adiciona uma nova linha ao final da matriz. A nova linha é composta pelos valores
 * fornecidos no array `rowData`. Após adicionar a nova linha, a matriz é escrita de volta ao
 * arquivo especificado por `filename`. Se a matriz estava inicialmente vazia (i.e., `head` é NULL),
 * a nova linha se tornará a primeira linha da matriz.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada 2D. Pode ser NULL se a lista estiver vazia.
 * @param rowData Array contendo os dados para a nova linha.
 * @param size Número de elementos no array `rowData`.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita.
 * @return Node* Retorna o ponteiro para o nó cabeça da lista ligada 2D atualizada.
 */
Node* addRow(Node* head, int rowData[], int size, const char* filename);

/**
 * @brief Adiciona uma nova coluna ao final de cada linha da matriz.
 * 
 * Esta função percorre todas as linhas da matriz representada por uma lista ligada bidimensional,
 * adicionando um novo nó ao final de cada linha com os dados fornecidos em `columnData`.
 * Cada elemento do array `columnData` corresponde ao dado a ser inserido em cada nova célula da coluna.
 * Após a adição da nova coluna, a função grava a matriz atualizada de volta ao arquivo especificado por `filename`.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param columnData Array contendo os dados a serem adicionados na nova coluna.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita.
 */
void addColumn(Node* head, int columnData[], const char* filename);

/**
 * @brief Remove uma linha específica da matriz.
 * 
 * Dada a posição especificada por `rowIndex`, esta função remove a linha correspondente da matriz representada
 * por uma lista ligada bidimensional. Se a linha a ser removida é a primeira, o ponteiro de cabeça da lista (`head`)
 * é atualizado. Para linhas subsequentes, a conexão `down` do nó anterior é ajustada para pular a linha removida.
 * Após a remoção, os recursos alocados para os nós da linha removida são liberados. Finalmente, a matriz atualizada
 * é escrita de volta ao arquivo especificado por `filename`. Se `rowIndex` for inválido ou a lista estiver vazia,
 * a função exibe uma mensagem de erro e retorna sem modificar a matriz.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param rowIndex Índice baseado em zero da linha a ser removida.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita.
 * @return O novo ponteiro para o nó cabeça da lista após a remoção da linha.
 */
Node* removeRow(Node* head, int rowIndex, const char* filename);

/**
 * @brief Remove uma coluna específica da matriz.
 * 
 * Esta função itera sobre cada linha da matriz, representada por uma lista ligada bidimensional,
 * e remove o nó correspondente à coluna especificada por `columnIndex`. Se a coluna a ser removida
 * é a primeira, o ponteiro da linha é atualizado para o próximo nó à direita. Para colunas no meio
 * ou no final da linha, ajusta-se o ponteiro `right` do nó anterior para pular o nó da coluna removida.
 * Os nós removidos são liberados para evitar vazamentos de memória. Após a conclusão da remoção em
 * todas as linhas, a matriz atualizada é gravada de volta ao arquivo especificado por `filename`.
 * Mensagens de erro são exibidas se a lista estiver vazia ou o índice da coluna for inválido.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param columnIndex Índice baseado em zero da coluna a ser removida.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita.
 */
void removeColumn(Node* head, int columnIndex, const char* filename);

/**
 * @brief Calcula a soma máxima de uma seleção de nós em uma matriz bidimensional representada por uma lista ligada.
 * 
 * Esta função inicia o processo de calcular a soma máxima onde nenhum dois nós selecionados estão na mesma linha ou coluna.
 * Utiliza uma abordagem de backtracking para explorar todas as combinações possíveis de seleção de nós, mantendo a restrição
 * de que apenas um nó por linha e por coluna pode ser escolhido. A função `calculateMaxSumUtil` é chamada recursivamente para
 * percorrer a matriz e acumular a soma de valores selecionados, atualizando `maxSum` com a maior soma encontrada durante a
 * exploração. Um array `visited` é utilizado para marcar as colunas já visitadas e evitar seleções repetidas na mesma coluna.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional que representa a matriz.
 * @param numRows Número de linhas na matriz, utilizado para inicializar o array `visited` e controlar a recursão.
 * @return A soma máxima obtida pela seleção de nós conforme as regras especificadas.
 */
int calculateMaxSum(Node* head, int numRows);

#endif