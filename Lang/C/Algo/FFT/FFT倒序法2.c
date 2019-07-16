/*******************************************
[  �ļ�  ]			Practice.c
[  ����  ]			Dell PC_��
[����ʱ��]	2015/5/6 [14:02:00]
[  ����  ]	����
[  ע��  ]
FFT��	���Ǵ�����ѧ���ķ���	
********************************************/
#include <stdio.h>
#define SIZE 16
typedef unsigned int Array[SIZE];

void inverted_order(Array a)		//����
{
	unsigned int N,K;//N����������K��Ӧ�����λȨֵ
	unsigned int I,J;//I�������У�J����<FFT>
	N = SIZE;
	J = N / 2;
	for(I = 1; I <= N - 2; I ++)//��Ϊ��Ԫ�غ�βԪ�ز���Ҫ����
	{
		if(I < J)
		{
			//������������
			a[I] ^= a[J];
			a[J] ^= a[I];
			a[I] ^= a[J];
		}
		K = N / 2;		//���λȨֵ
		while(J >= K)
		{
			J = J - K;	//����ʱ��Ӧ�����λ��0
			K = K / 2;	//��ʱ��Ӧ�Ĵθ�λȨֵ
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