#include "object_manager.h"
#include <assert.h>
#include <string.h>

void *custom_constructor(pool_allocator_t *allocator)
{
    void *memory = pool_allocator_alloc(allocator);
    memset(memory, 0, sizeof(int));
    return memory;
}

void custom_destructor(pool_allocator_t *allocator, void *memory)
{
    pool_allocator_free(allocator, memory);
}

void object_manager_default_test()
{
    pool_allocator_t *pool_allocator = pool_allocator_initialize(100, sizeof(object_manager_t));

    object_manager_t *object_manager = object_manager_create(pool_allocator, NULL, NULL);

    assert(object_manager != NULL);
    assert(object_manager->constructor == pool_allocator_alloc);
    assert(object_manager->destructor == pool_allocator_free);

    object_manager_release(object_manager);
    pool_allocator_deinitialize(pool_allocator);
}

void object_manager_custom_test()
{
    pool_allocator_t *pool_allocator = pool_allocator_initialize(10, sizeof(object_manager_t));

    object_manager_t *object_manager = object_manager_create(pool_allocator, custom_constructor, custom_destructor);

    assert(object_manager != NULL);
    assert(object_manager->constructor == custom_constructor);
    assert(object_manager->destructor == custom_destructor);
    assert(*(int *)object_manager->object == 0);

    object_manager_release(object_manager);
    pool_allocator_deinitialize(pool_allocator);
}

int main()
{
    object_manager_default_test();
    object_manager_custom_test();
    printf("Success!\n");
}