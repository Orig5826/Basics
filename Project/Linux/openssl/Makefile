
# 编译工具
CC	:= gcc
AR	:= ar

INCDIR	:= $(shell pwd)

# --C预处理器使用 flag是编译器可选择的选项
# 不使用标准库和标准头文件
CPPFLAGS	:= -I$(INCDIR)/Source -I$(INCDIR)/Library
# --C编译器的falg
# -Wall警告信息开      -O2优化程度2	-fno-buitin不用标准的，用自己的..
CFLAGS		:=  -Wall -O0 -g
# LIB
CLIBFLAGS	:= -lcrypto

#导出这些变量到全局，给其对应的子文件makefile使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS CLIBFLAGS


#
obj := Source/main.o
# 
obj += Library/libc.a


# -----------------------------------------
# 				命令
# -----------------------------------------
all: $(obj)
	$(CC) -o main.out $^ $(CLIBFLAGS)

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c $(CLIBFLAGS)

#  调用子文件下的makefile生成库
Library/libc.a:
	cd Library; make; cd ..
clean:
	cd Library; make clean; cd ..
	cd Source ; rm *.o ; cd ..
	rm -f *.out
