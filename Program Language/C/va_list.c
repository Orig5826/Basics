//----------------------------------------------------
//				print
//经过实验测试：
//print函数第一个参数和函数中的第一个局部变量，它们所在的
//栈地址，并非是连续的。
//进过百度查看资料，可能原因：
//1.返回地址
//2.为了处理异常而增加的信息
//3. ...
// 不同的平台，编译器等都可能会有所不同。这个可以先不管
// 有时间，再有针对性的去研究
//----------------------------------------------------
typedef char *va_list;

#define	 NATIVE_INT		 int
#define  _AUPBND         (sizeof (NATIVE_INT) - 1)		//sizeof(int)==4; 
#define  _ADNBND         (sizeof (NATIVE_INT) - 1)		//

#define _bnd(X, bnd)    (((sizeof (X)) + (bnd)) & (~(bnd)))		//
#define va_arg(ap, T)   (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)      (void) 0
#define va_start(ap, A) (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))

#define	OUTBUFSIZE	0x200
static char g_pcOutBuf[OUTBUFSIZE];

int strlen(char * src)
{
	int i = 0;
	while(*src != '\0')
	{
		src++;
		i++;
	}
	return i;
}
char* memcpy(char * des,char * src)
{
	while(*src != '\0')
	{
		*des = *src;
		src++;
		des++;
	}
	return des;
}

//-----------------------------------------------
// 百度查询之后：
// C语言支持变长形参，根本的原因是
// 形参压入栈的顺序是从右至左
// 
// 因此只要有了第一个形参的地址，那么其他形参不就都有了
// 当然，第一个参数需要包含形参总个数的相关信息
// 否则也是没辙的。
// 例如printf中，第一个参数中的%d,%x,%p等
//-----------------------------------------------
int print(int num ,...)
{
	int i;
	char * p = g_pcOutBuf;

	//------------------------------------
	// 0.原理：
	// typedef char *va_list;
	//------------------------------------
	va_list args;

	//------------------------------------
	// 1.原理：
	// args = (char *)((int)&num + sizeof(void *)); 
	//------------------------------------
	va_start(args, num);
	
	LED1_ON;
	for(i = 0; i < num; i++)
	{
		//--------------------------------------------
		// 此处主要是理解
		// 假设：int print(int num,char *str)
		// args在栈中，相当于是&str,即形参的地址
		// *(int *)args 的就相当于是str
		// 我举的例子，传来的形参是字符串(或说：char *)
		// 所以最终再将其强制转换为(char*)传给memcpy
		// ::注
		// 这里的memcpy是我自己写的用来调试，不是库函数
		//--------------------------------------------
		p = memcpy((char*)p,(char*)(*(int*)args));

		//--------------------------------------------
		// 2.原理：
		// args += sizeof(void *);	//指针占用字节长
		//--------------------------------------------
		va_arg(args,char*);
	}
	LED2_ON;

	//--------------------------------------------
	// 原理：
	// args = (va_list)0;		//将指针置为无效
	//--------------------------------------------
	va_end(args);

	
	for (i = 0; i < strlen(g_pcOutBuf); i++)
	{
		putc(g_pcOutBuf[i]);
	}
	return num;
}


//------------------------------------------------------------
//					上述函数的调用如下
print(5,"Hello ","world! ","I ","am ","Bruce!\r\n");