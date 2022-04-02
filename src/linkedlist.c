#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <contact.h>

typedef struct node
{
    contact_t *data;
    struct node *next;
} node_t;

node_t *init_node(contact_t *contact)
{
    node_t *temp = malloc(sizeof(node_t));
    temp->data = contact;
    temp->next = NULL;
    return temp;
}

typedef struct LinkedList
{
    uint32_t length;
    node_t *head;
} list_t;

list_t *init_list(node_t *head)
{
    list_t *temp = malloc(sizeof(list_t));
    if (head == NULL)
    {
        temp->length = 0;
    }
    else
    {
        temp->length = 1;
    }
    temp->head = head;
    return temp;
}

void print_list(list_t *list)
{
    if (list == NULL)
    {
        printf("NULL");
        return;
    }
    node_t *temp = list->head;
    if (list->head == NULL)
    {
        printf("Empty List");
        return;
    }
    else
    {
        printf("Len %d:  |  ", list->length);
    }
    while (temp != NULL)
    {
        printf("[%s ; %s] -> ", temp->data->name, temp->data->number);
        temp = temp->next;
    }
    printf("NULL");
}

list_t *append(list_t *list, node_t *node)
{
    if (list == NULL)
    {
        list = init_list(node);
    }
    else if (list->head == NULL)
    {
        list->head = node;
        list->length++;
    }
    else
    {
        node_t *tmp = list->head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = node;
        list->length++;
    }
    return list;
}

node_t *in_list(list_t *list, const char *name)
{
    node_t *tmp = list->head;
    while (tmp != NULL)
    {
        if (tmp->data->name == name)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void push(list_t *list, node_t *node)
{
    node->next = list->head;
    list->head = node;
    list->length++;
}