#include "object_manager.h"
#include "pool_allocator.h"
#include <assert.h>

void create_cycle_reference_test()
{
    pool_allocator_t *allocator = pool_allocator_initialize(100, sizeof(object_manager_t));
    assert(allocator != NULL);
    cycle_object *obj1 = create_cycle_object(allocator);
    cycle_object *obj2 = create_cycle_object(allocator);
    assert(obj1 != NULL);
    assert(obj2 != NULL);
    assert(obj1->manager != NULL);
    assert(obj2->manager != NULL);
    assert(obj1->manager->count == 1);
    assert(obj2->manager->count == 1);
    create_cycle_reference(obj1, obj2);
    assert(obj1->ref_to == obj2);
    assert(obj2->ref_to == obj1);
    assert(obj1->manager->count == 2);
    assert(obj2->manager->count == 2);
    assert(detected_cycle(obj1) == 1);
    assert(detected_cycle(obj2) == 1);
    delete_cycle(allocator, obj1);
    pool_allocator_deinitialize(allocator);
}

void detected_cycle_test()
{
    pool_allocator_t *allocator = pool_allocator_initialize(100, sizeof(object_manager_t));
    assert(allocator != NULL);
    cycle_object *obj1 = create_cycle_object(allocator);
    cycle_object *obj2 = create_cycle_object(allocator);
    cycle_object *obj3 = create_cycle_object(allocator);
    assert(obj1 != NULL);
    assert(obj2 != NULL);
    assert(obj3 != NULL);
    obj1->ref_to = obj2;
    object_manager_increase(obj2->manager);
    obj2->ref_to = obj3;
    object_manager_increase(obj3->manager);
    obj3->ref_to = obj1;
    object_manager_increase(obj1->manager);
    assert(detected_cycle(obj1) == 1);
    assert(detected_cycle(obj2) == 1);
    assert(detected_cycle(obj3) == 1);
    cycle_object *obj4 = create_cycle_object(allocator);
    assert(obj4 != NULL);
    assert(detected_cycle(obj4) == 0);
    delete_cycle(allocator, obj1);
    object_manager_release(obj4->manager);
    pool_allocator_deinitialize(allocator);
}

int main()
{
    create_cycle_reference_test();
    detected_cycle_test();
    return 0;
}
