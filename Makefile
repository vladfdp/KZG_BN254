main: main.o Fp.o int256.o int512.o
	gcc -o prog main.o Fp.o int256.o int512.o

test: test.o Fp.o int256.o int512.o
	gcc -o test test.o Fp.o int256.o int512.o
	./test

main.o: main.c
	gcc -c main.c
	

Fp.o: Fp.c
	gcc -c Fp.c 

int256.o: int256.c
	gcc -c int256.c 
int512.o: int512.c
	gcc -c int512.c 


clean:
	rm *.o