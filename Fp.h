#include <stdint.h>
#include "int256.h"

#ifndef FP_H
#define FP_H

typedef struct Fp{
    int256 num;
}Fp;

Fp Fp_add(Fp a, Fp b);

void print_Fp(Fp x);

#endif