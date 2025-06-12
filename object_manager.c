#include "object_manager.h"

object_manager_t *object_manager_create(pool_allocator_t *allocator, constructor_t constructor, destructor_t destructor)
{
    if (allocator == NULL)
        return NULL;

    object_manager_t *manager = pool_allocator_alloc(allocator);

    if (manager == NULL)
        return NULL;

    if (constructor == NULL)
        manager->constructor = pool_allocator_alloc;
    else
        manager->constructor = constructor;

    if (destructor == NULL)
        manager->destructor = pool_allocator_free;
    else
        manager->destructor = destructor;

    manager->allocator = allocator;
    manager->object = manager->constructor(allocator);
    manager->count = 1;

    return manager;
}

void object_manager_increase(object_manager_t *object_manager)
{
    if (object_manager == NULL)
        return;

    object_manager->count++;
}

void object_manager_release(object_manager_t *object_manager)
{
    if (object_manager == NULL)
        return;

    object_manager->count--;

    if (object_manager->count <= 0)
    {
        if (object_manager->object == NULL)
        {
            pool_allocator_free(object_manager->allocator, object_manager);
            return;
        }

        object_manager->destructor(object_manager->allocator, object_manager->object);
        pool_allocator_free(object_manager->allocator, object_manager);
    }
}
