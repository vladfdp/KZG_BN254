#include <stdint.h>
#include <stdio.h>
#include "int256.h"
#include "int512.h"
#include "Fp.h"

Fp Fp_zero(){
    Fp zero = {{0,0,0,0}};
    return zero;
}

int Fp_is_zero(Fp x){
    return !(x.num.u0 || x.num.u1 || x.num.u2 || x.num.u3);
}

Fp Fp_one(){
    Fp one = {{0,0,0,1}};
    return one;
}

int Fp_equal(Fp a, Fp b){
    return (a.num.u0 == b.num.u0 &&
    a.num.u1 == b.num.u1 &&
    a.num.u2 == b.num.u2 &&
    a.num.u3 == b.num.u3
    );
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

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3 )
    {
        if (exponent.u0 & 1){
            ans = Fp_mul(ans,base);
        }
        base = Fp_mul(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}


Fp Fp_opp(Fp x){   //retourne -x dans Fp

    if (x.num.u0 || x.num.u1 || x.num.u2 || x.num.u3)
    {
        Fp ans = {sub_256(P,x.num)};
        return ans;
    }
    return x;
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
    printf("{%llx,%llx,%llx,%llx}", A.u3 ,A.u2,A.u1,A.u0);
    //print_256(A);
}

Fp Fp_inv(Fp x){            //algo d'euclide etendu

    int256 t = zero_256();
    int256 newt = {0,0,0,1};
    int256 r = P;   
    int256 newr = x.num;
    int i = 0;
    
    while (newr.u0 || newr.u1 || newr.u2 || newr.u3) {

        QR qr = euclidean_div_256(r, newr);
        
        int256 tmp = t;
        t = newt;
        int256 mul = int512_to_256(mul_from_256(qr.quotient , newt));
        newt = add_256(tmp , mul);
        tmp = r;
        r = newr;
        newr = qr.rest;
        i++;
    }
    Fp ans = {t};
    if (i & 1){
        return ans;
    }
    return Fp_opp(ans);


}

Fp Fp_div(Fp a,Fp b){
    return Fp_mul(a,Fp_inv(b));
}


