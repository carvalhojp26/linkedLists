#ifndef UTILS_H
#define UTILS_H

#include "types.h"

/**
 * @brief Cria um novo nó para ser utilizado na matriz bidimensional representada por uma lista ligada.
 * 
 * Aloca memória para um novo nó da lista ligada e inicializa seus campos. O campo `data` é definido
 * com o valor passado como argumento, enquanto os ponteiros `right` e `down`, que apontam,
 * respectivamente, para o próximo nó na mesma linha e para o próximo nó na mesma coluna,
 * são inicializados como NULL. Se a alocação de memória falhar, o programa exibe uma mensagem de erro
 * e encerra a execução.
 * 
 * @param data O valor do inteiro a ser armazenado no novo nó.
 * @return Um ponteiro para o novo nó criado.
 */
Node* createNode(int data);

/**
 * @brief Lê uma matriz de inteiros de um arquivo e constrói uma representação de lista ligada bidimensional.
 * 
 * Abre o arquivo especificado por `filename` e lê sua conteúdo linha por linha, onde os valores inteiros são esperados
 * estar separados por ponto e vírgula (`;`). Cada linha do arquivo corresponde a uma linha da matriz e cada valor é
 * inserido em um novo nó na lista ligada. Os nós são conectados tanto horizontalmente (na mesma linha) quanto verticalmente
 * (na mesma coluna) para formar a estrutura bidimensional. A função retorna um ponteiro para o nó cabeça da lista ligada,
 * que representa o canto superior esquerdo da matriz. Em caso de falha ao abrir o arquivo, o programa exibe uma mensagem
 * de erro e termina.
 * 
 * @param filename Nome do arquivo de onde a matriz será lida.
 * @return Um ponteiro para o nó cabeça da lista ligada bidimensional que representa a matriz lida.
 */
Node* readFile(char* filename);

/**
 * @brief Escreve o conteúdo da matriz representada por uma lista ligada bidimensional em um arquivo.
 * 
 * Esta função abre o arquivo especificado por `filename` para escrita e percorre a estrutura de lista ligada
 * bidimensional apontada por `head`, escrevendo os dados de cada nó no arquivo. Os valores dentro de uma mesma linha
 * são separados por ponto e vírgula (`;`), e cada linha da matriz é escrita em uma nova linha no arquivo. Se não for
 * possível abrir o arquivo para escrita, a função exibirá uma mensagem de erro e terminará o programa.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param filename Nome do arquivo no qual a matriz será escrita.
 */
void writeToFile(Node* head, const char* filename);

/**
 * @brief Imprime a matriz representada por uma lista ligada bidimensional.
 * 
 * Esta função percorre a estrutura de lista ligada bidimensional apontada por `head`, imprimindo cada valor de nó
 * em um formato de tabela. Cada célula da tabela é delimitada por linhas horizontais e verticais, com cada valor
 * alinhado à direita dentro de uma largura fixa. A função assume que os valores dos nós têm até três dígitos.
 * Esta representação visual facilita a compreensão da estrutura da matriz no console.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 */
void printList(Node* head);

/**
 * @brief Calcula as dimensões de uma matriz representada por uma lista ligada bidimensional.
 * 
 * Através da travessia da estrutura da lista ligada bidimensional, esta função determina o número total de linhas e colunas
 * na matriz. Os valores calculados são armazenados nas variáveis apontadas por `numRows` e `numCols`, respectivamente. A função
 * inicia no nó cabeça da lista (`head`) e percorre a estrutura tanto na direção horizontal (para contar colunas) quanto na direção
 * vertical (para contar linhas), atualizando os contadores conforme avança.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param numRows Ponteiro para a variável onde o número total de linhas será armazenado.
 * @param numCols Ponteiro para a variável onde o número total de colunas será armazenado.
 */
void getDimensions(Node *head, int *numRows, int *numCols);

/**
 * @brief Ajusta a matriz para ser quadrada, adicionando linhas ou colunas de zeros conforme necessário.
 * 
 * Avalia as dimensões atuais da matriz e determina se é necessário adicionar linhas ou colunas para torná-la quadrada.
 * Linhas ou colunas adicionais são preenchidas com zeros. Esta operação é essencial para garantir que a matriz
 * atenda aos requisitos de determinados algoritmos que assumem uma estrutura quadrada. Os ajustes são feitos in-place
 * na estrutura de lista ligada bidimensional, e a matriz ajustada é opcionalmente escrita de volta ao arquivo especificado.
 * 
 * @param head Referência ao ponteiro para o nó cabeça da lista ligada bidimensional.
 * @param filename Nome do arquivo onde a matriz ajustada pode ser escrita. Este parâmetro é usado
 *                 apenas se linhas ou colunas forem efetivamente adicionadas à matriz.
 */
void makeSquare(Node **head);

/**
 * @brief Função auxiliar recursiva para calcular a soma máxima de valores selecionados da matriz.
 * 
 * Esta função é chamada recursivamente para explorar todas as possíveis combinações de seleção de nós
 * na matriz, sob a condição de que apenas um nó por linha e por coluna seja escolhido. Ela utiliza um
 * vetor de visitados `visited` para marcar as colunas já exploradas em cada caminho recursivo, evitando
 * seleções repetidas e garantindo que a restrição de um nó por coluna seja respeitada.
 * 
 * A cada chamada recursiva, a função avança para a próxima linha (`row->down`) e tenta adicionar o valor
 * de cada nó acessível (não visitado) na linha atual ao `currentSum`. Se a última linha for atingida e
 * o `currentSum` for maior que o `maxSum` atual, `maxSum` é atualizado com o valor de `currentSum`.
 * 
 * @param row Ponteiro para o nó atual que representa a linha sendo explorada na chamada recursiva.
 * @param visited Vetor que indica quais colunas já foram visitadas/consideradas na seleção atual.
 * @param currentSum Soma acumulada dos valores dos nós selecionados até o momento.
 * @param maxSum Ponteiro para o valor da maior soma encontrada durante a execução da função.
 * @param numRows Número total de linhas da matriz, usado para dimensionar o vetor `visited`.
 */
void calculateMaxSumUtil(Node* row, int* visited, int currentSum, int* maxSum, int numRows);

/**
 * @brief Limpa o buffer de entrada do stdin.
 * 
 * Esta função lê e descarta caracteres do buffer de entrada até que um caractere de nova linha ('\n')
 * ou o fim do arquivo (EOF) seja encontrado. É útil para remover caracteres indesejados ou não lidos
 * após uma entrada de usuário, garantindo que leituras subsequentes de entrada funcionem como esperado.
 */
void clearInputBuffer();

#endif