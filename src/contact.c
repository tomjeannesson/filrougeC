#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct contact
{
    char name[32];
    char number[32];
};

typedef struct LinkedList
{
    struct contact *data;
    struct LinkedList *next;
} list;

typedef list *node;

node create_node()
{
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    temp->next = NULL;
    return temp;
}
node append(node head, struct contact *value)
{
    node single_cell, full_list;        // declare two nodes temp and p
    single_cell = create_node(); // createNode will return a new node with data = value and next pointing to NULL.
    single_cell->data = value;  // add element's value to data part of node
    if (head == NULL)
    {
        head = single_cell; // when linked list is empty
    }
    else
    {
        full_list = head; // assign head to p
        while (full_list->next != NULL)
        {
            full_list = full_list->next; // traverse the list until p is the last node.The last node always points to NULL.
        }
        full_list->next = single_cell; // Point the previous last node to the new node created.
    }
    return head;
}

struct dir
{
    uint32_t *length;
    list *table[];
};

char *display_cell(list *head)
{
    char *res = "\0";
    struct LinkedList *current = head;
    while (current != NULL)
    {
        strcat(res, current->data->name);
        current = current->next;
    }
    return res;
}

void display_dir(struct dir *directory)
{
    printf("Directory of length %u\n", *directory->length);
    for (uint32_t i = 0; i < *directory->length; i++)
    {
        list *current_cell = directory->table[i];
        char *cell_str = display_cell(current_cell);
        printf("--> %s", cell_str);
    }
}

int main(int argc, char *argv[])
{
    // struct contact mycontact = {};
    // struct cell mycell = {"Tom", "06 38 18 92 31", NULL};
    // uint32_t * len = 1;
    // const char * name = "Tom";
    // const char * phone = "06 38 18 92 31";
    // struct dir mycell = {1, name, phone, NULL};
    printf("Start\n");
    node my_node = create_node();
    struct contact *tom = {"Tom", "06 38 18 92 31"};
    my_node->data = tom;

}
