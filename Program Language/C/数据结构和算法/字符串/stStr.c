
#include "stStr.h"

// ------------------------------------------
// [2017/4/19/ Original 10:18:59] 
// 调试接口
// ------------------------------------------
#define DBG_LOG		printf
#define LOG(x)		printf("//");printf(x);printf("\n");


void StrCreate(pstStr pStr)
{
	pStr->strlen = -1;
}

int StrGetLen(const pstStr pStr)
{
	return pStr->strlen + 1;
}

void StrDisplay(pstStr pStr)
{
	int i = 0;
	if(0 == StrGetLen(pStr))
	{
		LOG("串空");
		return;
	}
	for(i = 0; i < StrGetLen(pStr); i++)
	{
		printf("%c",pStr->name[i]);
	}
}

void StrAppend(pstStr pStr,const char ch)
{
	if(StrGetLen(pStr) >= NAMESIZE)
	{
		LOG("超出范围");
		return;
	}
	pStr->name[++pStr->strlen] = ch;
}

void StrAppendStr(pstStr pStr,const char *str,int strlen)
{
	int i = 0;
	if(StrGetLen(pStr) + strlen >= NAMESIZE)
	{
		LOG("超出范围");
		return;
	}
	for(i = 0; i < strlen; i ++)
	{
		StrAppend(pStr,str[i]);
	}
}

//-----------------------(^_^)-------------------------
// 函数: AppendStr2
// 时间: 2017/4/19__Original__9:57:17
// 功能：把串2追加到串1上
// 参数: 
// 		pstStr pStr		
// 		pstStr pStr2		
// 返回: 
// 		void	
//-----------------------------------------------------
void StrAppendStr2(pstStr pStr,const pstStr pStr2)
{
	int i = 0;
	if(StrGetLen(pStr) + StrGetLen(pStr2) >= NAMESIZE)
	{
		LOG("超出范围");
		return;
	}
	for(i = 0; i < StrGetLen(pStr2); i ++)
	{
		StrAppend(pStr,pStr2->name[i]);
	}
}

