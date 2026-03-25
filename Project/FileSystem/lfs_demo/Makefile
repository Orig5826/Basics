
objs = file.o lfs_util.o lfs.o main.o

all: ${objs}
	gcc -o a.exe $^

%.o : %.c
	gcc -o $@ -c $<

clean:
	del *.exe
	del *.bin
