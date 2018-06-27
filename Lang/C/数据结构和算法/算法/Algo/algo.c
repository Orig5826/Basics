#include "algo.h"
#include <time.h>

#define NDEBUG

// ==================================== 测试 ====================================
static void Algo_Display(const int *data,int dataLen)
{
	int  i = 0;
	printf("-------------------- INT --------------------\n");
	for(i = 0;i < dataLen; i++)
	{
		if(i % 16 == 0 && i != 0)
		{
			printf("\n");
		}
		printf("%4d ",*(data + i));
	}
	printf("\n");
}

unsigned char Algo_Judge(int * pArray,int iLen,unsigned char mode)
{
	int i = 0;
	for(i = 1; i < iLen; i++)
	{
		if(mode == 0)
		{
			//按照从小到大的顺序排序
			if(pArray[i - 1] > pArray[i])
			{
				return 0;
			}
		}
		else
		{
			//按照从大到小的顺序排序
			if(pArray[i - 1] < pArray[i])
			{
				return 0;
			}
		}
	}
	return 1;
}

// ==================================== 排序算法实现 ====================================
//-----------------------(^_^)-------------------------
// 函数: Algo_SortInsert
// 时间: 2017/5/3__Original__15:46:53
// 功能：插入排序
// 参数: 
// 		int * pArray			数据
// 		int iLen				数据长度
// 		unsigned char mode		0.从小到大 !0.从大到小
// 返回: 
// 		void	
//-----------------------------------------------------
void Algo_SortInsert(int * pArray,int iLen,unsigned char mode)
{
	int i = 0,j = 0;
	int key = 0;
	for(i = 1; i < iLen;i ++)
	{
		key = pArray[i];
		j = i - 1;
		if(mode == 0)
		{
			while(j >= 0 && key < pArray[j])
			{
				pArray[j + 1] = pArray[j]; 
				j --;
			}
		}
		else
		{
			while(j >= 0 && key > pArray[j])
			{
				pArray[j + 1] = pArray[j]; 
				j --;
			}
		}
		pArray[j + 1] = key; 
	}
}


static void Algo_GetMemory(int ** p,int size)
{
	(*p) = (int *)malloc(sizeof(int) * size);
}

//-----------------------(^_^)-------------------------
// 函数: Algo_SoutMerge_0
// 时间: 2017/5/10__Original__11:53:24
// 功能：将两段有序数列重组为一组有序数列
// 参数: 
// 		int * pArray		
// 		int IndexLeftStart		左数列起始下标
// 		int IndexLeftEnd		左数列终止下标
// 		int IndexRightEnd		右数列终止下标（右数列起始下标为 IndexLeftEnd+1 ）
// 返回: 
// 		void	
//-----------------------------------------------------
static void Algo_SoutMerge_0(int * pArray,int IndexLeftStart,int IndexLeftEnd,int IndexRightEnd)
{
	int i = 0;
	int j = 0,k = 0;
	int LenLeft = IndexLeftEnd - IndexLeftStart + 1;		//左 数据个数
	int LenRight = IndexRightEnd - IndexLeftEnd;			//右 数据个数
	int * pArrayLeft = (int *)malloc(LenLeft * sizeof(int));
	int * pArrayRight = (int *)malloc(LenRight * sizeof(int));

#ifndef NDEBUG
	printf("Left = %d,Right = %d\n",LenLeft,LenRight);
#endif
	for(i = 0;i < LenLeft; i++)
	{
		pArrayLeft[i] = pArray[IndexLeftStart + i];
	}
	for(i = 0;i < LenRight; i++)
	{
		pArrayRight[i] = pArray[IndexLeftEnd + 1 + i];
	}

	// ------------------------------------------ 
	//	方法1.利用各自的长度作为检测判断
	// ------------------------------------------
	for(i = IndexLeftStart; i <= IndexRightEnd; i++)
	{
		if(j == LenLeft)
		{
			pArray[i] = pArrayRight[k];
			k ++;
		}
		else if(k == LenRight)
		{
			pArray[i] = pArrayLeft[j];
			j ++;
		}
		else
		{
			if(pArrayLeft[j] <= pArrayRight[k])
			{
				pArray[i] = pArrayLeft[j];
				j ++;
			}
			else
			{
				pArray[i] = pArrayRight[k];
				k ++;
			}
		}
	}
	// ------------------------------------------
	// 	方法2.可以在新建的两个数列的最后，各添加一个
	//  最大值，作为“哨兵”。则可以使代码略微简化。
	//  此处，不再细描述。
	// ------------------------------------------
}

