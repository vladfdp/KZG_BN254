#include <stdint.h>
#include <stdio.h>
#include "int256.h"
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
    do{
        random = rand_256();

    }while (cmp_256(R, random));       //on recommence au lieu de reduire pour pas perdre l'uniformité de la distribution
    
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

Fr Fr_mul(Fr a, Fr b){

    int512 prod = mul_from_256(a.num , b.num);
    Fr ans = {modulo(prod , R)};
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
