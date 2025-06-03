#include "hash_table.h"
#include "pool_allocator.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

void init_test()
{
    hash_table table;
    pool_allocator_t *pool = pool_allocator_initialize(100, sizeof(hashtable_item) + sizeof(int));
    assert(pool != NULL);

    hashtable_init(42, sizeof(int), pool, &table);

    assert(table.capacity == 42);
    assert(table.items != NULL);

    hashtable_free(&table);
}

void insert_test()
{
    hash_table table;
    pool_allocator_t *pool = pool_allocator_initialize(100, sizeof(hashtable_item) + sizeof(int));
    assert(pool != NULL);

    hashtable_init(10, sizeof(int), pool, &table);

    int z = 42;
    int x = 52;
    int c = 242;

    hashtable_insert(&table, "one", &z);
    hashtable_insert(&table, "two", &x);
    hashtable_insert(&table, "two", &c);

    assert(*(int *)hashtable_get(&table, "one") == z);
    assert(*(int *)hashtable_get(&table, "two") == c);
    assert(hashtable_get(&table, "nonexistent_key") == NULL);

    hashtable_free(&table);
}

void delete_test()
{
    hash_table table;
    pool_allocator_t *pool = pool_allocator_initialize(100, sizeof(hashtable_item) + sizeof(int));
    assert(pool != NULL);

    hashtable_init(42, sizeof(int), pool, &table);

    int fit = 242;
    hashtable_insert(&table, "key", &fit);

    assert(*(int *)hashtable_get(&table, "key") == fit);

    hashtable_delete(&table, "key");
    assert(hashtable_get(&table, "key") == NULL);

    hashtable_free(&table);
}

void capacity_test()
{
    hash_table table;
    pool_allocator_t *pool = pool_allocator_initialize(100, sizeof(hashtable_item) + sizeof(int));
    assert(pool != NULL);

    hashtable_init(10, sizeof(int), pool, &table);

    int values[] = {1, 2, 3, 4, 5};
    const char *keys[] = {"1", "2", "3", "4", "5"};

    for (int i = 0; i < 5; i++)
    {
        hashtable_insert(&table, keys[i], &values[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        assert(*(int *)hashtable_get(&table, keys[i]) == values[i]);
    }

    hashtable_free(&table);
}

int main()
{
    init_test();
    insert_test();
    delete_test();
    capacity_test();
    printf("Success!\n");
    return 0;
}
