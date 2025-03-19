#include "list.h"
#include <stdlib.h>

size_t list_get_size(list_t *head)
{
    list_t *last_node = head->next;
    int i = 1;
    while (last_node != NULL)
    {
        last_node = last_node->next;
        i++;
    }

    return i;
}

list_t *list_create(int data)
{
    list_t *new_node = (list_t *)malloc(sizeof(list_t));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void list_free(list_t *head)
{
    list_t *current, *tmp;

    if (head != NULL)
    {
        current = head->next;
        head->next = NULL;
        while (current != NULL)
        {
            tmp = current->next;
            free(current);
            current = tmp;
        }

        free(head);
    }
}

void list_insert_head(list_t **head, int data)
{
    list_t *new_node = list_create(data);
    new_node->next = *head;
    *head = new_node;
}

void list_insert_end(list_t **head, int data)
{
    list_t *current = *head;
    list_t *new_node = list_create(data);

    if (head == NULL)
    {
        *head = new_node;
    }

    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

void list_insert_at(list_t **head, int data, size_t position)
{
    if (head == NULL)
        return;

    if (position == 0)
    {
        list_insert_head(head, data);
        return;
    }

    list_t *previous = NULL;
    list_t *current = *head;
    int i = 0;

    while (current != NULL)
    {
        previous = current;
        current = current->next;
        i++;

        if (i == position)
            break;
    }

    if (position > i)
        return;

    list_t *new_node = list_create(data);
    previous->next = new_node;
    new_node->next = current;
}

void list_delete_at(list_t **head, size_t position)
{
    if (head == NULL)
        return;

    list_t *previous = NULL;
    list_t *current = *head;
    int i = 0;

    if (position == 0)
    {
        if (current->next == NULL)
        {
            free(current);
            return;
        }

        *head = current->next;
        free(current);
        return;
    }

    while (current != NULL)
    {
        previous = current;
        current = current->next;
        i++;

        if (i == position)
            break;
    }

    if (i > position)
        return;

    previous->next = current->next;
    free(current);
}

int list_get_at(list_t **head, size_t position)
{
    if (head == NULL)
        return 0;

    list_t *current = *head;
    int i = 0;

    while (i < position)
    {
        if (current->next != NULL)
        {
            current = current->next;
            i++;
        }
        else
            return -1;
    }

    return current->data;
}
