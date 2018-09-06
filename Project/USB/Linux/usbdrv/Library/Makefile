objs := usbdrv.o

usbdrv.a: $(objs)
	${AR} -r -o $@ $^
	
%.o:%.c
	${CC} $(CFLAGS) $(HEADER) -o $@ -c $< $(LIB) 

clean:
	rm -f usbdrv.a *.o
