#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"
#include "Poly.h"

Poly Poly_init(unsigned int degree){
    Fr* coeffs = calloc(degree + 1, sizeof(Fr));
    //assert(coeffs != NULL);
    Poly ans = {coeffs, degree};
    return ans;
}

Fr Poly_eval(Poly poly, Fr x){
    Fr ans = Fr_zero();
    Fr x_exp = Fr_one();
    for (int i = 0; i < poly.degree + 1; i++)
    {
        ans = Fr_add(ans, Fr_mul( poly.coeffs[i], x_exp) );
        x_exp = Fr_mul(x_exp, x);
    }
    return ans;
    
}

Poly euclidean_div_Poly(Poly f, Poly g){
    int dif = f.degree - g.degree;
    Poly ans = Poly_init(dif);
    if (dif < 0)
    {
        return Poly_init(0);
    }
    Fr pivot = Fr_inv(g.coeffs[g.degree]);

    for (int i = 0; i < dif; i++)
    {

        for (int j = 0; j < g.degree; j++)
        {
            
        }
    }
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
    for (int i = 1; i < poly.degree + 1; i++)
    {
        printf(" + ");
        print_Fr(poly.coeffs[i]);
        printf(" * X^%u",i);
    }
    printf("\n");
}