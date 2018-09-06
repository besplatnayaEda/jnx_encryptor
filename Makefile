all: jnx_enc.exe

jnx_enc.exe: jnx_enc.o
	 gcc -o jnx_enc.exe jnx_enc.o

jnx_enc.o: jnx_enc.c
	 gcc -c jnx_enc.c 
     
clean:
	 rm jnx_enc.o jnx_enc.exe