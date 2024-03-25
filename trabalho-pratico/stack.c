#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include <assert.h>

/**
 * \brief
 * 
 * 
 * @param  
 * @return
 */

void handle(STACK *s, char *token, STACK_ELEM **lista);

STACK *newStack()
{
  return calloc(1, sizeof(STACK));
}


/** 
 * \brief Função geral que insere um elemento no topo da Stack.
*/
void push(STACK *s, STACK_ELEM x)
{
  s->stack[s->sp++] = x;
}

STACK_ELEM pop(STACK *s)
{
  assert(s->sp > 0);
  s->sp--;
  STACK_ELEM ret = s->stack[s->sp];
  return ret; 
}

/**
 * @brief Função que lê os carateres relativos à modificação da stack e modifica-a.
 *
 * 
 * @param s 
 * @param token
*/

int stackman(STACK *s, char *token)
{
  if (s->stack != NULL && strcmp(token, "@") == 0) //roda os 3 elementos no topo da stack
  {
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);
    STACK_ELEM z = pop(s);

    push(s, y);
    push(s, x);
    push(s, z);

    return 1;
  }

  if (s->stack != NULL && strcmp(token, "_") == 0) //duplica o no topo da stack
  {
    STACK_ELEM x = pop(s);
    
    push(s, x);
    push(s, x);

    return 1;
  }
  if (s->stack != NULL && strcmp(token, "$") == 0) //copia n-ésimo elemento para o topo da stack
  {
    if (s->stack[0].type != LONG)
    {
      fprintf(stderr, "erro\n");
      exit(1);
    }
    else 
    {
      STACK_ELEM x = pop(s);
      long id = x.var.l;
      push(s, s->stack[(s->sp)-id-1]);
    }
    return 1;
  }
  if (s->stack != NULL && strcmp(token, ";") == 0) //pop
  {
    pop(s);
    return 1;
  }
  if (s->stack != NULL && strcmp(token, "\\") == 0) //troca os dois elementos do topo da stack
  {
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

    push(s, x);
    push(s, y);

    return 1;
  }
  return 0;
}


/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o num LONG, fazendo push após a conversão.
 * 
 * 
 * @param s 
 */

int converteSTAckTopTOLONG(STACK *s)
{
  STACK_ELEM x = pop(s);
    if(x.type==CHAR) 
    {
      int w = (int)(x.var.c);
      x.type=LONG;
      x.var.l = w;
      push(s, x);
      return 1;
    }
    if(x.type==DBL)
    {
      int w = (int) (x.var.d);
      x.type=LONG;
      x.var.l = w;
      push(s, x);
      return 1;
    }
    if(x.type==STR)
    { 
      char *endptrStrl;
      long w = strtol(x.var.s, &endptrStrl,  10);
      if(*endptrStrl=='\0')
      { 
        x.type=LONG;
        x.var.l=w;
        push(s, x);
        return 1;
      }
      
    }
    else 
    {
      push(s, x);//quando o topo da stack já é um int
      return 1;
    }
    return 0;
}


/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o num DOUBLE, fazendo push após a conversão.
 * 
 * 
 * @param s 
 */

int converteStackTopTODOUBLE(STACK *s)
{
  STACK_ELEM x = pop(s);
    if(x.type==CHAR) 
    {
      double w = (double)(x.var.c);
      x.type=DBL;
      x.var.d = w;
      push(s, x);
      return 1;
    }
    if(x.type==LONG)
    {
      double w = (double)(x.var.l);
      x.type=DBL;
      x.var.d = w;
      push(s, x);
      return 1;
    }
    if(x.type==STR)
    {
      char *endptrStrd;
      double w = strtol(x.var.s, &endptrStrd,  10);
      if(*endptrStrd=='\0')
      {
        x.type=DBL;
        x.var.d=w;
        push(s, x);
        return 1;
      }
      //return 1; 
    }
    else 
    {
      push(s, x);//quando o topo da stack já é um double
      return 1;
    }
  return 0;
}

/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o num CHAR, fazendo push após a conversão.
 * 
 *  
 * @param s 
 */

int converteStackTopTOCHAR(STACK *s)
{
  STACK_ELEM x = pop(s);
    if(x.type==LONG) 
    {
      char w = (char)(x.var.l);
      x.type=CHAR;
      x.var.c = w;
      push(s, x);
      return 1;
    }
    if(x.type==DBL)
    {
      char w = (char)(x.var.d);
      x.type=CHAR;
      x.var.c = w;
      push(s, x);
      return 1;
    }
    /*if(x.type==STR)
    {
      //converter string para char
    }*/
    else
    { 
      push(s, x);//quando o topo da stack já é um char
      return 1;
    }
    return 0;
}


/**
 * \brief Função que faz pop do elemento no topo da stack e converte-o numa STR, fazendo push após a conversão.
 * 
 * 
 * @param s 
 */

int converteStackTopTOSTR(STACK *s)
{
  STACK_ELEM x = pop(s);
    if(x.type==CHAR) 
    {
      //char string[TAM];
      char* str = malloc(sizeof(char) * 128);
      sprintf(str,"%c",x.var.c);
      x.type=STR;
      x.var.s = str;
      push(s, x);
      return 1;
    }
    if(x.type==LONG)
    {
      //char string[TAM];
      char *str = malloc(sizeof(char) * 128);
      sprintf(str,"%ld",x.var.l);
      x.type=STR;
      x.var.s = str;
      push(s, x);
      
      return 1;
    }
    if(x.type==DBL)
    {
      //char string[TAM];
      char *str = malloc(sizeof(char) * 128);
      sprintf(str,"%lf",x.var.d);
      x.type=STR;
      x.var.s = str;
      push(s, x);
      return 1;
    }
    else 
    {
      push(s, x);//quando o topo da stack já é uma string
      return 1;
    }
  return 0;
}

