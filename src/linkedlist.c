#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
node_t *init_node(contact_t *contact)
{
    node_t *temp = malloc(sizeof(node_t));
    temp->data = contact;
    temp->next = NULL;
    return temp;
}

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

/*
  Affiche une liste chainée.
*/
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
        printf("Empty List");
        return;
    }
    else
    {
        printf("Len %d:  |  ", list->length);
    }
    while (temp != NULL)
    {
        printf("[%s ; %s] -> ", temp->data->name, temp->data->number);
        temp = temp->next;
    }
    printf("NULL");
}

/*
  Ajoute un élément en fin de liste chainée, et retourne cette liste.
*/
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

/*
  Retourne la cellule contenant le contact du nom demandé si ce dernier est dans la liste, sinon NULL.
*/
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

/*
  Ajoute une cellule en tete de liste.
*/
void push(list_t *list, node_t *node)
{
    node->next = list->head;
    list->head = node;
    list->length++;
}