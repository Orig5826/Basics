# linux下动态链接库的测试
`2019.04.25 by jianfeng`


### gcc简介
- gcc -o 目标文件 -c 待编译的C文件
    > 编译阶段，将源文件编译为*.o文件
- gcc -o 目标文件 *.o(多个也可)
    > 链接阶段，将*.o文件和其他目标文件和标准库文件链接，生成可执行文件
###  测试Makefile
> 代码简介：main.c中调用test.c生成的so文件
```
all:
	gcc -o libtest.so -c test.c -fPIC -shared

	gcc -o main.o -c main.c
	gcc -o main main.o -L. -ltest
clean:
	rm *.so main
```

- fPIC
    > 表示编译为位置独立的代码，不用此选项的话编译后的代码是位置相关的所以动态载入时是通过代码拷贝的方式来满足不同进程的需要，而不能达到真正代码段共享的目的。
- shared
    > 该选项指定生成动态连接库（让连接器生成T类型的导出符号表，有时候也生成弱连接W类型的导出符号），不用该标志外部程序无法连接。相当于一个可执行文件
- L.
    > 表示要连接的库在当前目录中
- ltest
    > 编译器查找动态连接库时有隐含的命名规则，即在给出的名字前面加上lib，后面加上.so来确定库的名称


### 注意事项
- 出现找不到我们自己的动态链接库
    ./main: error while loading shared libraries: libtest.so: cannot open shared object file: No such file or directory
    > 可以通过以下方式
    1. 命令行：export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
        > 将当前路径添加到 LD_LIBRARY_PATH 中，
    2. 命令行：source ./config
        > config这个是我自己写的bash脚本，本质上也是执行以上命令。但是当前多次执行，会多次添加当前路径到 LD_LIBRARY_PATH 中

    3. 也可以通过修改/etc/ld.so.conf文件来指定动态库的目录
    4. export重启后失效，则可以将 LD_LIBRARY_PATH 添加到 /etc/bashrc中。
