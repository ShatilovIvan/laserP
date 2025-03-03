#include "list.h"

#include <stdlib.h>

size_t list_get_size(struct node *head)
{
    struct node *last_node = head->next;
    int i = 1;
    while (last_node != NULL)
    {
        last_node = last_node->next;
        i++;
    }

    return i;
}

struct node *list_create(int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void list_free(struct node *head)
{
    struct node *current, *tmp;

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

void list_insert_head(struct node **head, int data)
{
    struct node *new_node = list_create(data);
    new_node->next = *head;
    *head = new_node;
}

void list_insert_end(struct node **head, int data)
{
    struct node *current = *head;
    struct node *new_node = list_create(data);

    if (*head == NULL)
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

void list_insert_at(struct node **head, int data, size_t position)
{
    if (position == 0 || *head == NULL)
    {
        list_insert_head(head, data);
        return;
    }

    struct node *previous = NULL;
    struct node *current = *head;
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

    struct node *new_node = list_create(data);
    previous->next = new_node;
    new_node->next = current;
}

void list_delete_at(struct node **head, size_t position)
{
    if (head == NULL)
        return;

    struct node *previous = NULL;
    struct node *current = *head;
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

int list_get_at(struct node **head, size_t position)
{
    if (head == NULL)
        return 0;

    struct node *current = *head;
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