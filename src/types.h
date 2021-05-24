#ifndef _TYPES_
#define _TYPES_

typedef struct {
	char page[9];
	char offset[9];
} logic_t;

typedef struct {
	char frame[9];
	char offset[9];
} physic_t;

typedef struct {
	int page;
	int frame;
} tlb_t;

typedef struct {
	int frame;
	int valid;
} pt_t;

#endif
