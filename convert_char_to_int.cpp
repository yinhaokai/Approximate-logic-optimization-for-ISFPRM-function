# include "header.h"
# include <iostream>
void convert_char_to_int(struct readin *head_read, struct convt_int *convt_head, int VarNumber, int Num_out)
	{
		int i;
		char *readterm, *c_outs;
		struct convt_int *convt_current, *convt_new;
		struct readin *current_read;

		int  *p_int, *out_int;
		//	int length;
		p_int = (int *)malloc(VarNumber*sizeof(int));
		out_int = (int *)malloc(Num_out*sizeof(int));
		readterm = (char *)malloc(VarNumber*sizeof(char));
		c_outs = (char *)malloc(Num_out*sizeof(char));
		current_read = head_read->link; 

		convt_current = convt_head;
		int	count = 0;
		while (current_read != NULL)
		{

			strcpy(readterm, current_read->term);
			strcpy(c_outs, current_read->out);

			//		printf("readterm= %s ",readterm);

			//p_int = (int *)malloc(VarNumber*sizeof(int));
			//out_int = (int *)malloc(Num_out*sizeof(int));

			convert_binary_in(p_int, readterm, VarNumber);
			convert_binary_out(out_int, c_outs, Num_out);
			convt_new = new struct convt_int;
			convt_new->link = NULL;
			convt_new->bin_array = (int *)malloc(VarNumber*sizeof(int));
			convt_new->out = (int *)malloc(Num_out*sizeof(int));

			for (i = 0; i<VarNumber; i++)
			{
				*(convt_new->bin_array + i) = *(p_int + i);
				//		printf("%d ",*(p_int+i));

			}

			for (i = 0; i<Num_out; i++)
				*(convt_new->out + i) = *(out_int + i);
			
			convt_current->link = convt_new;
			convt_current = convt_new;
			current_read = current_read->link;
			convt_current->id = count++;
		}
		free(p_int);
		free(out_int);

	}