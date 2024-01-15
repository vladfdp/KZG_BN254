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




Fr Fr_opp(Fr x){   //retourne -x dans Fr

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
    //print_512(prod);
    Fr ans = {modulo(prod , R)};
    return ans;
}

void print_Fr(Fr x){
    int256 A = x.num;
    printf("{%lx,%lx,%lx,%lx}", A.u3 ,A.u2,A.u1,A.u0);
    //print_256(A);
}

Fr Fr_inv(Fr x){

    int256 t = zero_256();
    int256 newt = {0,0,0,1};
    int256 r = R;   
    int256 newr = x.num;
    int i = 0;
    
    while (newr.u0 || newr.u1 || newr.u2 || newr.u3) {

        QR qr = euclidean_div_256(r, newr);
        
        int256 a = add_256(int512_to_256(mul_from_256(qr.quotient , newr)), qr.rest);
        
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
