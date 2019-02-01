
#include "typedef.h"
#include "alg_sm3.h"


//==============================================
//					函数声明
static void sm3_CF(u32 * Vin,u32 * msg_filled,u32 * Vout);



//==============================================
//					辅助用的函数
// 大小端切换
static void format_endian_oneself(u8 * result,u32 len,u8 size)
{
	u32 i = 0;
	u8 temp,j;
	for (i = 0; i < len/size ; i++)
	{
		for(j = 0; j < size/2; j ++)
		{
			temp = result[i*size + j];
			result[i*size + j] = result[i*size + size-1 - j];
			result[i*size + size-1 - j] = temp;
		}
	}
}
//判断是否为大端
static BOOL isBigEndian()
{
	u16 a = 0x0055;
	u8 b = ((u8*)&a)[0];
	if(b == 0x55)
	{
		return FALSE;
	}
	return TRUE;
}



// ------------------------------------------
//     4.1 初始值
// ------------------------------------------
static u32 s_uiIV[8] =
{
	0x7380166f,0x4914b2b9,0x172442d7,0xda8a0600,
	0xa96f30bc,0x163138aa,0xe38dee4d,0xb0fb0e4e
};

// ------------------------------------------
//     4.2 常量
// ------------------------------------------
static u32 sm3_getTj(u8 j)
{
	if(j >= 0 && j <= 15)
	{
		return 0x79cc4519;
	}
	else if(j >= 16 && j <= 63)
	{
		return 0x7a879d8a;
	}
	else
	{
		return 0;
	}
}

// ------------------------------------------
//     4.3 布尔函数
// ------------------------------------------
static u32 sm3_FFj(u8 j,u32 X,u32 Y,u32 Z)
{
	if(j >= 0 && j <= 15)
	{
		return X ^ Y ^ Z;
	}
	else if(j >= 16 && j <= 63)
	{
		return (X & Y)|(X & Z)|(Y & Z);
	}
	else
	{
		return 0;
	}
}
static u32 sm3_GGj(u8 j,u32 X,u32 Y,u32 Z)
{
	if(j >= 0 && j <= 15)
	{
		return X ^ Y ^ Z;
	}
	else if(j >= 16 && j <= 63)
	{
		return (X & Y)|((~X) & Z);
	}
	else
	{
		return 0;
	}
}

// ------------------------------------------
//      3.0 ring shift left (32 bit)
//随后会用到的循环左移函数
// ------------------------------------------
static u32 ROL(u32 X,u8 bit_cnt)
{
	u32 temp;
	bit_cnt %= 32;
	temp = X >> (32 - bit_cnt);
	temp |= X << bit_cnt;
	return temp;
}

// ------------------------------------------
//     4.4 置换函数
// ------------------------------------------
static u32 sm3_getP0(u32 X)
{
	return X ^ (ROL(X,9)) ^ (ROL(X,17));
}
static u32 sm3_getP1(u32 X)
{
	return X ^ (ROL(X,15)) ^ (ROL(X,23));
}

// ------------------------------------------
//     5.2 SM3 数据填充
// 根据SM3 规范总结的填充规则
// 0x80 + 0x00...0x00 + msg的bit长(8 Bytes)
// ------------------------------------------
u32 sm3_filling(u8 * msg,u32 len,u8 * msg_filled)
{
	u32 msg_fill_len = 0;
	u32 fill_zero_cnt = 0;
	u32 len_bit_cnt = 0;
	// 先计算出后续需要用到的数据长度(单位bit)
	len_bit_cnt = len<<3;
	//先将所有的数据复制到填充区
	memcpy(msg_filled+msg_fill_len,msg,len);
	msg_fill_len += len;
	// 获取余数
	len %= 64;

	// ------------------------------------------
	//     数据填充
	// ------------------------------------------
	msg_filled[msg_fill_len] = 0x80;
	msg_fill_len ++;

	fill_zero_cnt = 64 - len - 1 - 4;
	if(len >= 56)
	{
		fill_zero_cnt += 64;
	}
	memset(msg_filled+msg_fill_len,0,fill_zero_cnt);
	msg_fill_len += fill_zero_cnt;
	if(FALSE == isBigEndian())
	{
		format_endian_oneself((u8*)&len_bit_cnt,4,4);
	}
	memcpy(msg_filled+msg_fill_len,(u8*)&len_bit_cnt,4);
	msg_fill_len += 4;

	// ------------------------------------------
	//     
	// ------------------------------------------
	if(msg_fill_len % 64 == 0)
	{
		//目的是返回大端数据，方便后续sm3 hash运算直接调用
		if(FALSE == isBigEndian())
		{
			format_endian_oneself(msg_filled,msg_fill_len,4);
		}
		//返回填充好的数据长度
		return msg_fill_len;
	}
	else
	{
		return 0;
	}
}

