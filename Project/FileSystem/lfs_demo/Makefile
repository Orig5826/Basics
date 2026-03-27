
INCLUDES = -I.

objs = file.o lfs_util.o lfs.o main.o

all: ${objs}
	gcc -o a.exe $^ ${INCLUDES}

%.o : %.c
	gcc -o $@ -c $< ${INCLUDES}

clean:
	rm *.exe
	rm *.bin
	rm *.o
