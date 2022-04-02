#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdint.h>
#include <contact.h>

typedef struct node
{
    contact_t *data;
    struct node *next;
} node_t;

extern node_t *init_node(contact_t *contact);

typedef struct LinkedList
{
    uint32_t length;
    node_t *head;
} list_t;

extern list_t *init_list(node_t *head);

extern void print_list(list_t *list);

extern list_t *append(list_t *list, node_t *node);

extern void push(list_t *list, node_t *node);

extern node_t *in_list(list_t *list, const char *name);

#endif /* _LINKEDLIST_H */
