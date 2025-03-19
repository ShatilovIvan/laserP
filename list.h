#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct node
{
    int data;
    struct node *next;
} list_t;

size_t list_get_size(list_t *head);

list_t *list_create(int);

void list_free(list_t *);

void list_insert_head(list_t **, int);

void list_insert_end(list_t **, int);

void list_insert_at(list_t **, int, size_t);

void list_delete_at(list_t **, size_t);

int list_get_at(list_t **, size_t);

#endif
