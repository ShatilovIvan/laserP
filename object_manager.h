#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "pool_allocator.h"
#include <stdlib.h>

typedef void *(*constructor_t)(pool_allocator_t *allocator);
typedef void (*destructor_t)(pool_allocator_t *allocator, void *object);

typedef struct
{
    size_t count;
    void *object;
    pool_allocator_t *allocator;
    constructor_t constructor;
    destructor_t destructor;
} object_manager_t;

object_manager_t *object_manager_create(pool_allocator_t *allocator, constructor_t constructor,
                                        destructor_t destructor);

void object_manager_increase(object_manager_t *object_manager);

void object_manager_release(object_manager_t *object_manager);

#endif
