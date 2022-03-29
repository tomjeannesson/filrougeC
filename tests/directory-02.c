/*
  Test du module directory.

  Crée un annuaire, y rajoute une entrée, l'affiche et le libère.
 */

#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <contact.h>

int main(void)
{
    struct dir *dir = dir_create(5);
    display_dir(dir);
    printf("Start");
    dir_insert(dir, "Colonel Moutarde", "06789435351");
    // dir_print(dir);
    // dir_free(dir);

    // (void)dir;
    return EXIT_SUCCESS;
}
