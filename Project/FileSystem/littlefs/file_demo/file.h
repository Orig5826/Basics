/**
 * @file file.h
 * @author wenjf (wenjf@hongsi-ic.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _flash_H_
#define _flash_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>


typedef enum _bool
{
	false = 0,
	true = !false,
}bool;


bool file_write(const char * file_name,uint32_t addr,uint8_t *data,uint32_t len);
uint32_t file_read(const char* file_name, uint32_t addr, uint8_t* data, uint32_t len);

#endif
