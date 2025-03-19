#ifndef STACK_H
#define STACK_H
#define STACK_EMPTY -1
#define STACK_FULL -2

#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    int *arr;
    size_t top;
    size_t max_size;
} stack_t;

bool stack_is_empty(stack_t *);

bool stack_is_full(stack_t *);

stack_t *stack_initialize(size_t);

void stack_free(stack_t *);

int stack_push(stack_t *, int);

int stack_peek(stack_t *st);

int stack_pop(stack_t *);

#endif
