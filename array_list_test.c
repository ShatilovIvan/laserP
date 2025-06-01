#include "array_list.h"
#include <assert.h>
#include <stdio.h>

void array_list_init_test() {
  linear_allocator_t *allocator = linear_allocator_initialize(4 * sizeof(int));
  array_list_t array_list;
  array_list_initialize(&array_list, allocator, sizeof(int));

  assert(array_list.allocator == allocator);
  assert(array_list.count == 0);
  assert(array_list.capacity == DEFAULT_CAPACITY);
  assert(array_list.element_size == sizeof(int));

  array_list_free(&array_list);
  linear_allocator_deinitialize(allocator);
}

void array_list_add_test() {
  linear_allocator_t *allocator = linear_allocator_initialize(4 * sizeof(int));
  array_list_t array_list;
  array_list_initialize(&array_list, allocator, sizeof(int));

  int a = 1;
  int b = 2;

  char letter = 'A';

  array_list_add(&array_list, &a, 0);
  array_list_add(&array_list, &b, 1);
  array_list_add(&array_list, &b, -1);

  assert(*(int *)array_list_get(&array_list, 0) == a);
  assert(*(int *)array_list_get(&array_list, 1) == b);
  assert(array_list_get(&array_list, -1) == NULL);

  array_list_add(&array_list, &letter, 0);

  assert(*(char *)array_list_get(&array_list, 0) == letter);

  array_list_free(&array_list);
  linear_allocator_deinitialize(allocator);
}

void array_list_delete_test() {
  linear_allocator_t *allocator = linear_allocator_initialize(4 * sizeof(int));
  array_list_t array_list;
  array_list_initialize(&array_list, allocator, sizeof(int));

  int a = 1;
  int b = 2;

  array_list_add(&array_list, &a, 0);
  array_list_add(&array_list, &b, 1);

  array_list_delete(&array_list, 0);

  assert(*(int *)array_list_get(&array_list, 0) == b && array_list.count == 1);

  array_list_free(&array_list);
  linear_allocator_deinitialize(allocator);
}

void array_list_resize_test() {
  linear_allocator_t *allocator =
      linear_allocator_initialize(100 * sizeof(int));
  array_list_t array_list;
  array_list_initialize(&array_list, allocator, sizeof(int));

  int a = 1;

  array_list_add(&array_list, &a, 0);
  array_list_add(&array_list, &a, 1);
  array_list_add(&array_list, &a, 2);
  array_list_add(&array_list, &a, 3);

  assert(array_list.capacity == 4);

  array_list_add(&array_list, &a, 4);
  assert(array_list.capacity == 8);

  array_list_free(&array_list);
  linear_allocator_deinitialize(allocator);
}

int main() {
  array_list_init_test();
  array_list_add_test();
  array_list_delete_test();
  array_list_resize_test();
  printf("Success!\n");
  return 0;
}
