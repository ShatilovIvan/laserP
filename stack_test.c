#include "stack.h"
#include <assert.h>

void stack_is_empty_test()
{
    struct stack *st = stack_initialize();
    assert(stack_is_empty(st));

    stack_free(st);
}

void stack_is_full_test()
{
    struct stack *st = stack_initialize();

    for (int i = 0; i < MAX_SIZE; i++)
    {
        stack_push(st, i);
    }

    assert(stack_is_full(st));

    stack_free(st);
}

void stack_initialize_test()
{
    struct stack *st = stack_initialize();
    assert(st != NULL);

    stack_free(st);
}

void stack_push_test()
{
    struct stack *st = stack_initialize();
    stack_push(st, 10);
    assert(st->arr[0] == 10);

    stack_free(st);
}

void stack_peek_test()
{
    struct stack *st = stack_initialize();
    stack_push(st, 10);
    assert(stack_peek(st) == 10);

    stack_free(st);
}

void stack_pop_test()
{
    struct stack *st = stack_initialize();
    stack_push(st, 10);

    assert(stack_pop(st) == 10);
    assert(stack_is_empty(st));

    stack_free(st);
}

int main()
{
    stack_is_empty_test();
    stack_is_full_test();
    stack_initialize_test();
    stack_push_test();
    stack_peek_test();
    stack_pop_test();
    printf("success\n");
    return 0;
}