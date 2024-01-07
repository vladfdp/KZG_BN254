#include <stdint.h>
#include "int256.h"

#ifndef FP_H
#define FP_H

typedef struct Fp{
    int256 num;
}Fp;

Fp Fp_from_int(uint64_t n);

Fp Fp_zero();

Fp Fp_add(Fp a, Fp b);

Fp Fp_mul(Fp a, Fp b);

Fp Fp_sub(Fp a, Fp b);

Fp Fp_opp(Fp x);

Fp Fp_exp(Fp base, int256 exponent);

void print_Fp(Fp x);

#endif