//-----------------------(^_^)-------------------------
// 函数: StrCmp
// 时间: 2017/4/19__Original__10:14:59
// 功能：串比较
// 参数: 
// 		pstStr pStr		
// 		pstStr pStr2		
// 返回: 
// 		unsigned char	0.相等 1.pStr大 -1.pStr小
//-----------------------------------------------------
unsigned char StrCmp(pstStr pStr,pstStr pStr2)
{
	int i = 0;
	int len = StrGetLen(pStr) - StrGetLen(pStr2);
	for(i = 0; i < len; i ++)
	{
		if(pStr->name[i] > pStr2->name[i])
		{
			return 1;
		}
		else if (pStr->name[i] < pStr2->name[i])
		{
			return -1;
		}
		else
		{
		}
	}
	//若前面都相同
	//则最后根据长度确认大小
	if(len == 0)
	{
		return 0;
	}
	else if (len < 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

//-----------------------(^_^)-------------------------
// 函数: StrSub
// 时间: 2017/4/19__Original__10:26:39
// 功能：返回其子串
// 参数: 
// 		pstStr pStr		
// 		int index		
// 		int sublen		
// 返回: 
// 		stStr	
//-----------------------------------------------------
stStr StrSub(pstStr pStr,int index,int sublen)
{
	int i = 0;
	static stStr	str;
	StrCreate(&str);
	if(index + sublen > StrGetLen(pStr))
	{
		LOG("Error");
		return str;
	}
	for (i = 0; i < sublen ; i++)
	{
		StrAppend(&str,pStr->name[index + i]);
	}
	return str;
}
//-----------------------(^_^)-------------------------
// 函数: StrInsert
// 时间: 2017/4/19__Original__11:07:37
// 功能：插入：：先从最后搬移，然后插入
// 参数: 
// 		pstStr pStr		
// 		int index		
// 		const char * str		
// 		int strlen		
// 返回: 
// 		void	
//-----------------------------------------------------
void StrInsert(pstStr pStr,int index,const char * str,int strlen)
{
	int i = 0;
	if(StrGetLen(pStr) + strlen >= NAMESIZE)
	{
		LOG("超出范围");
		return;
	}
	//移动
	if(StrGetLen(pStr) != 0)
	{
		for(i = StrGetLen(pStr) - 1; i >= index; i --)
		{
			pStr->name[i + strlen] = pStr->name[i]; 
		}
	}
	//插入
	for(i = 0; i < strlen; i ++)
	{
		pStr->name[index + i] = str[i];
		pStr->strlen ++;
	}
}

//-----------------------(^_^)-------------------------
// 函数: StrInsert2
// 时间: 2017/4/19__Original__11:08:18
// 功能：串2插入到串pStr中
// 参数: 
// 		pstStr pStr		
// 		int index		
// 		const pstStr pStr2		
// 返回: 
// 		void	
//-----------------------------------------------------
void StrInsert2(pstStr pStr,int index,const pstStr pStr2)
{
	int i = 0;
	if(StrGetLen(pStr) + StrGetLen(pStr2) >= NAMESIZE)
	{
		LOG("超出范围");
		return;
	}
	//移动
	if(StrGetLen(pStr) != 0)
	{
		for(i = StrGetLen(pStr) - 1; i >= index; i --)
		{
			pStr->name[i + StrGetLen(pStr2)] = pStr->name[i]; 
		}
	}
	//插入
	for(i = 0; i < StrGetLen(pStr2); i ++)
	{
		pStr->name[index + i] = pStr2->name[i];
		pStr->strlen ++;
	}
}

//-----------------------(^_^)-------------------------
// 函数: StrDelete
// 时间: 2017/4/19__Original__11:20:25
// 功能：从pStr指定偏移中删除指定长度的串
// 参数: 
// 		pstStr pStr		
// 		int index		
// 		int strlen		
// 返回: 
// 		void	
//-----------------------------------------------------
void StrDelete(pstStr pStr,int index,int strlen)
{
	int i = 0;
	if(strlen >= NAMESIZE)
	{
		LOG("超出范围");
		return;
	}
	if(StrGetLen(pStr) != 0)
	{
		for(i = 0; i < StrGetLen(pStr) - strlen; i ++)
		{
			pStr->name[index + i] = pStr->name[index + i + strlen]; 
		}
		pStr->strlen -= strlen;
	}
	else
	{
		LOG("串空");
	}
}



// ==================================== 用于子串查找 ====================================
//-----------------------(^_^)-------------------------
// 函数: StrMakeNext
// 时间: 2017/4/20__Original__14:01:33
// 功能：计算部分匹配值——kmp算法核心1
// 参数: 
// 		const char P[]		待查找的子串
// 		int next[]			next值
// 返回: 
// 		void	
//-----------------------------------------------------
static void StrMakeNext(const char P[],int strlen,int next[])
{
	int q,k;            //q:模版字符串下标；k:最大前后缀长度
	//int m = strlen(P);  //模版字符串长度
	int m = strlen;
	next[0] = 0;        //模版字符串的第一个字符的最大前后缀长度为0
	for (q = 1,k = 0; q < m; ++q)       //for循环，从第二个字符开始，依次计算每一个字符对应的next值
	{
		while(k > 0 && P[q] != P[k])    //递归的求出P[0]···P[q]的最大的相同的前后缀长度k
		{
			k = next[k-1];          	//这个while循环是整段代码的精髓所在，需要好好理解
		}

		if (P[q] == P[k])               //如果相等，那么最大相同前后缀长度加1
		{
			k++;
		}
		next[q] = k;
	}
}

//-----------------------(^_^)-------------------------
// 函数: StrFindSub
// 时间: 2017/4/20__Original__14:13:57
// 功能：KMP算法
// 参数: 
// 		const pstStr pStr		
// 		const pstStr pSubStr		
// 返回: 
// 		int	
//-----------------------------------------------------
int StrFindSub(const pstStr pStr,const pstStr pSubStr)
{
#define ORIG_DEBUG
#ifdef ORIG_DEBUG
	static int dbg_shift_cnt = 0;
	static int dbg_cmp_cnt = 0;
#endif
	int i = 0,j = 0;
	unsigned char cmpFlag = 0;
	//存放next数组
	int next[NAMESIZE] = {0};

	if(StrGetLen(pSubStr) > StrGetLen(pStr))
	{
		LOG("无");
		return -1;
	}

	//核心点1
	StrMakeNext(pSubStr->name,StrGetLen(pSubStr),next);

#ifdef ORIG_DEBUG
	printf("部分匹配值:\n");
	for(i = 0; i < StrGetLen(pSubStr);i++)
	{
		printf("%4d",next[i]);
	}
	printf("\n");
#endif

	// ------------------------------------------
	// 				一般的查找方法
	// ------------------------------------------
	for (i = 0; i <= StrGetLen(pStr) - StrGetLen(pSubStr) ; i++)
	{
		cmpFlag = 1;
#ifdef ORIG_DEBUG
		dbg_shift_cnt++;
#endif
		for (j = 0; j < StrGetLen(pSubStr) ; j++)
		{
#ifdef ORIG_DEBUG
			dbg_cmp_cnt++;
#endif
			if(pSubStr->name[j] != pStr->name[i + j])
			{
				cmpFlag = 0;
				break;
			}
		}

		if(1 == cmpFlag)
		{
#ifdef ORIG_DEBUG
			printf("移动的次数为：%d",dbg_shift_cnt);
			printf("\n");
			printf("比较的次数为: %d",dbg_cmp_cnt);
			printf("\n");
#endif
			return i;
		}
		else
		{
			//核心点2
			//移动位数 = 已匹配的字符数 - 对应的部分匹配值
			if(j != 0)
			{
				i += j - next[j];
			}
		}
	}
#ifdef ORIG_DEBUG
	printf("移动的次数为：%d",dbg_shift_cnt);
	printf("\n");
	printf("比较的次数为: %d",dbg_cmp_cnt);
	printf("\n");
#endif
	return -1;
}

//-----------------------(^_^)-------------------------
// 函数: StrFindSub
// 时间: 2017/4/20__Original__14:02:48
// 功能：一般的查找子串方法
// 参数: 
// 		const pstStr pStr		
// 		const pstStr pSubStr		
// 返回: 
// 		int	
//-----------------------------------------------------
int StrFindSub1(const pstStr pStr,const pstStr pSubStr)
{
#define ORIG_DEBUG
#ifdef ORIG_DEBUG
	static int dbg_shift_cnt = 0;
	static int dbg_cmp_cnt = 0;
#endif
	int i = 0,j = 0;
	unsigned char cmpFlag = 0;
	if(StrGetLen(pSubStr) > StrGetLen(pStr))
	{
		LOG("无");
		return -1;
	}

	// ------------------------------------------
	// 				一般的查找方法
	// ------------------------------------------
	for (i = 0; i <= StrGetLen(pStr) - StrGetLen(pSubStr) ; i++)
	{
		cmpFlag = 1;
#ifdef ORIG_DEBUG
		dbg_shift_cnt++;
#endif
		for (j = 0; j < StrGetLen(pSubStr) ; j++)
		{
#ifdef ORIG_DEBUG
			dbg_cmp_cnt++;
#endif
			if(pSubStr->name[j] != pStr->name[i + j])
			{
				cmpFlag = 0;
				break;
			}
		}

		if(cmpFlag == 1)
		{
#ifdef ORIG_DEBUG
			printf("移动的次数为：%d",dbg_shift_cnt);
			printf("\n");
			printf("比较的次数为: %d",dbg_cmp_cnt);
			printf("\n");
#endif
			return i;
		}
	}
#ifdef ORIG_DEBUG
	printf("移动的次数为：%d",dbg_shift_cnt);
	printf("\n");
	printf("比较的次数为: %d",dbg_cmp_cnt);
	printf("\n");
#endif
	return -1;
}


// ==================================== Str测试 ====================================
void StrTest()
{
	int i = 0;
	const char name[] = "Hello world!";
	const char name2[] = "Let it go!";
	stStr str;
	stStr str2;

	StrCreate(&str);
	StrCreate(&str2);
	//Display(&str);
	//测试1
	for(i = 0; i < sizeof(name); i++)
	{
		StrAppend(&str,name[i]);
	}
	StrDisplay(&str);
	LOG("1.str");
	//测试2

	StrAppendStr(&str2,name,sizeof(name));
	StrDisplay(&str2);
	LOG("2.str2");

	//对比
	if(0 == StrCmp(&str,&str2))
	{
		LOG("相等");
	}
	else if(1 == StrCmp(&str,&str2))
	{
		LOG("str 大");
	}
	else
	{
		LOG("str2 大");
	}

	//test3
	StrAppendStr2(&str,&str2);
	StrDisplay(&str);
	LOG("3.str");

	//对比
	if(0 == StrCmp(&str,&str2))
	{
		LOG("相等");
	}
	else if(1 == StrCmp(&str,&str2))
	{
		LOG("str 大");
	}
	else
	{
		LOG("str2 大");
	}

	str2 = StrSub(&str,4,12);
	StrDisplay(&str2);
	LOG("4.str2");

	StrInsert(&str,6,name2,sizeof(name2));
	StrDisplay(&str);
	LOG("5.str");

	StrInsert2(&str,0,&str2);
	StrDisplay(&str);
	LOG("6.str");

	StrDelete(&str,5,12);
	StrDisplay(&str);
	LOG("7.str");
}

void StrTest2()
{
	//专门测试一下，字符串子串查找函数
	const char name[] = "0000000000000000000000000000001";
	const char name2[] = "000001";

	//const char name[] = "ababxbababcadfdsss";
	//const char name2[] = "abcdabd";

	stStr str,str2;
	StrCreate(&str);
	StrCreate(&str2);
	StrAppendStr(&str,name,sizeof(name) - 1);
	StrAppendStr(&str2,name2,sizeof(name2) - 1);

	//
	printf("------------------------\n");
	printf("KMP 算法 \n");
	if(-1 != StrFindSub(&str,&str2))
	{
		LOG("存在该子串！");
	}
	else
	{
		LOG("不存在该子串");
	}

	printf("------------------------\n");
	printf("一般查找算法 \n");
	if(-1 != StrFindSub1(&str,&str2))
	{
		LOG("存在该子串！");
	}
	else
	{
		LOG("不存在该子串");
	}
}