
# all:
# 	gcc -o test.o -c test.c
# 	gcc -o main.o -c main.c

# 	gcc -o main main.o test.o
# clean:
# 	rm *.o main


all:
	gcc -o libtest.so test.c test2.c -fPIC -shared 
	gcc -o main.o -c main.c
	gcc -o main main.o -L. -ltest 
clean:
	rm *.so *.o main
