/*******************************************
[  �ļ�  ]			Practice.c
[  ����  ]			Dell PC_��
[����ʱ��]	2015/5/5 [21:21:53]
[  ����  ]
[  ע��  ]
FFT���������뵽�ĵ�һ�ֵ���ķ���	
********************************************/
#include <stdio.h>
#include <math.h>

//=================================================
//�궨��
#define Size(x) (sizeof(x)/sizeof(x[0]))
#define log2(x) (unsigned int)(log(x)/log(2))

#define SIZE 16
//��������
typedef unsigned char Array[SIZE];

//------------------------------------------------------------
//�����ܡ�			����
//��������
//�����ء�
//�����̡�
//===DATE===2015����05�ܶ�//===TIME===21:23:44===//
//------------------------------------------------------------
unsigned char * inverted_order(const Array a)	//����
{
	static Array b = {0};
	static unsigned char temp = 0;
	unsigned int i = 0, j = 0;
	
	//printf("ԭ���У�");
	//for(i = 0; i < SIZE; i ++)
	//{
	//	printf("%d\t",a[i]);
	//}
	//printf("\n");
	for(i = 0; i < SIZE; i ++)
	{
		for(j = 0; j < log2(SIZE); j ++)
		{
			temp = a[i];
			b[i] |= (((temp >> j) & 0x01)<<(log2(SIZE) - 1 - j));
		}
	}
	//����
	//printf("�����");
	//for(i = 0; i < SIZE; i ++)
	//{
	//	printf("%d\t",b[i]);
	//}
	//printf("\n");
	return b;
}

void main(void )
{
	unsigned char i = 0;
	Array a = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

	unsigned char * pp = NULL;
	pp = inverted_order(a);

	printf("�����");
	for(i = 0; i < SIZE; i ++)
	{
		printf("%d\t",*( pp + i));
	}
	printf("\n");
}
