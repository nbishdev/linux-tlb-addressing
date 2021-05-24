#ifndef _FUNCT_
#define _FUNCT_

#include <string.h>
#include <math.h>
#include "types.h"

void dec2bin16 (int, char*);

void dec2bin8 (int, char*);

void bin2dec (int*, char*, int);

void logic_insert (char*, logic_t*, int);

void physic_insert (char*, char*, physic_t*);

#endif
