#include <stdio.h>
#include"sw_calculation.h"
# include <time.h> 
#include <stdlib.h>
#include "header.h"
 int RM_numgatend/*门数*/;
 int RM_numtinputs/*输入数*/;
 int RM_numtoutputs/*输出数*/;
 double RM__sw/*功耗*/;
 char RM_inputname[400][9],RM_outputname[400][9];
  double messagebox[500][10];
 struct toolnodes
{
    char outputname[9];
    char inputname[100][9];
    int outputi;//原来的位置
    int inputi[100];
    int numinput;
    int upi[100];
    int numup;
    /*------flag-----------*/
    int flag_use;
    /*------POWER-----------*/
    int nodetype;
    double nodeswith;
    double nodeprob;
}rmnode[3000];
void RM_vActivity(toolnodes graph[],int randornot,double p,double d);
void init_messagebox(int numvars,int randornot,double p,double d);
void jisuan_RMgateSW(toolnodes g1[],int igate);
double jisuan_RMSW(toolnodes g1[],int key);
void return_new_pt(struct convt_int *&pt,struct convt_int *&new_pt,int ,int VarNumber);
int return_xor_numinput(int seq,int memory[1000][50],int Num_outs);
void transRMandgate(toolnodes g[]);
void takechange(toolnodes g1[],int i_gate);
double precompution(toolnodes graph[],int randornot,double p,double d);
double  sw_decogate_RM(toolnodes g[]);


double struction(struct convt_int *&convt_head,int VarNumber,int Num_outs,int P_FPRM,int memory[1000][50]){
	struct convt_int *pt = convt_head, *prev_const = convt_head, *new_pt = convt_head;
	pt = convt_head;
	double sw;
	int innumber_1,innumber_0;
    RM_numgatend=P_FPRM+Num_outs;//v代表输入数门，n代表异或门，p代表与门
    RM_numtinputs=VarNumber;
	RM_numtoutputs=Num_outs;
	int i;int j;
	int input_a[1000];i=0;
	while (pt != NULL)//链的所有乘积项的字母数用数组储存
	{   
		innumber_1=innumber_0=0;
		int temp=0;
		for ( j = 0; j < VarNumber; j++)
		{
			if (pt->bin_array[j]==1) 
				{
					innumber_1++;
				    pt->bin_array_1[temp]=j;
					temp++;
				}
			
		};
		
		input_a[i]=innumber_1;
		i++;
		pt = pt->link;
		
	}
	
	for(i=0;i<VarNumber;i++)
	{
		rmnode[i].nodetype=0;
		
	}
	pt = convt_head;
	for(i=VarNumber;i<P_FPRM+VarNumber;i++)
	{

		rmnode[i].nodetype=1;
        rmnode[i].numinput=input_a[i-VarNumber];
		//printf("%d ",rmnode[i].numinput);
		if(rmnode[i].numinput<11)
		      {
			for (j = 0; j< rmnode[i].numinput; j++){
					  return_new_pt(pt,new_pt,i,VarNumber);
					  rmnode[i].inputi[j]=new_pt->bin_array_1[j];
				  }			  
		     }
		else
		{
			printf("chaochu%d", rmnode[i].numinput);
		}
	}
	
    for(i=P_FPRM+VarNumber;i<P_FPRM+VarNumber+Num_outs;i++){
		rmnode[i].nodetype=5;
		rmnode[i].numinput=return_xor_numinput(i-P_FPRM-VarNumber,memory,Num_outs);
		for(j=0;j<rmnode[i].numinput;j++)
		{
		rmnode[i].inputi[j]=memory[i-P_FPRM-VarNumber][j]+VarNumber;
		}		
		//printf("shuru %d\n",rmnode[i].numinput);
    }
	for(i=VarNumber;i<P_FPRM+VarNumber+Num_outs;i++){
		if(rmnode[i].numinput==1){
		  takechange(rmnode,i);
		}	
	}
   // transRMandgate(rmnode);
	sw=precompution(rmnode,2,0,0)+sw_decogate_RM(rmnode);
	//printf("sw=%f\n",sw);
	//RM_vActivity(rmnode,1,0,0);	
	if (0<sw<0.01)
	{
		system("pause");
		show_lianbiao(prev_const,VarNumber,Num_outs);

	}
	return sw;
}
double sw_decogate_RM(toolnodes g[])
{
	int k0;int i=0;
	double xor_sw=0;
	for(k0=RM_numgatend+RM_numtinputs-1; k0>=0; k0--){
			if(g[k0].nodetype==5){
				   for(i=0;i<g[k0].numinput;i++){
					   xor_sw=xor_sw+g[g[k0].inputi[i]].nodeswith;
				   }
			}

	}
	return xor_sw;
}



int 
return_xor_numinput(int seq,int memory[1000][50],int Num_outs){
	int k=0;
	while(memory[seq][k]!=0){
             k++;	
	}

	return k ;


}

void 
return_new_pt(struct convt_int *&pt,struct convt_int *&new_pt,int i ,int VarNumber){
	  
	  new_pt=pt;
	  int temp=0;
      while (new_pt != NULL&&temp<i-VarNumber)//链的所有乘积项的字母数用数组储存
	{   
		new_pt = new_pt->link;	
		temp++;
	}

}

