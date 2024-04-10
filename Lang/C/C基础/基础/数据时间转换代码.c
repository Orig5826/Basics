
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	time_t timer;
	struct tm * tblock;
	timer = time(NULL);
	
	printf("-----------------------------------\n");
	printf("     将4位16进制数据转换为时间     \n");
	printf("-----------------------------------\n");

	printf("1.输入16进制：\n\t");
	scanf("%x",&timer);

	printf("2.十进制:\n\t%d\n",timer);

	tblock = localtime(&timer);
	printf("3.时间:\n\t%s\n",asctime(tblock));

	system("pause");
	return 0;
}