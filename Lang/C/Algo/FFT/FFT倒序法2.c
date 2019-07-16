/*******************************************
[  文件  ]			Practice.c
[  作者  ]			Dell PC_峰
[创建时间]	2015/5/6 [14:02:00]
[  功能  ]	倒序
[  注释  ]
FFT：	这是从书上学到的方法	
********************************************/
#include <stdio.h>
#define SIZE 16
typedef unsigned int Array[SIZE];

void inverted_order(Array a)		//倒序
{
	unsigned int N,K;//N数据总数，K对应的最高位权值
	unsigned int I,J;//I正常序列，J倒序<FFT>
	N = SIZE;
	J = N / 2;
	for(I = 1; I <= N - 2; I ++)//因为首元素和尾元素不需要交换
	{
		if(I < J)
		{
			//交换两个数据
			a[I] ^= a[J];
			a[J] ^= a[I];
			a[I] ^= a[J];
		}
		K = N / 2;		//最高位权值
		while(J >= K)
		{
			J = J - K;	//将此时对应的最高位清0
			K = K / 2;	//此时对应的次高位权值
		}
		J = J + K;
	}
}

void main(void )
{
	unsigned int i;
	unsigned int a[SIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	for(i = 0; i < SIZE; i ++)
	{
		printf("%d\t",a[i]);
	}
	printf("\n");

	inverted_order(a);
	for(i = 0; i < SIZE; i ++)
	{
		printf("%d\t",a[i]);
	}
	printf("\n");
}