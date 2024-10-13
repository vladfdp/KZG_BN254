#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "int256.h"
#include "int512.h"

#ifndef FP6_H
#define FP6_H


typedef struct Fp6
{
	Fp2 x0;
	Fp2 x1;
	Fp2 x2;
	
}Fp6; // Fp6 = Fp2[v]/(v^3-(9+u))

Fp6 Fp6_zero();

int Fp6_is_zero(Fp6 x);

Fp6 Fp6_one();

int Fp6_equal(Fp6 a, Fp6 b);

Fp6 Fp6_add(Fp6 a,Fp6 b);

Fp6 Fp6xFp_add(Fp6 a, Fp b);

Fp6 Fp6_sub(Fp6 a,Fp6 b);

Fp6 Fp6_opp(Fp6 x);

Fp6 Fp6_mul(Fp6 a,Fp6 b);

Fp6 Fp6_mul_by_scalar(Fp6 x, Fp alpha);

Fp6 Fp6_mul_by_Fp2(Fp6 a, Fp2 b);

Fp6 Fp6_inv(Fp6 x);

void print_Fp6(Fp6 a);

Fp6 Fp6_frobenius(Fp6 x);

Fp6 Fp6_exp(Fp6 base, int256 exponent);

#endif

#ifdef __cplusplus
}
#endif