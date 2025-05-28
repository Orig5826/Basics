RM:= del

CC:= g++

HEADER:= -I./Source/

CPPFLAGS:= -std=c++17 -Wall -Wextra -Werror -pedantic

exe:= main.exe
# 匹配所有 .cpp 文件，包括 Source 目录下的
src := $(wildcard *.cpp ./Source/*.cpp) 
# 将所有 .cpp 文件转换为 .o 文件
obj := $(src:.cpp=.o)

all: $(exe)

$(exe): $(obj)
	$(CC) -o $@ $^ $(HEADER)

%.o: %.cpp
	$(CC) -c $< -o $@ $(HEADER) $(CPPFLAGS)

clean:
	$(RM) $(obj) $(exe)
