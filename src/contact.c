#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
    int length;
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
        printf("NULL\n");
        return;
    }
    node_t *temp = list->head;
    if (list->head == NULL)
    {
        printf("Empty List\n");
    }
    else
    {
        // printf("Linked List:\n\t");
    }
    while (temp != NULL)
    {
        // printf(temp->data->name);
        printf("[%s ; %s] -> ", temp->data->name, temp->data->number);
        temp = temp->next;
    }
    printf("NULL\n");
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
        list->head = tmp;
        list->length++;
    }
    return list;
}

typedef struct dir
{
    uint32_t length;
    list_t *table[];
} dir_t;

dir_t *init_dir(int len)
{
    dir_t *temp = malloc(sizeof(node_t) * len);
    temp->length = len;
    list_t *array[len];
    for (int i = 0; i < len; i++)
    {
        array[i] = init_list(NULL);
    }
    return temp;
}

int hash(contact_t *contact)
{
    int res = 0;
    for (int i = 0; i < strlen(contact->name); i++)
    {
        res += contact->name[i];
    }
    for (int i = 0; i < strlen(contact->number); i++)
    {
        res += contact->number[i];
    }
    return res % 10;
}

void add_contact(contact_t *contact, dir_t *directory)
{
    int hash_val = hash(contact);
    if (hash_val > directory->length)
    {
        printf("Can't add this contact because hash value is too high (%d is greater than %d).\n", hash_val, directory->length);
    }
    else
    {
        node_t *tmp = init_node(contact);
        directory->table[hash_val] = append(directory->table[hash_val], tmp);
    }
}

void add_contacts(contact_t *contacts[], dir_t *directory, uint16_t len)
{
    for (int i = 0; i < len; i++)
    {
        add_contact(contacts[i], directory);
    }
}


void display_dir(dir_t *directory)
{
    printf("Directory of length %u\n", directory->length);
    for (int i = 0; i < directory->length; i++)
    {
        printf("\t=>  ");
        print_list(directory->table[i]);
    }
}

int main(int argc, char *argv[])
{
    contact_t *tom = init_contact("Tom", "06 38 18 92 31");
    contact_t *helo = init_contact("Helo", "06 99 99 99 99");
    contact_t *per1 = init_contact("per1", "06 00 00 00 00");
    contact_t *per2 = init_contact("per2", "06 11 11 11 11");
    contact_t *per3 = init_contact("per3", "06 11 11 11 11");
    contact_t *per4 = init_contact("per4", "06 11 11 11 11");
    int num_contacts = 6;
    contact_t *my_contacts[6] = {tom, helo, per1, per2, per3, per4};
 

    // contact_t tom = *init_contact("Tom", "06 38 18 92 31");
    // contact_t helo = *init_contact("Helo", "06 99 99 99 99");
    // contact_t per1 = *init_contact("per1", "06 00 00 00 00");
    // contact_t per2 = *init_contact("per2", "06 11 11 11 11");
    // contact_t my_contacts[4] = {tom, helo, per1, per2};

    // node_t *my_node = init_node(tom);
    // append(my_node, helo);
    // append(my_node, per1);
    // append(my_node, per2);
    // list_t *my_list = init_list(my_node);
    // print_list(my_list);

    dir_t *my_dir = init_dir(10);
    // my_dir->table[hash(&tom)] = my_list;
    // add_contact(tom, my_dir);
    add_contacts(my_contacts, my_dir, num_contacts);

    display_dir(my_dir);
}
