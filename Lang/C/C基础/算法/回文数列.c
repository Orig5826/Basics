/*
	将不是回文的数列，通过两相邻数和的方式取代这两个数，
	来想办法达到最终为回文的数列。
*/
#include<stdio.h>

/*
 *head：代表数组的起始索引，tail代表数组的最后一个元素的索引
 *对于数字序列，分别使用两个索引（头索引head和尾索引tail），
 *如果可以构造成回文数字，则head和tail分别向中间靠，
 *即head与它右边的数字求和，tail和它左边的数字求和。
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
	printf("要处理的次数为：%d\n", count);
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
