#include "ft.h"

extern int frames;

int lastframe = 0;

void FT_init (char** ft)
{
	int i;
	
	for (i = 0; i < frames; i++)
		ft[i][0] = '\0';
}

void FT_insert (tlb_t* tlb, pt_t* pt, char** ft, char* data, int page)
{
	memcpy(ft[lastframe], data, 256 * sizeof(char));
	lastframe++;
	PT_update(pt, page, lastframe);
	TLB_clean(tlb);
	TLB_update(tlb, pt, page, lastframe, 0);
}
