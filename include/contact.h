#ifndef _CONTACT_H_
#define _CONTACT_H_

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
extern contact_t *init_contact(const char *name, const char *number);

/*
  Affiche un contact.
*/
extern void contact_print(contact_t *contact);

#endif /* _CONTACT_H_ */
