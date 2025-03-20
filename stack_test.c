#include "stack.h"
#include <assert.h>

void stack_is_empty_test()
{
    stack_t *st = stack_initialize(4);
    assert(stack_is_empty(st));

    stack_free(st);
}

void stack_is_full_test()
{
    stack_t *st = stack_initialize(4);

    for (int i = 0; i < st->max_size; i++)
    {
        stack_push(st, i);
    }

    assert(stack_is_full(st));

    stack_free(st);
}

void stack_initialize_test()
{
    stack_t *st = stack_initialize(4);
    assert(st != NULL);

    stack_free(st);
}

void stack_push_test()
{
    stack_t *st = stack_initialize(4);
    int res = stack_push(st, 10);
    assert(st->arr[0] == 10 && res == STACK_OK);

    stack_free(st);
}

void stack_peek_test()
{
	int out;
    stack_t *st = stack_initialize(4);
    stack_push(st, 10);
	int res = stack_peek(st, &out);
    assert(out == 10 && res == STACK_OK);

    stack_free(st);
}

void stack_pop_test()
{ 
	int out;
    stack_t *st = stack_initialize(4);
    stack_push(st, 10);
	int res = stack_pop(st, &out);
    assert(out == 10 && res == STACK_OK); 
    
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