/**
 * \brief Função que lê os carateres relativos às conversões e converte o elemento no topo da stack.
 * 
 * 
 * @param s 
 * @param token
 */

int convertStackTop(STACK *s, char *token)
{
  int r=0;
  if(s->stack != NULL && strcmp(token, "i") == 0) r = converteSTAckTopTOLONG(s);
  
  else if(s->stack != NULL && strcmp(token, "f") == 0) r =  converteStackTopTODOUBLE(s);
  
  else if(s->stack != NULL && strcmp(token, "c") == 0) r =  converteStackTopTOCHAR(s);
  
  else if(s->stack != NULL && strcmp(token, "s") == 0) r =  converteStackTopTOSTR(s);

  return r;  
}

/**
 * \brief Função que lê os carateres relativos à leitura da stack.
 * 
 * 
 * @param s 
 * @param token
 * @param lista
 */

int lerStack(STACK *s, char *token, STACK_ELEM**lista)
{
  if(s->stack != NULL && strcmp(token, "p")==0)
  { 
    STACK_ELEM x = pop(s);
    if(x.type==DBL) printf("%lf", x.var.d);
    if(x.type==LONG) printf("%ld", x.var.l);
    if(x.type==CHAR) printf("%c", x.var.c);
    if(x.type==STR) printf("%s",x.var.s);

    return 1;
  }

  if(s->stack != NULL && strcmp(token, "l")==0)
  { 
    char line[BUFSIZ];
    char token2[BUFSIZ];
    
     if (fgets(line, BUFSIZ, stdin) != NULL)
  {
    while (sscanf(line, "%s%[^\n]", token2, line) == 2)
    {
      handle(s, token2, lista);
    }
    handle(s, token2, lista);
    //return 1;
    }
  }

  if(s->stack !=NULL && strcmp(token, "t")==0)
  {
    char line[BUFSIZ];
    STACK_ELEM x;
    while(fgets(line, BUFSIZ, stdin)!=NULL)
    { 
      x.type=STR;
      x.var.s=line;
    }
    push(s, x);
    return 1;
  }
  return 0;
}

/**
 * \brief Função que lê os carateres relativos à leitura da stack.
 * 
 * 
 * @param x 
 * @param y
 */

TYPE typemaior(STACK_ELEM x, STACK_ELEM y)
{ 
  TYPE t = CHAR;
  if(x.type==y.type) t=x.type;
  if((x.type==LONG&&y.type==CHAR) || (x.type==CHAR && y.type==LONG)) t=LONG;
  if((x.type==DBL &&y.type==CHAR) || (x.type==CHAR && y.type==DBL)) t=DBL ;
  if((x.type==LONG && y.type==DBL)|| (x.type==DBL && y.type==LONG)) t=DBL;

  return t; 

}

/**
 * \brief Função que trabalha com bits individuais (bitwise) e é relativa às operações "E", "ou", "xor" e "not"
 * 
 * 
 * @param s 
 * @param token
 */

int bitwise(STACK *s, char *token)
{
  if(strcmp(token, "&")==0) 
    {  
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        STACK_ELEM w;
        w.type=LONG;
        w.var.l=(y.var.l & x.var.l);

        push(s, w);
        return 1;
    }
    if(strcmp(token, "|")==0)
    {  
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        STACK_ELEM w;
        w.type=LONG;
        w.var.l=(y.var.l | x.var.l);
        
        push(s, w);
        return 1;
    }
    if(strcmp(token, "^")==0)
    {   
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        STACK_ELEM w;
        w.type=LONG;
        w.var.l=(y.var.l ^ x.var.l);
        
        push(s, w);
        return 1;
    }
    if(strcmp(token, "~")==0)
    {
      STACK_ELEM x = pop(s);

      STACK_ELEM w;
      w.type=LONG;
      w.var.l=(~(x.var.l));

      push(s, w);
      return 1;
    }
    return 0;
}

/**
 * \brief Função relativa à operação módulo
 * 
 * 
 * @param s
 * @param token
 */

int modulo(STACK *s, char *token)
{
  if(strcmp(token, "%")==0)
  {
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);
        
    STACK_ELEM w;
    w.type=LONG;
    w.var.l=(y.var.l%x.var.l);
        
    push(s, w);
    return 1;
  }
  return 0;
}

/**
 * \brief Função relativa à operação da soma
 * 
 * 
 * @param s 
 * @param token
 */

