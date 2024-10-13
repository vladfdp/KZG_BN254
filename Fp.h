#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "int256.h"

#ifndef FP_H
#define FP_H

typedef struct Fp{
    int256 num;
}Fp;

const static int256 P = {0x30644e72e131a029,0xb85045b68181585d,0x97816a916871ca8d,0x3c208c16d87cfd47};


Fp Fp_from_int(uint64_t n);

Fp Fp_zero();

int Fp_is_zero(Fp x);

Fp Fp_one();

int Fp_equal(Fp a, Fp b);

Fp Fp_add(Fp a, Fp b);

Fp Fp_mul(Fp a, Fp b);

Fp Fp_mul_original(Fp a, Fp b);

Fp Fp_sub(Fp a, Fp b);

Fp Fp_opp(Fp x);

Fp Fp_exp(Fp base, int256 exponent);

void print_Fp(Fp x);

Fp Fp_inv(Fp x);

Fp Fp_div(Fp a,Fp b);

#endif

#ifdef __cplusplus
}
#endif