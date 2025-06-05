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

typedef struct
{
    object_manager_t *manager;
    void *ref_to;
} cycle_object;

object_manager_t *object_manager_create(pool_allocator_t *allocator, constructor_t constructor,
                                        destructor_t destructor);

void object_manager_increase(object_manager_t *object_manager);

void object_manager_release(object_manager_t *object_manager);

cycle_object *create_cycle_object(pool_allocator_t *allocator);

void create_cycle_reference(cycle_object *obj1, cycle_object *obj2);

int detected_cycle(cycle_object *start);

void delete_cycle(pool_allocator_t *allocator, cycle_object *obj);

#endif
