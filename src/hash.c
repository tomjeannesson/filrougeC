#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
  Retourne un entier correspondant au hash du nom donné.
*/
uint32_t hash(const char *str)
{
    uint32_t hash = 5381;
    for (uint32_t i = 0; i < strlen(str); i++)
    {
        hash = hash * 33 + str[i];
    }
    return hash;
}
