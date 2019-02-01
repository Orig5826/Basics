
#ifndef _ALG_SM3_H_
#define _ALG_SM3_H_

// 用来支持函数：
// memcpy
#include <string.h>



//	计算SM3 Hash
void sm3_iteration(u32 * msg_filled,u32 msg_len,u32 * hash_result);
#define SM3_Hash	sm3_iteration
//	SM3 数据填充
u32 sm3_filling(u8 * msg,u32 len,u8 * msg_filled);



#endif
