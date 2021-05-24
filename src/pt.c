#include "pt.h"

void PT_init (pt_t* pt)
{
	int i;
	
	for (i = 0; i < 256; i++)
	{
		pt[i].frame = -1;
		pt[i].valid = 0;
	}
}

void PT_update (pt_t* pt, int page, int lastframe)
{
	pt[page].frame = lastframe - 1;
	pt[page].valid = 1;
}
