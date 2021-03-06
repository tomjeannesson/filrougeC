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
        temp->table[i] = init_list(NULL); // On initie chaque case du tableau à une liste vide
    }
    return temp;
}

/*
  Si nécessaire, redimensionne un _dir_, selon un facteur d'agrandissement 
  _increase_factor_ ou un facteur de rétrécissement _decrease_factor_.
  Retourne un nouveau dir redimentionné.
*/
dir_t *resize_dir(dir_t *directory, _Float32 increase_factor, _Float32 decrease_factor)
{
    dir_t *new_dir = NULL;
    uint32_t start = directory->length;
    uint32_t new_size = 0;
    if ((float)directory->num_elem / directory->length >= 0.75)
    // si le dir est rempli à plus de 75%, on le grandit
    {
        new_size = directory->length * increase_factor;
        new_dir = dir_create(new_size);
        for (uint32_t i = 0; i < directory->length; i++)
        // on parcourt le dir pour transférer toutes les cellules
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
    // si le dir est rempli à moins de 15%, on le grandit
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
                new_size = directory->length; // si le dir avait une taille de moins de 10, on lui laisse sa taille
            }
        }
        new_dir = dir_create(new_size);
        for (uint32_t i = 0; i < directory->length; i++)
        // on parcourt le dir pour transférer toutes les cellules
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
        // si on a resize le dir, on copie toutes les attributs du nouveau dir dans l'ancien
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
    if (tmp)
    {
        const char *store_num = tmp->data->number;
        tmp->data = contact;
        free(tmp);
        return (char *)store_num;
    }
    push(directory->table[hash_val], contact_node); // On ajoute le nouveau contact en tete de liste
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
    if (dir_lookup_num(directory, name)) // si le contatc est dans le dir
    {
        uint32_t hash_val = hash(name) % directory->length;
        if (directory->table[hash_val]->length == 0) 
        // si la liste est vide, on ne fait rien
        {
            return;
        }
        if (directory->table[hash_val]->length == 1)
        // si la liste est de longueur 1, on la vide
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
        // si le contact est dans la premiere cellule
        {
            directory->table[hash_val]->head = current;
            directory->table[hash_val]->length--;
            directory->num_elem--;
            apply_resize(directory);
            return;
        }
        for (uint32_t i = 0; i < directory->table[hash_val]->length; i++)
        // sinon, on avance dans la liste jusqu'à le trouver
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
    else
    {
        printf("%s isn't in this directory.\n", name);
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    node_t *next;
    for (uint32_t i = 0; i < dir->length; i++)
    {
        node_t *tmp = dir->table[i]->head; 
        while (tmp){
            next = tmp->next;
            free(tmp->data); // On free le contact
            free(tmp); // On free la cellule
            tmp = next;
        }
        free(dir->table[i]); // On free la liste chainée
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
