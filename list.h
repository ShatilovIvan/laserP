#ifndef LIST_H
#define LIST_H

#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

size_t list_get_size(struct node *head);

struct node *list_create(int);

void list_free(struct node *);

void list_insert_head(struct node **, int);

void list_insert_end(struct node **, int);

void list_insert_at(struct node **, int, size_t);

void list_delete_at(struct node **, size_t);

int list_get_at(struct node **, size_t);

#endif
