<<<<<<< HEAD
main: main.o Fp.o int256.o int512.o extensions.o
	gcc -o prog main.o Fp.o int256.o int512.o extensions.o 

test: test.o Fp.o int256.o int512.o extensions.o
	gcc -o test test.o Fp.o int256.o int512.o extensions.o
	./test

main.o: main.c 
	gcc -c main.c 
=======
main: main.o Fp.o int256.o int512.o
	gcc -o prog main.o Fp.o int256.o int512.o

test: test.o Fp.o int256.o int512.o
	gcc -o test test.o Fp.o int256.o int512.o
	./test

main.o: main.c
	gcc -c main.c
>>>>>>> 191d2d14b6cf22fab1d3816414560341338d8e27
	

Fp.o: Fp.c
	gcc -c Fp.c 
<<<<<<< HEAD
int256.o: int256.c
	gcc -c int256.c 
int512.o: int512.c
	gcc -c int256.c 

extensions.o: extensions.c
	gcc -c extensions.c
=======

int256.o: int256.c
	gcc -c int256.c 
int512.o: int512.c
	gcc -c int512.c 
>>>>>>> 191d2d14b6cf22fab1d3816414560341338d8e27


clean:
	rm *.o