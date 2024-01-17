#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"
#include "Poly.h"

Poly Poly_init(unsigned int degree){
    Fr* coeffs = calloc(degree, sizeof(Fr));
    assert(coeffs != NULL);
    Poly ans = {coeffs, degree};
    return ans;
}

void free_Poly(Poly poly){ //il faut utiliser cette fonction
    free(poly.coeffs);
}


void print_Poly(Poly poly){
    if (!poly.degree)
    {
        return;
    }
    print_Fr(poly.coeffs[0]);
    for (int i = 1; i < poly.degree; i++)
    {
        printf(" + ");
        print_Fr(poly.coeffs[i]);
        printf(" * X^%u",i);
    }
}