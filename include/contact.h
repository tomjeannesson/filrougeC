#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
typedef struct contact
{
    const char *name;
    const char *number;
} contact_t;

extern contact_t *init_contact(const char *name, const char *number);
extern void contact_print(contact_t *contact);


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

#endif /* _CONTACT_H_ */
