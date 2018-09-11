# include "header.h"
void convert_binary_in(int *out, char *C, int length)//convert_binary_in(p_int, readterm, VarNumber);ÊäÈë
	{

		int i;

		for (i = 0; i<length; i++)
		{
			if (*(C + i) == '1')
			{
				*(out + i) = 1;
			}
			else if (*(C + i) == '0')
			{
				*(out + i) = 0;
			}
			else if (*(C + i) == '-' || *(C + i) == '~')
			{
				*(out + i) = 2;
			}
		}
	}
