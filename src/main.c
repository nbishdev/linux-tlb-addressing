#include <stdio.h>
#include <stdlib.h>
#include "funct.h"
#include "types.h"

int frames;

int main(int argc, char** argv)
{
	int page, address, offset, pf, hit, total, physical, r, i;
	char *dir, *addrfilepath, *pagefilepath, buf[17], signed_byte;
	FILE *addrf, *binf;
	
	if (argc < 3)
	{
		printf("Usage: ./addr DIRECTORY_PATH NUMBER_OF_FRAMES\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		dir = argv[1];
		frames = atoi(argv[2]);
	}
	if (frames < 256 || frames % 2 != 0)
	{
		printf("Number of frames must be an integer, a power of 2 and at least 256\n");
		exit(EXIT_FAILURE);
	}
	
	addrfilepath = malloc((strlen(dir) + 14 + 1) * sizeof(char));
	pagefilepath = malloc((strlen(dir) + 18 + 1) * sizeof(char));
	strcpy(addrfilepath, dir);
	strcpy(pagefilepath, dir);
	strcat(addrfilepath, "/addresses.txt");
	strcat(pagefilepath, "/BACKING_STORE.bin");
	
	logic_t logic;
	physic_t physic;
	tlb_t tlb[16];
	pt_t pt[256];
	char** ft;
	char* read;
	
	ft = malloc(frames * sizeof(char*));
	for (i = 0; i < frames; i++)
		ft[i] = malloc(256 * sizeof(char));
		
	read = malloc(256 * sizeof(char));
	
	if ((addrf = fopen(addrfilepath, "r")) == NULL || (binf = fopen(pagefilepath, "rb")) == NULL)
	{
		printf("Either addresses.txt or BACKING_STORE.bin were not found into the chosen directory\n");
		exit(EXIT_FAILURE);
	}
	
	TLB_init(tlb);
	PT_init(pt);
	FT_init(ft);
	
	pf = 0;
	hit = 0;
	total = 0;
	
	printf("\tLogical Address\t\t\t\t\t\tPhysical Address\t\tSigned Byte\n\n");
	while (!feof(addrf))
	{
		if (fscanf(addrf, "%d", &address) == -1)
			break;
		dec2bin16(address, buf);
		logic_insert(buf, &logic, 8);
		bin2dec(&page, logic.page, 0);
		bin2dec(&offset, logic.offset, 0);
		if ((r = TLB_insert(tlb, pt, ft, page)) == -1)
		{
			pf++;
			fseek(binf, 0, page * 256);
			fread(read, 1, 256, binf);
			FT_insert(tlb, pt, ft, read, page);
			if ((binf = fopen("../files/BACKING_STORE.bin", "rb")) == NULL)
			{
				printf("Place BACKING_STORE.bin into the appropriate directory\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (r == 1)
			hit++;
		total++;
		dec2bin8(pt[page].frame, physic.frame);
		physic_insert(physic.frame, logic.offset, &physic);
		strcpy(buf, physic.frame);
		strcat(buf, physic.offset);
		bin2dec(&physical, buf, 0);
		memcpy((void*)&signed_byte, ft[pt[page].frame] + (offset * sizeof(char)), sizeof(char));
		printf("%d\t\t%s%s\t\t\t%s%s\t%d\t\t\t%d\n", address, logic.page, logic.offset, physic.frame, physic.offset, physical, signed_byte);
	}
	
	printf("\nPage faults:\t\t\t%d\n", pf);
	printf("Page faults ratio:\t\t%.2f\%\n", ((float) pf / (float) total) * 100);
	printf("TLB hits:\t\t\t%d\n", hit);
	printf("TLB hits ratio:\t\t\t%.2f\%\n", ((float) hit / (float) total) * 100);
	
	fclose(binf);
	fclose(addrf);
	
	for (i = 0; i < frames; i++)
		free(ft[i]);
	free(ft);
	
	free(read);
	
	exit(EXIT_SUCCESS);
}
