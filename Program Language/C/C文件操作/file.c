#include "file.h"

// ==================================== File 基本接口 ====================================
//-----------------------(^_^)-------------------------
// 函数: bFileWrite
// 时间: 2017/4/21__Original__10:45:54
// 功能：给文件写入内容
// 参数:
// 		const char * pcName		文件名称（字符串）
// 		uint32_t uiAddr			写入地址
// 		uint8_t * pucIn			写入长度
// 		uint32_t uidlen			写入的数据
// 返回:
// 		bool
//-----------------------------------------------------
bool FileWrite(const char * pcName,uint32_t uiAddr,uint8_t *pucIn,uint32_t uidlen)
{
	FILE * pf;
	//printf("---------------------------\n");
	if((pf = fopen(pcName,"rb+")) == NULL)
	{
		printf("[%s] File Read Error\n",pcName);
		if((pf = fopen(pcName,"wb")) != NULL)
		{
			printf("[ %s ] Create File Succeed!\n",pcName);
		}
		else
		{
			printf("[ %s ] Create File Failed!\n",pcName);
			return FALSE;
		}
	}
	fseek(pf,uiAddr,SEEK_SET);
	fwrite(pucIn,sizeof(uint8_t),uidlen,pf);
	fclose(pf);
	printf("[ %s ] Write File Succeed!\n",pcName);
	return TRUE;
}

//-----------------------(^_^)-------------------------
// 函数: bFileRead
// 时间: 2017/4/21__Original__10:46:30
// 功能：读出文件内容
// 参数:
// 		const char * pcName		文件名称（字符串）
// 		uint32_t uiAddr			读出地址
// 		uint32_t uidlen			期望读出长度
// 		uint8_t * pucOut		读出的数据
// 返回:
// 		uint32_t 0.读取失败或者不读任何数据
//		other.实际读取的数据长度
//-----------------------------------------------------
uint32_t FileRead(const char * pcName,uint32_t uiAddr,uint32_t uidlen,uint8_t *pucOut)
{
	FILE * pf;
	uint32_t datalen = 0;
	//printf("---------------------------\n");
	//之前直接"r"，读取到0x19之后的数据就读不出来了。现在使用二进制读取，则全部读出
	if((pf = fopen(pcName,"rb")) == NULL)
	{
		printf("[%s] File Read Error\n",pcName);
		if((pf = fopen(pcName,"wb")) != NULL)
		{
			printf("[ %s ] Create File Succeed!\n",pcName);
		}
		else
		{
			printf("[ %s ] Create File Failed!\n",pcName);
			return 0;
		}
	}

	//-------------------------------------------
	// 此处的目的，仅仅是为了定位文件的结尾。
	// 这样ftell就能够返回文件结尾的地址
	//-------------------------------------------
	fseek(pf,0,SEEK_END);
	//-------------------------------------------
	// 若长度+偏移超出文件，则返回实际读取的长度
	//-------------------------------------------
	datalen = ftell(pf) - uiAddr;
	if(uidlen < datalen)
	{
		datalen = uidlen;
	}

	fseek(pf,uiAddr,SEEK_SET);
	fread(pucOut,sizeof(uint8_t),datalen,pf);
	fclose(pf);
	printf("[ %s ] Read File Succeed!\n",pcName);
	return datalen;
}

//-----------------------(^_^)-------------------------
// 函数: vFileEraseAll
// 时间: 2017/4/21__Original__11:07:50
// 功能：若文件存在则擦除。若不存在，则提示
// 参数:
// 		const char * pcName
// 返回:
// 		void
//-----------------------------------------------------
void FileEraseAll(const char * pcName)
{
	FILE * pf;
	//printf("---------------------------\n");
	if((pf = fopen(pcName,"rb")) == NULL)
	{
		printf("[ %s ] File not exist!\n",pcName);
		return;
	}
	else
	{
		//若文件存在
		if((pf = fopen(pcName,"wb")) != NULL)
		{
			printf("[ %s ] Clear File Succeed!\n",pcName);
		}
		else
		{
			printf("[ %s ] Clear File Failed!\n",pcName);
			return;
		}
	}
	fclose(pf);
}

