#include <stdio.h>
#include <stdlib.h>

//#define DEBUG


//-------------------------------
//		HEX -> ASSIC显示
//-------------------------------
#define HEX_H(x) ((((x>>4)&0x0f)<=9)?(((x>>4)&0x0f) + 0x30):(((x>>4)&0x0f)-0x0A+0x41))
#define HEX_L(x) ((((x>>0)&0x0f)<=9)?(((x>>0)&0x0f) + 0x30):(((x>>0)&0x0f)-0x0A+0x41))

void ReadFile(char * fname,unsigned char ** pStr,unsigned int *strlen)
{
	unsigned int i = 0,ch = 0;
	unsigned char *str;
	FILE * pf;
	if((pf = fopen(fname,"r")) == NULL)
	{
		printf("文件打开失败！\n");
		exit(-1);
	}
	//1.获取文件总长度
	fseek(pf,0,SEEK_END);
	*strlen = 3 * ftell(pf);
	//debug
	printf("The size of \"%s\" is %d Bytes\n",fname,*strlen);

	//2.分配空间
	*pStr = (unsigned char *)malloc((*strlen) * sizeof(unsigned char));
	if(*pStr == NULL)
	{
		printf("分配空间失败！\n");
		exit(-1);
	}

	//3.数据复制
	//4.同时将HEX转化为assic码显示
	str = *pStr;
	fseek(pf,0,SEEK_SET);
	for(i = 0; i < *strlen ; i+= 3)
	{
		ch = fgetc(pf);
		*(str) = HEX_H(ch);
		*(str+1) = HEX_L(ch);
		*(str+2) = 0x20;
#ifdef DEBUG
		printf("%c%c%c",*(str),*(str+1),*(str+2));
#endif
		str += 3;
	}
#ifdef DEBUG
	printf("\n");
#endif
	fclose(pf);
}

void WriteFile(char * fname,unsigned char * str,unsigned int strlen)
{
	unsigned int i = 0,ch = 0;
	FILE * pf;
	if((pf = fopen(fname,"w")) == NULL)
	{
		printf("文件打开失败！\n");
		exit(-1);
	}
	//将数据分组后，写入到文件中
	fseek(pf,0,SEEK_SET);
	for(i = 0; i < strlen ; i+=3)
	{
		//这是我自己添加的回车
// 		if(i!=0 && i%(3*16)==0)
// 		{
// 			fprintf(pf,"\n");
// 		}

		fprintf(pf,"%c%c%c",*str,*(str+1),*(str+2));
		str += 3;
	}

	fclose(pf);
}
#ifdef DEBUG
void Display(char * str,unsigned int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		if(i!=0 && i%(3*8)==0)
		{
			printf("\n");
		}
		printf("%c",*(str + i));
	}
}
#endif
int main(int argc,char * argv[])
{
	unsigned char * str;
	unsigned int strlen;
	if(argc != 2 + 1)
	{
		printf("参数输入错误！\n");
		return -1;
	}
	//argv[1] 原始文件
	//argv[2] 输入hex的文件
	ReadFile(argv[1],&str,&strlen);
#ifdef DEBUG
	Display(str,strlen);
#endif
	WriteFile(argv[2],str,strlen);

	return 0;
}