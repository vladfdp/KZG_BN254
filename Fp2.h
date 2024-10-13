#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "int256.h"
#include "int512.h"

#ifndef FP2_H
#define FP2_H

typedef struct Fp2
{
	Fp x0;
	Fp x1;
	
}Fp2;  // Fp2 = Fp[u]/(u^2+1)

Fp2 Fp2_zero();

int Fp2_is_zero(Fp2 x);

Fp2 Fp2_one();

int Fp2_equal(Fp2 a, Fp2 b);

Fp2 Fp2_from_int(uint64_t a, uint64_t b);

Fp2 Fp2_mul_by_scalar(Fp2 x, Fp alpha);

Fp2 Fp2_add(Fp2 a,Fp2 b);

Fp2 Fp2_sub(Fp2 a,Fp2 b);

Fp2 Fp2_opp(Fp2 x);

Fp2 Fp2_mul(Fp2 a,Fp2 b);

Fp2 Fp2_exp(Fp2 base, int256 exponent);

Fp2 Fp2_frobenius(Fp2 x);

Fp2 Fp2_inv(Fp2 x);

Fp2 Fp2_div(Fp2 a, Fp2 b);

void print_Fp2(Fp2 a);

#endif

#ifdef __cplusplus
}
#endif