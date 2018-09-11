# include "header.h"
void convert_binary_out(int *out, char *C, int length)
	{

		int i;

		for (i = 0; i<length; i++)
		{
			if (*(C + i) == '1')
			{
				*(out + i) = 1;
			}
			else if (*(C + i) == '0' || *(C + i) == '~')  //指定“~”输出表示0.将输出为“0”，“~”和“-”都定义为“0”，即输出未定义。
			{
				*(out + i) = 0;
			}
			else //if (c_outs[i]=='-')
			{
				*(out + i) = 2;
			}
		}

	}