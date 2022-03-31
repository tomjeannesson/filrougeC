#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>

typedef struct dir
{
    uint32_t length;
    uint32_t num_elem;
    list_t *table[];
} dir_t;

dir_t *resize_dir(dir_t *directory, _Float32 increase_factor, _Float32 decrease_factor)
{
    dir_t *new_dir = NULL;
    if (directory->num_elem / directory->length > 1.5)
    {
        uint32_t new_size = directory->length * increase_factor;
        new_dir = dir_create(new_size);
        for (uint32_t i = 0; i < directory->length; i++)
        {
            node_t *tmp = directory->table[i]->head;
            while (tmp)
            {
                dir_insert(new_dir, tmp->data->name, tmp->data->number, false);
                dir_print(new_dir);
                tmp = tmp->next;
            }
        }
        dir_free(directory);

    }
    else if (directory->num_elem / directory->length < 0.5)
    {
        uint32_t new_size = directory->length * decrease_factor;
        new_dir = dir_create(new_size);
        for (uint32_t i = 0; i < directory->length; i++)
        {
            node_t *tmp = directory->table[i]->head;
            while (tmp)
            {
                dir_insert(new_dir, tmp->data->name, tmp->data->number, false);
                dir_print(new_dir);
                tmp = tmp->next;
            }
        }
        dir_free(directory);
    }
    return new_dir;
}

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
dir_t *dir_create(uint32_t len)
{
    dir_t *temp = malloc(sizeof(list_t) * len);
    temp->length = len;
    temp->num_elem = 0;
    for (uint32_t i = 0; i < len; i++)
    {
        temp->table[i] = init_list(NULL);
    }
    return temp;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(dir_t *directory, const char *name, const char *num, bool resize)
{
    contact_t *contact = init_contact(name, num);
    node_t *contact_node = init_node(contact);
    if (resize)
    {
        printf("RESIZING\n");
        dir_t *resized_dir = resize_dir(directory, 2, 0.5);
        if (resized_dir != NULL)
        {
            directory->length = resized_dir->length;
            directory->num_elem = resized_dir->num_elem;
            *directory->table = *resized_dir->table;
            free(resized_dir);
        }
        dir_print(directory);
        printf("END OF RESIZING\n");

    }
    uint32_t hash_val = hash(name) % directory->length;
    // print_list(directory->table[hash_val]);
    printf("%s => hash %d\n", name, hash_val);
    node_t *tmp = in_list(directory->table[hash_val], name);
    if (tmp != NULL)
    {
        const char *store_num = tmp->data->number;
        tmp->data = contact;
        return (char *)store_num;
    }
    if (contact_node->next)
    {
        printf("%s", contact_node->next->data->name);
    }
    append(directory->table[hash_val], contact_node);
    directory->num_elem++;

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
    if (dir_lookup_num(directory, name) != NULL)
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
            }
            return;
        }
        node_t *prev = directory->table[hash_val]->head;
        node_t *current = directory->table[hash_val]->head->next;
        if (prev->data->name == name)
        {
            directory->table[hash_val]->head = current;
            directory->table[hash_val]->length--;
            return;
        }
        for (uint32_t i = 0; i < directory->table[hash_val]->length; i++)
        {
            if (current->data->name == name)
            {
                prev->next = current->next;
                directory->table[hash_val]->length--;
                free(current);
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
    free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(dir_t *dir)
{
    printf("Directory of length %u containing %d elements:\n", dir->length, dir->num_elem);
    uint32_t count = 0;
    for (uint32_t i = 0; i < dir->length; i++)
    {
        if (dir->table[i]->head != NULL)
        {
            count = 0;
            printf("\t%d\t", i);
            print_list(dir->table[i]);
            printf("\n");
        }
        else
        {
            count++;
            if ((i < dir->length - 1 && dir->table[i + 1]->head != NULL) || i == dir->length - 1)
            {
                printf("     ( ... )\t(%dx) ", count);
                print_list(dir->table[i]);
                printf("\n");
            }
        }
    }
}
