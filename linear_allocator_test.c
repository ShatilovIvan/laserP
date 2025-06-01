#include "assert.h"
#include "linear_allocator.h"
#include "stdio.h"

void linear_allocator_initialize_test()
{
    linear_allocator_t *allocator = linear_allocator_initialize(sizeof(int));

    assert(allocator != NULL);
    assert(allocator->memory != NULL);
    assert(allocator->offset == 0);
    assert(allocator->total_size == sizeof(int));

    linear_allocator_deinitialize(allocator);
}

void linear_allocator_reset_test()
{
    linear_allocator_t *allocator = linear_allocator_initialize(4 * sizeof(int));
    void *ptr1 = linear_allocator_alloc(allocator, sizeof(void *));
    linear_allocator_reset(allocator);
    void *ptr2 = linear_allocator_alloc(allocator, sizeof(void *));

    assert(ptr1 == ptr2);
    linear_allocator_deinitialize(allocator);
}

void linear_allocator_alloc_test()
{
    linear_allocator_t *allocator = linear_allocator_initialize(4 * sizeof(int));

    int *ptr1 = linear_allocator_alloc(allocator, sizeof(int));
    assert(ptr1 != NULL);
    *ptr1 = 10;
    assert(*ptr1 == 10);
    assert(allocator->offset == sizeof(int));

    char *ptr2 = linear_allocator_alloc(allocator, sizeof(char));
    assert(ptr2 != NULL);
    *ptr2 = 'A';
    assert(*ptr2 == 'A');
    assert(allocator->offset == sizeof(int) + sizeof(char));

    linear_allocator_deinitialize(allocator);
}

void linear_allocator_out_of_memory_test()
{
    linear_allocator_t *allocator = linear_allocator_initialize(4 * sizeof(int));
    int *ptr = linear_allocator_alloc(allocator, 5 * sizeof(int));

    assert(ptr == NULL);
    linear_allocator_deinitialize(allocator);
}

void linear_allocator_alloc_zero_bytes_test()
{
    linear_allocator_t *allocator = linear_allocator_initialize(4 * sizeof(int));
    int *ptr = linear_allocator_alloc(allocator, 0);

    assert(ptr == NULL);
    linear_allocator_deinitialize(allocator);
}

int main()
{
    linear_allocator_initialize_test();
    linear_allocator_reset_test();
    linear_allocator_alloc_test();
    linear_allocator_out_of_memory_test();
    linear_allocator_alloc_zero_bytes_test();
    printf("Success!\n");
    return 0;
}
