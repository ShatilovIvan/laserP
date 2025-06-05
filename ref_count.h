#ifndef REF_COUNT_H
#define REF_COUNT_H

#include "pool_allocator.h"
#include <stdlib.h>

typedef struct
{
    size_t count;
    void *object;
    pool_allocator_t *allocator;
} ref_count_t;

ref_count_t *ref_count_create(void *object, pool_allocator_t *allocator);

void ref_count_increase(ref_count_t *ref_count);

void ref_count_release(ref_count_t *ref_count);

#endif
