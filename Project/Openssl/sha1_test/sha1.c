#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>

int main()
{
    SHA_CTX stx;
    unsigned char outmd[20];
    char buffer[1024];
    char filename[32];
    int len=0;
    int i;
    FILE * fp=NULL;
    memset(outmd,0,sizeof(outmd));
    memset(filename,0,sizeof(filename));
    memset(buffer,0,sizeof(buffer));
//	printf("请输入文件名，用于计算SHA1值:");
//	scanf("%s",filename);
	//
	// a.txt 中的内容是"12345678"
	// sha1结果是hex：7C222FB2927D828AF22F592134E8932480637C0D
	memcpy(filename,"a.txt",sizeof("a.txt"));
    fp=fopen(filename,"rb");
    if(fp==NULL)
    {
        printf("Can't open file\n");
        return 0;
    }

    SHA1_Init(&stx);
    while((len=fread(buffer,1,1024,fp))>0)
    {
        SHA1_Update(&stx,buffer,len);
        memset(buffer,0,sizeof(buffer));
    }
    SHA1_Final(outmd,&stx);

    for(i=0;i<20;i<i++)
    {
        printf("%02X",outmd[i]);
    }
    printf("\n");
    return 0;
}