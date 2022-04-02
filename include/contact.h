#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
typedef struct contact
{
    const char *name;
    const char *number;
} contact_t;

extern contact_t *init_contact(const char *name, const char *number);

extern void contact_print(contact_t *contact);

#endif /* _CONTACT_H_ */
