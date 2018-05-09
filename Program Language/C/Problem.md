# **C语言奇葩问题记录**
`2018.04.27 by jianfeng`

## **移位问题**
- << 右值是负数，或者右值大于左值的最大位数
	> VS2010中，在测试unsigned int类型时，出现过左移-1相当于右移1bit的情况。(似乎是偶尔发生?我也忘记了)但最好不要这样使用。移植到其他平台可能出错。MSDN如下解释。
	```
	[MSDN] The result is undefined if the right operand of a shift expression is negative or if the right operand is greater than or equal to the number of bits in the (promoted) left operand.
	```

## **C语言中的默认类型转换**
- 运算和比较中的默认类型转换
	1. 例如：
		```
		short a = 0;
		unsigned char b = 0;
		a = a + (b - 15) * 2;
		```
	
		- 运算的结果，和我们想象中是一样的，b-15会得到一个负数，然后参与运算
		> 若b = b - 15 这种情况，则b永远都是一个正数。
		> 
		> 与此类似的有，b--，--b，b++，++b。这个递减/增的操作，通常在for等循环中出现，这种情况下，就需要考虑该变量是有符号还是没有符号，需要重点考虑一些边界等问题。


	2. 例如：
		```
		unsigned int a = 0;
		int b = 0;
		if(b - 15 > a)
		{
			printf("QQQ");
		}
		else
		{
			printf("HHH");
		}
		```
		- 结果输出为：QQQ
		> 为什么呢？因为当同一个等级出现有符号和无符号进行对比的时候，就直接切换为无符号进行对比了。若想要你原本想要的结果，则可以：
		```
		if(b - 15 > (int)a)
		{
			printf("QQQ");
		}
		else
		{
			printf("HHH");
		}
		```