// ------------------------------------------
//     5.3.1 迭代过程
// [计算SM3_Hash的外部接口]
// msg_filled 已经填充好的数据
// msg_len 单位是byte
// hash_result 输出的hash结果
// ------------------------------------------
void sm3_iteration(u32 * msg_filled,u32 msg_len,u32 * hash_result)
{
	u32 i = 0;
	u32 n = 0;
	u32 Vin[8];
	u32 Vout[8];	//32 Byte

	n = (msg_len << 3) / 512;
	memcpy(Vin,s_uiIV,32);
	for(i = 0; i < n; i++)
	{
		sm3_CF(Vin,msg_filled + 16*i,Vout);
		memcpy(Vin,Vout,32);
	}

	memcpy(hash_result,Vout,32);	//SM3 规范得到的是大端数据

	//根据平台，输出相应的大小端数据
	if(FALSE == isBigEndian())
	{
		format_endian_oneself((u8*)hash_result,32,4);
	}
}

// ------------------------------------------
//     5.3.2 消息扩展
// ------------------------------------------
typedef struct _SM3_W_Ext
{
	u32 Wa[68];
	u32 Wb[64];
}SM3_W_Ext;

static void sm3_extend(u32 * msg_filled,SM3_W_Ext * W_Ext)
{
	u32 j = 0;

	memcpy(W_Ext->Wa,msg_filled,64);
	for(j = 16; j <= 67; j++)
	{
		W_Ext->Wa[j] = sm3_getP1( (W_Ext->Wa[j-16] ^ W_Ext->Wa[j - 9] ^ \
			ROL(W_Ext->Wa[j-3],15)) ) ^ ROL(W_Ext->Wa[j-13],7) ^ W_Ext->Wa[j-6];
	}
	for(j = 0; j <= 63; j++)
	{
		W_Ext->Wb[j] = W_Ext->Wa[j] ^ W_Ext->Wa[j+4];
	}
}

// ------------------------------------------
//     5.3.3 压缩函数
// ------------------------------------------
static void sm3_CF(u32 * Vin,u32 * msg_filled,u32 * Vout)
{
	u32 j = 0;
	u32 A,B,C,D,E,F,G,H;	//字寄存器
	u32 SS1,SS2,TT1,TT2;	//中间变量
	SM3_W_Ext W_Ext;
	
	//为了方便计算
	u32 * pReg[8] = {&A,&B,&C,&D,&E,&F,&G,&H};
	for(j = 0; j < 8; j++)
	{
		*pReg[j] = Vin[j];
	}

	sm3_extend(msg_filled,&W_Ext);
	for(j = 0; j <= 63; j++)
	{
		SS1 = ROL((ROL(A,12) + E + ROL(sm3_getTj(j),j)), 7);
		SS2 = SS1 ^ ROL(A,12);
		TT1 = sm3_FFj(j,A,B,C) + D + SS2 + W_Ext.Wb[j];
		TT2 = sm3_GGj(j,E,F,G) + H + SS1 + W_Ext.Wa[j];
		D = C;
		C = ROL(B,9);
		B = A;
		A = TT1;
		H = G;
		G = ROL(F,19);
		F = E;
		E = sm3_getP0(TT2);
	}

	for(j = 0; j < 8; j++)
	{
		Vout[j] = (*pReg[j]) ^ Vin[j];
	}
}