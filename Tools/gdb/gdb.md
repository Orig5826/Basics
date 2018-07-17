# **gdb命令的使用笔记**
![apaki](../../apaki.jpg)
`2018.07.17 by jianfeng`
#### 知识来源：[孤剑之家的博客](https://www.cnblogs.com/AloneSword/p/3512797.html)

> 暂时可能有一些不是太会用，或者某些解释不对的。若后续用到，则再修改

- list
	- list(l)：列出源代码，接着上次的位置往下列，每次列10行
	- list 行号：列出产品从第几行开始的源代码
	- list 函数名：列出某个函数的源代码
- start：开始执行程序，停在main函数第一行语句前面等待命令
- next(n)：执行下一列语句
- step(s):执行下一行语句，如果有函数调用则进入到函数中
- breaktrace(或bt)：查看各级函数调用及参数
- frame(f) 帧编号：选择栈帧
- info（i) locals：查看当前栈帧局部变量的值
- finish：执行到当前函数返回，然后挺下来等待命令
- print(p)：打印表达式的值，通过表达式可以修改变量的值或者调用函数
```
	例如 p/a sum
	- 其中/a为显示格式的参数
	x 按十六进制格式显示变量。 
	d 按十进制格式显示变量。 
	u 按十六进制格式显示无符号整型。 
	o 按八进制格式显示变量。 
	t 按二进制格式显示变量。 
	a 按十六进制格式显示变量。 
	c 按字符格式显示变量。 
	f 按浮点数格式显示变量。
```
- set var：修改变量的值
- quit：退出gdb

### 断点
- break
	- break(b) 行号：在某一行设置断点
	- break 函数名：在某个函数开头设置断点
	- break...if...：设置条件断点
- continue(或c)：从当前位置开始连续而非单步执行程序
- delete 
	- delete breakpoints：删除所有断点
	- delete breakpoints n：删除序号为n的断点
- disable breakpoints：禁用断点
- enable breakpoints：启用断点
- info(或i) breakpoints：参看当前设置了哪些断点
- run(或r)：从开始连续而非单步执行程序
- display 变量名：跟踪查看一个变量，每次停下来都显示它的值
- undisplay：取消对先前设置的那些变量的跟踪

### watch
- watch：设置观察点
- info(或i) watchpoints：查看当前设置了哪些观察点