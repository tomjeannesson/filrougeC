#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <directory.h>
#include <linkedlist.h>
#include <contact.h>
#include <hash.h>

/*
  Un dir est une structure de données représentant un annuaire, composé de:
  - une longueur (int)
  - un nombre de contacts (int)
  - un tableau de longueur listes chainées contenant les contacts
  Il est défini dans directory.h
*/
struct dir;

bool resize = true;

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
dir_t *dir_create(uint32_t len)
{
    dir_t *temp = malloc(sizeof(list_t) * len + 2 * sizeof(uint32_t));
    temp->length = len;
    temp->num_elem = 0;
    for (uint32_t i = 0; i < len; i++)
    {
        temp->table[i] = init_list(NULL);
    }
    return temp;
}

dir_t *resize_dir(dir_t *directory, _Float32 increase_factor, _Float32 decrease_factor)
{
    dir_t *new_dir = NULL;
    uint32_t start = directory->length;
    uint32_t new_size = 0;
    if ((float)directory->num_elem / directory->length >= 0.75)
    {
        new_size = directory->length * increase_factor;
        new_dir = dir_create(new_size);
        for (uint32_t i = 0; i < directory->length; i++)
        {
            node_t *tmp = directory->table[i]->head;
            while (tmp)
            {
                dir_insert(new_dir, tmp->data->name, tmp->data->number);
                tmp = tmp->next;
            }
            free(tmp);
        }
    }
    else if ((float)directory->num_elem / directory->length <= 0.15)
    {
        new_size = directory->length * decrease_factor;
        if (new_size < 10)
        {
            if (directory->length >= 10)
            {
                new_size = 10;
            }
            else
            {
                new_size = directory->length;
            }
        }
        new_dir = dir_create(new_size);
        for (uint32_t i = 0; i < directory->length; i++)
        {
            node_t *tmp = directory->table[i]->head;
            while (tmp)
            {
                dir_insert(new_dir, tmp->data->name, tmp->data->number);
                tmp = tmp->next;
            }
            free(tmp);
        }
    }
    if (start != new_size && new_size != 0)
    {
        printf("###   Resizing from len %d to len %d.   ###\n", start, new_size);
    }
    return new_dir;
}

/*
  Applique le redimensionnement _resize_dir_ à un _dir.
*/
void apply_resize(dir_t *directory)
{
    if (resize)
    {
        resize = false;
        dir_t *resized_dir = resize_dir(directory, 2, 0.5);
        resize = true;
        if (resized_dir != NULL)
        {
            directory->length = resized_dir->length;
            directory->num_elem = resized_dir->num_elem;
            for (uint32_t i = 0; i < directory->length; i++)
            {
                directory->table[i] = resized_dir->table[i];
            }
        }
        free(resized_dir);
    }
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(dir_t *directory, const char *name, const char *num)
{
    contact_t *contact = init_contact(name, num);
    node_t *contact_node = init_node(contact);
    uint32_t hash_val = hash(name) % directory->length;

    node_t *tmp = in_list(directory->table[hash_val], name);
    if (tmp != NULL)
    {
        const char *store_num = tmp->data->number;
        tmp->data = contact;
        free(tmp);
        return (char *)store_num;
    }
    push(directory->table[hash_val], contact_node);
    directory->num_elem++;
    apply_resize(directory);
    free(tmp);
    return NULL;
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(dir_t *directory, const char *name)
{
    uint32_t hash_val = hash(name) % directory->length;
    node_t *tmp = in_list(directory->table[hash_val], name);
    if (tmp != NULL)
    {
        return tmp->data->number;
    }
    return NULL;
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(dir_t *directory, const char *name)
{
    if (dir_lookup_num(directory, name))
    {
        uint32_t hash_val = hash(name) % directory->length;
        if (directory->table[hash_val]->length == 0)
        {
            return;
        }
        if (directory->table[hash_val]->length == 1)
        {
            if (directory->table[hash_val]->head->data->name == name)
            {
                directory->table[hash_val]->head = NULL;
                directory->table[hash_val]->length = 0;
                directory->num_elem--;
            }
            apply_resize(directory);
            return;
        }
        node_t *prev = directory->table[hash_val]->head;
        node_t *current = directory->table[hash_val]->head->next;
        if (prev->data->name == name)
        {
            directory->table[hash_val]->head = current;
            directory->table[hash_val]->length--;
            directory->num_elem--;
            apply_resize(directory);
            return;
        }
        for (uint32_t i = 0; i < directory->table[hash_val]->length; i++)
        {
            if (current->data->name == name)
            {
                prev->next = current->next;
                directory->table[hash_val]->length--;
                directory->num_elem--;
                free(current);
                apply_resize(directory);
                return;
            }
            prev = current;
            current = current->next;
        }
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for (uint32_t i = 0; i < dir->length; i++)
    { 
        free(dir->table[i]->head); // On free change liste chainéé
    }
    free(dir); // On free le dir
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(dir_t *dir)
{
    printf("Directory of length %u containing %u elements:\n", dir->length, dir->num_elem);
    uint32_t count = 0;
    for (uint32_t i = 0; i < dir->length; i++)
    {
        if (dir->table[i]->head != NULL)
        {
            count = 0; // Compte le nombre de listes vides depuis la dernière liste pleine
            printf("\t%d\t", i);
            print_list(dir->table[i]);
            printf("\n");
        }
        else
        {
            count++;
            if ((i < dir->length - 1 && dir->table[i + 1]->head != NULL) || i == dir->length - 1) 
            {
                printf("     ( ... )\t\t|  (%dx) ", count); // On print toutes les listes vides ensemble
                print_list(dir->table[i]);
                printf("\n");
            }
        }
    }
}
