#include <stdint.h>
#include <stdio.h>
#include "int256.h"
#include "int512.h"
#include "Fp.h"

const Fp P = {{10,10,10,10}};



Fp Fp_add(Fp a, Fp b){
    
    Fp sum = {add_256(a.num, b.num)};
    
    if (cmp_256(sum.num, P.num )){
        Fp sum_min_P = {sub_256(sum.num , P.num)};
        return sum_min_P;
    }
    return sum;  
}

Fp Fp_mul(Fp a, Fp b){

    int512 prod = mul_from_256(a.num , b.num);
    Fp ans = {modulo(prod , P.num)};

    return ans;

}

void print_Fp(Fp x){
    int256 A = x.num;
    //printf("{%.64X,%.64X,%.64X,%.64X}\n",A.u3,A.u2,A.u1,A.u0);
    printf("{%lu,%lu,%lu,%lu}\n",A.u3,A.u2,A.u1,A.u0);
}


