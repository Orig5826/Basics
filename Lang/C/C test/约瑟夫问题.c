/*
	约瑟夫问题

	设有n个人围坐在圆桌周围，从某个位置开始用自然数进行编号为1，2，…，n。然后从
	设有n个人围坐在圆桌周围，从某个位置开始用自然数进行编号为1，2，…，n。然后从编号为k的人从1开始报数，
	数到m的人便出列；下一个人(第m十1个)又从1开始报数，数到m的人便是第二个出列的人。如此继续下去，直到最
	后一个人出列为止。要求输出这个出列的顺序。
	这个问题称为雅瑟夫(Josephu)问题。
	具体要求如下：
	(1)n、m、k由键盘输入，输入前要有提示。
	(2)在输入n后，动态建立方法说明中所需要建立的数组空间；程序运行结束时释放该
	存储空间。
	(3)分别用n＝8，m＝4，k＝1以及n＝10，m＝12，k = 4调试运行你的程序。

	// 以下的代码根据朋友提供，我仅仅做了的修改。且根据题目要求，k=0恒定不变(即开始时从编号为1的人开始报1)。
	// 源地址如下：https://zhidao.baidu.com/question/268672208.html
	// 本次记录仅仅方便以后自己查看
*/

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
};


void main()
{
	int n = 0, m = 0, k = 0, i = 0;
	int j = 0,cnt = 0;
	struct node * head, *s, *temp;
	int * pData = NULL;

	//scanf("%d", &n);
	//scanf("%d", &m);
#if 0
	printf("请输入k: ");
	scanf("%d", &k);
#endif

	scanf("%d", &cnt);
	pData = (int *)malloc(sizeof(int) * cnt * 2);
	j = 0;
	while (j < cnt)
	{
		scanf("%d", &n);
		scanf("%d", &m);

		pData[2 * j] = n;
		pData[2 * j + 1] = m;
		j++;
	}

	j = 0;
	while (j < cnt)
	{
		n = pData[2 * j];
		m = pData[2 * j + 1];

		head = (struct node*)malloc(sizeof(struct node));//第一个人的信息
		head->data = 1;
		temp = head->next = head;
		for (i = 2; i <= n; i++)//所有人的序号信息
		{
			s = (struct node*)malloc(sizeof(struct node));
			s->data = i;
			s->next = head;
			temp->next = s;
			temp = s;
		}
		s = head;
		for (i = 1; i < k; i++)
		{
			s = s->next;
		}

		while (s->next != s)
		{
			for (i = 1; i < m; i++)//先数m-1个数
			{
				temp = s;
				s = s->next;
			}
			printf("%d ", s->data);
			temp->next = s->next;
			free(s);
			s = temp->next;
		}
		printf("%d\n", s->data);
		free(s);
		j++;
	}
	free(pData);
}
