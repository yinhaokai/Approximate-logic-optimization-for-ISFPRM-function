
/*
���԰���prob���ʲ���1����0��
��prob=30ʱ����ʾ����1�ĸ���Ϊ30%��

*/
#include "header.h"

int flip(float prob)          /* ��һ�����ʲ���0��1 */
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
