#include "pool_allocator.h"
#include <assert.h>

void pool_allocator_initialize_test()
{
    pool_allocator_t *allocator = pool_allocator_initialize(2, sizeof(int));

    assert(allocator != NULL);
    assert(allocator->chunk_count == 2);
    assert(allocator->memory != NULL);
    assert(allocator->free_list != NULL);

    pool_allocator_deinitialize(allocator);
}

void pool_allocator_alloc_test()
{
    pool_allocator_t *allocator = pool_allocator_initialize(2, sizeof(int));

    chunk_t *current = allocator->free_list;
    chunk_t *next = current->next;

    int *memory1 = (int *)pool_allocator_alloc(allocator);
    assert(memory1 != NULL);
    *memory1 = 1;
    assert(*memory1 == 1);
    assert(current == (chunk_t *)memory1);
    assert(next == allocator->free_list);

    current = allocator->free_list;
    int *memory2 = (int *)pool_allocator_alloc(allocator);
    assert(memory2 != NULL);
    *memory2 = 2;
    assert(*memory2 == 2);
    assert(current == (chunk_t *)memory2);
    assert(allocator->free_list == NULL);

    pool_allocator_deinitialize(allocator);
}

void pool_allocator_free_test()
{
    pool_allocator_t *allocator = pool_allocator_initialize(2, sizeof(int));

    void *memory1 = pool_allocator_alloc(allocator);
    void *memory2 = pool_allocator_alloc(allocator);

    pool_allocator_free(allocator, memory2);
    assert(allocator->free_list == (chunk_t *)memory2);
    pool_allocator_free(allocator, memory1);
    assert(allocator->free_list == (chunk_t *)memory1);

    pool_allocator_deinitialize(allocator);
}

void pool_allocator_overflow_test()
{
    pool_allocator_t *allocator = pool_allocator_initialize(1, sizeof(int));

    void *memory1 = pool_allocator_alloc(allocator);
    void *memory2 = pool_allocator_alloc(allocator);
    assert(memory2 == NULL);

    pool_allocator_deinitialize(allocator);
}

void pool_allocator_request_zero_bytes_test()
{
    pool_allocator_t *allocator = pool_allocator_initialize(0, sizeof(int));
    assert(allocator == NULL);

    allocator = pool_allocator_initialize(4, 0);
    assert(allocator == NULL);
}

int main()
{
    pool_allocator_initialize_test();
    pool_allocator_alloc_test();
    pool_allocator_free_test();
    pool_allocator_overflow_test();
    pool_allocator_request_zero_bytes_test();
    printf("Success!\n");
    return 0;
}