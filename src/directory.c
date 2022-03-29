#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
dir_t *dir_create(uint32_t len)
{
    return init_dir(len);
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
    uint32_t hash_val = hash(contact->name);
    if (hash_val > directory->length)
    {
        printf("Can't add this contact because hash value is too high (%d is greater than %d).\n", hash_val, directory->length);
    }
    else
    {
        int is_in_list = 0;
        node_t *tmp = directory->table[hash_val]->head;

        while (is_in_list == 0 && tmp != NULL)
        {
            if (tmp->data->name == name)
            {
                is_in_list = 1;
            }
            tmp = tmp->next;
        }

        if (is_in_list == 1)
        {
            char *store_num = tmp->data->number;
            // tmp->data->number = num;
            return store_num;
        }

        node_t *temp = init_node(contact);
        directory->table[hash_val] = append(directory->table[hash_val], tmp);
    }
    return NULL;
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    (void)dir;
    (void)name;
    return NULL;
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    (void)dir;
    (void)name;
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    (void)dir;
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    (void)dir;
}
