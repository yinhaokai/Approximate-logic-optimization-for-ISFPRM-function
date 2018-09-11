
/*
可以按照prob概率产生1或者0、
当prob=30时，表示产生1的概率为30%。

*/
#include "header.h"

int flip(float prob)          /* 以一定概率产生0或1 */
{
	//float randomperc();
	float K;
//	srand( (unsigned)time( NULL ) );
	K=(int)rand()%100;
	if( K < prob)
		return(1);
	else
		return(0);
}
