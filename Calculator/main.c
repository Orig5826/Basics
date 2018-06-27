#include "common.h"
#include "getBuff.h"
#include "Calc.h"

void print()
{
	int i = 0;
	printf("----------------------------------\n");
	for(i = 0; i < getBuffLen();i++)
	{
		printf("%c",g_str.buff[i]);
	}
	printf("\n----------------------------------\n");
}

int main(int argc, char * argv[])
{
	while(1)
	{
		double num = 0;
		CalcInit();

		getBuff();
		print();
		getNum(g_str.buff,&num);
		printf("%f\n",num);

		InfixToSuffix();
		printf("\n-----------------------------------\n");

		Calculate();
	}
	return 0;
}