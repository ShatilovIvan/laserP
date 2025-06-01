#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#define DEFAULT_CAPACITY 4

#include "linear_allocator.h"
#include <memory.h>
#include <stdlib.h>

typedef struct {
  void *data;
  size_t count;
  size_t capacity;
  size_t element_size;
  linear_allocator_t *allocator;
} array_list_t;

void array_list_initialize(array_list_t *list, linear_allocator_t *allocator,
                           size_t element_size);

void array_list_add(array_list_t *list, void *data, size_t index);

void *array_list_get(array_list_t *list, size_t index);

void *array_list_get(array_list_t *list, size_t index);

void array_list_delete(array_list_t *list, size_t index);

void array_list_free(array_list_t *list);

#endif
