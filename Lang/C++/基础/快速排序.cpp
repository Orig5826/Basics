/***********************
	快速排序法的原理
	现在我还不是很懂
***********************/

#include<iostream>
using namespace std;

void wen_sort(int array[],int n,int low,int high)
{
	int i,j,t;
	if(low<high)
	{
		i=low;
		j=high;
		t=array[low];
		while(i<j)
		{
			while(i<j && array[j]>t)
			{
				j--;
			}
			if(i<j)
			{
				array[i]=array[j];
				i++;
			}
			while(i<j && array[i]<=t)
			{
				i++;
			}
			if(i<j)
			{
				array[j]=array[i];
				j--;
			}
		}
		array[i]=t;
		wen_sort(array,n,low,i-1);
		wen_sort(array,n,i+1,high);
	}
}
int main()
{
	int i;
	int a[]={1,4,2,3,5};
	cout<<"原来："<<endl;
	for(i=0;i<5;i++)
	{
		cout<<a[i]<<",";
	}
	wen_sort(a,5,0,4);
	cout<<endl;
	cout<<"之后："<<endl;
	for(i=0;i<5;i++)
	{
		cout<<a[i]<<",";
	}
	return 0;
}