int soma(STACK *s, char *token)
{   
    if(strcmp(token,"+")==0) 
    {   

        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        if(typemaior(x, y)==LONG)//ou ambos são long ou um é long e outro é char 
        {  
          STACK_ELEM w ;
          w.type = LONG;
          if(x.type==LONG && y.type != LONG) w.var.l = (long)(y.var.c) + (x.var.l);//se o type maior é long e y não é long entao y tem de ser char  
          else if(x.type != LONG && y.type == LONG) w.var.l=(y.var.l) + (long)(x.var.c);
          else w.var.l = y.var.l + x.var.l;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==DBL)
        {  
          STACK_ELEM w;
          w.type = DBL;
          if(x.type==DBL && y.type==LONG) w.var.d=(double)(y.var.l) +(x.var.d);
          else if(x.type==DBL&&y.type==CHAR) w.var.d=(double)(y.var.c)+(x.var.d);
          else if(x.type==LONG &&y.type==DBL) w.var.d=(y.var.d) + (double)(x.var.l);
          else if(x.type==CHAR&&y.type==DBL) w.var.d=(y.var.d) + (double)(x.var.c);
          else w.var.d=y.var.d + x.var.d;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==CHAR)//quando o maior tipo é char significa que ambos os stack_elem sao char
        {  
          STACK_ELEM w;
          w.type = CHAR;
          w.var.c = (y.var.c + x.var.c);
          push(s, w);
          return 1;
        }
    }
    return 0;
}   

/**
 * \brief Função relativa à operação da subtração
 * 
 * 
 * @param s
 * @param token
 */
    
int subtracao(STACK *s, char *token)
{   
    if(strcmp(token,"-")==0) 
    {   

        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        if(typemaior(x, y)==LONG)//ou ambos são long ou um é long e outro é char 
        {  
          STACK_ELEM w ;
          w.type = LONG;
          if(x.type==LONG && y.type != LONG) w.var.l = (long)(y.var.c) - (x.var.l);//se o type maior é long e y não é long entao y tem de ser char  
          else if(x.type != LONG && y.type == LONG) w.var.l=(y.var.l) - (long)(x.var.c);
          else w.var.l = y.var.l - x.var.l;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==DBL)
        {  
          STACK_ELEM w;
          w.type = DBL;
          if(x.type==DBL && y.type==LONG) w.var.d=(double)(y.var.l) -(x.var.d);
          else if(x.type==DBL&&y.type==CHAR) w.var.d=(double)(y.var.c)-(x.var.d);
          else if(x.type==LONG &&y.type==DBL) w.var.d=(y.var.d)-(double)(x.var.l);
          else if(x.type==CHAR&&y.type==DBL) w.var.d=(y.var.d)-(double)(x.var.c);
          else w.var.d=y.var.d - x.var.d;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==CHAR)//quando o maior tipo é char significa que ambos os stack_elem sao char
        {  
          STACK_ELEM w;
          w.type = CHAR;
          w.var.c = (y.var.c - x.var.c);
          push(s, w);
          return 1;
        }
      return 1;
    }
    return 0;
}    

/**
 * \brief Função relativa à operação da multiplicação
 * 
 * 
 * @param s
 * @param token 
 */

int multiplicacao(STACK *s, char *token)
{   
    if(strcmp(token,"*")==0) 
    {   

        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        if(typemaior(x, y)==LONG)//ou ambos são long ou um é long e outro é char 
        {  
          STACK_ELEM w ;
          w.type = LONG;
          if(x.type==LONG && y.type != LONG) w.var.l = (long)(y.var.c) * (x.var.l);//se o type maior é long e y não é long entao y tem de ser char  
          else if(x.type != LONG && y.type == LONG) w.var.l=(y.var.l) * (long)(x.var.c);
          else w.var.l = y.var.l * x.var.l;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==DBL)
        {  
          STACK_ELEM w;
          w.type = DBL;
          if(x.type==DBL && y.type==LONG) w.var.d=(double)(y.var.l) *(x.var.d);
          else if(x.type==DBL&&y.type==CHAR) w.var.d=(double)(y.var.c)*(x.var.d);
          else if(x.type==LONG &&y.type==DBL) w.var.d=(y.var.d) * (double)(x.var.l);
          else if(x.type==CHAR&&y.type==DBL) w.var.d=(y.var.d) * (double)(x.var.c);
          else w.var.d=y.var.d * x.var.d;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==CHAR)//quando o maior tipo é char significa que ambos os stack_elem sao char
        {  
          STACK_ELEM w;
          w.type = CHAR;
          w.var.c = (y.var.c * x.var.c);
          push(s, w);
          return 1;
        }
    }
    return 0;
}    

/**
 * \brief Função relativa à operação da divisão
 * 
 * 
 * @param s
 * @param token
 */

int divisao(STACK *s, char *token)
{   
    if(strcmp(token,"/")==0) 
    {   

        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        if(typemaior(x, y)==LONG)//ou ambos são long ou um é long e outro é char 
        {  
          STACK_ELEM w ;
          w.type = LONG;
          if(x.type==LONG && y.type != LONG) w.var.l = (long)(y.var.c) / (x.var.l);//se o type maior é long e y não é long entao y tem de ser char  
          else if(x.type != LONG && y.type == LONG) w.var.l=(y.var.l) / (long)(x.var.c);
          else w.var.l = y.var.l / x.var.l;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==DBL)
        {  
          STACK_ELEM w;
          w.type = DBL;
          if(x.type==DBL && y.type==LONG) w.var.d=(double)(y.var.l)/(x.var.d);
          else if(x.type==DBL&&y.type==CHAR) w.var.d=(double)(y.var.c)/(x.var.d);
          else if(x.type==LONG &&y.type==DBL) w.var.d=(y.var.d) / (double)(x.var.l);
          else if(x.type==CHAR&&y.type==DBL) w.var.d=(y.var.d) / (double)(x.var.c);
          else w.var.d=y.var.d / x.var.d;
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==CHAR)//quando o maior tipo é char significa que ambos os stack_elem sao char
        {  
          STACK_ELEM w;
          w.type = CHAR;
          w.var.c = (y.var.c / x.var.c);
          push(s, w);
          return 1;
        }
        return 1;
    }
    return 0;
}  

