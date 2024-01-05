main: main.o Fp.o int256.o int512.o
	gcc -o prog main.o Fp.o int256.o int512.o -L/opt/homebrew/lib -lgmp

test: test.o Fp.o int256.o int512.o
	gcc -o test test.o Fp.o int256.o int512.o -L/opt/homebrew/lib -lgmp
	./test

main.o: main.c
	gcc -c main.c -I/opt/homebrew/include
	

Fp.o: Fp.c
	gcc -c Fp.c -I/opt/homebrew/include

int256.o: int256.c
	gcc -c int256.c -I/opt/homebrew/include
int256.o: int512.c
	gcc -c int256.c -I/opt/homebrew/include


clean:
	rm *.o