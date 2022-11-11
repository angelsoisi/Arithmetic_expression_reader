#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int *newInt(int valor)
{
  int *new=malloc(sizeof(int));
  *new=valor;
  return new;
}

float *newFloat(float valor)
{
  float *new=malloc(sizeof(float));
  *new=valor;
  return new;
}


int verificador(char formula[100])
{
  Stack s1=stack_create(sizeof(short));
   for(int i=0;formula[i]!='\0';i++)
  {
    if(formula[i]=='('||formula[i]=='{'||formula[i]=='[')
    {
      stack_push(s1,&formula[i]);
    }
    if(formula[i]==')'||formula[i]=='}'||formula[i]==']')
    {
      if(stack_isEmpty(s1))
      {
        printf("La formula es incorrecta");
        return 0;
      }
      char* last=stack_pop(s1);
      if((formula[i]==')'&&*last=='(')||(formula[i]=='}'&&*last=='{')||(formula[i]==']'&&*last=='['))
      {
        continue;
      }
      else
      {
        printf("La formula es correcta");
        return 0;
      }
    }
  }
  if(stack_isEmpty(s1))
  {
    printf("La formula es correcta");
  }
  else
  {
    printf("La formula es incorrecta");
  }
  
}


int invalido(char* formula)
{
  int i=0;
  while(formula[i]!='\0')
  {
    if(formula[i]!='+'&&formula[i]!='-'&&formula[i]!='*'&&formula[i]!='/'&&formula[i]!='('&&formula[i]!=')'&&formula[i]!='{'&&formula[i]!='}'&&formula[i]!='['&&formula[i]!=']'
    &&!isdigit(formula[i]))
    {
      return 1;
    }
    i++;
  }
  return 0;
}

int operador(char* formula)
{
  int i=0;
  while(formula[i]!='\0')
  {
    if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/')
    {
      return 1;
    }
    i++;
  }
  return 0;
}

int parentesisysimbolo(char* formula)
{
  int i=0;
  while(formula[i]!='\0')
  {
    if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/')
    {
      if(formula[i-1]=='('||formula[i-1]=='{'||formula[i-1]=='[')
      {
        if (isdigit(formula[i-2]))
        {
          return 1;
        }
      }
    }
    i++;
  }
  return 0;
}

int prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
 
    case '^':
        return 3;
    }
    return -1;
}

//do infixToPostfix function considering numbers with 
void infixToPostfix(char* formula)
{
    Stack s1=stack_create(sizeof(char));
    int i, k;
 
    
    for (i = 0, k = -1; formula[i]; ++i)
    {
        if (formula[i]==' ')
      {
        formula[++k] = formula[i];
        continue;
      }
    
        // If the scanned character is an operand, add it to output.
        if ((isdigit(formula[i])))
            formula[++k] = formula[i];
         
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (formula[i] == '('||formula[i]=='{'||formula[i]=='[')
            stack_push(s1,&formula[i]);
         
        // If the scanned character is an ‘)’, pop and output from the stack 
        // until an ‘(‘ is encountered.
        else if (formula[i] == ')'||formula[i]=='}'||formula[i]==']')
        {
            while (!stack_isEmpty(s1) && *(char*)stack_top(s1) != '(' && *(char*)stack_top(s1) != '{' && *(char*)stack_top(s1) != '[')
                formula[++k] = *(char*)stack_pop(s1);
            if (!stack_isEmpty(s1) && *(char*)stack_top(s1) != '(' && *(char*)stack_top(s1) != '{' && *(char*)stack_top(s1) != '[')
                return ; // invalid formularession               
            else
                stack_pop(s1);
        }
        else // an operator is encountered
        {
            while (!stack_isEmpty(s1) && prec(formula[i]) <= prec(*(char*)stack_top(s1)))
                formula[++k] = *(char*)stack_pop(s1);
            stack_push(s1,&formula[i]);
        }
 
    }
 
    // pop all the operators from the stack
    while (!stack_isEmpty(s1))
        formula[++k] = *(char*)stack_pop(s1);
 
    formula[++k] = '\0';
    printf( "%s", formula );
}

void deleteSpaces(char *str)
{
    int i = 0, j = 0,chk=0;
    while(str[i]!='\0')
    {
        chk=0;
        if(str[i]==' ')
        {
            j=i;
            while(str[j-1]!='\0')
            {
                str[j] = str[j+1];
                j++;
            }
            chk = 1;
        }
        if(chk==0)
            i++;
    }
}

