# 仅仅用来创建目标文件的存放路径
DIR_OBJ = Obj
CMD_MKOBJDIR = if [ -d ${DIR_OBJ} ]; then exit 0; else mkdir ${DIR_OBJ}; fi

# 源码路径
SRC_PATH = Source
LIB_PATH = Library

# 头文件路径
INCDIR	:= $(shell pwd)
CPPFLAGS := -I$(INCDIR)/$(SRC_PATH)  -I$(INCDIR)/$(LIB_PATH)


obj := $(DIR_OBJ)/parse_line.o $(DIR_OBJ)/main.o
main: $(obj)
	@echo "  0.生成可执行文件"
	gcc $(CPPFLAGS) -o main.out $^

$(DIR_OBJ)/%.o : $(LIB_PATH)/%.c
	@echo "  1.编译Library中的c文件"
	@${CMD_MKOBJDIR}
	gcc $(CPPFLAGS) -o $@ -c $^

$(DIR_OBJ)/%.o : $(SRC_PATH)/%.c
	@echo "  2.编译Source中的c文件"
	@${CMD_MKOBJDIR}
	gcc $(CPPFLAGS) -o $@ -c $^

clean:
	@if [ -d $(DIR_OBJ) ]; then rm -r $(DIR_OBJ); fi 
	@if [ -e *.out ]; then rm *.out; fi
	@echo "clean finished!"