/**
 * \brief Função auxiliar que introduz as potências
 * 
 * 
 * @param num
 * @param exp
 */

long potencia(long num, long exp)
{   
    long total=1, i;
    for(i = 1; i<=exp;i++)
        total *= num;
    return total;
}

/**
 * \brief Função relativa à operação da exponenciação 
 * 
 * 
 * @param s
 * @param token
 */

int exponenciacao(STACK *s, char *token)
{
  if(strcmp(token,"#")==0) 
    {   

        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        
        if(typemaior(x, y)==LONG)//ou ambos são long ou um é long e outro é char 
        {  
          STACK_ELEM w ;
          w.type = LONG;
          if(x.type==LONG && y.type != LONG) w.var.l = potencia((long)(y.var.c) , (x.var.l));//se o type maior é long e y não é long entao y tem de ser char  
          else if(x.type != LONG && y.type == LONG) w.var.l=potencia((y.var.l), (long)(x.var.c));
          else w.var.l = potencia(y.var.l, x.var.l);
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==DBL)
        {  
          STACK_ELEM w;
          w.type = DBL;
          if(x.type==DBL && y.type==LONG) w.var.d=pow((double)(y.var.l), (x.var.d));
          else if(x.type==DBL&&y.type==CHAR) w.var.d=pow((double)(y.var.c), (x.var.d));
          else if(x.type==LONG &&y.type==DBL) w.var.d=pow((y.var.d) ,(double)(x.var.l));
          else if(x.type==CHAR&&y.type==DBL) w.var.d=pow((y.var.d), (double)(x.var.c));
          else w.var.d=pow(y.var.d , x.var.d);
          push(s, w);
          return 1;
        }
        if(typemaior(x, y)==CHAR)//quando o maior tipo é char significa que ambos os stack_elem sao char
        {  
          STACK_ELEM w;
          w.type = CHAR;
          long h = potencia((long)y.var.c , (long)x.var.c);
          char t = (char) h;
          w.var.c=t;
          push(s, w);
          return 1;
        }
    }
    return 0;
}    

/**
 * \brief Função relativa à incrementação de um valor
 * 
 * 
 * @param s
 * @param token
 */

int incrementar(STACK *s, char *token)
{    
  if(strcmp(token, ")")==0) 
  {   ///operação incrementar
    STACK_ELEM x = pop(s); 
    if(x.type==LONG)
    {
      x.var.l=(x.var.l) +1;
      push(s, x);
      return 1;
    }
    if(x.type==DBL)
    {
      STACK_ELEM w;
      w.type=DBL;
      w.var.d=(x.var.d) + 1.0;
      push(s, w);
      return 1;
    }
    if(x.type==CHAR)
    {
      STACK_ELEM w;
      w.type=CHAR;
      long h = ((long)(x.var.c)) + 1;
      char t = (char) h;
      w.var.c=t;
      push(s, w);
      return 1;  
    }
    return 1;
  }
  return 0;
}

/**
 * \brief Função relativa à decrementação de um valor
 * 
 * 
 * @param s
 * @param token
 */

int decrementar(STACK *s, char *token)
{
  if(strcmp(token, "(")==0) 
  {   ///operação incrementar
    STACK_ELEM x = pop(s); 
    if(x.type==LONG)
    {
      x.var.l=(x.var.l) -1;
      push(s, x);
      return 1;
    }
    if(x.type==DBL)
    {
      STACK_ELEM w;
      w.type=DBL;
      w.var.d=(x.var.d) - 1.0;
      push(s, w);
      return 1;
    }
    if(x.type==CHAR)
    {
      STACK_ELEM w;
      w.type=CHAR;
      long h = ((long)x.var.c) - 1;
      char t =(char) h;
      w.var.c = t;
      push(s, w);
      return 1;  
    }
    return 1;
  }
  return 0;
}

/**
 * \brief Função que crias os registos
 */

static STACK_ELEM ** cria_registos()
{   
    static STACK_ELEM *variaveis[26];
    
    for(int i=0; i <= 25; i++)  
        variaveis[i]=malloc(sizeof(STACK_ELEM));
    

variaveis['A'-65]->type = LONG;
variaveis['A'-65]->var.l = 10;
variaveis['B'-65]->type = LONG;
variaveis['B'-65]->var.l=11;
variaveis['C'-65]->type = LONG;
variaveis['C'-65]->var.l = 12;
variaveis['D'-65]->type = LONG;
variaveis['D'-65]->var.l = 13;
variaveis['E'-65]->type = LONG;
variaveis['E'-65]->var.l = 14;
variaveis['F'-65]->type = LONG;
variaveis['F'-65]->var.l = 15;
variaveis['N'-65]->type = CHAR;
variaveis['N'-65]->var.c = '\n';
variaveis['S'-65]->type = CHAR;
variaveis['S'-65]->var.c = ' '; 
variaveis['X'-65]->type = LONG;
variaveis['X'-65]->var.l = 0;
variaveis['Y'-65]->type = LONG;
variaveis['Y'-65]->var.l = 1;
variaveis['Z'-65]->type = LONG;
variaveis['Z'-65]->var.l = 2;
    
return variaveis; 
}    

/**
 * \brief Função que copia um elemento da stack
 */

