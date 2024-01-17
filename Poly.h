#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"

#ifndef POLY_H
#define POLY_H

typedef struct Poly{
    Fr* coeffs;
    unsigned int degree;
}Poly;


#endif