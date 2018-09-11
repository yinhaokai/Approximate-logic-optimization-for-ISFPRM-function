//��������Ƚϵķ�����ⲻ�ཻ�ĳ˻���
//  0:(01)
//  1:(10)
//  x,4:(11)`
//��2��ʮ����������ʾһ��cube��
//��cube a��0101x a=(ai,aj)=01011    cube b=01xxx=(bi,bj)=01111
//                          10101                         10111
//if ai & bi= ai
//   aj & bj= aj, then cube b include cube a.
//////////////////////////////////////////////////////////////////////////


//ע�⣺
// ����һ��4�����˻�����(-a)bcd,����ϵ���ж�Ӧ��ʮ�������ǣ���0111��2����7��10
// �����������ط������ʮ��������dcb(-a)=��1110��2=(14)10
// �����XORֵת��Ϊ�˻����ʱ��Ҫ����ߵ���


//���ݴ洢������˵����

//convt_ON_head�����洢PLA�Ķ��������飬����������onset�� ����PLA��0��01��ʾ��1��10��ʾ��-��11��ʾ��
//convt_head�����洢PLA�Ķ��������飬�Ȱ���onset��Ҳ����offset��
//  
//  ��־˵����
//  xor:=��XOR=1ʱ��˵���ó˻����Ѿ������������һ��XOR�Ĺ�ϵ����֮����XOR=0˵���޷���
//  �����˻����һ��XOR��ϵ��
//  �ڽ���BOOLEAN�Ż�ʱ����XOR=0�ĳ˻���Ϳ��Թ���XOR�ĳ˻���ԣ������Ϊ����̬������ESSPReso
//  �Ż���

//xor_fit_head�������洢��Щ�ʺ�XOR�ۺϵĳ˻���	
//��Щ�˻����ڲ����ۺϹ������ò���̬�����档
#include <stdio.h>
#include <math.h>
# include "windows.h"
# include <stdlib.h>
# include <time.h> 
# include <string.h>
# include "conio.h"
# include <vector>
using namespace std;

# define max_var 200
# define max_out 200
# define pmutation 16.0
# define maxrun 20
# define maxgen 20
# define FAULT_popsize 100
# define FAULT_maxgen 100
# define Fault_pcross 55.0
# define Fault_pmutation 16.0
# define aef 1
# define bet 1
struct disrelation
{
	int num;
	int* position;
};
struct convt_int
{
	struct convt_int *prev;
	int *bin_array;
	int *out;
	int bin_array_1[100];
	int flag;//��ʶ0��λ��
	int res;//
	int *deration;//λ���λ�ã�
	int **miji_temp;
	int **mjchart;
	int id;  //�ڼ�����
	int seq_num;
	struct convt_int *link;
};

struct individual                       /* ����*/
{
	int *chrom;                         /* Ⱦɫ�� */
	double   fitness;                   /* ������Ӧ��*/
	double   varible;                   /* �����Ӧ�ı���ֵ*/  
	int      P_of_FPRM;					/* �����Ӧ��FPRM�˻�������*/ 
	double    P_of_sw;
	int      xsite;                     /* ����λ�� */
	int      parent[2];                 /* ������  */
//	int      fitness_need;				/* fitness_need=0,����Ҫ�ٴμ���fitness��ֵ   */
	int      *utility;                  /* �ض�����ָ����� */
};

struct best_individual                         /* ��Ѹ���*/
{
	int *chrom;                         /* ��Ѹ���Ⱦɫ��*/
	double   best_fitness;                   /* ��Ѹ�����Ӧ�� */
	double   avg_fitness;
	double   varible;                   /* ��Ѹ����Ӧ�ı���ֵ */
	int      P_of_FPRM;					/* �����Ӧ��FPRM�˻�������*/ 
	double      P_of_sw;
	int      generation;                /* ��Ѹ������ɴ� */
};

struct readin
{
	char *term;
	char *out;
	struct readin *link;
};


struct FAULT_individual                       /* ����*/
{
	int *chrom;                         /* Ⱦɫ�� */
	double   fitness;                   /* ������Ӧ��*/
	double   varible;                   /* �����Ӧ�ı���ֵ*/
	double   FAULT_sw;
	int      FAULT_fprm;
	int      xsite;                     /* ����λ�� */
	int      parent[2];                 /* ������  */
	//	int      fitness_need;				/* fitness_need=0,����Ҫ�ٴμ���fitness��ֵ   */
	int      *utility;                  /* �ض�����ָ����� */
};