STACK_ELEM * copia_Stack_ELEM(STACK_ELEM x)
{
    STACK_ELEM * cpy = malloc(sizeof(STACK_ELEM));

    if(x.type==LONG) 
    {
        cpy->type=x.type;
        cpy->var.l = x.var.l;
        return cpy;
    }
    if(x.type==DBL)
    {
        cpy->type = x.type;
        cpy->var.d = x.var.d;
        return cpy;
    }
    if(x.type==CHAR)
    {
        cpy->type=x.type;
        cpy->var.c=x.var.c;
        return cpy;
    }
    
    return cpy;
}

/**
 * \brief Função que inicializa as variáveis
 * 
 * 
 * @param s
 * @param token
 * @param vars
 */

int variables(STACK *s, char *token, STACK_ELEM **vars)
{   
    if(token[0] >='A' && token[0]<='Z')
    {
        STACK_ELEM *novo=malloc(sizeof(STACK_ELEM));
        
        novo=copia_Stack_ELEM(*vars[token[0]-'A']);
        push(s,*novo);
        return 1;
    }
    return 0; 
}

/**
 * \brief Função que carrega as variáveis
 * 
 * 
 * @param s
 * @param token
 * @param vars
 */

int carregavar(STACK *s, char *token, STACK_ELEM **vars)
{   
    if(token[0]==':' && (token[1]>='A' && token[1]<='Z'))  
    {    
            
            STACK_ELEM x;
            x=s->stack[s->sp-1]; 
            vars[token[1]-'A'] = copia_Stack_ELEM(x);
        return 1;
    }
    return 0;
}


/**
 * \brief  Função relativa à operação de "maior" 
 *
 * @param s 
 */

