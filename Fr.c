#include <stdint.h>
#include <stdio.h>
#include "int256.h"
#include "int320.h"
#include "int512.h"
#include "Fr.h"



Fr Fr_zero(){
    Fr zero = {{0,0,0,0}};
    return zero;
}

Fr Fr_one(){
    Fr one = {{0,0,0,1}};
    return one;
}

Fr Fr_from_int(uint64_t n){
    Fr ans = {{
        0,0,0,n
    }};
    return ans;
}

Fr Fr_from_4_int(uint64_t n1, uint64_t n2, uint64_t n3, uint64_t n4){
    Fr ans = {{
        n1, n2, n3, n4
    }};
    return ans;
}

Fr get_rand_Fr(){

    int256 random;
    int i = 0;
    do{
        random = rand_256();
    

    }while (cmp_256(random, R));      //on recommence au lieu de reduire pour pas perdre l'uniformité de la distribution

    
    Fr ans = {random};
    return ans;
}

Fr Fr_add(Fr a, Fr b){
    
    Fr sum = {add_256(a.num, b.num)};
    
    if (cmp_256(sum.num, R )){
        Fr sum_min_R = {sub_256(sum.num , R)};
        return sum_min_R;
    }
    return sum;  
}

Fr Fr_exp(Fr base, int256 exponent){

    Fr ans = Fr_one();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3 )
    {
        if (exponent.u0 & 1){
            ans = Fr_mul(ans,base);
        }
        base = Fr_mul(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}

int Fr_equal(Fr a, Fr b){
    return (a.num.u0 == b.num.u0 &&
    a.num.u1 == b.num.u1 &&
    a.num.u2 == b.num.u2 &&
    a.num.u3 == b.num.u3
    );
}


Fr Fr_opp(Fr x){

    if (x.num.u0 || x.num.u1 || x.num.u2 || x.num.u3)
    {
        Fr ans = {sub_256(R,x.num)};
        return ans;
    }
    return x;
}

Fr Fr_sub(Fr a,Fr b){
    return Fr_add( a, Fr_opp(b));
}

Fr Fr_mul_original(Fr a, Fr b){

    int512 prod = mul_from_256(a.num , b.num);
    Fr ans = {modulo(prod , R)};
    return ans;
}

Fr Fr_mul_daa(Fr a, Fr b){

    Fr base = a;
    int256 exponent = b.num;

    Fr ans = Fr_zero();

    while (exponent.u0  || exponent.u1  || exponent.u2 ||  exponent.u3 )
    {
        if (exponent.u0 & 1){
            ans = Fr_add(ans,base);
        }
        base = Fr_add(base, base);
        exponent = shift_right_256(exponent);
    }
    return ans;
}

Fr Fr_mul_mq(Fr a, Fr b){

    int512 prod = mul_from_256(a.num , b.num);

    int256 pre_256_mod_R = {0xe0a77c19a07df2f,0x666ea36f7879462e,0x36fc76959f60cd29,0xac96341c4ffffffb};
    int256 pre_320_mod_R = {0x215b02ac9a392866,0x9ffd1de404f7e0ef,0x708c8d50bfeb93be,0xb4c6edf97c5fb586};
    int256 pre_384_mod_R = {0x3d581d748ffa25e,0x32c475047957bf7b,0xa7f12acca5b6cd8c,0xb075da81ef8cfeb9};
    int256 pre_448_mod_R = {0x621c0bbcccdc65d,0xb09192e52f747168,0xe7f02ade75c713,0x5665c3b5c177f51a};

    int320 prod320 = {0,prod.u3,prod.u2,prod.u1,prod.u0};
    // printf("\n prod320");
    // print_320(prod320);

    prod320 = add_320(prod320, mul_by_64_320(pre_256_mod_R, prod.u4));
    prod320 = add_320(prod320, mul_by_64_320(pre_320_mod_R, prod.u5));
    prod320 = add_320(prod320, mul_by_64_320(pre_384_mod_R, prod.u6));
    prod320 = add_320(prod320, mul_by_64_320(pre_448_mod_R, prod.u7));

    // printf("\n prod512");
    // print_512(prod);
    // printf("\n prod320");
    // print_320(prod320);

    Fr ans = {modulo_320(prod320 , R)};

    return ans;
}

Fr Fr_mul_mq2(Fr a, Fr b){

    int512 prod = mul_from_256(a.num , b.num);

    int256 pre_256_mod_R = {0xe0a77c19a07df2f,0x666ea36f7879462e,0x36fc76959f60cd29,0xac96341c4ffffffb};
    int256 pre_288_mod_R = {0x6bc037eec6c226e,0x1271b743302ab839,0x16df2426b05ea154,0x93e7886515b8b9da};
    int256 pre_320_mod_R = {0x215b02ac9a392866,0x9ffd1de404f7e0ef,0x708c8d50bfeb93be,0xb4c6edf97c5fb586};
    int256 pre_352_mod_R = {0x1847e4868229aff4,0xbe492693330a5a6d,0x2b82a1ef97aa45f6,0x54c81065af8b5a7a};
    int256 pre_384_mod_R = {0x3d581d748ffa25e,0x32c475047957bf7b,0xa7f12acca5b6cd8c,0xb075da81ef8cfeb9};
    int256 pre_416_mod_R = {0x1df79fc3ff54fbf4,0xe590c2b8184bf72d,0x76add9c483e9406,0xee881bd8ebb7ae00};
    int256 pre_448_mod_R = {0x621c0bbcccdc65d,0xb09192e52f747168,0xe7f02ade75c713,0x5665c3b5c177f51a};
    int256 pre_480_mod_R = {0x2ab23b99093f81dd,0xa6132126440ad260,0x9f36d6010a58dc0f,0x41a9cbe48f8fc595};

    int320 prod320 = {0,prod.u3,prod.u2,prod.u1,prod.u0};
    // printf("\n prod320");
    // print_320(prod320);

    prod320 = add_320(prod320, mul_by_32_320(pre_256_mod_R, (prod.u4 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, shift_left_by_32_320( mul_by_32_320(pre_256_mod_R, prod.u4 >> 32)));
    prod320 = add_320(prod320, mul_by_32_320(pre_320_mod_R, (prod.u5 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, shift_left_by_32_320( mul_by_32_320(pre_320_mod_R, prod.u5 >> 32)));
    prod320 = add_320(prod320, mul_by_32_320(pre_384_mod_R, (prod.u6 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, shift_left_by_32_320( mul_by_32_320(pre_384_mod_R, prod.u6 >> 32)));
    prod320 = add_320(prod320, mul_by_32_320(pre_448_mod_R, (prod.u7 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, shift_left_by_32_320( mul_by_32_320(pre_448_mod_R, prod.u7 >> 32)));


    Fr ans = {modulo_320(prod320 , R)};

    return ans;
}

Fr Fr_mul(Fr a, Fr b){

    int512 prod = mul_from_256(a.num , b.num);

    int256 pre_256_mod_R = {0xe0a77c19a07df2f,0x666ea36f7879462e,0x36fc76959f60cd29,0xac96341c4ffffffb};
    int256 pre_288_mod_R = {0x6bc037eec6c226e,0x1271b743302ab839,0x16df2426b05ea154,0x93e7886515b8b9da};
    int256 pre_320_mod_R = {0x215b02ac9a392866,0x9ffd1de404f7e0ef,0x708c8d50bfeb93be,0xb4c6edf97c5fb586};
    int256 pre_352_mod_R = {0x1847e4868229aff4,0xbe492693330a5a6d,0x2b82a1ef97aa45f6,0x54c81065af8b5a7a};
    int256 pre_384_mod_R = {0x3d581d748ffa25e,0x32c475047957bf7b,0xa7f12acca5b6cd8c,0xb075da81ef8cfeb9};
    int256 pre_416_mod_R = {0x1df79fc3ff54fbf4,0xe590c2b8184bf72d,0x76add9c483e9406,0xee881bd8ebb7ae00};
    int256 pre_448_mod_R = {0x621c0bbcccdc65d,0xb09192e52f747168,0xe7f02ade75c713,0x5665c3b5c177f51a};
    int256 pre_480_mod_R = {0x2ab23b99093f81dd,0xa6132126440ad260,0x9f36d6010a58dc0f,0x41a9cbe48f8fc595};

    int320 prod320 = {0,prod.u3,prod.u2,prod.u1,prod.u0};
    // printf("\n prod320");
    // print_320(prod320);

    prod320 = add_320(prod320, mul_by_32_320(pre_256_mod_R, (prod.u4 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_288_mod_R, prod.u4 >> 32));
    prod320 = add_320(prod320, mul_by_32_320(pre_320_mod_R, (prod.u5 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_352_mod_R, prod.u5 >> 32));
    prod320 = add_320(prod320, mul_by_32_320(pre_384_mod_R, (prod.u6 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_416_mod_R, prod.u6 >> 32));
    prod320 = add_320(prod320, mul_by_32_320(pre_448_mod_R, (prod.u7 & 0x00000000FFFFFFFF)));
    prod320 = add_320(prod320, mul_by_32_320(pre_480_mod_R, prod.u7 >> 32));


    int320 mod_shifted = {0,R.u3,R.u2,R.u1,R.u0};    

    mod_shifted = shift_left_320( shift_left_by_32_320(mod_shifted));

    Fr ans = {modulo_33(prod320 , mod_shifted)};

    return ans;
}





void print_Fr(Fr x){
    int256 A = x.num;
    printf("{%llx,%llx,%llx,%llx}", A.u3 ,A.u2,A.u1,A.u0);

}

Fr Fr_inv(Fr x){

    int256 t = zero_256();
    int256 newt = {0,0,0,1};
    int256 r = R;   
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
    Fr ans = {t};
    if (i & 1){
        return ans;
    }
    return Fr_opp(ans);


}

Fr Fr_div(Fr a,Fr b){
    return Fr_mul(a,Fr_inv(b));
}
