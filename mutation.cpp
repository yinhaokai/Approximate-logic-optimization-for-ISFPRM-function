#include "header.h"

int  mutation(int *child, int Varnumber)   /*±äÒì²Ù×÷*/
{
	int j,k;
	int mutted;
	int do_mutation;

	mutted=0;

	for(k = 0; k < Varnumber; k++)
	{
		do_mutation=flip(pmutation);
		if(do_mutation)
		{
			mutted=1;
			j=child[k];
			if (j)
				child[k]=0;
			else 
				child[k]=1;

		}

	}

	return(mutted);
}