void maior(STACK *s)
{   
    int ret = 0; 
    
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

        if(typemaior(x, y)==LONG)
        {
            if(x.type==LONG && y.type != LONG)
            {
                if((long)(y.var.c)>(x.var.l)) ret = 1;
                
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }
            else if(x.type != LONG && y.type == LONG) 
            {
                if((y.var.l)>(long)(x.var.c)) ret = 1;
                
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }
            else 
            {
                if(y.var.l > x.var.l) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
        }
        else if(typemaior(x, y)==DBL)
        {
            if(x.type==DBL && y.type==LONG)
            {
                if((double)(y.var.l)>(x.var.d)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }

            else if(x.type==DBL&&y.type==CHAR) 
            {
                if((double)(y.var.c)>(x.var.d)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
            
            else if(x.type==LONG &&y.type==DBL) 
            {
                if((y.var.d)>(double)(x.var.l)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }

            else if(x.type==CHAR&&y.type==DBL) 
            {
                if((y.var.d)>(double)(x.var.c)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
            else 
            {
                if(y.var.d > x.var.d) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
          
        }
        else//caso em que ambos são char
        {
            if(y.var.c > x.var.c) ret = 1;
            STACK_ELEM w;
            w.type=LONG;
            w.var.l=ret;
            push(s, w);
        } 

}


/**
 * \brief  Função relativa à operação de "menor" 
 *
 * @param s 
 */

void menor(STACK *s)
{   
    int ret = 0; 
    
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

        if(typemaior(x, y)==LONG)
        {
            if(x.type==LONG && y.type != LONG)
            {
                if((long)(y.var.c)<(x.var.l)) ret = 1;
                
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }
            else if(x.type != LONG && y.type == LONG) 
            {
                if((y.var.l)<(long)(x.var.c)) ret = 1;
                
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }
            else 
            {
                if(y.var.l< x.var.l) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
        }
        else if(typemaior(x, y)==DBL)
        {
            if(x.type==DBL && y.type==LONG)
            {
                if((double)(y.var.l)<(x.var.d)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }

            else if(x.type==DBL&&y.type==CHAR) 
            {
                if((double)(y.var.c)<(x.var.d)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
            
            else if(x.type==LONG &&y.type==DBL) 
            {
                if((y.var.d)<(double)(x.var.l)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }

            else if(x.type==CHAR&&y.type==DBL) 
            {
                if((y.var.d)<(double)(x.var.c)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
            else 
            {
                if(y.var.d <x.var.d) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
          
        }
        else//caso em que ambos são char
        {
            if(y.var.c < x.var.c) ret = 1;
            STACK_ELEM w;
            w.type=LONG;
            w.var.l=ret;
            push(s, w);
        } 
}


/**
 * \brief  Função relativa à operação de "igual" 
 *
 * @param s 
 */

void igual(STACK *s)
{   
    int ret = 0; 
    
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

        if(typemaior(x, y)==LONG)
        {
            if(x.type==LONG && y.type != LONG)
            {
                if((long)(y.var.c)==(x.var.l)) ret = 1;
                
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }
            else if(x.type != LONG && y.type == LONG) 
            {
                if((y.var.l)==(long)(x.var.c)) ret = 1;
                
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }
            else 
            {
                if(y.var.l==x.var.l) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
        }
        else if(typemaior(x, y)==DBL)
        {
            if(x.type==DBL && y.type==LONG)
            {
                if((double)(y.var.l)==(x.var.d)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w); 
            }

            else if(x.type==DBL&&y.type==CHAR) 
            {
                if((double)(y.var.c)==(x.var.d)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
            
            else if(x.type==LONG &&y.type==DBL) 
            {
                if((y.var.d)==(double)(x.var.l)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }

            else if(x.type==CHAR&&y.type==DBL) 
            {
                if((y.var.d)==(double)(x.var.c)) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
            else 
            {
                if(y.var.d == x.var.d) ret = 1;
                STACK_ELEM w;
                w.type=LONG;
                w.var.l=ret;
                push(s, w);
            }
          
        }
        else//caso em que ambos são char
        {
            if(y.var.c == x.var.c) ret = 1;
            STACK_ELEM w;
            w.type=LONG;
            w.var.l=ret;
            push(s, w);
        } 

}



int rOrdem(STACK *s, char *token)
{
    if(strcmp(token, "=")==0) 
    {
        igual(s);
        return 1;
    }
    if(strcmp(token, "<")==0)
    {
        menor(s);
        return 1;
    }
    if(strcmp(token, ">")==0)
    {
        maior(s);
        return 1;
    }
    return 0;
}


/**
 * \brief  Função relativa à operação de "maoir" que insere o maoir de dois valores na stack
 *
 * @param s 
 */

void ebigger(STACK *s)
{
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

        if(typemaior(x, y)==LONG)
        {
            if(x.type==LONG && y.type != LONG)
            {
                if((long)(y.var.c)>(x.var.l))
                {
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=y.var.c;
                    push(s, w); 
                }
                else
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=x.var.l;
                    push(s, w);
                }
            }
            else if(x.type != LONG && y.type == LONG) 
            {
                if((y.var.l)>(long)(x.var.c))
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=y.var.l;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=x.var.c;
                    push(s, w);
                }
            }
            else 
            {
                if(y.var.l>x.var.l)
                {
                
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=y.var.l;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=x.var.l;
                    push(s, w);
                }
            }
        }
        else if(typemaior(x, y)==DBL)
        {
            if(x.type==DBL && y.type==LONG)
            {
                if((double)(y.var.l)>(x.var.d))
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=y.var.l;
                    push(s, w); 
                }
                else
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=x.var.d;
                    push(s, w); 
                }
            }

            else if(x.type==DBL&&y.type==CHAR) 
            {
                if((double)(y.var.c)>(x.var.d))
                {    
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=y.var.c;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=x.var.d;
                    push(s, w);
                }
            }
            
            else if(x.type==LONG &&y.type==DBL) 
            {
                if((y.var.d)>(double)(x.var.l))
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=y.var.d;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=x.var.l;
                    push(s, w);
                }
            }

            else if(x.type==CHAR&&y.type==DBL) 
            {
                if((y.var.d)>(double)(x.var.c))
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=y.var.d;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=x.var.c;
                    push(s, w);
                }
            }
            else 
            {
                if(y.var.d>x.var.d)
                {    
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=y.var.d;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=x.var.d;
                    push(s, w);
                }
            }
          
        }
        else//caso em que ambos são char
        {
            if(y.var.c > x.var.c)
            {
                STACK_ELEM w;
                w.type=CHAR;
                w.var.c=y.var.c;
                push(s, w);
            }

            else
            {   
                STACK_ELEM w;
                w.type=CHAR;
                w.var.c=x.var.c;
                push(s, w);
            }
        } 
}


/**
 * \brief  Função relativa à operação de "menor" que insere o menor de dois valores na stack
 *
 * @param s 
 */

void esmaller(STACK *s)
{
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

        if(typemaior(x, y)==LONG)
        {
            if(x.type==LONG && y.type != LONG)
            {
                if((long)(y.var.c)<(x.var.l))
                {
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=y.var.c;
                    push(s, w); 
                }
                else
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=x.var.l;
                    push(s, w);
                }
            }
            else if(x.type != LONG && y.type == LONG) 
            {
                if((y.var.l)<(long)(x.var.c))
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=y.var.l;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=x.var.c;
                    push(s, w);
                }
            }
            else 
            {
                if(y.var.l<x.var.l)
                {
                
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=y.var.l;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=x.var.l;
                    push(s, w);
                }
            }
        }
        else if(typemaior(x, y)==DBL)
        {
            if(x.type==DBL && y.type==LONG)
            {
                if((double)(y.var.l)<(x.var.d))
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=y.var.l;
                    push(s, w); 
                }
                else
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=x.var.d;
                    push(s, w); 
                }
            }

            else if(x.type==DBL&&y.type==CHAR) 
            {
                if((double)(y.var.c)<(x.var.d))
                {    
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=y.var.c;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=x.var.d;
                    push(s, w);
                }
            }
            
            else if(x.type==LONG &&y.type==DBL) 
            {
                if((y.var.d)<(double)(x.var.l))
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=y.var.d;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=LONG;
                    w.var.l=x.var.l;
                    push(s, w);
                }
            }

            else if(x.type==CHAR&&y.type==DBL) 
            {
                if((y.var.d)<(double)(x.var.c))
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=y.var.d;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=CHAR;
                    w.var.c=x.var.c;
                    push(s, w);
                }
            }
            else 
            {
                if(y.var.d<x.var.d)
                {    
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=y.var.d;
                    push(s, w);
                }
                else
                {
                    STACK_ELEM w;
                    w.type=DBL;
                    w.var.d=x.var.d;
                    push(s, w);
                }
            }
          
        }
        else//caso em que ambos são char
        {
            if(y.var.c < x.var.c)
            {
                STACK_ELEM w;
                w.type=CHAR;
                w.var.c=y.var.c;
                push(s, w);
            }

            else
            {   
                STACK_ELEM w;
                w.type=CHAR;
                w.var.c=x.var.c;
                push(s, w);
            }
        } 
}


/**
 * \brief Função que analisa os valores e retorna o maior ou menor (dependendo do sinal) para ser colocado no topo da stack 
 *
 * @param s 
 */
int eorder(STACK *s, char *token)
{
    if(strcmp(token, "e<")==0)
    {
        esmaller(s);
        return 1;
    }
    if(strcmp(token, "e>")==0)
    {
        ebigger(s);
        return 1;
    }

    return 0;
}


/**
 * \brief Função relativa à operação "contrário"
 *
 * @param s 
 */

int opContrario(STACK *s, char *token)
{   

    if(strcmp(token, "!")==0)
    {
        STACK_ELEM x = pop(s);
        if(x.type==LONG)
        {   
            x.var.l = !(x.var.l);
            push(s, x);
            return 1;
        }
        if(x.type==CHAR) 
        {
            STACK_ELEM w;
            w.type=LONG;
            w.var.l = !((long)x.var.c);
            push(s, w);
            return 1;
        }
        if(x.type==DBL)
        {
            x.var.d=!(x.var.d);
            push(s, x);
            return 1;
        }
    }
    return 0;
}


/**
 * \brief  Função relativa ao "ou" com shortcut e sua respetiva auxiliar
 *
 * @param s 
 */

void orShortcut(STACK *s)
{
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

        if(typemaior(x, y)==LONG)
        {
            if(x.type==LONG && y.type != LONG)
            {
                if((long)(y.var.c) != 0 && (x.var.l) !=0)
                {
                    push(s, y); 
                }
                else if((long)(y.var.c) == 0 && (x.var.l)!=0)
                {
                    push(s, y);
                }
                else push(s, x);
            }
            else if(x.type != LONG && y.type == LONG) 
            {
                if((y.var.l)!= 0 && (long)(x.var.c) != 0)
                {
                    push(s, y);
                }
                else if((y.var.l)!= 0 && (long)(x.var.c)== 0)
                {
                    push(s, y);
                }
                else push(s, x);
            }
            else 
            {
                if(y.var.l != 0 && x.var.l != 0)
                {
                    push(s, y);
                }
                else if(y.var.l != 0 && x.var.l==0)
                {
                    push(s, y);
                }
                else push(s, x);
            }
        }
        else if(typemaior(x, y)==DBL)
        {
            if(x.type==DBL && y.type==LONG)
            {
                if((y.var.l) != 0 && (long)(x.var.d) != 0)
                {
                    push(s, y); 
                }
                else if((y.var.l) != 0 && (long)(x.var.d) == 0)
                {
                    push(s, y); 
                }
                else push(s, x);
            }

            else if(x.type==DBL&&y.type==CHAR) 
            {
                if((long)(y.var.c) != 0 && (long)(x.var.d) != 0)
                {    
                    push(s, y);
                }
                else if((long)(y.var.c) != 0 && (long)(x.var.d) == 0)
                {
                    push(s, y);
                }
                else push(s, x);
            }
            
            else if(x.type==LONG &&y.type==DBL) 
            {
                if((long)(y.var.d) != 0 && (x.var.l) != 0)
                {
                    push(s, y);
                }
                else if((long) (y.var.d) != 0 && (x.var.l) == 0)
                {
                    push(s, y);
                }
                else push(s,x);
            }

            else if(x.type==CHAR&&y.type==DBL) 
            {
                if((long)(y.var.d) != 0 && (long)(x.var.c) != 0)
                {
                    push(s, y);
                }
                else if((long) (y.var.d) != 0 && (long) (x.var.c) == 0)
                {
                    push(s, y);
                }
                else push(s, x);
            }
            else 
            {
                if((long) y.var.d !=0 && (long) x.var.d != 0)
                {    
                    push(s, y);
                }
                else if((long) y.var.d != 0 && (long) x.var.d == 0)
                {
                    push(s, y);
                }
                else push(s, x);
            }
          
        }
        else//caso em que ambos são char
        {
            if((long) y.var.c != 0 && (long) x.var.c != 0)
            {
                push(s, y);
            }

            else if((long) y.var.c != 0 && (long)x.var.c == 0)
            {   
                push(s, y);
            }
            else push(s, x);
        } 
}


/**
 * \brief  Função relativa ao "e" com shortcut e sua respetiva auxiliar
 *
 * @param s 
 */
 
void andShortcut(STACK *s)
{
    STACK_ELEM x = pop(s);
    STACK_ELEM y = pop(s);

        if(typemaior(x, y)==LONG)
        {
            if(x.type==LONG && y.type != LONG)
            {
                if((long)(y.var.c) != 0 && (x.var.l) !=0)
                {
                    push(s, x); 
                }
                else if((long)(y.var.c) == 0 && (x.var.l)!=0)
                {
                    push(s, x);
                }
                else push(s, y);
            }
            else if(x.type != LONG && y.type == LONG) 
            {
                if((y.var.l)!= 0 && (long)(x.var.c) != 0)
                {
                    push(s, x);
                }
                else if((y.var.l)!= 0 && (long)(x.var.c)== 0)
                {
                    push(s, x);
                }
                else push(s, y);
            }
            else 
            {
                if(y.var.l != 0 && x.var.l != 0)
                {
                    push(s, x);
                }
                else if(y.var.l != 0 && x.var.l==0)
                {
                    push(s, x);
                }
                else push(s, y);
            }
        }
        else if(typemaior(x, y)==DBL)
        {
            if(x.type==DBL && y.type==LONG)
            {
                if((y.var.l) != 0 && (long)(x.var.d) != 0)
                {
                    push(s, x); 
                }
                else if((y.var.l) != 0 && (long)(x.var.d) == 0)
                {
                    push(s, x); 
                }
                else push(s, y);
            }

            else if(x.type==DBL&&y.type==CHAR) 
            {
                if((long)(y.var.c) != 0 && (long)(x.var.d) != 0)
                {    
                    push(s, x);
                }
                else if((long)(y.var.c) != 0 && (long)(x.var.d) == 0)
                {
                    push(s, x);
                }
                else push(s, y);
            }
            
            else if(x.type==LONG &&y.type==DBL) 
            {
                if((long)(y.var.d) != 0 && (x.var.l) != 0)
                {
                    push(s, x);
                }
                else if((long) (y.var.d) != 0 && (x.var.l) == 0)
                {
                    push(s, x);
                }
                else push(s,y);
            }

            else if(x.type==CHAR&&y.type==DBL) 
            {
                if((long)(y.var.d) != 0 && (long)(x.var.c) != 0)
                {
                    push(s, x);
                }
                else if((long) (y.var.d) != 0 && (long) (x.var.c) == 0)
                {
                    push(s, x);
                }
                else push(s, y);
            }
            else 
            {
                if((long) y.var.d !=0 && (long) x.var.d != 0)
                {    
                    push(s, x);
                }
                else if((long) y.var.d != 0 && (long) x.var.d == 0)
                {
                    push(s, x);
                }
                else push(s, y);
            }
          
        }
        else//caso em que ambos são char
        {
            if((long) y.var.c != 0 && (long) x.var.c != 0)
            {
                push(s, x);
            }

            else if((long) y.var.c != 0 && (long)x.var.c == 0)
            {   
                push(s, x);
            }
            else push(s, y);
        } 
}

/**
 * \brief  Função relativa ao "shortcut" e a sua respetiva auxiliar
 *
 *
 * @param s 
 * @param token
 */
int shortcut(STACK *s, char *token)
{
    if(strcmp(token, "e&")==0)
    {
        andShortcut(s);
        return 1;
    }
    if(strcmp(token, "e|")==0)
    {
        orShortcut(s);
        return 1;
    }
    return 0;
}


/**
 * \brief  Função relativa ao "If-Then-Else" e a sua respetiva auxiliar
 *
 * @param s 
 */
 
void ifTEAux(STACK *s)
{   
    
        STACK_ELEM x = pop(s);
        STACK_ELEM y = pop(s);
        STACK_ELEM z = pop(s);

        if(z.type == LONG)
        {
            if(z.var.l) push(s, y);
            else push(s, x); 
        }
        else if(z.type == DBL)
        {
            if((long)z.var.d) push(s, y);
            else push(s, x);
        }
        else
        {
            if((long)z.var.c) push(s, y);
            else push(s, y);
        }
}

int ifThenElse(STACK *s, char *token)
{
    if(strcmp(token, "?")==0)
    {
        ifTEAux(s);
        return 1;
    }
    return 0;
}


/**
 * \brief Função que dá push para a stack do valor de acordo com o seu type e va
 * 
 * 
 * @param s
 * @param token
 */
int val(STACK *s, char *token)
{
  
  char *endptrl;
  char *endptrd;
  long x = strtol(token, &endptrl, 10);//strtol le o token e guarda-o em endptrl(pointer para o final do que leu)
  double y = strtod(token, &endptrd);//faz o mesmo q strtol só que para double
  if((*endptrl)=='\0')//se o pointer final apontar para '\0' então quer dizer q leu o token todo e é um long
  {
    STACK_ELEM val;
    val.type =LONG;
    val.var.l=x;
    push(s, val);
    return 1;
  }
  if((*endptrd)=='\0')
  {
    STACK_ELEM val;
    val.type =DBL;
    val.var.d=y;
    push(s, val);
    return 1;
  }
  //não tem parser para string
  return 0;
}


/**
 * \brief  Função que imprime a stack
 *
 * @param s 
 */

void printstack(STACK *s)
{
  for (int i = 0; i < s->sp; i++)
    {
      if (s->stack[i].type == LONG)
        printf("%ld", s->stack[i].var.l);
      if (s->stack[i].type == CHAR)
        printf("%c", s->stack[i].var.c);
      if (s->stack[i].type == DBL)
        printf("%g", s->stack[i].var.d);
      if(s->stack[i].type == STR)
        printf("%s", s->stack[i].var.s);
    }
}

void handle(STACK *s, char *token, STACK_ELEM**lista)
{
  int a = stackman(s, token)|| convertStackTop(s, token)||lerStack(s, token, lista)|| bitwise(s, token)|| modulo(s, token)||soma(s, token)||subtracao(s, token) ||multiplicacao(s, token)||divisao(s, token) ||exponenciacao(s, token)||decrementar(s, token)||incrementar(s, token)|| eorder(s, token)||rOrdem(s, token)||opContrario(s, token)|| shortcut(s, token)||ifThenElse(s, token)||variables(s, token, lista)||carregavar(s, token, lista)||val(s, token);
  
  if (a == 0)
    a = 0;
}


/**
 * \brief  Função principal do programa responsavél por gerir a stack
 */
int main()
{
  STACK *s = newStack();
  STACK_ELEM **lista=cria_registos();
  char line[BUFSIZ];
  char token[BUFSIZ];

  if (fgets(line, BUFSIZ, stdin) != NULL)
  {
    while (sscanf(line, "%s%[^\n]", token, line) == 2)
    {
      handle(s, token, lista);
    }
    handle(s, token, lista);

    printstack(s);
    
    putchar('\n');
  }
  return 0;
}
