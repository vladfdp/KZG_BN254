#include <stdint.h>
#include <stdio.h>
#include "int256.h"
#include "int512.h"
#include "Fp.h"

const int256 P = {0,0,0x706,0x0f9e24e6ffdbd05d};//{0x30644e72e131a029,0xb85045b68181585d,0x97816a916871ca8d,0x3c208c16d87cfd47};

Fp Fp_zero(){
    Fp zero = {{0,0,0,0}};
    return zero;
}

Fp Fp_one(){
    Fp one = {{0,0,0,1}};
    return one;
}

Fp Fp_from_int(uint64_t n){
    Fp ans = {{
        0,0,0,n
    }};
    return ans;
}

Fp Fp_add(Fp a, Fp b){
    
    Fp sum = {add_256(a.num, b.num)};
    
    if (cmp_256(sum.num, P )){
        Fp sum_min_P = {sub_256(sum.num , P)};
        return sum_min_P;
    }
    return sum;  
}

Fp Fp_exp(Fp base, int256 exponent){

    Fp ans = Fp_one();

    while (exponent.u3  || exponent.u2 ||  exponent.u1 ||exponent.u0 )
    {
        if (exponent.u0 & 1){
            ans = Fp_mul(ans,base);
        }
        print_Fp(base);
        base = Fp_mul(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
    
}

Fp Fp_opp(Fp x){        //retourne -x dans Fp
    Fp ans = {sub_256(P,x.num)};
    return ans;
}

Fp Fp_sub(Fp a,Fp b){
    return Fp_add( a, Fp_opp(b));
}

Fp Fp_mul(Fp a, Fp b){

    int512 prod = mul_from_256(a.num , b.num);
    //print_512(prod);
    Fp ans = {modulo(prod , P)};
    return ans;
}

void print_Fp(Fp x){
    int256 A = x.num;
    printf("{%lX,%lX,%lX,%lX}",A.u3,A.u2,A.u1,A.u0);
    //print_256(A);
}

// Fp Fp_inv(Fp x){

// }


