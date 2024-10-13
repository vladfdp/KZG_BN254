#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"

#ifndef POLY_H
#define POLY_H

typedef struct Poly{
    Fr* coeffs;
    int degree;
}Poly;

Poly Poly_init(int degree);

Poly vanish_Poly(Fr x);

Fr Poly_eval(Poly poly, Fr x);

Poly euclidean_div_Poly(Poly f, Poly g);

void free_Poly(Poly poly);

void print_Poly(Poly poly);


#endif

#ifdef __cplusplus
}
#endif