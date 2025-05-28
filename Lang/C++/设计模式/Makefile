ifeq ($(OS),Windows_NT)
RM := del /q /f /s
else
RM := rm -f
endif

# compiler
CC:= g++

# header
HEADER:= -I./Source/

# c++ flags
CPPFLAGS:= -std=c++17 
CPPFLAGS+= -g
CPPFLAGS+= -O2
CPPFLAGS+= -Wall
#CPPFLAGS+= -Wextra
#CPPFLAGS+= -Werror
#CPPFLAGS+= -pedantic

# target 
exe:= a.exe
src := $(wildcard *.cpp Source/*.cpp) 
obj := $(src:.cpp=.o)

.PHONY: all
all: $(exe)

$(exe): $(obj)
	$(CC) -o $@ $^ $(HEADER)

%.o: %.cpp
	$(CC) -c $< -o $@ $(HEADER) $(CPPFLAGS)

.PHONY: clean
clean:
	$(RM) *.o *.exe
