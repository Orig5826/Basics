
#include "alg_demo.h"
#include <stdio.h>

// ------------------------------------------
// 1. 3字节数据
// 2. 64字节数据
// 3. 56字节数据
// 4. 任意长度数据测试(本次以113为例子)
// ------------------------------------------
#define SM3_TEST_MODE	1

void display(u8 * data,u32 len)
{
	u32 i = 0;
	for(i = 0; i < len; i++)
	{
		if(i != 0 && i % 16 == 0)
		{
			printf("\r\n");
		}
		printf("%02X ",*(data+i));
	}
	printf("\r\n");
}

void alg_sm3_demo(void)
{
#if SM3_TEST_MODE == 1
	// ------------------------------------------
	// 测试数据：参见msg
	// 最终得到的SM3 Hash应该为
	// 66C7F0F4 62EEEDD9 D1F2D46B DC10E4E2 4167C487 5CF2F7A2 297DA02B 8F4BA8E0  
	// ------------------------------------------
	u8 msg[3] = {0x61,0x62,0x63};
	// 用于填充函数自动填充的缓存
	u8 msg_filled[64] = {0};
	// SM3 手动填充好的数据
	u32 msg_filling[16] = {
		0x61626380,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
		0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000018
	};
#elif SM3_TEST_MODE == 2
	// ------------------------------------------
	// 测试数据：参见msg
	// 最终得到的SM3 Hash应该为
	// DEBE9FF9 2275B8A1 38604889 C18E5A4D 6FDB70E5 387E5765 293DCBA3 9C0C5732 
	// ------------------------------------------
	u8 msg[64] = {
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,};
	// 用于填充函数自动填充的缓存
	u8 msg_filled[128] = {0};
	// SM3 手动填充好的数据
	u32 msg_filling[32] = {
		0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,
		0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,
		0x80000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
		0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000200,
	};
#elif SM3_TEST_MODE == 3
	// ------------------------------------------
	// 测试数据：参见msg
	// 最终得到的SM3 Hash应该为
	// 9A032F0C F27E4B40 8F252452 D451CAC5 1A422D43 AE73AB6C D7EC2483 241358E9
	// ------------------------------------------
	u8 msg[56] = {
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
		0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64};
	// 用于填充函数自动填充的缓存
	u8 msg_filled[128] = {0};
	// SM3 手动填充好的数据
	u32 msg_filling[32] = {
		0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,
		0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x61626364,0x80000000,0x00000000,
		0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
		0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x000001C0,
	};
#elif SM3_TEST_MODE == 4
	// ------------------------------------------
	// 测试数据：参见msg
	// 最终得到的SM3 Hash应该为
	// 2C828958 C3F34A25 87DF239F 258F52B3 ECB599F6 7E96A406 4DA2D4FA 1A955F2C
	// ------------------------------------------
	u8 msg[113] = {
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
		0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
		0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
		0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
		0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
		0x70};
	// 用于填充函数自动填充的缓存
	u8 msg_filled[128] = {0};
	// SM3 手动填充好的数据
	u32 msg_filling[32] = {
		0x00010203,0x04050607,0x08090a0b,0x0c0d0e0f,0x10111213,0x14151617,0x18191a1b,0x1c1d1e1f,
		0x20212223,0x24252627,0x28292a2b,0x2c2d2e2f,0x30313233,0x34353637,0x38393a3b,0x3c3d3e3f,
		0x40414243,0x44454647,0x48494a4b,0x4c4d4e4f,0x50515253,0x54555657,0x58595a5b,0x5c5d5e5f,
		0x60616263,0x64656667,0x68696a6b,0x6c6d6e6f,0x70800000,0x00000000,0x00000000,0x00000388,
	};
#endif

	u32 result[8] = {0};	//32 Byte Hash Data
	u32 msg_f_len = 0;

	// ------------------------------------------
	// 1.0 直接使用外部填充好的数据，进行SM3 Hash
	//     运算
	SM3_Hash(msg_filling,sizeof(msg_filling),result);
	printf(" 手动填充得到的SM3 Hash结果：\r\n");
	display((u8*)result,32);

	// ------------------------------------------
	// 2.0 使用未填充的数据,填充好的数据为大端，
	//     方便SM3 Hash函数直接调用
	msg_f_len = sm3_filling(msg,sizeof(msg),msg_filled);
	if(msg_f_len != 0)
	{
		SM3_Hash((u32*)msg_filled,msg_f_len,result);
		printf("自动填充得到的SM3 Hash结果：\r\n");
		display((u8*)result,32);
	}

	while(1)
	{
		;
	}
}