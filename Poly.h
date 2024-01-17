#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"

#ifndef POLY_H
#define POLY_H

typedef struct Poly{
    Fr* coeffs;
    int degree;
}Poly;

Poly Poly_init(unsigned int degree);

Fr Poly_eval(Poly poly, Fr x);

void free_Poly(Poly poly);

void print_Poly(Poly poly);


#endif