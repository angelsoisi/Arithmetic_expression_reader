#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#ifndef STACK_H_
#define STACK_H_

typedef void* Type;

typedef struct strStack *Stack;


Stack stack_create();

int stack_size(Stack);

bool stack_isEmpty(Stack);

Type stack_top(Stack);

void stack_push(Stack,Type);

Type stack_pop(Stack);

void stack_destroy(Stack);



#endif