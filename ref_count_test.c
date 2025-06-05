#include "ref_count.h"
#include <assert.h>

void ref_count_create_test()
{
    pool_allocator_t *pool_allocator = pool_allocator_initialize(100, sizeof(ref_count_t));
    void *object = pool_allocator_alloc(pool_allocator);

    ref_count_t *ref_count = ref_count_create(object, pool_allocator);

    assert(ref_count != NULL);
    assert(ref_count->allocator == pool_allocator);
    assert(ref_count->object == object);
    assert(ref_count->count == 1);

    ref_count_release(ref_count);
    pool_allocator_deinitialize(pool_allocator);
}

void ref_count_increase_test()
{
    pool_allocator_t *pool_allocator = pool_allocator_initialize(100, sizeof(ref_count_t));
    void *object = pool_allocator_alloc(pool_allocator);

    ref_count_t *ref_count = ref_count_create(object, pool_allocator);

    ref_count_increase(ref_count);

    assert(ref_count->count == 2);

    ref_count->count = 1;
    ref_count_release(ref_count);

    pool_allocator_deinitialize(pool_allocator);
}

void ref_count_release_test()
{
    pool_allocator_t *pool_allocator = pool_allocator_initialize(100, sizeof(ref_count_t));
    void *object = pool_allocator_alloc(pool_allocator);

    ref_count_t *ref_count = ref_count_create(object, pool_allocator);

    ref_count_increase(ref_count);
    ref_count_release(ref_count);

    assert(ref_count->count == 1);

    ref_count_release(ref_count);
    pool_allocator_deinitialize(pool_allocator);
}

int main()
{
    ref_count_create_test();
    ref_count_increase_test();
    ref_count_release_test();
    printf("Success!\n");
}