void 
RM_vActivity(toolnodes graph[],int randornot,double p,double d)
{	double sw;
    sw=jisuan_RMSW(graph,1);
    /*
    **输出屏幕信息
    */
    printf("\n------------------------------------------\n");
	printf("RM_numtinputs=%d",RM_numtinputs);
    printf("SA:   %f\n",sw);
    printf("\n------------------------------------------\n");
}
double precompution(toolnodes graph[],int randornot,double p,double d)
{
	double sw=0;
    init_messagebox(RM_numtinputs,randornot,p,d);	
    sw=jisuan_RMSW(graph,0);
    /*
    **输出屏幕信息
    */
	//printf("\n------------------------------------------\n");
	//printf("RM_numtinputs=%d",RM_numtinputs);
	//printf("pre SA:   %f\n",sw);
	//printf("\n------------------------------------------\n");
	return sw;

}
void
jisuan_RMgateSW(toolnodes g1[],int igate)
{
    int i1,i2,i3,i4,i5,i6,i7,i8,i9,i10;
    int iinput;
    double tmppro=0,tmpden=0;
    double tmpp1,tmpd1,tmpp2,tmpd2;
    double p[10],d[10];
    /*
    **单输入的门的处理
    */
    if(g1[igate].numinput==1)
    {
        /*
        **输入的信号概率和跳变密度的存储：方便后面调用计算
        */
        i1=g1[igate].inputi[0];
        p[1]=g1[i1].nodeprob;
        d[1]=g1[i1].nodeswith;
        /*
        **计算相应门的信号概率和跳变密度
        */
        if(g1[igate].nodetype==2)/*bufforwire*/
        {
            tmppro=p[1];
            tmpden=d[1];
        }
    }
    /*
    **2输入的门的处理
    */
    else if(g1[igate].numinput==2)
    {
        /*
        **输入的信号概率和跳变密度的存储：方便后面调用计算
        */
        i1=g1[igate].inputi[0];
        i2=g1[igate].inputi[1];
        p[1]=g1[i1].nodeprob;
        d[1]=g1[i1].nodeswith;
        p[2]=g1[i2].nodeprob;
        d[2]=g1[i2].nodeswith;
        /*
        **计算相应门的信号概率和跳变密度
        */
        if(g1[igate].nodetype==1)/*and2*/
        {
            tmppro=p[1]*p[2];
            tmpden=p[1]*d[2]+p[2]*d[1];
        }
	}
    /*
    **3输入的门的处理
    */
    else if(g1[igate].numinput==3)
    {
        /*
        **输入的信号概率和跳变密度的存储：方便后面调用计算
        */
        i1=g1[igate].inputi[0];
        i2=g1[igate].inputi[1];
        i3=g1[igate].inputi[2];
        p[1]=g1[i1].nodeprob;
        d[1]=g1[i1].nodeswith;
        p[2]=g1[i2].nodeprob;
        d[2]=g1[i2].nodeswith;
        p[3]=g1[i3].nodeprob;
        d[3]=g1[i3].nodeswith;
        /*
        **计算相应门的信号概率和跳变密度
        */
        if(g1[igate].nodetype==1)//and3
        {
            tmppro=p[1]*p[2]*p[3];
            tmpden=p[1]*p[2]*d[3]+p[1]*p[3]*d[2]+p[3]*p[2]*d[1];
        }
	}
    /*
    **4输入的门的处理
    */
    else if(g1[igate].numinput==4)
    {
        /*
        **输入的信号概率和跳变密度的存储：方便后面调用计算
        */
        i1=g1[igate].inputi[0];
        i2=g1[igate].inputi[1];
        i3=g1[igate].inputi[2];
        i4=g1[igate].inputi[3];
        p[1]=g1[i1].nodeprob;
        d[1]=g1[i1].nodeswith;
        p[2]=g1[i2].nodeprob;
        d[2]=g1[i2].nodeswith;
        p[3]=g1[i3].nodeprob;
        d[3]=g1[i3].nodeswith;
        p[4]=g1[i4].nodeprob;
        d[4]=g1[i4].nodeswith;
        /*
        **计算相应门的信号概率和跳变密度
        */
        if(g1[igate].nodetype==1)/*and4*/
        {
            tmppro=p[1]*p[2]*p[3]*p[4];
            tmpden=p[1]*p[2]*p[3]*d[4]+p[1]*p[2]*p[4]*d[3]+p[1]*p[3]*p[4]*d[2]+p[3]*p[2]*p[4]*d[1];
        }
    }
	else if (g1[igate].numinput == 5)
	{
		/*
		**输入的信号概率和跳变密度的存储：方便后面调用计算
		*/
		i1 = g1[igate].inputi[0];
		i2 = g1[igate].inputi[1];
		i3 = g1[igate].inputi[2];
		i4 = g1[igate].inputi[3];
		i5 = g1[igate].inputi[4];
		p[1] = g1[i1].nodeprob;
		d[1] = g1[i1].nodeswith;
		p[2] = g1[i2].nodeprob;
		d[2] = g1[i2].nodeswith;
		p[3] = g1[i3].nodeprob;
		d[3] = g1[i3].nodeswith;
		p[4] = g1[i4].nodeprob;
		d[4] = g1[i4].nodeswith;
		p[5] = g1[i5].nodeprob;
		d[5] = g1[i5].nodeswith;
		/*
		**计算相应门的信号概率和跳变密度
		*/
		if (g1[igate].nodetype == 1)/*and4*/
		{
			tmppro = p[1] * p[2] * p[3] * p[4] * p[5];
			tmpden = p[1] * p[2] * p[3] * p[4] * d[5] + p[1] * p[2] * p[3] * d[4] * p[5] + p[1] * p[2] * d[3] * p[4] * p[5] + p[1] * d[2] * p[3] * p[4] * p[5] + d[1] * p[2] * p[3] * p[4] * p[5];
		}
	}
	else if (g1[igate].numinput == 6)
	{
		/*
		**输入的信号概率和跳变密度的存储：方便后面调用计算
		*/
		i1 = g1[igate].inputi[0];
		i2 = g1[igate].inputi[1];
		i3 = g1[igate].inputi[2];
		i4 = g1[igate].inputi[3];
		i5 = g1[igate].inputi[4];
		i6 = g1[igate].inputi[5];
		p[1] = g1[i1].nodeprob;
		d[1] = g1[i1].nodeswith;
		p[2] = g1[i2].nodeprob;
		d[2] = g1[i2].nodeswith;
		p[3] = g1[i3].nodeprob;
		d[3] = g1[i3].nodeswith;
		p[4] = g1[i4].nodeprob;
		d[4] = g1[i4].nodeswith;
		p[5] = g1[i5].nodeprob;
		d[5] = g1[i5].nodeswith;
		p[6] = g1[i6].nodeprob;
		d[6] = g1[i6].nodeswith;
		/*
		**计算相应门的信号概率和跳变密度
		*/
		if (g1[igate].nodetype == 1)/*and4*/
		{
			tmppro = p[1] * p[2] * p[3] * p[4] * p[5] * p[6];
			tmpden = p[1] * p[2] * p[3] * p[4] * d[5] * p[6] + p[1] * p[2] * p[3] * d[4] * p[5] * p[6] + p[1] * p[2] * d[3] * p[4] * p[5] * p[6] + p[1] * d[2] * p[3] * p[4] * p[5] * p[6] + d[1] * p[2] * p[3] * p[4] * p[5] * p[6] + p[1] * p[2] * p[3] * p[4] * p[5] * d[6];
		}
	}

	else if (g1[igate].numinput == 7)
	{
		/*
		**输入的信号概率和跳变密度的存储：方便后面调用计算
		*/
		i1 = g1[igate].inputi[0];
		i2 = g1[igate].inputi[1];
		i3 = g1[igate].inputi[2];
		i4 = g1[igate].inputi[3];
		i5 = g1[igate].inputi[4];
		i6 = g1[igate].inputi[5];
		i7 = g1[igate].inputi[6];
		p[1] = g1[i1].nodeprob;
		d[1] = g1[i1].nodeswith;
		p[2] = g1[i2].nodeprob;
		d[2] = g1[i2].nodeswith;
		p[3] = g1[i3].nodeprob;
		d[3] = g1[i3].nodeswith;
		p[4] = g1[i4].nodeprob;
		d[4] = g1[i4].nodeswith;
		p[5] = g1[i5].nodeprob;
		d[5] = g1[i5].nodeswith;
		p[6] = g1[i6].nodeprob;
		d[6] = g1[i6].nodeswith;
		p[7] = g1[i7].nodeprob;
		d[7] = g1[i7].nodeswith;
		/*
		**计算相应门的信号概率和跳变密度
		*/
		if (g1[igate].nodetype == 1)/*and4*/
		{
			tmppro = p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7];
			tmpden = p[1] * p[2] * p[3] * p[4] * d[5] * p[6] * p[7] + p[1] * p[2] * p[3] * d[4] * p[5] * p[6] * p[7] + p[1] * p[2] * d[3] * p[4] * p[5] * p[6] * p[7] + p[1] * d[2] * p[3] * p[4] * p[5] * p[6] * p[7] + d[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] + p[1] * p[2] * p[3] * p[4] * p[5] * d[6] * p[7] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * d[7];
		}
	}
	else if (g1[igate].numinput == 8)
	{
		/*
		**输入的信号概率和跳变密度的存储：方便后面调用计算
		*/
		i1 = g1[igate].inputi[0];
		i2 = g1[igate].inputi[1];
		i3 = g1[igate].inputi[2];
		i4 = g1[igate].inputi[3];
		i5 = g1[igate].inputi[4];
		i6 = g1[igate].inputi[5];
		i7 = g1[igate].inputi[6];
		i8 = g1[igate].inputi[7];
		p[1] = g1[i1].nodeprob;
		d[1] = g1[i1].nodeswith;
		p[2] = g1[i2].nodeprob;
		d[2] = g1[i2].nodeswith;
		p[3] = g1[i3].nodeprob;
		d[3] = g1[i3].nodeswith;
		p[4] = g1[i4].nodeprob;
		d[4] = g1[i4].nodeswith;
		p[5] = g1[i5].nodeprob;
		d[5] = g1[i5].nodeswith;
		p[6] = g1[i6].nodeprob;
		d[6] = g1[i6].nodeswith;
		p[7] = g1[i7].nodeprob;
		d[7] = g1[i7].nodeswith;
		p[8] = g1[i8].nodeprob;
		d[8] = g1[i8].nodeswith;
		/*
		**计算相应门的信号概率和跳变密度
		*/
		if (g1[igate].nodetype == 1)/*and4*/
		{
			tmppro = p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7]*p[8];
			tmpden = p[1] * p[2] * p[3] * p[4] * d[5] * p[6] * p[7] * p[8] + p[1] * p[2] * p[3] * d[4] * p[5] * p[6] * p[7] * p[8] + p[1] * p[2] * d[3] * p[4] * p[5] * p[6] * p[7] * p[8] + p[1] * d[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] + d[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] + p[1] * p[2] * p[3] * p[4] * p[5] * d[6] * p[7] * p[8] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * d[7] * p[8] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * d[8];
		}
	}
	else if (g1[igate].numinput == 9)
	{
		/*
		**输入的信号概率和跳变密度的存储：方便后面调用计算
		*/
		i1 = g1[igate].inputi[0];
		i2 = g1[igate].inputi[1];
		i3 = g1[igate].inputi[2];
		i4 = g1[igate].inputi[3];
		i5 = g1[igate].inputi[4];
		i6 = g1[igate].inputi[5];
		i7 = g1[igate].inputi[6];
		i8 = g1[igate].inputi[7];
		i9 = g1[igate].inputi[8];
		p[1] = g1[i1].nodeprob;
		d[1] = g1[i1].nodeswith;
		p[2] = g1[i2].nodeprob;
		d[2] = g1[i2].nodeswith;
		p[3] = g1[i3].nodeprob;
		d[3] = g1[i3].nodeswith;
		p[4] = g1[i4].nodeprob;
		d[4] = g1[i4].nodeswith;
		p[5] = g1[i5].nodeprob;
		d[5] = g1[i5].nodeswith;
		p[6] = g1[i6].nodeprob;
		d[6] = g1[i6].nodeswith;
		p[7] = g1[i7].nodeprob;
		d[7] = g1[i7].nodeswith;
		p[8] = g1[i8].nodeprob;
		d[8] = g1[i8].nodeswith;
		p[9] = g1[i9].nodeprob;
		d[9] = g1[i9].nodeswith;

		/*
		**计算相应门的信号概率和跳变密度
		*/
		if (g1[igate].nodetype == 1)/*and4*/
		{
			tmppro = p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7]*p[8]*p[9];
			tmpden = p[1] * p[2] * p[3] * p[4] * d[5] * p[6] * p[7] * p[8] * p[9] + p[1] * p[2] * p[3] * d[4] * p[5] * p[6] * p[7] * p[8] * p[9] + p[1] * p[2] * d[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9] + p[1] * d[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9] + d[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9] + p[1] * p[2] * p[3] * p[4] * p[5] * d[6] * p[7] * p[8] * p[9] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * d[7] * p[8] * p[9] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * d[8] * p[9] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * d[9];
		}
	}
	else if (g1[igate].numinput == 10)
	{
		/*
		**输入的信号概率和跳变密度的存储：方便后面调用计算
		*/
		i1 = g1[igate].inputi[0];
		i2 = g1[igate].inputi[1];
		i3 = g1[igate].inputi[2];
		i4 = g1[igate].inputi[3];
		i5 = g1[igate].inputi[4];
		i6 = g1[igate].inputi[5];
		i7 = g1[igate].inputi[6];
		i8 = g1[igate].inputi[7];
		i9 = g1[igate].inputi[8];
		i10 = g1[igate].inputi[9];
		p[1] = g1[i1].nodeprob;
		d[1] = g1[i1].nodeswith;
		p[2] = g1[i2].nodeprob;
		d[2] = g1[i2].nodeswith;
		p[3] = g1[i3].nodeprob;
		d[3] = g1[i3].nodeswith;
		p[4] = g1[i4].nodeprob;
		d[4] = g1[i4].nodeswith;
		p[5] = g1[i5].nodeprob;
		d[5] = g1[i5].nodeswith;
		p[6] = g1[i6].nodeprob;
		d[6] = g1[i6].nodeswith;
		p[7] = g1[i7].nodeprob;
		d[7] = g1[i7].nodeswith;
		p[8] = g1[i8].nodeprob;
		d[8] = g1[i8].nodeswith;
		p[9] = g1[i9].nodeprob;
		d[9] = g1[i9].nodeswith;
		p[10] = g1[i10].nodeprob;
		d[10] = g1[i10].nodeswith;

		/*
		**计算相应门的信号概率和跳变密度
		*/
		if (g1[igate].nodetype == 1)/*and4*/
		{
			tmppro = p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9]*p[10];
			tmpden = p[1] * p[2] * p[3] * p[4] * d[5] * p[6] * p[7] * p[8] * p[9] * p[10] + p[1] * p[2] * p[3] * d[4] * p[5] * p[6] * p[7] * p[8] * p[9] * p[10] + p[1] * p[2] * d[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9] * p[10] + p[1] * d[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9] * p[10] + d[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9] * p[10] + p[1] * p[2] * p[3] * p[4] * p[5] * d[6] * p[7] * p[8] * p[9] * p[10] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * d[7] * p[8] * p[9] * p[10] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * d[8] * p[9] * p[10] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * d[9] * p[10] + p[1] * p[2] * p[3] * p[4] * p[5] * p[6] * p[7] * p[8] * p[9] * d[10];
		}
	}



    /*
    **将计算结果赋给节点
    */
    g1[igate].nodeprob=tmppro;
    g1[igate].nodeswith=tmpden;
}	
//**================================================================
//*
//* 函 数 名: jisuan_ABCSW()
//* 参 数:
//*
//* 功能描述:  计算整体功耗
//*
//* 返 回 值:  整体功耗
//*
//* side-effects:
//*
//===============================================================*/




