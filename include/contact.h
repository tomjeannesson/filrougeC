#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact;

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */
/* 
    Implémetation d'une liste chainée simple.
*/
struct cell;

struct dir;

extern char *display_cell(struct cell *head);

extern void display_dir(struct dir *directory); 



#endif /* _CONTACT_H_ */