//-----------------------(^_^)-------------------------
// 函数: Algo_SortMerge
// 时间: 2017/5/10__Original__11:57:03
// 功能：请仔细理解该处的递归
// 参数: 
// 		int * pArray		待排序数列
// 		int IndexStart		数列待排序起始下标
// 		int IndexEnd		数列待排序终止下标
// 返回: 
// 		void	
//-----------------------------------------------------
void Algo_SortMerge(int * pArray,int IndexStart,int IndexEnd)
{
	int index = 0;
	if(IndexStart < IndexEnd)
	{
		index = (IndexStart + IndexEnd)/2;
#ifndef NDEBUG
		printf("start = %d\tend = %d\n",IndexStart,IndexEnd);
#endif
		Algo_SortMerge(pArray,IndexStart,index);
		Algo_SortMerge(pArray,index + 1,IndexEnd);
		Algo_SoutMerge_0(pArray,IndexStart,index,IndexEnd);
	}
}


//-----------------------(^_^)-------------------------
// 函数: Algo_MaxHeap
// 时间: 2017/5/10__Original__17:51:07
// 功能：维护堆的性质（以最大堆为例）
// 参数: 
// 		int * pArray	数列	
// 		int index		下标
// 		int iLen		总长度（该数用于判断）
// 返回: 
// 		void	
//-----------------------------------------------------
// ------------------------------------------
// 				堆排序
// 此处宏定义，方便使用
// ------------------------------------------
#define LEFT(x)		((x) << 1)
#define RIGHT(x)	(((x) << 1) + 1)
static void Algo_MaxHeap(int * pArray,int index,int iLen)
{
	int indexleft = LEFT(index);
	int indexright = RIGHT(index);
	int indexlargest;

	// ------------------------------------------
	// 	三个数比较大小，得到最大值的下标
	// ------------------------------------------
	if((indexleft <= iLen) && (pArray[indexleft-1] > pArray[index-1]))
	{
		indexlargest = indexleft;
	}
	else
	{
		indexlargest = index;
	}

	if((indexright <= iLen) && (pArray[indexright-1] > pArray[indexlargest-1]))
	{
		indexlargest = indexright;
	}
	// ------------------------------------------
	// 			交换父节点和最大值
	// ------------------------------------------
	if(indexlargest != index)
	{
		int temp = 0;
		temp = pArray[index-1];
		pArray[index-1] = pArray[indexlargest-1];
		pArray[indexlargest-1] = temp;

		Algo_MaxHeap(pArray,indexlargest,iLen);
	}
}

//-----------------------(^_^)-------------------------
// 函数: Algo_BuiltMaxHeap
// 时间: 2017/5/11__Original__11:00:25
// 功能：建立（最大）堆，自底向上
// 参数: 
// 		int * pArray		
// 		int iLen		
// 返回: 
// 		void	
//-----------------------------------------------------
static void Algo_BuiltMaxHeap(int * pArray,int iLen)
{
	int i = iLen/2;
	for(; i >= 1; i--)
	{
		Algo_MaxHeap(pArray,i,iLen);
	}
}

//-----------------------(^_^)-------------------------
// 函数: Algo_SortHeap
// 时间: 2017/5/11__Original__11:31:03
// 功能：堆排序
// 参数: 
// 		int * pArray	待排序数据
// 		int iLen		待排序数据总长度
// 返回: 
// 		void	
//-----------------------------------------------------
void Algo_SortHeap(int * pArray,int iLen)
{
	int i = iLen,temp = 0;
	int heapsize = iLen;
	Algo_BuiltMaxHeap(pArray,iLen);
	for (i = iLen; i >= 2 ; i--)
	{
		// ------------------------------------------
		// 	每次都交换最大堆的根和最后一个元素
		//  相当于将最大值每次都交换到最后一个位置
		// ------------------------------------------
		temp = pArray[0];
		pArray[0] = pArray[i-1];
		pArray[i-1] = temp;

		// ------------------------------------------
		// 				重新维护最大堆的性质
		//  注意：此处堆中不再包含每次循环的最后一个值
		// ------------------------------------------
		heapsize--;
		Algo_MaxHeap(pArray,1,heapsize);

#ifndef NDEBUG
		printf("测试：%d\n",heapsize);
		Algo_Display(pArray,heapsize);
#endif
	}
}