double
jisuan_RMSW(toolnodes g1[],int key)
{
    int i,k;
    /*int iinput,iinput1中间量*/;
    double sw=0/*整体功耗*/;
    /*
    **输入信号的功耗信息
    */
    for(i=0; i<RM_numtinputs; i++)
    {
        g1[i].nodeprob=messagebox[i][0];
        g1[i].nodeswith=messagebox[i][1];
    }
    /*
    **结算每个节点的功耗
    */
	if (key==1)
	{
		for(k=RM_numtinputs; k<RM_numgatend+RM_numtinputs; k++)
		{
			jisuan_RMgateSW(g1,k);
		//    /*printf("%d\t%d\t%f   %f\n",k,g1[k].nodetype,g1[k].nodeprob,g1[k].nodeswith);*/
		//    /*
		//    **除去buffer（nodetype=6）的情况
		//    */
			sw=sw+g1[k].nodeswith;
		}
	}


	else 
		{
		for(k=RM_numtinputs; k<RM_numgatend-RM_numtoutputs; k++)
		{
			jisuan_RMgateSW(g1,k);
		//    /*printf("%d\t%d\t%f   %f\n",k,g1[k].nodetype,g1[k].nodeprob,g1[k].nodeswith);*/
		//    /*
		//    **除去buffer（nodetype=6）的情况
		//    */
			sw=sw+g1[k].nodeswith;
		}
	}

    return sw;
}
void
init_messagebox(int numvars,int randornot,double p,double d)
{
    int i;
    srand( (unsigned)time( NULL ) );
    if(randornot==1)//随机概率和跳变密度
    {
        for(i=0; i<numvars; i++)
        {
            messagebox[i][0]=rand() % 9 * 0.1+0.1;
            if(messagebox[i][0]==1||messagebox[i][0]==0)
                messagebox[i][1]=0;
            else
                messagebox[i][1]=rand() %19*0.1+0.1 ;//+0.5;
        }
    }
    else if(randornot==0)//规定p，d
    {
        for(i=0; i<numvars; i++)
        {
            messagebox[i][0]=p;
            messagebox[i][1]=d;
        }
    }
    else if(randornot==2)
    {
        messagebox[0][0]=0.500000;
        messagebox[0][1]=1.500000;
        messagebox[1][0]=0.300000;
        messagebox[1][1]=1.000000;
        messagebox[2][0]=0.500000;
        messagebox[2][1]=1.900000;
        messagebox[3][0]=0.200000;
        messagebox[3][1]=1.800000;
        messagebox[4][0]=0.200000;
        messagebox[4][1]=1.300000;
        messagebox[5][0]=0.600000;
        messagebox[5][1]=0.700000;
        messagebox[6][0]=0.400000;
        messagebox[6][1]=1.100000;
        messagebox[7][0]=0.700000;
        messagebox[7][1]=1.100000;
        messagebox[8][0]=0.200000;
        messagebox[8][1]=0.700000;
        messagebox[9][0]=0.100000;
        messagebox[9][1]=0.200000;
        messagebox[10][0]=0.700000;
        messagebox[10][1]=0.800000;
        messagebox[11][0]=0.700000;
        messagebox[11][1]=0.300000;
        messagebox[12][0]=0.900000;
        messagebox[12][1]=0.300000;
        messagebox[13][0]=0.100000;
        messagebox[13][1]=1.000000;
        messagebox[14][0]=0.700000;
        messagebox[14][1]=0.200000;
        messagebox[15][0]=0.900000;
        messagebox[15][1]=0.300000;
        messagebox[16][0]=0.100000;
        messagebox[16][1]=1.600000;
        messagebox[17][0]=0.700000;
        messagebox[17][1]=1.200000;
        messagebox[18][0]=0.400000;
        messagebox[18][1]=1.300000;
        messagebox[19][0]=0.700000;
        messagebox[19][1]=0.400000;
        messagebox[20][0]=0.600000;
        messagebox[20][1]=1.500000;
        messagebox[21][0]=0.600000;
        messagebox[21][1]=1.100000;
        messagebox[22][0]=0.500000;
        messagebox[22][1]=1.000000;
        messagebox[23][0]=0.900000;
        messagebox[23][1]=0.800000;
        messagebox[24][0]=0.800000;
        messagebox[24][1]=1.200000;
        messagebox[25][0]=0.200000;
        messagebox[25][1]=1.100000;
        messagebox[26][0]=0.800000;
        messagebox[26][1]=1.900000;
        messagebox[27][0]=0.600000;
        messagebox[27][1]=0.600000;
        messagebox[28][0]=0.600000;
        messagebox[28][1]=1.200000;
        messagebox[29][0]=0.300000;
        messagebox[29][1]=1.400000;
        messagebox[30][0]=0.400000;
        messagebox[30][1]=0.600000;
        messagebox[31][0]=0.300000;
        messagebox[31][1]=0.700000;
        messagebox[32][0]=0.700000;
        messagebox[32][1]=0.300000;
        messagebox[33][0]=0.500000;
        messagebox[33][1]=0.900000;
        messagebox[34][0]=0.600000;
        messagebox[34][1]=0.600000;
        messagebox[35][0]=0.300000;
        messagebox[35][1]=1.500000;
        messagebox[36][0]=0.300000;
        messagebox[36][1]=1.900000;
        messagebox[37][0]=0.200000;
        messagebox[37][1]=0.100000;
        messagebox[38][0]=0.800000;
        messagebox[38][1]=0.300000;
        messagebox[39][0]=0.200000;
        messagebox[39][1]=0.300000;
        messagebox[40][0]=0.700000;
        messagebox[40][1]=1.300000;
        messagebox[41][0]=0.600000;
        messagebox[41][1]=1.100000;
        messagebox[42][0]=0.800000;
        messagebox[42][1]=1.900000;
        messagebox[43][0]=0.100000;
        messagebox[43][1]=0.800000;
        messagebox[44][0]=0.200000;
        messagebox[44][1]=0.300000;
        messagebox[45][0]=0.600000;
        messagebox[45][1]=0.200000;
        messagebox[46][0]=0.800000;
        messagebox[46][1]=1.100000;
        messagebox[47][0]=0.600000;
        messagebox[47][1]=0.400000;
        messagebox[48][0]=0.600000;
        messagebox[48][1]=0.300000;
        messagebox[49][0]=0.300000;
        messagebox[49][1]=0.300000;
        messagebox[50][0]=0.100000;
        messagebox[50][1]=0.200000;
        messagebox[51][0]=0.400000;
        messagebox[51][1]=0.100000;
        messagebox[52][0]=0.900000;
        messagebox[52][1]=0.100000;
        messagebox[53][0]=0.700000;
        messagebox[53][1]=0.400000;
        messagebox[54][0]=0.100000;
        messagebox[54][1]=0.300000;
        messagebox[55][0]=0.800000;
        messagebox[55][1]=1.400000;
        messagebox[56][0]=0.900000;
        messagebox[56][1]=1.200000;
        messagebox[57][0]=0.200000;
        messagebox[57][1]=0.200000;
        messagebox[58][0]=0.300000;
        messagebox[58][1]=1.400000;
        messagebox[59][0]=0.800000;
        messagebox[59][1]=1.900000;
        messagebox[60][0]=0.100000;
        messagebox[60][1]=0.400000;
        messagebox[61][0]=0.800000;
        messagebox[61][1]=1.800000;
        messagebox[62][0]=0.900000;
        messagebox[62][1]=1.800000;
        messagebox[63][0]=0.200000;
        messagebox[63][1]=1.800000;
        messagebox[64][0]=0.200000;
        messagebox[64][1]=1.100000;
        messagebox[65][0]=0.600000;
        messagebox[65][1]=0.300000;
        messagebox[66][0]=0.400000;
        messagebox[66][1]=1.400000;
        messagebox[67][0]=0.900000;
        messagebox[67][1]=0.600000;
        messagebox[68][0]=0.800000;
        messagebox[68][1]=0.100000;
        messagebox[69][0]=0.600000;
        messagebox[69][1]=1.100000;
        messagebox[70][0]=0.200000;
        messagebox[70][1]=0.800000;
        messagebox[71][0]=0.200000;
        messagebox[71][1]=1.400000;
        messagebox[72][0]=0.500000;
        messagebox[72][1]=0.600000;
        messagebox[73][0]=0.200000;
        messagebox[73][1]=0.500000;
        messagebox[74][0]=0.100000;
        messagebox[74][1]=1.700000;
        messagebox[75][0]=0.800000;
        messagebox[75][1]=1.300000;
        messagebox[76][0]=0.100000;
        messagebox[76][1]=1.400000;
        messagebox[77][0]=0.500000;
        messagebox[77][1]=0.900000;
        messagebox[78][0]=0.500000;
        messagebox[78][1]=1.000000;
        messagebox[79][0]=0.200000;
        messagebox[79][1]=0.900000;
        messagebox[80][0]=0.500000;
        messagebox[80][1]=0.400000;
        messagebox[81][0]=0.400000;
        messagebox[81][1]=0.300000;
        messagebox[82][0]=0.200000;
        messagebox[82][1]=1.100000;
        messagebox[83][0]=0.600000;
        messagebox[83][1]=0.600000;
        messagebox[84][0]=0.500000;
        messagebox[84][1]=1.100000;
        messagebox[85][0]=0.400000;
        messagebox[85][1]=1.000000;
        messagebox[86][0]=0.400000;
        messagebox[86][1]=1.800000;
        messagebox[87][0]=0.300000;
        messagebox[87][1]=1.200000;
        messagebox[88][0]=0.600000;
        messagebox[88][1]=1.600000;
        messagebox[89][0]=0.300000;
        messagebox[89][1]=0.200000;
        messagebox[90][0]=0.200000;
        messagebox[90][1]=1.300000;
        messagebox[91][0]=0.200000;
        messagebox[91][1]=0.800000;
        messagebox[92][0]=0.400000;
        messagebox[92][1]=0.300000;
        messagebox[93][0]=0.900000;
        messagebox[93][1]=1.800000;
        messagebox[94][0]=0.700000;
        messagebox[94][1]=1.600000;
        messagebox[95][0]=0.200000;
        messagebox[95][1]=0.300000;
        messagebox[96][0]=0.500000;
        messagebox[96][1]=1.500000;
        messagebox[97][0]=0.500000;
        messagebox[97][1]=1.100000;
        messagebox[98][0]=0.400000;
        messagebox[98][1]=0.900000;
        messagebox[99][0]=0.400000;
        messagebox[99][1]=1.400000;
        messagebox[100][0]=0.100000;
        messagebox[100][1]=0.700000;
        messagebox[101][0]=0.100000;
        messagebox[101][1]=0.900000;
        messagebox[102][0]=0.100000;
        messagebox[102][1]=0.900000;
        messagebox[103][0]=0.900000;
        messagebox[103][1]=0.700000;
        messagebox[104][0]=0.400000;
        messagebox[104][1]=1.000000;
        messagebox[105][0]=0.700000;
        messagebox[105][1]=0.900000;
        messagebox[106][0]=0.900000;
        messagebox[106][1]=1.800000;
        messagebox[107][0]=0.500000;
        messagebox[107][1]=0.600000;
        messagebox[108][0]=0.100000;
        messagebox[108][1]=0.700000;
        messagebox[109][0]=0.800000;
        messagebox[109][1]=0.300000;
        messagebox[110][0]=0.100000;
        messagebox[110][1]=0.400000;
        messagebox[111][0]=0.400000;
        messagebox[111][1]=1.600000;
        messagebox[112][0]=0.800000;
        messagebox[112][1]=0.600000;
        messagebox[113][0]=0.900000;
        messagebox[113][1]=0.300000;
        messagebox[114][0]=0.500000;
        messagebox[114][1]=1.400000;
        messagebox[115][0]=0.700000;
        messagebox[115][1]=0.800000;
        messagebox[116][0]=0.600000;
        messagebox[116][1]=1.700000;
        messagebox[117][0]=0.700000;
        messagebox[117][1]=1.900000;
        messagebox[118][0]=0.500000;
        messagebox[118][1]=1.000000;
        messagebox[119][0]=0.900000;
        messagebox[119][1]=0.200000;
        messagebox[120][0]=0.500000;
        messagebox[120][1]=0.700000;
        messagebox[121][0]=0.900000;
        messagebox[121][1]=1.800000;
        messagebox[122][0]=0.300000;
        messagebox[122][1]=0.700000;
        messagebox[123][0]=0.400000;
        messagebox[123][1]=1.600000;
        messagebox[124][0]=0.400000;
        messagebox[124][1]=1.700000;
        messagebox[125][0]=0.600000;
        messagebox[125][1]=1.100000;
        messagebox[126][0]=0.500000;
        messagebox[126][1]=0.100000;
        messagebox[127][0]=0.800000;
        messagebox[127][1]=1.400000;
        messagebox[128][0]=0.200000;
        messagebox[128][1]=0.800000;
        messagebox[129][0]=0.200000;
        messagebox[129][1]=1.500000;
        messagebox[130][0]=0.700000;
        messagebox[130][1]=0.600000;
        messagebox[131][0]=0.800000;
        messagebox[131][1]=1.500000;
        messagebox[132][0]=0.200000;
        messagebox[132][1]=1.300000;
        messagebox[133][0]=0.500000;
        messagebox[133][1]=0.600000;
        messagebox[134][0]=0.700000;
        messagebox[134][1]=1.400000;
        messagebox[135][0]=0.300000;
        messagebox[135][1]=1.900000;
        messagebox[136][0]=0.800000;
        messagebox[136][1]=1.400000;
        messagebox[137][0]=0.400000;
        messagebox[137][1]=0.100000;
        messagebox[138][0]=0.400000;
        messagebox[138][1]=1.500000;
        messagebox[139][0]=0.800000;
        messagebox[139][1]=0.800000;
        messagebox[140][0]=0.500000;
        messagebox[140][1]=0.900000;
        messagebox[141][0]=0.800000;
        messagebox[141][1]=1.000000;
        messagebox[142][0]=0.900000;
        messagebox[142][1]=0.300000;
        messagebox[143][0]=0.200000;
        messagebox[143][1]=1.000000;
        messagebox[144][0]=0.100000;
        messagebox[144][1]=1.300000;
        messagebox[145][0]=0.400000;
        messagebox[145][1]=0.800000;
        messagebox[146][0]=0.700000;
        messagebox[146][1]=0.100000;
        messagebox[147][0]=0.300000;
        messagebox[147][1]=0.300000;
        messagebox[148][0]=0.300000;
        messagebox[148][1]=1.100000;
        messagebox[149][0]=0.200000;
        messagebox[149][1]=1.300000;
        messagebox[150][0]=0.900000;
        messagebox[150][1]=0.900000;
        messagebox[151][0]=0.800000;
        messagebox[151][1]=0.100000;
        messagebox[152][0]=0.300000;
        messagebox[152][1]=0.600000;
        messagebox[153][0]=0.500000;
        messagebox[153][1]=1.900000;
        messagebox[154][0]=0.500000;
        messagebox[154][1]=1.000000;
        messagebox[155][0]=0.900000;
        messagebox[155][1]=1.000000;
        messagebox[156][0]=0.500000;
        messagebox[156][1]=0.300000;
        messagebox[157][0]=0.700000;
        messagebox[157][1]=0.600000;
        messagebox[158][0]=0.900000;
        messagebox[158][1]=0.100000;
        messagebox[159][0]=0.900000;
        messagebox[159][1]=1.100000;
        messagebox[160][0]=0.700000;
        messagebox[160][1]=1.600000;
        messagebox[161][0]=0.900000;
        messagebox[161][1]=0.900000;
        messagebox[162][0]=0.700000;
        messagebox[162][1]=1.500000;
        messagebox[163][0]=0.700000;
        messagebox[163][1]=0.700000;
        messagebox[164][0]=0.700000;
        messagebox[164][1]=1.300000;
        messagebox[165][0]=0.600000;
        messagebox[165][1]=0.500000;
        messagebox[166][0]=0.900000;
        messagebox[166][1]=0.800000;
        messagebox[167][0]=0.300000;
        messagebox[167][1]=0.100000;
        messagebox[168][0]=0.100000;
        messagebox[168][1]=0.200000;
        messagebox[169][0]=0.300000;
        messagebox[169][1]=1.100000;
        messagebox[170][0]=0.800000;
        messagebox[170][1]=0.100000;
        messagebox[171][0]=0.400000;
        messagebox[171][1]=0.500000;
        messagebox[172][0]=0.500000;
        messagebox[172][1]=1.600000;
        messagebox[173][0]=0.900000;
        messagebox[173][1]=0.500000;
        messagebox[174][0]=0.300000;
        messagebox[174][1]=1.800000;
        messagebox[175][0]=0.700000;
        messagebox[175][1]=0.700000;
        messagebox[176][0]=0.600000;
        messagebox[176][1]=0.500000;
        messagebox[177][0]=0.200000;
        messagebox[177][1]=0.700000;
        messagebox[177][0]=0.300000;
        messagebox[178][0]=0.700000;
        messagebox[178][1]=1.000000;
        messagebox[179][0]=0.100000;
        messagebox[179][1]=1.100000;
        messagebox[180][0]=0.900000;
        messagebox[180][1]=1.400000;
        messagebox[181][0]=0.100000;
        messagebox[181][1]=1.400000;
        messagebox[182][0]=0.600000;
        messagebox[182][1]=1.900000;
        messagebox[183][0]=0.200000;
        messagebox[183][1]=1.700000;
        messagebox[184][0]=0.200000;
        messagebox[184][1]=0.500000;
        messagebox[185][0]=0.400000;
        messagebox[185][1]=0.600000;
        messagebox[186][0]=0.500000;
        messagebox[186][1]=1.800000;
        messagebox[187][0]=0.200000;
        messagebox[187][1]=1.600000;
        messagebox[188][0]=0.200000;
        messagebox[188][1]=0.400000;
        messagebox[189][0]=0.600000;
        messagebox[189][1]=1.400000;
        messagebox[190][0]=0.200000;
        messagebox[190][1]=0.500000;
        messagebox[191][0]=0.900000;
        messagebox[191][1]=0.100000;
        messagebox[192][0]=0.400000;
        messagebox[192][1]=0.400000;
        messagebox[193][0]=0.600000;
        messagebox[193][1]=0.300000;
        messagebox[194][0]=0.400000;
        messagebox[194][1]=0.200000;
        messagebox[195][0]=0.700000;
        messagebox[195][1]=1.200000;
        messagebox[196][0]=0.500000;
        messagebox[196][1]=1.600000;
        messagebox[197][0]=0.100000;
        messagebox[197][1]=1.200000;
        messagebox[198][0]=0.600000;
        messagebox[198][1]=0.600000;
    }
   else if(randornot==3)
    {
        messagebox[0][0]=0.700000;
        messagebox[0][1]=0.100000;
        messagebox[1][0]=0.300000;
        messagebox[1][1]=0.400000;
        messagebox[2][0]=0.500000;
        messagebox[2][1]=0.300000;
        messagebox[3][0]=0.700000;
        messagebox[3][1]=0.400000;
        messagebox[4][0]=0.200000;
        messagebox[4][1]=0.100000;
        messagebox[5][0]=0.400000;
        messagebox[5][1]=0.600000;


    }
    /*
    **输出原始输入信号的信号概率和跳变密度
    */
#if 0

    int j;
    printf("\n");
    printf("the p and D of inputs:\n");
    for(i=0; i<numvars; i++)
    {
        for(j=0; j<2; j++)
        {
            printf("%f ",messagebox[i][j]);
        }
        printf("\n");
    }


#endif

#if 0
    /*
    **输出原始输入信号的信号概率和跳变密度到文件./output/init_pd.txt
    */
    printinitPD(numvars);

#endif
}
void
takechange(toolnodes g1[],int i_gate)
{
	g1[i_gate].nodetype=2; //把单输入门记为wire，没有功耗   
}


