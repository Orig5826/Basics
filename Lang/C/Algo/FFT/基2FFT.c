/*******************************************
[  文件  ]			Practice.c
[  作者  ]			Dell PC_峰
[创建时间]	2015/5/7 [13:45:04]
[  功能  ]			基2DDT算法
[  注释  ]
		版本1.0【程序编写成功用时3天】
********************************************/
#include<stdio.h>
#include<math.h>

//SIZE-point DFT
//本程序SIZE只能是2的整次幂
#define SIZE	16
typedef unsigned int Array[SIZE];
#define PI		3.14159265358979323846

typedef struct
{
	double real;
	double imag;
}Complex,* pComplex;

pComplex Complex_Add(const Complex C1,const Complex C2)
{
	static Complex C;
	C.real = C1.real + C2.real;
	C.imag = C1.imag + C2.imag;
	return &C;
}
pComplex Complex_Sub(const Complex C1,const Complex C2)
{
	static Complex C;
	C.real = C1.real - C2.real;
	C.imag = C1.imag - C2.imag;
	return &C;
}

pComplex Complex_Mul(const Complex C1,const Complex C2)
{
	static Complex C;
	C.real = (C1.real * C2.real) - (C1.imag * C2.imag);
	C.imag = C1.real * C2.imag + C1.imag * C2.real;
	return &C;
}

void Display(pComplex pC)
{
	static unsigned char count = 1;
	if(pC->imag < 0)
	{
		printf("%7.4f-%6.4fi ",pC->real,-pC->imag);
	}
	else
	{
		printf("%7.4f-%6.4fi ",pC->real,pC->imag);
	}

	if(count ++ >= 4)//先判断后加1
	{
		count = 1;
		printf("\n");
	}
}

pComplex TwiddleFactor(unsigned int p, unsigned int N)
{
	static Complex C;
	C.real = cos((2 * PI * p)/ N);
	C.imag = -sin((2 * PI * p)/ N);
	return &C;
}


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

pComplex fft(Array a,unsigned int M)
{
	unsigned int i = 0;
	unsigned int Level = 0;
	unsigned int N = pow(2,M);
	unsigned int B,J,k;
	unsigned int exponent;
//	double temp;	//用于暂时存储
	static Complex C[SIZE];
	pComplex pComp_temp1,pComp_temp2;

	inverted_order(a);	//倒序
	for(i = 0; i < SIZE; i ++)
	{
		C[i].real = (double)a[i];
		C[i].imag = 0.0;
	}
	for(Level = 1; Level <= M; Level ++)
	{
		B = (unsigned int)pow(2,Level - 1);
		for(J = 0; J <= B - 1; J++ )
		{
			exponent = J * (unsigned int)pow(2,M - Level);
			for(k = J; k <= N - 1; k += (unsigned int)pow(2,Level))
			{
				pComp_temp1 = Complex_Add(C[k],(*Complex_Mul(C[k + B],(* TwiddleFactor(exponent,N)))));
				pComp_temp2 = Complex_Sub(C[k],(*Complex_Mul(C[k + B],(* TwiddleFactor(exponent,N)))));
				C[k].real = pComp_temp1->real;
				C[k].imag = pComp_temp1->imag;
				C[k + B].real = pComp_temp2->real;
				C[k + B].imag = pComp_temp2->imag;
			}
		}
	}
	return &C[0];
}


void main(void )
{
	pComplex pC;
	unsigned int i;
	unsigned int a[SIZE] = {0,1,2,3,4,3,2,1,0};//,8,9,10,11,12,13,14,15};
//	unsigned int a[SIZE] = {1,1,1,1,1,1,1,1};
	for(i = 0; i < SIZE; i ++)
	{
		printf("%d\t",a[i]);
	}
	printf("\n");

	pC = fft(a,(unsigned int )((double)log(SIZE)/(double)log(2)));
//	pC = fft(a,16);

	//结果显示
	for(i = 0; i < SIZE; i ++)
	{
		Display((pC + i));
	}
}