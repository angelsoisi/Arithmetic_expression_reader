#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
struct strNode{
  Type data;
  struct strNode *prior;

};


typedef struct strNode *Node;


struct strStack
{
  Node top;
  size_t size_data;
  unsigned int size;
};

Stack stack_create(size_t bytes)
{
  Stack newStack=malloc(sizeof(struct strStack));
  newStack->size_data=bytes;
  newStack->top=NULL;
  newStack->size=NULL;
  return newStack;
}

int stack_size(Stack s)
{ if (s!=NULL)
{
  return s->size;
}
  else {
    return 0;
  }
    
  }

bool stack_isEmpty(Stack s)
{
  if(s->top!=NULL)
  {
    return false;
  }
    else
  {
    return true;
  }
     
}

Type stack_top(Stack s)
{
  if (s!=NULL)
  {
    if(stack_isEmpty(s))
    {
      return NULL;
    }
    else {
      Type data=malloc(s->size_data);
      memcpy(data,s->top->data,s->size_data);
      return data;
      //return s->top->data;
    }
  }
  return NULL;
}

Node newNode(Type d,size_t bytes)
{
  Node new=malloc(sizeof(struct strNode));
  //clonamos el dato
  new->data=malloc(bytes);
  memcpy(new->data,d,bytes);
 // new->data=d;
  new->prior=NULL;
  return new;
}

void stack_push(Stack s,Type d)
{
  if (s!=NULL)
  {
    Node new=newNode(d,s->size_data);
    if (stack_isEmpty(s)){
      s->top=new;
    }
    else {
      new->prior=s->top;
      s->top=new;
    }
    s->size+=1;
    }
  }


Type stack_pop(Stack s)
{
  if (s!=NULL)
  {
    if(stack_isEmpty(s))
    {
      return NULL;
    }
    else {
      //apuntar al nuevo tope
      Node temp=s->top->prior;
      //apuntar al dato a retornar 
      Type data = s->top->data;
      free(s->top);
      
       s->top=temp;
      s->size-=1;
      return data;
    }
  }
  return NULL;
}

void stack_destroy(Stack s)
{
  Type temp;
  while (!stack_isEmpty(s))
    {
      temp=stack_pop(s);
      free(temp);
    }
  free(s);
}
