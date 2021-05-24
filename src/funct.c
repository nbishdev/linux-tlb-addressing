#include "funct.h"

void dec2bin16 (int num, char* str)
{
	*(str+16) = '\0';
	int mask = 0x8000 << 1;
	while(mask >>= 1)
		*str++ = !!(mask & num) + '0';
}

void dec2bin8 (int num, char* str)
{
	int i = 7;
	*(str + 8) = '\0';
	while (num != 0)
	{
		*(str + i) = ((num % 2) == 0 ? '0' : '1');
		num = num / 2;
		i--;
	}
	for (; i >= 0; i--)
		*(str + i) = '0';
}

void bin2dec (int* num, char* str, int s)
{
	int i, temp = strlen(str);
	
	*num = 0;
	if (s == 0)
		for (i = 0; i < temp; i++)
			*num += (*(str+i) - '0') * pow(2, temp - 1 - i);
	else
	{
		for (i = 1; i < temp; i++)
			*num += (*(str+i) - '0') * pow(2, temp - 1 - i);
		if (*(str+0) == '1')
			*num = -1 * *num;
	}
}

void logic_insert (char* str, logic_t* logic, int size)
{
	int i = 0, j = 0;
	
	while (*str != '\0')
	{
		if (size != 0)
		{
			logic->page[i++] = *str;
			size--;
		}
		else
		{
			logic->offset[j++] = *str;
		}
		str++;
	}
	logic->page[i] = '\0';
	logic->offset[j] = '\0';
}

void physic_insert (char* frame, char* offset, physic_t* physic)
{
	strcpy(physic->frame, frame);
	strcpy(physic->offset, offset);
	physic->frame[8] = '\0';
	physic->offset[8] = '\0';
}
