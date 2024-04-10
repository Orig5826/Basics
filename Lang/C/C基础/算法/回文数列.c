/*
	�����ǻ��ĵ����У�ͨ�����������͵ķ�ʽȡ������������
	����취�ﵽ����Ϊ���ĵ����С�
*/
#include<stdio.h>

/*
 *head�������������ʼ������tail������������һ��Ԫ�ص�����
 *�����������У��ֱ�ʹ������������ͷ����head��β����tail����
 *������Թ���ɻ������֣���head��tail�ֱ����м俿��
 *��head�����ұߵ�������ͣ�tail������ߵ�������͡�
 */
int hand(int a[], int head, int rear);
int main()
{
	// int a[] = { 1,1,1,3 };
	// int a[] = { 2,4,4,2 };
	//int a[] = { 2,3,1,4,2 };
	int a[] = { 1,2,3,5,7,10,9,1,7,8,1,1,1 };

	int n = sizeof(a)/sizeof(a[0]);

	int count = hand(a, 0, n - 1);
	printf("Ҫ����Ĵ���Ϊ��%d\n", count);
	return 0;
}


int hand(int a[], int head, int rear)
{
	int left = a[head];
	int right = a[rear];
	int times = 0;

	while (head < rear && left != right)
	{
		if (left < right)
		{
			left += a[++head];
		}
		else
		{
			right += a[--rear];
		}
		times++;
	}

	if (head >= rear - 1)
	{
		return times;
	}
	else
	{
		return times + hand(a, ++head, --rear);
	}
}
