#ifndef FP12_H
#define FP12_H

#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "int256.h"
#include "int512.h"




typedef struct Fp12
{
	Fp6 x0;
	Fp6 x1;
	
}Fp12; // Fp12 = Fp6[w]/(w^2-v)

Fp12 Fp12_zero();

Fp12 Fp12_one();

int Fp12_equal(Fp12 a, Fp12 b);

Fp12 Fp12_add(Fp12 a,Fp12 b);

Fp12 Fp12_sub(Fp12 a,Fp12 b);

Fp12 Fp12_mul(Fp12 a,Fp12 b);

Fp12 Fp12_mul_by_scalar(Fp12 a, Fp alpha);

void print_Fp12(Fp12 a);

Fp12 Fp12_exp(Fp12 base, int256 exponent);

Fp12 Fp12_inv(Fp12 a);

Fp12 Fp12_div(Fp12 a,Fp12 b);

Fp12 Fp12_mul_by_Fp6(Fp12 a, Fp6 b);

Fp6 Fp12_to_Fp6(Fp12 a);

Fp12 Fp6_to_Fp12(Fp6 a);


Fp12 Fp12xFp_add(Fp12 a,Fp b);

#endif