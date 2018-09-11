//采用逐项比较的方法求解不相交的乘积项
//  0:(01)
//  1:(10)
//  x,4:(11)`
//用2个十进制数来表示一个cube。
//如cube a＝0101x a=(ai,aj)=01011    cube b=01xxx=(bi,bj)=01111
//                          10101                         10111
//if ai & bi= ai
//   aj & bj= aj, then cube b include cube a.
//////////////////////////////////////////////////////////////////////////


//注意：
// 对于一个4变量乘积项如(-a)bcd,在谱系数中对应的十进制数是：（0111）2＝（7）10
// 但是在其他地方输出的十进制数是dcb(-a)=（1110）2=(14)10
// 因此由XOR值转换为乘积项的时候，要次序颠倒。


//数据存储的链表说明：

//convt_ON_head用来存储PLA的二进制数组，仅仅包含了onset。 其中PLA中0用01表示，1用10表示，-用11表示。
//convt_head用来存储PLA的二进制数组，既包含onset，也包含offset。
//  
//  标志说明：
//  xor:=当XOR=1时，说明该乘积项已经与其他项构成了一个XOR的关系。反之，当XOR=0说明无法与
//  其他乘积项构成一个XOR关系。
//  在进行BOOLEAN优化时，将XOR=0的乘积项和可以构成XOR的乘积项对（输出置为不定态），用ESSPReso
//  优化。

//xor_fit_head是用来存储那些适合XOR综合的乘积项	
//这些乘积项在布尔综合过程中用不定态来代替。
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
	int flag;//标识0的位数
	int res;//
	int *deration;//位零的位置；
	int **miji_temp;
	int **mjchart;
	int id;  //第几个表
	int seq_num;
	struct convt_int *link;
};

struct individual                       /* 个体*/
{
	int *chrom;                         /* 染色体 */
	double   fitness;                   /* 个体适应度*/
	double   varible;                   /* 个体对应的变量值*/  
	int      P_of_FPRM;					/* 个体对应的FPRM乘积项数量*/ 
	double    P_of_sw;
	int      xsite;                     /* 交叉位置 */
	int      parent[2];                 /* 父个体  */
//	int      fitness_need;				/* fitness_need=0,不需要再次计算fitness的值   */
	int      *utility;                  /* 特定数据指针变量 */
};

struct best_individual                         /* 最佳个体*/
{
	int *chrom;                         /* 最佳个体染色体*/
	double   best_fitness;                   /* 最佳个体适应度 */
	double   avg_fitness;
	double   varible;                   /* 最佳个体对应的变量值 */
	int      P_of_FPRM;					/* 个体对应的FPRM乘积项数量*/ 
	double      P_of_sw;
	int      generation;                /* 最佳个体生成代 */
};

struct readin
{
	char *term;
	char *out;
	struct readin *link;
};


struct FAULT_individual                       /* 个体*/
{
	int *chrom;                         /* 染色体 */
	double   fitness;                   /* 个体适应度*/
	double   varible;                   /* 个体对应的变量值*/
	double   FAULT_sw;
	int      FAULT_fprm;
	int      xsite;                     /* 交叉位置 */
	int      parent[2];                 /* 父个体  */
	//	int      fitness_need;				/* fitness_need=0,不需要再次计算fitness的值   */
	int      *utility;                  /* 特定数据指针变量 */
};

struct best_FAULT_individual                         /* 最佳个体*/
{
	int *chrom;                         /* 最佳个体染色体*/
	double   best_fitness;                   /* 最佳个体适应度 */
	double   avg_fitness;
	double   FAULT_sw;
	int      FAULT_fprm;
	double   varible;                   /* 最佳个体对应的变量值 */
	int      generation;                /* 最佳个体生成代 */
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
void copy_list1(struct convt_int *convt_head,struct convt_int *convt_head_temp,int VarNumber,int Num_outs);//从头结点开始复制
void chromosome_DC(struct convt_int *convt_head_temp1,int VarNumber,int *chrom,struct disrelation *dis_pt);//从第二个节点开始
int counter_products(struct convt_int *convt_head);
struct convt_int* plarity_chrom(struct convt_int *convt_head_temp1,int same,int *same_temp,int VarNumber,int Num_outs);


void find_best_individual(struct individual *newpop,int popsize,int VarNumber,struct best_individual *best_chrom);

void generation1(struct individual *oldpop,struct individual *newpop,int popsize,int VarNumber,int pcross,struct convt_int *convert_head,struct disrelation *dis_pt,int *plarity,int Num_outs,int chrom_Number);
int select(struct individual *oldpop,int popsize,double sumfitness);//选择
int crossover(int *parent1,int *parent2,int *child1,int *child2, float pcross, int VarNumber);//交叉
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
