#include "linear_allocator.h"

linear_allocator_t *linear_allocator_initialize(size_t size)
{
    linear_allocator_t *new_allocator = (linear_allocator_t *)malloc(sizeof(linear_allocator_t));

    if (new_allocator == NULL)
        return NULL;

    new_allocator->total_size = size;
    new_allocator->offset = 0;
    new_allocator->memory = (void *)calloc(1, size);

    return new_allocator;
}

void linear_allocator_deinitialize(linear_allocator_t *allocator)
{
    if (allocator == NULL)
        return;

    if (allocator->memory != NULL)
        free(allocator->memory);

    free(allocator);
}

void linear_allocator_reset(linear_allocator_t *allocator)
{
    if (allocator == NULL)
        return;

    allocator->offset = 0;
}

void *linear_allocator_alloc(linear_allocator_t *allocator, size_t size)
{
    if (allocator == NULL)
        return NULL;

    if (allocator->offset + size > allocator->total_size || size == 0)
        return NULL;

    void *current_address = allocator->memory + allocator->offset;
    allocator->offset += size;

    return current_address;
}
