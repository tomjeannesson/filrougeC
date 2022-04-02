#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <stdint.h>
#include <stdbool.h>

#include <linkedlist.h>
#include <contact.h>
#include <hash.h>

/*
  Structure de données représentant un annuaire.
  Son contenu est détaillé dans directory.c.
*/
typedef struct dir
{
    uint32_t length;
    uint32_t num_elem;
    list_t *table[];
} dir_t;

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
extern struct dir *dir_create(uint32_t len);

/*
  Si nécessaire, redimensionne un _dir_, selon un facteur d'agrandissement 
  _increase_factor_ ou un facteur de rétrécissement _decrease_factor_.
*/
extern struct dir *resize_dir(dir_t *directory, _Float32 increase_factor, _Float32 decrease_factor);

/*
  Applique le redimensionnement _resize_dir_ à un _dir.
*/
extern void apply_resize(dir_t *directory);
/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
extern char *dir_insert(struct dir *dir, const char *name, const char *num);

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun
  contact ne correspond, retourne NULL.
*/
extern const char *dir_lookup_num(struct dir *dir, const char *name);

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
extern void dir_delete(struct dir *dir, const char *name);

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
extern void dir_free(struct dir *dir);

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
extern void dir_print(struct dir *dir);

#endif /* _DIRECTORY_H_ */
