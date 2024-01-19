#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"
#include "Poly.h"

Poly Poly_init(int degree){
    Fr* coeffs = calloc(degree + 1, sizeof(Fr));
    Poly ans = {coeffs, degree};
    return ans;
}

Poly vanish_Poly(Fr x){
    Poly ans = Poly_init(1);
    ans.coeffs[0] = Fr_opp(x);
    ans.coeffs[1] = Fr_one();
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

Poly clone_Poly(Poly poly){
    Fr* coeffs = malloc((poly.degree + 1) * sizeof(Fr));
    for (int i = 0; i < poly.degree + 1; i++)
    {
        coeffs[i] = poly.coeffs[i];
    }
    
    Poly ans = {coeffs, poly.degree};
    return ans;
}

Fr leading_term(Poly poly){
    return poly.coeffs[poly.degree];
}

Poly euclidean_div_Poly(Poly f, Poly g){ //renvoie le quotient de f/g, attention f devient son reste par la division
    int dif = f.degree - g.degree;
    Poly ans = Poly_init(dif);
    if (dif < 0)
    {
        return Poly_init(0);
    }
    Fr lt_inv = Fr_inv(g.coeffs[g.degree]);

    for (int i = 0; i < dif + 1; i++)
    {
        Fr pivot = Fr_mul(lt_inv,f.coeffs[f.degree - i]);
        for (int j = 0; j < g.degree + 1; j++)
        {
            Fr a = Fr_mul(pivot, g.coeffs[g.degree - j]);
            f.coeffs[f.degree - i - j] = Fr_sub(f.coeffs[f.degree - i - j], a );
        }
        ans.coeffs[dif - i] = pivot;
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