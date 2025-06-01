#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct chunk_t chunk_t;

struct chunk_t
{
    chunk_t *next;
};

typedef struct
{
    void *memory;
    size_t chunk_count;
    chunk_t *free_list;
} pool_allocator_t;

pool_allocator_t *pool_allocator_initialize(size_t chunk_count, size_t chunk_size);

void pool_allocator_deinitialize(pool_allocator_t *allocator);

void *pool_allocator_alloc(pool_allocator_t *allocator);

void pool_allocator_free(pool_allocator_t *allocator, void *memory);

#endif