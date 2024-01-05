#include <stdint.h>
#include <stdio.h>
#include "int256.h"
#include "int512.h"
#include "Fp.h"

const Fp P = {{10,10,10,10}};

Fp Fp_zero(){
    Fp zero = {zero_256()};
    return zero;
}

Fp Fp_from_int(uint64_t n){
    Fp ans = {{
        0,0,0,n
    }};
    return ans;
}

Fp Fp_add(Fp a, Fp b){
    
    Fp sum = {add_256(a.num, b.num)};
    
    if (cmp_256(sum.num, P.num )){
        Fp sum_min_P = {sub_256(sum.num , P.num)};
        return sum_min_P;
    }
    return sum;  
}

Fp Fp_exp(Fp base, int256 exponant){

    Fp ans = Fp_zero();

    for (int i = 0; i < 256; i++)
    {
        if (exponant.u0 & 1){
            ans = Fp_add(ans,base);
        }
        base = Fp_mul(base, base);
        exponant = shift_right_256(exponant);
    }
    return ans;
    
}

Fp Fp_opp(Fp x){        //retourne -x dans Fp
    Fp ans = {sub_256(P.num,x.num)};
    return ans;
}

Fp Fp_sub(Fp a,Fp b){
    return Fp_add( a, Fp_opp(b));
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

Fp Fp_inv(Fp x){

}


