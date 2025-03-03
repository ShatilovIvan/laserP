#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 8

bool stack_is_empty(struct stack *st)
{
    return st->top == -1;
}

bool stack_is_full(struct stack *st)
{
    return st->top == MAX_SIZE - 1;
}

struct stack *stack_initialize()
{
    struct stack *new_stack = (struct stack *)malloc(sizeof(struct stack));
    new_stack->top = -1;
    return new_stack;
}

void stack_free(struct stack *st)
{
    if (st == NULL)
        return;

    free(st);
}

void stack_push(struct stack *st, int data)
{
    if (stack_is_full(st))
        return;

    st->top++;
    st->arr[st->top] = data;
}

int stack_peek(struct stack *st)
{
    if (stack_is_empty(st))
        return -1;

    return st->arr[st->top];
}

int stack_pop(struct stack *st)
{
    if (stack_is_empty(st))
        return -1;

    int result = st->arr[st->top];
    st->arr[st->top] = 0;
    st->top--;
    return result;
}