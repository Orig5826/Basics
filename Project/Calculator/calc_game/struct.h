#define MAX 10
#define TRUE 1
#define FALSE 0

typedef struct Information
{
	unsigned char flag;		//��4λΪ���Ѷ�
	char name[31];
	int age;
	int grade;
}Infor_List;

typedef struct Calculate
{
	unsigned char flag[MAX];		//ÿ�����ݵķ����־(�ӡ������ˡ���)
	int num_1[MAX];
	int num_2[MAX];
	int sum_w[MAX];	//��¼��Ĵ����
	int last;
}List;

void InitList(List *L);
int ListEmpty(List L);
void ListAdd(List *L,int a,int b,int sum);
int ListLength(List L);