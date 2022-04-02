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

void contact_print(contact_t *contact)
{
    printf("Name: %s\nNumber: %s\n", contact->name, contact->number);
}

