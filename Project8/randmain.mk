randlibhw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -shared -fPIC -o randlibsw.so
randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -shared -fPIC -o randlibhw.so
randmain: randcpuid.o randmain.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) -o randcpuid.o randmain.o randmain
