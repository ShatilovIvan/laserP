#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

bool stack_is_empty(stack_t *st)
{
    return st->top == STACK_EMPTY;
}

bool stack_is_full(stack_t *st)
{
    return st->top == st->max_size - 1;
}

stack_t *stack_initialize(size_t count)
{
    stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t));
    new_stack->arr = (int *)malloc(sizeof(int) * count);
    new_stack->top = STACK_EMPTY;
    new_stack->max_size = count;
    return new_stack;
}

void stack_free(stack_t *st)
{
    if (st == NULL)
        return;

    if (st->arr != NULL)
        free(st->arr);

    free(st);
}

int stack_push(stack_t *st, int data)
{
    if (stack_is_full(st))
        return STACK_FULL;

    st->top++;
    st->arr[st->top] = data;
}

int stack_peek(stack_t *st)
{
    if (stack_is_empty(st))
        return STACK_EMPTY;

    return st->arr[st->top];
}

int stack_pop(stack_t *st)
{
    if (stack_is_empty(st))
        return STACK_EMPTY;

    int result = st->arr[st->top];
    st->arr[st->top] = 0;
    st->top--;
    return result;
}
