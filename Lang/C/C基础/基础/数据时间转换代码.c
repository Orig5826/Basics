
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	time_t timer;
	struct tm * tblock;
	timer = time(NULL);
	
	printf("-----------------------------------\n");
	printf("     ��4λ16��������ת��Ϊʱ��     \n");
	printf("-----------------------------------\n");

	printf("1.����16���ƣ�\n\t");
	scanf("%x",&timer);

	printf("2.ʮ����:\n\t%d\n",timer);

	tblock = localtime(&timer);
	printf("3.ʱ��:\n\t%s\n",asctime(tblock));

	system("pause");
	return 0;
}