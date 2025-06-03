#include "hash_table.h"
#include "pool_allocator.h"
#include <stdlib.h>
#include <string.h>

size_t hash_func(const char *key, size_t capacity)
{
    size_t hash = 5381;
    int c;
    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

void hashtable_init(size_t capacity, size_t value_size, pool_allocator_t *allocator, hash_table *table)
{
    if (!table || capacity == 0)
        return;

    if (!allocator)
    {
        size_t item_size = sizeof(hashtable_item) + value_size;
        allocator = pool_allocator_initialize(capacity, item_size);
        if (!allocator)
            return;
    }

    table->allocator = allocator;
    table->capacity = capacity;
    table->value_size = value_size;
    table->items = pool_allocator_alloc(allocator);

    for (size_t i = 0; i < capacity; i++)
    {
        hashtable_item *item = pool_allocator_alloc(allocator);
        item->key = NULL;
        item->value = (char *)item + sizeof(hashtable_item);
        item->is_occupied = 0;
        item->is_deleted = 0;
        table->items[i] = item;
    }
}

void hashtable_insert(hash_table *table, const char *key, void *value)
{
    if (!table || !key || !value)
        return;

    size_t hash = hash_func(key, table->capacity);
    size_t steps = 0;
    size_t item_size = sizeof(hashtable_item) + table->value_size;

    while (steps < table->capacity)
    {
        size_t index = (hash + steps) % table->capacity;
        hashtable_item *item = table->items[index];

        if (!item->is_occupied || item->is_deleted)
        {
            item->key = key;
            memcpy(item->value, value, table->value_size);
            item->is_occupied = 1;
            item->is_deleted = 0;
            return;
        }
        else if (strcmp(item->key, key) == 0)
        {
            memcpy(item->value, value, table->value_size);
            return;
        }

        steps++;
    }
}

void *hashtable_get(hash_table *table, const char *key)
{
    if (!table || !key)
        return NULL;

    size_t hash = hash_func(key, table->capacity);
    size_t steps = 0;

    while (steps < table->capacity)
    {
        size_t index = (hash + steps) % table->capacity;
        hashtable_item *item = table->items[index];

        if (item->is_occupied && !item->is_deleted && strcmp(item->key, key) == 0)
        {
            return item->value;
        }
        else if (!item->is_occupied && !item->is_deleted)
        {
            return NULL;
        }

        steps++;
    }

    return NULL;
}

void hashtable_delete(hash_table *table, const char *key)
{
    if (!table || !key)
        return;

    size_t hash = hash_func(key, table->capacity);
    size_t steps = 0;
    size_t item_size = sizeof(hashtable_item) + table->value_size;

    while (steps < table->capacity)
    {
        size_t index = (hash + steps) % table->capacity;
        hashtable_item *item = table->items[index];

        if (item->is_occupied && !item->is_deleted && strcmp(item->key, key) == 0)
        {
            item->key = NULL;
            item->is_occupied = 0;
            item->is_deleted = 1;
            return;
        }
        else if (!item->is_occupied && !item->is_deleted)
        {
            return;
        }

        steps++;
    }
}

void hashtable_free(hash_table *table)
{
    if (!table || !table->allocator)
        return;

    pool_allocator_deinitialize(table->allocator);
    table->items = NULL;
    table->allocator = NULL;
}