struct best_FAULT_individual                         /* ��Ѹ���*/
{
	int *chrom;                         /* ��Ѹ���Ⱦɫ��*/
	double   best_fitness;                   /* ��Ѹ�����Ӧ�� */
	double   avg_fitness;
	double   FAULT_sw;
	int      FAULT_fprm;
	double   varible;                   /* ��Ѹ����Ӧ�ı���ֵ */
	int      generation;                /* ��Ѹ������ɴ� */
};










void delete_B_list(struct convt_int *head);
void delete_readin_list(struct readin *head);
void convert_char_to_int(struct readin *head_read, struct convt_int *convt_head, int VarNumber, int Num_out);
void convert_binary_in(int *out, char *C, int length);
void convert_binary_out(int *out, char *C, int length); 

long long int lec(int c, int t)  ;
void p_stack(int *save);
void gen(int *save);
int **mj(int tar,int res);
int powerof2(int x) ;



void mj_rpl(struct convt_int *mc, int **mj_temp,struct convt_int *r);

void initpop(struct individual *oldpop,  int Varnumber, int popsize);
int flip(float);


void copy_list(struct convt_int *convt_head,struct convt_int *convt_head_temp,int VarNumber,int Num_outs);
void copy_list1(struct convt_int *convt_head,struct convt_int *convt_head_temp,int VarNumber,int Num_outs);//��ͷ��㿪ʼ����
void chromosome_DC(struct convt_int *convt_head_temp1,int VarNumber,int *chrom,struct disrelation *dis_pt);//�ӵڶ����ڵ㿪ʼ
int counter_products(struct convt_int *convt_head);
struct convt_int* plarity_chrom(struct convt_int *convt_head_temp1,int same,int *same_temp,int VarNumber,int Num_outs);


void find_best_individual(struct individual *newpop,int popsize,int VarNumber,struct best_individual *best_chrom);

void generation1(struct individual *oldpop,struct individual *newpop,int popsize,int VarNumber,int pcross,struct convt_int *convert_head,struct disrelation *dis_pt,int *plarity,int Num_outs,int chrom_Number);
int select(struct individual *oldpop,int popsize,double sumfitness);//ѡ��
int crossover(int *parent1,int *parent2,int *child1,int *child2, float pcross, int VarNumber);//����
int rnd(int low,int high) ;
int  mutation(int *child, int Varnumber) ;

double fitness_compute(int *chrom, struct convt_int *convt_head_temp12, struct disrelation *dis_pt, int *plarity, int VarNumber, int Num_outs, int chrom_Number, double *p_sw, int *pP_fprm);

void generation1(struct individual *oldpop,struct individual *newpop,int popsize,int VarNumber,int pcross,struct convt_int *convert_head,struct disrelation *dis_pt,int *plarity,int Num_outs,int chrom_Number);
void freeall(struct convt_int *convt_head_temp);
void freeall1(struct convt_int *convt_head_temp);
void freeall2(struct convt_int *convt_head_temp);


void QuickSort( struct convt_int *head, struct convt_int *end,int,int);

void DeleList( convt_int *&convt_head,int VarNumber,int Num_outs );
convt_int* delete_linklist(convt_int*,int,int);


double sw_calculation(struct convt_int *&convt_head,int VarNumber,int Num_outs,int P );
int combinator(int n, int m);
void show_lianbiao(struct convt_int * convt_next_head, int VarNumber, int Num_outs);


double small_ga(int  disrelation_num, int VarNumber, int popsize, int pcross, struct disrelation *dis_pt, int *plarity, int Num_outs, struct convt_int *saved_head, int i_count, int *a, double *b);
int big_ga(int VarNumber, int Numofproduct, int Num_outs, int  popsize, int  pcross, struct convt_int *convt_head_current, struct convt_int *convt_next_head, struct convt_int *convt_ON_head,int longth_big_chrom);
void pla_to_min(struct convt_int * convt_next_head, int VarNumber, int Num_outs, int **temp_complete, int same_posion[1024][15], int same_num[1024]);
double tb_to_rm0(int VarNumber, int Numofproduct, int Num_outs, int  popsize, int  pcross, struct convt_int *convt_next_head,int *a,double *b);
