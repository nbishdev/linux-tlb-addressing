#ifndef _TLB_
#define _TLB_

#include "types.h"

void TLB_init (tlb_t*);

int TLB_insert (tlb_t*, pt_t*, char**, int);

void TLB_update (tlb_t*, pt_t*, int, int, int);

void TLB_clean (tlb_t*);

#endif