//-----------------------(^_^)-------------------------
// 函数: Algo_Partition
// 时间: 2017/5/12__Original__11:51:48
// 功能：将数据重排，使得左侧的数据均<=pArray[IndexEnd],
//		右侧的数据，均>pArray[IndexEnd]
// 参数: 
// 		int * pArray		
// 		int IndexStart		
// 		int IndexEnd		
// 返回: 
// 		int	
//-----------------------------------------------------
static int Algo_Partition(int * pArray,int IndexStart,int IndexEnd)
{
	int maxData = pArray[IndexEnd];
	int i,temp;
	int index = IndexStart;
	for(i = IndexStart; i < IndexEnd; i ++)
	{
		if(pArray[i] <= maxData)
		{
			temp = pArray[index];
			pArray[index] = pArray[i];
			pArray[i] = temp;

			index++;
		}
	}
	temp = pArray[index];
	pArray[index] = pArray[IndexEnd];
	pArray[IndexEnd] = temp;
	return index;
}

static int Algo_RandPartition(int * pArray,int IndexStart,int IndexEnd)
{
	// ------------------------------------------
	// 		在原来快速排序基础上，增加一个随机
	// 技术，使得参考值的选取是等概率的
	// ------------------------------------------
	int temp;
	int index = (rand() % (IndexEnd - IndexStart + 1)) + IndexStart;
	temp = pArray[index];
	pArray[index] = pArray[IndexEnd];
	pArray[IndexEnd] = temp;

	return Algo_Partition(pArray,IndexStart,IndexEnd);
}

//-----------------------(^_^)-------------------------
// 函数: Algo_QuickSort
// 时间: 2017/5/12__Original__13:12:27
// 功能：快速排序算法，本质：分治思想
// 参数: 
// 		int * pArray		
// 		int IndexStart		
// 		int IndexEnd		
// 返回: 
// 		void	
//-----------------------------------------------------
void Algo_QuickSort(int * pArray,int IndexStart,int IndexEnd)
{
	int index = 0;
	srand((unsigned int)time(0));
	if(IndexStart < IndexEnd)
	{
		// ------------------------------------------
		// 			1.0 一般方式
		// ------------------------------------------
		//index = Algo_Partition(pArray,IndexStart,IndexEnd);
		// ------------------------------------------
		// 			1.1 在1.0基础上增加了随机技术
		// ------------------------------------------
		index = Algo_RandPartition(pArray,IndexStart,IndexEnd);

		Algo_QuickSort(pArray,IndexStart,index - 1);
		Algo_QuickSort(pArray,index + 1,IndexEnd);
	}
}



// ==================================== 测试 ====================================
void Algo_Test()
{
	int * pArray = NULL;
	int cnt = 0;
	int i = 0;
	time_t clk = 0;

	while(1)
	{
		//输入随机数长度
		printf("input the cnt:\t\n");
		if(1 != scanf("%d",&cnt))
		{
			break;
		}
		if(NULL == (pArray = (int *)malloc(cnt * sizeof(int))))
		{
			printf("malloc failed!");
			return;
		}
		//生成随机数
		srand((unsigned int)time(0));
		for(i = 0; i < cnt;i ++)
		{
			//*(pArray + i) = rand() % cnt;
			*(pArray + i) = rand() % 100;
		}

		// ------------------------------------------
		// 				1.显示排序前
		// ------------------------------------------
		Algo_Display(pArray,cnt);
		// ------------------------------------------
		// 				2.排序算法
		// ------------------------------------------
		clk = clock();
		//1.0 插入排序
//		Algo_SortInsert(pArray,cnt,0);
		//1.1 分治法排序
//		Algo_SortMerge(pArray,0,cnt - 1);
		//1.2 堆排序
//		Algo_SortHeap(pArray,cnt);
		//1.3 快速排序
		Algo_QuickSort(pArray,0,cnt-1);
		// ------------------------------------------
		// 				3.显示排序后
		// ------------------------------------------
		Algo_Display(pArray,cnt);

		// ------------------------------------------
		// 				4.判断排序是否成功
		// ------------------------------------------
		if(0 == Algo_Judge(pArray,cnt,0))
		{
			printf("排序失败！\n");
		}
		else
		{
			printf("排序成功！\n");
		}

		printf("time: %8dms\n",clock() - clk);
	}
}
