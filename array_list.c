#include "array_list.h"
#include "linear_allocator.h"

void array_list_initialize(array_list_t *list, linear_allocator_t *allocator,
                           size_t element_size) {
  if (list == NULL)
    return;

  list->allocator = allocator;
  list->element_size = element_size;
  list->count = 0;
  list->capacity = DEFAULT_CAPACITY;
  list->data = NULL;
}

void array_list_add(array_list_t *list, void *data, size_t index) {
  if (list == NULL || list->allocator == NULL)
    return;

  if (index > list->count || index < 0)
    return;

  if (list->data == NULL) {
    list->data = linear_allocator_alloc(list->allocator,
                                        list->capacity * list->element_size);

    if (list->data == NULL)
      return;
  }

  if (list->count == list->capacity) {
    size_t new_capacity = list->capacity * 2;
    void *new_data = linear_allocator_alloc(list->allocator,
                                            new_capacity * list->element_size);

    if (new_data == NULL)
      return;

    memcpy(new_data, list->data, list->count * list->element_size);
    list->data = new_data;
    list->capacity = new_capacity;
  }

  memcpy((char *)list->data + index * list->element_size, data,
         list->element_size);
  list->count++;
}

void *array_list_get(array_list_t *list, size_t index) {
  if (list == NULL)
    return NULL;

  if (index >= list->count || index < 0)
    return NULL;

  return (char *)list->data + index * list->element_size;
}

void array_list_delete(array_list_t *list, size_t index) {
  if (list == NULL)
    return;

  if (index >= list->count || index < 0)
    return;

  memmove((char *)list->data + index * list->element_size,
          (char *)list->data + (index + 1) * list->element_size,
          (list->count - index - 1) * list->element_size);
  list->count--;
}

void array_list_free(array_list_t *list) {
  if (list == NULL || list->allocator == NULL)
    return;

  linear_allocator_reset(list->allocator);
  list->data = NULL;
  list->count = 0;
  list->element_size = 0;
}
