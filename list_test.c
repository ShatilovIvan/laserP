#include "list.h"
#include <assert.h>

void list_get_size_test()
{
    list_t *list = list_create(10);
    list_insert_end(&list, 20);

    assert(list_get_size(list) == 2);

    list_free(list);
}

void list_create_test()
{
    list_t *list = list_create(10);
    assert(list != NULL);
    assert(list->data == 10);

    list_free(list);
}

void list_insert_head_test()
{
    list_t *list = list_create(10);
    list_insert_head(&list, 20);
    assert(list->data == 20);

    list_free(list);
}

void list_insert_end_test()
{
    list_t *list = list_create(10);
    list_insert_end(&list, 20);
    assert(list->next->data == 20);

    list_free(list);
}

void list_insert_at_test()
{
    list_t *list = list_create(10);
    list_insert_end(&list, 20);
    list_insert_at(&list, 30, 1);
    assert(list->next->data == 30);

    list_free(list);
}

void list_delete_at_test()
{
    list_t *list = list_create(10);
    list_insert_end(&list, 20);
    list_delete_at(&list, 0);
    assert(list->data == 20);

    list_free(list);
}

void list_get_at_test()
{
    list_t *list = list_create(10);
    list_insert_end(&list, 20);
    list_insert_end(&list, 30);
    assert(list_get_at(&list, 1) == 20);

    list_free(list);
}

int main()
{
    list_get_size_test();
    list_create_test();
    list_insert_head_test();
    list_insert_end_test();
    list_insert_at_test();
    list_delete_at_test();
    list_get_at_test();
    printf("success\n");
    return 0;
}
