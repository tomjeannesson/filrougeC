/*
  Test du module directory.

  Crée un annuaire et le libère.
 */

#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <contact.h>

int main(void)
{
    printf("Creating dir");
    struct dir *dir = dir_create(5);
    printf("Displaying dir");
    display_dir(dir);
    printf("Deleting dir");
    dir_free(dir);

    return EXIT_SUCCESS;
}
