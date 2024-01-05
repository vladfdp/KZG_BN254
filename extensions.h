#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "int256.h"
#include "int512.h"

typedef struct Fp2 Fp2;
struct Fp2
{
	Fp x;
	Fp y;
};

Fp2 Fp2_add(Fp2 a,Fp2 b);

Fp2 Fp2_sub(Fp2 a,Fp2 b);

Fp2 Fp2_mul(Fp2 a,Fp2 b); 

typedef struct Fp6 Fp6;
struct Fp6
{
	Fp2 x;
	Fp2 y;
	Fp2 z;
};

Fp6 Fp6_add(Fp6 a,Fp6 b);

Fp6 Fp6_sub(Fp6 a,Fp6 b);

Fp6 Fp6_mul(Fp6 a,Fp6 b,Fp6 c);

typedef struct Fp12 Fp12;
struct Fp12
{
	Fp6 x;
	Fp6 y;
};

Fp12 Fp12_add(Fp12 a,Fp12 b);

Fp12 Fp12_sub(Fp12 a,Fp12 b);

Fp12 Fp12_mul(Fp12 a,Fp12 b);
