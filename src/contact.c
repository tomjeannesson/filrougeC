#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
  Structure de données représentant une personne.
    Attributs:
      const char *name (pointeur veres le nom de la personne)
      const char *number (pointeur veres le numéro de la personne)
*/
typedef struct contact
{
    const char *name;
    const char *number;
} contact_t;

/*
  Retourne un pointeur vers un nouveau contact.
*/
contact_t *init_contact(const char *name, const char *number)
{
    contact_t *temp = malloc(sizeof(contact_t));
    temp->name = name;
    temp->number = number;
    return temp;
}

/*
  Affiche un contact.
*/
void contact_print(contact_t *contact)
{
    printf("Name: %s\nNumber: %s\n", contact->name, contact->number);
}

