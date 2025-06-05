#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stdlib.h>

typedef struct
{
    void *memory;
    size_t offset;
    size_t total_size;

} linear_allocator_t;

linear_allocator_t *linear_allocator_initialize(size_t size);

void linear_allocator_deinitialize(linear_allocator_t *allocator);

void linear_allocator_reset(linear_allocator_t *allocator);

void *linear_allocator_alloc(linear_allocator_t *allocator, size_t size);

#endif
