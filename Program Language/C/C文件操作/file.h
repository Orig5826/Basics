/*********************************************************************
文件：flash
时间：2016/4/25__Original__13:10:31
备注：

*********************************************************************/
#ifndef _flash_H_
#define _flash_H_
// ----------------------------------------------
// 					0.头文件
// ----------------------------------------------
#include <stdio.h>
#include <string.h>
// ----------------------------------------------
// 					1. 常量和typedef
// ----------------------------------------------
#define PAGESIZE		0x400		//每页大小	1k


typedef unsigned char uint8_t;
typedef unsigned long uint32_t;
typedef unsigned char bool;

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif
// ----------------------------------------------
// 					2. 结构体...
// ----------------------------------------------

// ----------------------------------------------
// 					3. 函数声明
// ----------------------------------------------
//是否关闭调试接口
#define NDEBUG

//file 基本接口
bool FileWrite(const char * pcName,uint32_t uiAddr,uint8_t *pucIn,uint32_t uidlen);
uint32_t FileRead(const char * pcName,uint32_t uiAddr,uint32_t uidlen,uint8_t *pucOut);
void FileEraseAll(const char * pcName);
//file 扩展接口
void File_Copy(const char * sfilename,const char * ofilename);
uint32_t File_Length(const char * pcName);
uint32_t FileToRam(const char * fname,uint8_t ** pData);

#ifndef NDEBUG
void FileTest(void);
#endif

/*********************************************************************
							结束
*********************************************************************/
#endif
