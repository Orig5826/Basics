/*********************************************************************
文件：Prac
时间：2016/3/28__Original__18:09:58
备注：
		C中出现下标为负值的情况也有，但一般情况下不这么做
	具体见：嵌入式开发  ----   SVC模块
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//注释：之所以出现这样的结果，是因为其为小端模式
	int a[20] = {0x01020304,0x05060708,0x090a0b0c,0x0e0f1011,0x12131415,0x16171819};
	int num = 0;
	num = ((char *)(a + 3))[2];
	printf("num = %02x\n",num);

	num = ((char *)(a + 3))[1];
	printf("num = %02x\n",num);

	num = ((char *)(a + 3))[0];
	printf("num = %02x\n",num);

	num = ((char *)(a + 3))[-1];
	printf("num = %02x\n",num);

	num = ((char *)(a + 3))[-2];
	printf("num = %02x\n",num);

	system("pause");
}