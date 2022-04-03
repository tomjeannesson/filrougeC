#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
  Retourne un entier correspondant au hash du nom donné.
*/
extern uint32_t hash(const char *str);

#endif /* _HASH_H_ */
