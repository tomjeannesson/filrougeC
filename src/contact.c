#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct contact
{
    /* data */
    char name[32];
    char number[32];
};

struct cell
{
    struct contact *data;
    struct cell *next;
};

struct dir
{
    uint32_t length;
    struct cell table[];
};
char display_cell(struct cell *head)
{
    char res[] = "\0";
    struct cell *current = head;
    while (current != NULL)
    {
        strcat(res, current->data->name);
        current = current->next;
    }
    return *res;
}
void display_dir(struct dir *directory)
{
    printf("Directory\n");
    for (uint32_t i = 0; i < directory->length; i++)
    {
        // printf("--> %s", display_cell(directory.table[i]));
    }
}
