# **C语言奇葩问题记录**
`2018.04.27 by jianfeng`

## **移位问题**
- << 右值是负数，或者右值大于左值的最大位数
	> VS2010中，在测试unsigned int类型时，出现过左移-1相当于右移1bit的情况。(似乎是偶尔发生?我也忘记了)但最好不要这样使用。移植到其他平台可能出错。MSDN如下解释。
	```
	[MSDN] The result is undefined if the right operand of a shift expression is negative or if the right operand is greater than or equal to the number of bits in the (promoted) left operand.
	```