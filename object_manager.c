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

cycle_object *create_cycle_object(pool_allocator_t *allocator)
{
    if (allocator == NULL)
    {
        return NULL;
    }
    cycle_object *obj = pool_allocator_alloc(allocator);
    if (obj == NULL)
    {
        return NULL;
    }
    obj->manager = object_manager_create(allocator, NULL, NULL);
    if (obj->manager == NULL)
    {
        pool_allocator_free(allocator, obj);
        return NULL;
    }
    obj->ref_to = NULL;
    return obj;
}

void create_cycle_reference(cycle_object *obj1, cycle_object *obj2)
{
    if (obj1 == NULL || obj2 == NULL || obj1->manager == NULL || obj2->manager == NULL)
    {
        return;
    }
    obj1->ref_to = obj2;
    obj2->ref_to = obj1;
    object_manager_increase(obj1->manager);
    object_manager_increase(obj2->manager);
}

int detected_cycle(cycle_object *start)
{
    if (start == NULL || start->ref_to == NULL)
    {
        return 0;
    }
    cycle_object *obj1 = start;
    cycle_object *obj2 = start->ref_to;
    while (obj2 && obj2->ref_to)
    {
        if (obj1 == obj2)
        {
            return 1;
        }
        obj1 = (cycle_object *)obj1->ref_to;
        obj2 = ((cycle_object *)obj2->ref_to)->ref_to;
    }
    return 0;
}

void delete_cycle(pool_allocator_t *allocator, cycle_object *obj)
{
    if (obj == NULL || obj->manager == NULL || allocator == NULL)
    {
        return;
    }
    if (detected_cycle(obj))
    {
        cycle_object *current = obj;
        cycle_object *next;
        do
        {
            next = (cycle_object *)current->ref_to;
            if (next == NULL)
            {
                break;
            }
            current->ref_to = NULL;
            if (next->manager)
            {
                object_manager_release(next->manager);
            }
            current = next;
        } while (current && current != obj);
        object_manager_release(obj->manager);
    }
}
