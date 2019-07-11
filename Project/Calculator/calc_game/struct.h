#define MAX 10
#define TRUE 1
#define FALSE 0

typedef struct Information
{
	unsigned char flag;		//低4位为困难度
	char name[31];
	int age;
	int grade;
}Infor_List;

typedef struct Calculate
{
	unsigned char flag[MAX];		//每组数据的分类标志(加、减、乘、除)
	int num_1[MAX];
	int num_2[MAX];
	int sum_w[MAX];	//记录你的错误答案
	int last;
}List;

void InitList(List *L);
int ListEmpty(List L);
void ListAdd(List *L,int a,int b,int sum);
int ListLength(List L);