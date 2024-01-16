main: main.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o
	gcc -o prog main.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o

test: test.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o
	gcc -o test test.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o
	./test

main.o: main.c 
	gcc -c main.c 


Fp.o: Fp.c
	gcc -c Fp.c 
Fr.o: Fr.c
	gcc -c Fr.c 
int256.o: int256.c
	gcc -c int256.c 
int512.o: int512.c
	gcc -c int512.c 
Fp2.o: Fp2.c
	gcc -c Fp2.c 
Fp6.o: Fp6.c
	gcc -c Fp6.c 
Fp12.o: Fp12.c
	gcc -c Fp12.c 


clean:
	rm *.o