#include "pool_allocator.h"

pool_allocator_t *pool_allocator_initialize(size_t chunk_count, size_t chunk_size)
{
    if (chunk_count == 0 || chunk_size == 0)
        return NULL;

    pool_allocator_t *allocator = (pool_allocator_t *)malloc(sizeof(pool_allocator_t));

    if (allocator == NULL)
        return NULL;

    size_t actual_size = sizeof(chunk_t) + chunk_size;

    allocator->chunk_count = chunk_count;
    allocator->memory = (void *)malloc(chunk_count * actual_size);

    if (allocator->memory == NULL)
    {
        free(allocator);
        return NULL;
    }

    allocator->free_list = (chunk_t *)allocator->memory;

    chunk_t *current = allocator->free_list;
    for (int i = 0; i < chunk_count - 1; i++)
    {
        current->next = (chunk_t *)((char *)current + actual_size);
        current = current->next;
    }

    current->next = NULL;

    return allocator;
}

void pool_allocator_deinitialize(pool_allocator_t *allocator)
{
    if (allocator == NULL)
        return;

    if (allocator->memory != NULL)
        free(allocator->memory);

    free(allocator);
}

void *pool_allocator_alloc(pool_allocator_t *allocator)
{
    if (allocator == NULL)
        return NULL;

    if (allocator->free_list == NULL)
        return NULL;

    chunk_t *allocation = allocator->free_list;
    allocator->free_list = allocation->next;

    return (void *)((char *)allocation + sizeof(chunk_t));
}

void pool_allocator_free(pool_allocator_t *allocator, void *memory)
{
    if (allocator == NULL)
        return;

    if (memory == NULL)
        return;

    chunk_t *free = (chunk_t *)((char *)memory - sizeof(chunk_t));
    free->next = allocator->free_list;
    allocator->free_list = free;
    return;
}
