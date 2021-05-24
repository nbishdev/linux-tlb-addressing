#include "tlb.h"

int counter = 0;

void TLB_init (tlb_t* tlb)
{
	int i;
	
	for (i = 0; i < 16; i++)
	{
		tlb[i].page = -1;
		tlb[i].frame = -1;
	}
}

int TLB_insert (tlb_t* tlb, pt_t* pt, char** ft, int page)
{
	int i, hit;
	
	hit = -1;
	for (i = 0; i < counter; i++)
	{
		if (tlb[i].page == page)
		{
			hit = 1;
			break;
		}
	}
	if (hit == -1)
	{
		if (pt[page].valid == 1)
		{
			TLB_update(tlb, pt, page, i, 0);
			hit = 0;
		}
	}
	else
		TLB_update(tlb, pt, page, i, 1);
	
	return hit;
}

void TLB_update (tlb_t* tlb, pt_t* pt, int page, int pos, int hit)
{
	int i;
	
	if (hit == 1)
	{
		tlb_t t;
		t = tlb[pos];
		for (i = pos; i < counter - 1; i++)
			tlb[i] = tlb[i + 1];
		tlb[counter - 1] = t;
	}
	else
	{
		if (counter < 16)
		{
			tlb[counter - 1].page = page;
			counter++;
		}
		else
		{
			for (i = 0; i < 15; i++)
				tlb[i] = tlb[i + 1];
			tlb[15].page = page;
		}
	}
	for (i = 0; i < counter; i++)
		tlb[i].frame = pt[tlb[i].page].frame;
}

void TLB_clean (tlb_t* tlb)
{
	int i, j, k;
	
	for (i = 0; i < counter - 1; i++)
		for (j = i + 1; j < counter; j++)
			if (tlb[i].page == tlb[j].page)
			{
				for (k = j; k < counter - 1; k++)
					tlb[k] = tlb[k + 1];
				counter--;
			}
}
