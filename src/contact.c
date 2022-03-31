#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// #include <hash.h>

typedef struct contact
{
    const char *name;
    const char *number;
} contact_t;

contact_t *init_contact(const char *name, const char *number)
{
    contact_t *temp = malloc(sizeof(contact_t));
    temp->name = name;
    temp->number = number;
    return temp;
}

void contact_print(contact_t *contact)
{
    printf("Name: %s\nNumber: %s\n", contact->name, contact->number);
}

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
        printf("Empty List (Len == %d && Head == NULL)", list->length);
        return;
    }
    else
    {
        printf("Len %d:  |  ", list->length);
    }
    while (temp != NULL)
    {
        // printf(temp->data->name);
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

int main()
{
    contact_t *tom = init_contact("Tom", "06 38 18 92 31");
    contact_t *helo = init_contact("Helo", "06 99 99 99 99");
    // contact_t *per1 = init_contact("per1", "06 00 00 00 00");
    // contact_t *per2 = init_contact("per2", "06 11 11 11 11");
    // contact_t *per3 = init_contact("per3", "06 11 11 11 11");
    // contact_t *per4 = init_contact("per4", "06 11 11 11 11");
    node_t *my_node = init_node(tom);
    node_t *helo_n = init_node(helo);
    list_t *my_list = init_list(NULL);
    append(my_list, my_node);
    append(my_list, helo_n);
    print_list(my_list);
    printf("\n");
}
