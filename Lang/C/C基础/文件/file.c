/**
 * @file file.c
 * @author wenjf (wenjf@hongsi-ic.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "file.h"

/**
 * @brief 文件写操作
 * 
 * @param file_name 文件名
 * @param addr 地址
 * @param data 数据
 * @param len 长度
 * @return true 
 * @return false 
 */
bool file_write(const char * file_name,uint32_t addr,uint8_t *data,uint32_t len)
{
	FILE * pf;
	if((pf = fopen(file_name,"rb+")) == NULL)
	{
		if((pf = fopen(file_name,"wb")) == NULL)
		{
			return false;
		}
	}
	fseek(pf,addr,SEEK_SET);
	fwrite(data,sizeof(uint8_t),len,pf);
	fclose(pf);
	return true;
}

/**
 * @brief 文件读操作
 * 
 * @param file_name 文件名
 * @param addr 地址
 * @param data 数据
 * @param len 长度
 * @return uint32_t 返回实际读取到的长度
 */
uint32_t file_read(const char * file_name,uint32_t addr,uint8_t *data,uint32_t len)
{
	FILE * pf;
	uint32_t datalen = 0;

	if((pf = fopen(file_name,"rb")) == NULL)
	{
		if((pf = fopen(file_name,"wb")) == NULL)
		{
			return 0;
		}
	}

	// 长度不能超过文件大小
	fseek(pf,0,SEEK_END);
	datalen = ftell(pf) - addr;
	if(len < datalen)
	{
		datalen = len;
	}

	fseek(pf,addr,SEEK_SET);
	fread(data,sizeof(uint8_t),datalen,pf);
	fclose(pf);
	
	return datalen;
}