// ==================================== File 扩展接口 ====================================
//-----------------------(^_^)-------------------------
// 函数: File_Copy
// 时间: 2017/6/30__Original__15:03:50
// 功能：将sfilename文件中的内容直接复制到ofilename文件中
// 参数:
// 		const char * sfilename      源文件
//      const char * ofilename      目标文件
// 返回:
// 		void
//-----------------------------------------------------
void File_Copy(const char * sfilename,const char * ofilename)
{
    #define DATASIZE    0x400
    int datalen = 0,addr = 0;
    unsigned char array[DATASIZE];
    //若文件存在，则清空。若不存在则创建
    FileEraseAll(ofilename);
    do
    {
        datalen = 0;
        datalen = FileRead(sfilename,addr,DATASIZE,array);
        printf("%d",addr );
        FileWrite(ofilename ,addr,array,datalen);
        addr += DATASIZE;
    }while(datalen == DATASIZE);
    printf("文件复制成功！\n");
}
//-----------------------(^_^)-------------------------
// 函数: File_Length
// 时间: 2017/6/30__Original__15:03:50
// 功能：获取文件总长度
// 参数:
// 		const char * pcName     文件名称
// 返回:
// 		void
//-----------------------------------------------------
uint32_t File_Length(const char * pcName)
{
	FILE * pf;
	uint32_t datalen = 0;
	//printf("---------------------------\n");
	//之前直接"r"，读取到0x19之后的数据就读不出来了。现在使用二进制读取，则全部读出
	if((pf = fopen(pcName,"rb")) == NULL)
	{
		printf("[%s] File Read Error\n",pcName);
		if((pf = fopen(pcName,"wb")) != NULL)
		{
			printf("[ %s ] Create File Succeed!\n",pcName);
		}
		else
		{
			printf("[ %s ] Create File Failed!\n",pcName);
			return 0;
		}
	}
	//-------------------------------------------
	// 此处的目的，仅仅是为了定位文件的结尾。
	// 这样ftell就能够返回文件结尾的地址
	//-------------------------------------------
	fseek(pf,0,SEEK_END);
	datalen = ftell(pf);
	printf("flen = %d\n",datalen);
	fclose(pf);
	return datalen;
}
//-----------------------(^_^)-------------------------
// 函数: FileToRam
// 时间: 2017/6/30__Original__15:03:50
// 功能：将文件所有内容读取到ram中
// 参数:
// 		const char * pcName     文件名称
//      uint8_t ** pData        数据二级指针
// 返回:
// 		uint32_t 返回该文件总长度
//-----------------------------------------------------
uint32_t FileToRam(const char * fname,uint8_t ** pData)
{
    uint32_t flength = 0;
    flength = File_Length(fname);

    //分配文件大小的空间
    *pData = (uint8_t * )malloc(sizeof(uint8_t) * flength);
    FileRead(fname,0,flength,*pData);
}

// ==================================== File接口测试 ====================================
#ifndef NDEBUG
//显示HEX数据
static void Orig_DisplayHex(const uint8_t *data,uint32_t dataLen)
{
	uint32_t  i = 0;
	printf("-------------------- HEX --------------------\n");
	for(i = 0;i < dataLen; i++)
	{
		if(i % 16 == 0 && i != 0)
		{
			printf("\n");
		}
		printf("%02x ",*(data + i));
	}
	printf("\n");
}
//显示字符串
static void Orig_Display(const char *str,uint32_t dataLen)
{
	uint32_t  i = 0;
	printf("-------------------- String --------------------\n");
	for(i = 0;i < dataLen && *(str + i) != '\0' ; i++)
	{
		printf("%c",*(str + i));
	}
	printf("\n");
}

void FileTest(void)
{
	const char * name = "Hello";
	const char * name2 = "a.txt";
	const uint8_t ch[] = "Hello World!\r\n HHH \x00\x01  ";
	uint8_t data[PAGESIZE] = {0};
	int datalen = PAGESIZE;

	datalen = FileRead(name2,0,PAGESIZE,data);
	Orig_DisplayHex(data,datalen);
	Orig_Display(data,datalen);

	FileEraseAll(name);
	FileWrite(name,0,data,datalen);

	datalen = FileRead(name,0,datalen,data);
	Orig_DisplayHex(data,datalen);
	Orig_Display(data,datalen);
}

#endif
