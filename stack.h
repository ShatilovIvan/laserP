#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 8

struct stack
{
    int arr[MAX_SIZE];
    int top;
};

bool stack_is_empty(struct stack *);

bool stack_is_full(struct stack *);

struct stack *stack_initialize();

void stack_free(struct stack *);

void stack_push(struct stack *, int);

int stack_peek(struct stack *st);

int stack_pop(struct stack *);

#endif