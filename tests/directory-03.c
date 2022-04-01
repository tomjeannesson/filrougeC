/*
  Test du module directory.

  Crée un directory, y rajoute trois entrées, l'affiche et le libère.
  Deux entrées sont en conflit dans ce test.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <directory.h>

int main(void)
{
    struct dir *dir = dir_create(10);
    dir_print(dir);
    dir_insert(dir, "Colonel Moutarde", "06789435351", true);
    dir_print(dir);
    dir_insert(dir, "Caporal Ketchup", "0678346533", true);
    dir_print(dir);
    dir_insert(dir, "Sergent Mayo", "06723236533", true);
    dir_print(dir);
    dir_free(dir);

    return EXIT_SUCCESS;
}
