#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdint.h>
#include <contact.h>

/*
  Structure de données représentant une cellule d'une liste chainée.
    Attributs:
      contact_t *data (un pointeur vers un contact)
      struct node *next (un pointeur vers la cellule suivante)
*/
typedef struct node
{
    contact_t *data;
    struct node *next;
} node_t;

/*
  Retourne un pointeur vers une nouvelle cellule.
*/
extern node_t *init_node(contact_t *contact);

/*
  Structure de données représentant une liste chainée.
    Attributs:
      uint32_t length (longeur de la liste)
      node_t *head (pointeur vers la première cellule de la liste)
*/
typedef struct LinkedList
{
    uint32_t length;
    node_t *head;
} list_t;

/*
  Retourne un pointeur vers une nouvelle liste.
*/
extern list_t *init_list(node_t *head);

/*
  Affiche une liste chainée.
*/
extern void print_list(list_t *list);

/*
  Ajoute un élément en fin de liste chainée, et retourne cette liste.
*/
extern list_t *append(list_t *list, node_t *node);

/*
  Retourne la cellule contenant le contact du nom demandé si ce dernier est dans la liste, sinon NULL.
*/
extern node_t *in_list(list_t *list, const char *name);

/*
  Ajoute une cellule en tete de liste.
*/
extern void push(list_t *list, node_t *node);

#endif /* _LINKEDLIST_H */
