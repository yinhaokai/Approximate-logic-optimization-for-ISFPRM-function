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
			else if (*(C + i) == '0' || *(C + i) == '~')  //ָ����~�������ʾ0.�����Ϊ��0������~���͡�-��������Ϊ��0���������δ���塣
			{
				*(out + i) = 0;
			}
			else //if (c_outs[i]=='-')
			{
				*(out + i) = 2;
			}
		}

	}