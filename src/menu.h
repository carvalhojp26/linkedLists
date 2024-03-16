#ifndef MENU_H
#define MENU_H

/**
 * @brief Solicita ao usuário valores para atualizar na matriz e aplica a atualização.
 * 
 * Interage com o usuário para obter um valor existente na matriz (`oldValue`) e o valor que deve substituí-lo (`newValue`).
 * Em seguida, chama a função `updateValue` para procurar na matriz o `oldValue` e substituí-lo pelo `newValue`. Após a conclusão
 * da atualização, uma mensagem é exibida para informar ao usuário que a operação foi realizada com sucesso. Se o `oldValue` não for
 * encontrado na matriz, `updateValue` cuidará de informar ao usuário.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional que representa a matriz.
 */
void requestUpdateValue(Node* head);

/**
 * @brief Solicita ao usuário a inserção de uma nova linha na matriz e adiciona a linha.
 * 
 * Primeiro, verifica se a lista está vazia. Se não estiver, a função obtém as dimensões atuais da matriz
 * para determinar quantos valores o usuário deve inserir para a nova linha. Em seguida, solicita ao usuário
 * que forneça esses valores, um por um, armazenando-os em um array temporário. Após coletar todos os valores,
 * chama a função `addRow` para adicionar efetivamente a nova linha à matriz com os valores fornecidos pelo usuário.
 * A função retorna o ponteiro atualizado para a cabeça da lista ligada bidimensional.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita.
 * @return Ponteiro para o nó cabeça atualizado da lista ligada bidimensional.
 */
Node* requestAddRow(Node* head, const char* filename);

/**
 * @brief Solicita ao usuário a inserção de uma nova coluna na matriz e a adiciona.
 * 
 * Após verificar que a lista não está vazia, a função obtém as dimensões atuais da matriz para determinar
 * quantos valores são necessários para a nova coluna, equivalente ao número de linhas atual. O usuário é
 * então solicitado a fornecer os valores para a nova coluna, que são lidos e armazenados em um array temporário.
 * Utilizando esses valores, a função `addColumn` é chamada para adicionar a nova coluna à matriz. Por fim, a
 * função informa ao usuário que a nova coluna foi adicionada com sucesso.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita após a adição da coluna.
 */
void requestAddColumn(Node* head, const char* filename);

/**
 * @brief Solicita ao usuário a remoção de uma linha específica da matriz.
 * 
 * Primeiro, verifica se a matriz não está vazia. Se não estiver, obtém as dimensões atuais da matriz
 * para informar ao usuário quantas linhas existem. O usuário é solicitado a inserir o índice da linha
 * que deseja remover. A função verifica se o índice fornecido é válido. Se for, a função `removeRow`
 * é chamada para remover a linha selecionada, e o ponteiro para a cabeça da lista é atualizado caso
 * necessário. Uma mensagem confirma a remoção bem-sucedida da linha.
 * 
 * @param head Referência ao ponteiro para o nó cabeça da lista ligada bidimensional.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita.
 */
void requestRemoveRow(Node** head, const char* filename);

/**
 * @brief Solicita ao usuário a remoção de uma coluna específica da matriz.
 * 
 * Primeiro, verifica se a matriz não está vazia. Se não estiver, a função obtém as dimensões atuais da matriz
 * para informar ao usuário o número de colunas disponíveis. Em seguida, solicita ao usuário que forneça o índice
 * da coluna que deseja remover. A função verifica a validade do índice fornecido. Se válido, `removeColumn` é
 * chamada para remover a coluna selecionada da matriz. Após a remoção, a função exibe uma mensagem confirmando
 * o sucesso da operação.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param filename Nome do arquivo onde a matriz atualizada será escrita.
 */
void requestRemoveColumn(Node* head, const char* filename);

/**
 * @brief Solicita o cálculo da soma máxima possível em uma matriz quadrada.
 * 
 * Verifica inicialmente se a matriz não está vazia. Em seguida, ajusta a matriz para garantir
 * que seja quadrada, adicionando linhas ou colunas de zeros se necessário. Após o ajuste, verifica
 * novamente se a matriz é quadrada. Se sim, procede com o cálculo da soma máxima usando a função
 * `calculateMaxSum`, que explora todas as combinações possíveis de seleção de valores sem repetir
 * linhas ou colunas. O resultado é exibido ao usuário. Esta função pode ser utilizada para ajustar
 * a matriz e realizar operações relacionadas a arquivos, como salvar a matriz ajustada, se necessário.
 * 
 * @param head Ponteiro para o nó cabeça da lista ligada bidimensional representando a matriz.
 * @param filename Nome do arquivo que pode ser usado para operações relacionadas ao arquivo, se necessário.
 */
void requestCalculateMaxSum(Node* head, const char* filename);

/**
 * @brief Exibe o menu de opções para o usuário e obtém a escolha feita.
 * 
 * Limpa a tela e exibe um menu de opções numéricas para diferentes operações que podem ser realizadas
 * na matriz (como visualizar a tabela de valores, modificar elementos, adicionar/remover linhas/colunas,
 * e calcular a soma máxima). O usuário é solicitado a escolher uma opção, e a entrada é validada para
 * garantir que seja um número correspondente a uma das opções. A função repete a solicitação até que
 * uma entrada válida seja fornecida.
 * 
 * @return A escolha do usuário como um inteiro, correspondendo a uma das opções do menu.
 */
int showMenuAndGetChoice();

/**
 * @brief Limpa a tela do console.
 * 
 * Executa o comando apropriado para limpar a tela do console, dependendo do sistema operacional em uso.
 * Utiliza "cls" para Windows (definido por _WIN32) e "clear" para sistemas Unix-like (como Linux e macOS).
 * Esta função facilita a visualização das informações atualizadas no console, removendo saídas anteriores.
 */
void clearScreen();

/**
 * @brief Aguarda até que o usuário pressione Enter.
 * 
 * Exibe uma mensagem solicitando que o usuário pressione Enter para continuar. Primeiro, limpa o buffer
 * de entrada para remover qualquer caractere residual que possa ter sido deixado por entradas anteriores.
 * Então, entra em um loop de espera até que o usuário pressione Enter, garantindo que o programa
 * só prossiga após a ação explícita do usuário. Essa função é útil para pausar a execução entre
 * diferentes seções de um menu ou após a execução de uma tarefa, permitindo que o usuário tenha tempo
 * para ler as informações exibidas antes de continuar.
 */
void waitForUserInput();

#endif 