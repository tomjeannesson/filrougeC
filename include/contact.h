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

typedef struct node
{
    contact_t *data;
    struct node *next;
} node_t;

extern node_t *init_node(contact_t *contact);

typedef struct LinkedList
{
    int length;
    node_t *head;
} list_t;

extern list_t *init_list(node_t *head);

extern void print_list(list_t *list);

extern list_t *append(list_t *list, node_t *node);

typedef struct dir
{
    uint32_t length;
    list_t *table[];
} dir_t;

extern dir_t *init_dir(int len);

extern void display_dir(struct dir *directory);

#endif /* _CONTACT_H_ */
