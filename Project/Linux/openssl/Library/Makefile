objs := public.o
objs += sha_demo.o aes_demo.o ecc_demo.o des_demo.o rsa_demo.o hmac_demo.o

libc.a: $(objs)
	${AR} -r -o $@ $^
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -o $@  -c $< $(CLIBFLAGS)

clean:
	rm -f libc.a *.o

