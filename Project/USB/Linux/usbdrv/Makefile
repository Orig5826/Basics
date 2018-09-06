
# 编译工具
CC	:= gcc
AR	:= ar

INCDIR	:= $(shell pwd)

# --C预处理器使用 flag是编译器可选择的选项
# 不使用标准库和标准头文件
HEADER	:= -I/usr/local/include/libusb-1.0
HEADER += -I$(INCDIR)/Library
HEADER	+= -I$(INCDIR)/Source

LIB	+= -L/usr/local/lib -lusb-1.0
# --C编译器的falg
# -Wall警告信息开      -O2优化程度2	-fno-buitin不用标准的，用自己的..
CFLAGS		:=  -Wall -O0

#导出这些变量到全局，给其对应的子文件makefile使用
export CC AR CFLAGS HEADER LIB

#
obj := Source/main.o
# 
obj += Library/usbdrv.a

# -----------------------------------------
# 				命令
# 最后注意：因为我封装的库usbdrv.a中调用了libusb
# 的库，因此再最终生成*.out文件时，也需要包含该库
# $(LIB)，否则会出现找不到函数的问题
# undefined reference to `libusb_init'
# ... ...
# -----------------------------------------
all: $(obj)
#	$(CC) -o main.out $^
	$(CC) -o main.out $^ $(LIB)
%.o : %.c
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $< $(LIB)

#  调用子文件下的makefile生成库
Library/usbdrv.a:
	cd Library; make; cd ..
clean:
	cd Source; rm *.o ; cd ..
	cd Library; make clean; cd ..
	rm *.out
