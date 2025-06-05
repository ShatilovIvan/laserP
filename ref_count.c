#include "ref_count.h"

ref_count_t *ref_count_create(void *object, pool_allocator_t *allocator)
{
    if (object == NULL || allocator == NULL)
        return NULL;

    ref_count_t *ref = pool_allocator_alloc(allocator);

    if (ref == NULL)
        return NULL;

    ref->allocator = allocator;
    ref->object = object;
    ref->count = 1;

    return ref;
}

void ref_count_increase(ref_count_t *ref_count)
{
    if (ref_count == NULL)
        return;

    ref_count->count++;
}

void ref_count_release(ref_count_t *ref_count)
{
    if (ref_count == NULL)
        return;

    ref_count->count--;

    if (ref_count->count <= 0)
    {
        if (ref_count->object == NULL)
        {
            pool_allocator_free(ref_count->allocator, ref_count);
            return;
        }

        pool_allocator_free(ref_count->allocator, ref_count->object);
        pool_allocator_free(ref_count->allocator, ref_count);
    }
}
