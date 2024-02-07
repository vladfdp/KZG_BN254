main: main.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o Poly.o Ec.o Pairing.o
	gcc -Wall -o prog main.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o Poly.o Ec.o Pairing.o

test: test.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o Poly.o EC.o KZG.o TwistedG2.o Pairing.o
	gcc -Wall -o test test.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o Poly.o EC.o KZG.o TwistedG2.o Pairing.o
	./test
	rm *.o
	rm test

setup: setup.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o Poly.o EC.o
	gcc -Wall -o setup setup.o Fp.o int256.o int512.o Fp2.o Fp6.o Fp12.o Fr.o Poly.o EC.o
	./setup
	rm setup

main.o: main.c 
	gcc -c main.c

Pairing.o: Pairing.c
	gcc -Wall -c Pairing.c
TwistedG2.o: TwistedG2.c
	gcc -Wall -c TwistedG2.c
KZG.o: KZG.c 
	gcc -Wall -c KZG.c
Fp.o: Fp.c
	gcc -Wall -c Fp.c 
Fr.o: Fr.c
	gcc -c Fr.c 
int256.o: int256.c
	gcc -c int256.c 
int512.o: int512.c
	gcc -c int512.c 
Fp2.o: Fp2.c
	gcc -Wall -c Fp2.c 
Fp6.o: Fp6.c
	gcc -Wall -c Fp6.c 
Fp12.o: Fp12.c
	gcc -Wall -c Fp12.c 
EC.o: EC.c 
	gcc -Wall -c EC.c 

Poly.o:
	gcc -Wall -c Poly.c

clean:
	rm *.o