#include <stdio.h>
#define TAM 500

/**
 * @brief Função utilizada para definir os vários tipos da nossa Stack.
 * 
 */
typedef enum {
  CHAR,
  LONG,
  DBL,
  STR,
} TYPE;


/**
 * @brief Função utilizada para dar o tipo ao que é pretendido.
 * 
 * 
*/
typedef struct 
{
  TYPE type;
  union
  {
    long l;
    double d;
    char c;
    char *s;
  }var;
} STACK_ELEM;

typedef struct
{
  STACK_ELEM stack[TAM];
  int sp;//indica onde está o topo da stack
} STACK;


/** 
 * \brief Função geral que insere um elemento no topo da Stack.
*/
void push (STACK *s, STACK_ELEM x);

/**
 * \brief Função que lê os carateres relativos à modificação da stack e modifica-a.
 *
 * 
 * @param s 
 * @param token
*/
int stackman (STACK *s, char *token);

/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o num LONG, fazendo push após a conversão.
 * 
 * @param s
 */
int converteSTAckTopTOLONG (STACK *s);

/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o num DOUBLE, fazendo push após a conversão.
 * 
 * @param s 
 */
int converteStackTopTODOUBLE (STACK *s);

/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o num CHAR, fazendo push após a conversão.
 * 
 * @param s 
 */
int converteStackTopTOCHAR (STACK *s);

/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o numa STR, fazendo push após a conversão.
 * 
 * @param s 
 */
int converteStackTopTOSTR (STACK *s);

/**
 * \brief Função que lê os carateres relativos às conversões e converte o elemento no topo da stack.
 * 
 * 
 * @param s 
 * @param token
 */
int convertStackTop (STACK *s, char *token);

/**
 * \brief Função que lê os carateres relativos à leitura da stack.
 * 
 * 
 *
 * @param s 
 * @param token
 * @param lista
 */
int lerStack(STACK *s, char *token, STACK_ELEM**lista);

/**
 * \brief Função que trabalha com bits individuais (bitwise) e é relativa às operações "E", "ou", "xor" e "not"
 * 
 * 
 * @param s 
 * @param token
 */
int bitwise(STACK *s, char *token);

/**
 * \brief Função relativa à operação módulo
 * 
 * 
 * @param s
 * @param token
 */
int modulo(STACK *s, char *token);

/**
 * \brief Função relativa à operação da soma
 * 
 * 
 * @param s 
 * @param token
 */
int soma(STACK *s, char *token);

/**
 * \brief Função relativa à operação da subtração
 * 
 * 
 * @param s
 * @param token
 */
int subtracao(STACK *s, char *token);

/**
 * \brief Função relativa à operação da multiplicação
 * 
 * 
 * @param s
 * @param token 
 */
int multiplicacao(STACK *s, char *token);

/**
 * \brief Função relativa à operação da divisão
 * 
 * 
 * @param s
 * @param token
 */
int divisao(STACK *s, char *token);

/**
 * \brief Função auxiliar que introduz as potências
 * 
 * 
 * @param num
 * @param exp
 */
long potencia(long num, long exp);

/**
 * \brief Função relativa à operação da exponenciação 
 * 
 * 
 * @param s
 * @param token
 */
int exponenciacao(STACK *s, char *token);

/**
 * \brief Função relativa à incrementação de um valor
 * 
 * 
 * @param s
 * @param token
 */
int incrementar(STACK *s, char *token);

/**
 * \brief Função relativa à decrementação de um valor
 * 
 * 
 * @param s
 * @param token
 */
int decrementar(STACK *s, char *token);

/**
 * \brief Função que inicializa as variáveis
 * 
 * 
 *
 * @param s
 * @param token
 * @param vars
 */
int variables(STACK *s, char *token, STACK_ELEM **vars);

/**
 * \brief Função que carrega as variáveis
 * 
 * 
 *
 * @param s
 * @param token
 * @param vars
 */
int carregavar(STACK *s, char *token, STACK_ELEM **vars);

/**
 * \brief  Função relativa à operação de "maior" 
 *
 * @param s 
 */
void maior(STACK *s);

/**
 * \brief  Função relativa à operação de "menor" 
 * @param s 
 */
void menor(STACK *s);

/**
 * \brief  Função relativa à operação de "menor" 
 *
 * @param s 
 */
void menor(STACK *s);

/**
 * \brief  Função relativa à operação de "maoir" que insere o maoir de dois valores na stack
 *
 * @param s 
 */
void ebigger(STACK *s);

/**
 * \brief  Função relativa à operação de "menor" que insere o menor de dois valores na stack
 *
 * @param s 
 */
void esmaller(STACK *s);

/**
 * \brief Função que analisa os valores e retorna o maior ou menor (dependendo do sinal) para ser colocado no topo da stack 
 *
 * @param s 
 */
int eorder(STACK *s, char *token);

/**
 * \brief Função relativa à operação "contrário"
 *
 * @param s 
 */
int opContrario(STACK *s, char *token);

/**
 * \brief  Função relativa ao "ou" com shortcut e sua respetiva auxiliar
 *
 * @param s 
 */
void orShortcut(STACK *s);

/**
 * \brief  Função relativa ao "e" com shortcut e sua respetiva auxiliar
 *
 * @param s 
 */
void andShortcut(STACK *s);

/**
 * \brief  Função relativa ao "shortcut" e a sua respetiva auxiliar
 *
 *
 * @param s 
 * @param token
 */
int shortcut(STACK *s, char *token);

/**
 * \brief  Função relativa ao "If-Then-Else" e a sua respetiva auxiliar
 *
 * @param s 
 */
void ifTEAux(STACK *s);

/**
 * \brief Função que dá push para a stack do valor de acordo com o seu type e va
 * 
 * 
 * @param s
 * @param token
 */
int val(STACK *s, char *token);

/**
 * \brief  Função que imprime a stack
 *
 * @param s 
 */
void printstack(STACK *s);

/**
 * \brief  Função principal do programa responsavél por gerir a stack
 */
int main();