/*
	Լɪ������

	����n����Χ����Բ����Χ����ĳ��λ�ÿ�ʼ����Ȼ�����б��Ϊ1��2������n��Ȼ���
	����n����Χ����Բ����Χ����ĳ��λ�ÿ�ʼ����Ȼ�����б��Ϊ1��2������n��Ȼ��ӱ��Ϊk���˴�1��ʼ������
	����m���˱���У���һ����(��mʮ1��)�ִ�1��ʼ����������m���˱��ǵڶ������е��ˡ���˼�����ȥ��ֱ����
	��һ���˳���Ϊֹ��Ҫ�����������е�˳��
	��������Ϊ��ɪ��(Josephu)���⡣
	����Ҫ�����£�
	(1)n��m��k�ɼ������룬����ǰҪ����ʾ��
	(2)������n�󣬶�̬��������˵��������Ҫ����������ռ䣻�������н���ʱ�ͷŸ�
	�洢�ռ䡣
	(3)�ֱ���n��8��m��4��k��1�Լ�n��10��m��12��k = 4����������ĳ���

	// ���µĴ�����������ṩ���ҽ������˵��޸ġ��Ҹ�����ĿҪ��k=0�㶨����(����ʼʱ�ӱ��Ϊ1���˿�ʼ��1)��
	// Դ��ַ���£�https://zhidao.baidu.com/question/268672208.html
	// ���μ�¼���������Ժ��Լ��鿴
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
	printf("������k: ");
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

		head = (struct node*)malloc(sizeof(struct node));//��һ���˵���Ϣ
		head->data = 1;
		temp = head->next = head;
		for (i = 2; i <= n; i++)//�����˵������Ϣ
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
			for (i = 1; i < m; i++)//����m-1����
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