char* multiplicacion(char* formula)
{
  int i=0;
  while(formula[i]!='\0')
  {
    if(formula[i]==' ') 
    {
      i++;
      continue;
    }
    if(formula[i]==')'&&formula[i+1]=='(')
    {
      for(int j=strlen(formula);j>i;j--)
      {
        formula[j+1]=formula[j];
      }
      formula[i+1]='*';
    }
    i++;
  }
  return formula;
}

char* multiplicacion2(char* formula)
{
  int i=0;
  while(formula[i]!='\0')
  {
    if(formula[i]==' ') 
    {
      i++;
      continue;
    }
    if(formula[i]=='}'&&formula[i+1]=='{')
    {
      for(int j=strlen(formula);j>i;j--)
      {
        formula[j+1]=formula[j];
      }
      formula[i+1]='*';
    }
    i++;
  }
  return formula;
}

//multiplication with square brackets
char* multiplicacion3(char* formula)
{
  int i=0;

  while(formula[i]!='\0')
  {
    if(formula[i]==' ') 
    {
      i++;
      continue;
    }
    if(formula[i]==']'&&formula[i+1]=='[')
    {
      for(int j=strlen(formula);j>i;j--)
      {
        formula[j+1]=formula[j];
      }
      formula[i+1]='*';
    }
    i++;
  }
  return formula;
}

//function to work with numbers with multiple 

//function evluatepostfix with float and multiplication 
float evaluatePostfix(char* formula)
{
    //create a stack and initialize top
    Stack s1=stack_create(sizeof(float));
    int i;
 
    // Scan all characters one by one
    for (i = 0; formula[i]; ++i)
    {
        if(formula[i]==' ') continue;
        // If the scanned character is an operand (number here),
        // push it to the stack.
      else if (isdigit(formula[i]))
        {
            float num=0;
             
            //extract full number
            while(isdigit(formula[i]))
            {
            num=num*10 + (float)(formula[i]-'0');
                i++;
            }
            i--;
             
            //push the element in the stack
            stack_push(s1,&num);
        }
        // If the scanned character is an operator, pop two
        // elements from stack apply the operator
        else
        {
            float val1 = *(float*)stack_pop(s1);
            float val2 = *(float*)stack_pop(s1);
            switch (formula[i])
            {
            case '+': stack_push(s1,newFloat(val2+val1)); break;
            case '-': stack_push(s1,newFloat(val2-val1)); break;
            case '*': stack_push(s1,newFloat(val2*val1)); break;
            case '/': stack_push(s1,newFloat(val2/val1)); break;
            }
        }
    }
    return *(float*)stack_pop(s1);
}



int check(char* formula)
{
  int i=0;
  while(formula[i]!='\0')
  {
    if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/')
    {
      if(formula[i-1]<')'||formula[i-1]>'}'||formula[i-1]<']')
      {
        return 0;
      }
      if(formula[i-1]<')'||formula[i-1]>'}'||formula[i-1]<']')
      {
        if (formula[i+1]>'0'||formula[i+1]<'9')
        {
          return 0;
        }
      if(formula[i-1]>'0'||formula[i-1]<'9');
        {
          if(formula[i+1]<'('||formula[i+1]>'['||formula[i+1]>'{')
          {
            return 0;
          }
        }
      }
      if(formula[i-1]<'0'||formula[i-1]>'9')
      {
        return 1;
      }
      if(formula[i+1]<'0'||formula[i+1]>'9')
      {
        return 1;
      }
    }
    i++;
  }
  return 0;
}

int main()
{
  Stack s1=stack_create(sizeof(short));  //Crear una instancia del contenedor Stack
  char formula[100];
  char copia[100];
  printf("ingresa la formula matematica: ");
  gets(formula);
  strcpy(copia,formula);
  deleteSpaces(copia);
  if(invalido(copia)!=0)
  {
    printf("La formula contiene caracteres invalidos");
    return 0;
  }
  if(operador(copia)==0)
  {
    printf("La formula no contiene operadores");
    return 0;
  }
  if(check(copia)!=0)
  {
    printf("La formula no esta bien escrita");
    return 0;
  }
  if (parentesisysimbolo(copia)!=0)
  {
    printf("La formula no esta bien escrita");
    return 0;
  }
  verificador(copia);
  printf("\n");
  multiplicacion(formula);
  multiplicacion2(formula);
  multiplicacion3(formula);
  infixToPostfix(formula);
  printf("\n");
  printf("%.2f",evaluatePostfix(formula));
  return 0;
}