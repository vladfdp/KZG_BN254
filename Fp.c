#include <stdint.h>
#include <stdio.h>
#include "int256.h"
#include "int320.h"
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

Fp Fp_mul_original(Fp a, Fp b){

    int512 prod = mul_from_256(a.num , b.num);
    Fp ans = {modulo(prod , P)};
    return ans;
}

Fp Fp_mul(Fp a, Fp b){

    int512 prod = mul_from_256(a.num , b.num);

    int256 pre_256_mod_P = {0xe0a77c19a07df2f,0x666ea36f7879462c,0xa78eb28f5c70b3d,0xd35d438dc58f0d9d};
    int256 pre_288_mod_P = {0x6bc037eec6c226e,0x1271b740e35bc824,0x7ee89afd34897ea0,0x7d81d725eb7ffd76};
    int256 pre_320_mod_P = {0x215b02ac9a392864,0x532e2dcf5d840e23,0x1be5d753eb3c74f7,0x2d9e3b3fb1d8c62a};
    int256 pre_352_mod_P = {0x1847e484355abfe0,0x16d553c691aba3c7,0xf21d65b8492b8e82,0xf54b1e88b28a9d6};
    int256 pre_384_mod_P = {0x2c1e8d981110f1af,0xed7948a39bab3e80,0xe0e407c3583ff802,0x70bb17072fcc56ea};
    int256 pre_416_mod_P = {0x1798cd75599e034b,0x7c85e31974c97a69,0x608145f0d3cf3fbc,0xcd9e8446cfc4da46};
    int256 pre_448_mod_P = {0x2e1043978c993ec8,0xa49e35d611a2ac87,0xc722ccf2a40f0271,0xd9e291c2cdd22cd6};
    int256 pre_480_mod_P = {0x1d7bcfc4aef5cf59,0xcd5b0ab04bce7022,0xb4c74c436b59411b,0xa021026fd86ece59};

    int320 prod320 = {0,prod.u3,prod.u2,prod.u1,prod.u0};

    prod320 = add_320(prod320, mul_by_32_320(pre_256_mod_P, (prod.u4 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_288_mod_P, prod.u4 >> 32));
    prod320 = add_320(prod320, mul_by_32_320(pre_320_mod_P, (prod.u5 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_352_mod_P, prod.u5 >> 32));
    prod320 = add_320(prod320, mul_by_32_320(pre_384_mod_P, (prod.u6 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_416_mod_P, prod.u6 >> 32));
    prod320 = add_320(prod320, mul_by_32_320(pre_448_mod_P, (prod.u7 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_480_mod_P, prod.u7 >> 32));


    int320 mod_shifted = {0,P.u3,P.u2,P.u1,P.u0};    

    mod_shifted = shift_left_320(shift_left_by_32_320(mod_shifted));

    Fp ans = {modulo_33(prod320 , mod_shifted)};

    return ans;









}

void print_Fp(Fp x){
    int256 A = x.num;
    printf("{0x%llx,0x%llx,0x%llx,0x%llx}", A.u3,A.u2,A.u1,A.u0);
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