void
transRMandgate(toolnodes g[])
{   
	FILE *fp;  
    if((fp=fopen("information of node.txt","w"))==NULL) /*建立新文件 */  
    {  
        printf("cannot open file\n"); /*建立新文件出错误信息*/  
        exit(1); /*终止调用过程、关闭所有文件*/  
    }  
    //ch=getchar( ); /*从键盘读入一个字符*/  
    //while(ch!='#') /*读到#时停止输入*/  
    //{  
    //    fputc(ch,fp); /*将ch内字符写入fp指向的文件*/  
    //    ch=getchar( );  
    //}  
    //fclose(fp); /*关闭文件*/   
	int k0=0;
	int i;
	for(k0=RM_numgatend+RM_numtinputs-1; k0>=0; k0--){
       /* printf("the number of out=%d,\nthe k's output name ",g[k0].outputi);

        for (i=0;i<9;i++){
            printf("%c",g[k0].outputname[i]);}
        printf("\n");*/
		fprintf(fp,"the %d node is %d have numinput %d\n",k0,g[k0].nodetype,g[k0].numinput);
       if(g[k0].nodetype==1){
		   for(i=0;i<g[k0].numinput;i++){
		      fprintf(fp,"the and  %dst of %d input is %d\n",i,k0,g[k0].inputi[i]);
		   }
	   }
	    if(g[k0].nodetype==2){
		   for(i=0;i<g[k0].numinput;i++){
		      fprintf(fp,"the buff %d input is %d\n",k0,g[k0].inputi[i]);
		   }
	   }
	    if(g[k0].nodetype==5){
		   for(i=0;i<g[k0].numinput;i++){
		      fprintf(fp,"the xor  %dst of %d input is %d\n",i,k0,g[k0].inputi[i]);
		   }
	   }
        /* if (g[k0].nodetype==1)
         {
             for (i=0;i<9;i++){
                printf("%c",g[tin1].outputname[i]);}
                printf(",");
            for (i=0;i<9;i++){
                printf("%c",g[tin2].outputname[i]);}
         }
         else
            for (i=0;i<9;i++){
                printf("%c",g[tin1].outputname[i]);}*/
       // printf("the %d have and\n",k);
       // printf("the upi of k i=%d,%dname",g[k0].upi[0],g[k0].upi[1]);
       // printf("the nodenumup of k=%d\n",g[k0].numup);
       // printf("the flag=%d\n",g[k0].flag_use);
        //printf("the input=%d\n",abcnode[k].inputi);
       // printf("\n");printf("\n");
    }    
	fprintf(fp,"ending  --------------------------------------------------------------------\n");
	fclose(fp); /*关闭文件*/  



	FILE *fp1; 
	
    if((fp1=fopen("sw information.txt","w"))==NULL) /*建立新文件 */  
    {  
        printf("cannot open file\n"); /*建立新文件出错误信息*/  
        exit(1); /*终止调用过程、关闭所有文件*/  
    }
	for(k0=RM_numgatend+RM_numtinputs-1; k0>=0; k0--){ 
    fprintf(fp1," k",k0);
	fprintf(fp1,"the nodeprob of k=%f\n",g[k0].nodeprob);
	fprintf(fp1,"the nodeswith of k=%f\n",g[k0].nodeswith);
	
	}
	fprintf(fp,"ending  --------------------------------------------------------------------\n");
	fclose(fp1);
}