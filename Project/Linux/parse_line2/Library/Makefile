objs := parse_line.o

libc.a: $(objs)
	${AR} -r -o $@ $^
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f libc.a *.o

