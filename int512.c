#include <stdint.h>
#include <stdio.h>
#include "int512.h"
#include "int256.h"


int cmp_512(int512 a, int512 b){ // verifie si a est plus grand ou egal a b
    if (a.u7 == b.u7){
        if (a.u6 == b.u6){
            if (a.u5 == b.u5){
                if (a.u4 == b.u4){
                    if (a.u3 == b.u3){
                        if (a.u2 == b.u2){
                            if (a.u1 == b.u1){
                                return a.u0 >= b.u0;
                            }
                            return a.u1 > b.u1;
                        }
                        return a.u2 > b.u2;
                    }
                    return a.u3 > b.u3;
                }
                return a.u4 > b.u4;
            }
            return a.u5 > b.u5;
        }
        return a.u6 > b.u6;
    }
    return a.u7 > b.u7;
}

int512 add_512(int512 a, int512 b){
    
    int512 ans = {a.u7 + b.u7,
    a.u6 + b.u6,
    a.u5 + b.u5,
    a.u4 + b.u4,
    a.u3 + b.u3,
    a.u2 + b.u2,
    a.u1 + b.u1,
    a.u0 + b.u0,
    };
    
    ans.u1 += (ans.u0 < a.u0) ? 1 : 0;                          //les retenues
    ans.u2 += (ans.u1 < a.u1) || (ans.u1 < b.u1) ? 1 : 0;
    ans.u3 += (ans.u2 < a.u2) || (ans.u2 < b.u2) ? 1 : 0;
    ans.u4 += (ans.u3 < a.u3) || (ans.u3 < b.u3) ? 1 : 0;
    ans.u5 += (ans.u4 < a.u4) || (ans.u4 < b.u4) ? 1 : 0;
    ans.u6 += (ans.u5 < a.u5) || (ans.u5 < b.u5) ? 1 : 0;
    ans.u7 += (ans.u6 < a.u6) || (ans.u6 < b.u6) ? 1 : 0;


    return ans;  
}

int512 sub_512(int512 a, int512 b){       //on assume que a > b

    int512 ans = {a.u7 - b.u7,
    a.u6 - b.u6,
    a.u5 - b.u5,
    a.u4 - b.u4,
    a.u3 - b.u3,
    a.u2 - b.u2,
    a.u1 - b.u1,
    a.u0 - b.u0,
    };

    ans.u1 -= (ans.u0 > a.u0) ? 1 : 0; //effectue la retenue inverse
    ans.u2 -= (ans.u1 > a.u1) || ((ans.u1 == a.u1) && b.u1 ) ? 1 : 0; //le short circuit evaluation fait que la deuxieme condition n'est pas souvent verifié
    ans.u3 -= (ans.u2 > a.u2) || ((ans.u2 == a.u2) && b.u2 ) ? 1 : 0;
    ans.u4 -= (ans.u3 > a.u3) || ((ans.u3 == a.u3) && b.u3 ) ? 1 : 0;
    ans.u5 -= (ans.u4 > a.u4) || ((ans.u4 == a.u4) && b.u4 ) ? 1 : 0;
    ans.u6 -= (ans.u5 > a.u5) || ((ans.u5 == a.u5) && b.u5 ) ? 1 : 0;
    ans.u7 -= (ans.u6 > a.u6) || ((ans.u6 == a.u6) && b.u6 ) ? 1 : 0;

    return ans;

}

int512 zero_512(){
    int512 zero = {0,0,0,0,0,0,0,0};
    return zero;
}

int512 mul_by_32( int256 x, uint64_t slice){ //multiplie un entier de 256 bit par un de 32

    
    int512 even = {0,0,0,0,
    (x.u3 & 0x00000000FFFFFFFF) * slice,
    (x.u2 & 0x00000000FFFFFFFF) * slice,
    (x.u1 & 0x00000000FFFFFFFF) * slice,
    (x.u0 & 0x00000000FFFFFFFF) * slice,   
    };



    int512 odd = {0,0,0,0,
    (x.u3 >> 32) * slice,
    (x.u2 >> 32) * slice,
    (x.u1 >> 32) * slice,
    (x.u0 >> 32) * slice,   
    };

    return add_512(even , shift_left_by_32(odd));

}

void print_512(int512 x){
    //printf("{%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu}\n",x.u7,x.u6,x.u5,x.u4,x.u3,x.u2,x.u1,x.u0);
    printf("{%lX,%lX,%lX,%lX,%lX,%lX,%lX,%lX}\n",x.u7,x.u6,x.u5,x.u4,x.u3,x.u2,x.u1,x.u0);
}


int512 mul_from_256(int256 a, int256 b){

    int512 sum = zero_512();

    for (int i = 0; i < 8; i++)
    {
        uint64_t slice = get_32_slice(b,i);
        int512 cur = mul_by_32(a,slice);
        for (int j = 0; j < i; j++)
        {
            cur = shift_left_by_32(cur);
        }
        
        sum = add_512(sum, cur);
    }
    return sum;
}




int512 shift_right_by_32(int512 x){

    x.u0 >>= 32;
    x.u0 ^= x.u1 << 32;
    x.u1 >>=32;
    x.u1 ^= x.u2 << 32;
    x.u2 >>=32;
    x.u2 ^= x.u3 << 32;
    x.u3 >>=32;
    x.u3 ^= x.u4 << 32;
    x.u4 >>=32;
    x.u4 ^= x.u5 << 32;
    x.u5 >>=32;
    x.u5 ^= x.u6 << 32;
    x.u6 >>=32;
    x.u6 ^= x.u7 << 32;
    x.u7 >>=32;
    return x;
}

int512 shift_left_by_32(int512 x){

    x.u7 <<=32;
    x.u7 ^= x.u6 >> 32;
    x.u6 <<=32;
    x.u6 ^= x.u5 >> 32;
    x.u5 <<=32;
    x.u5 ^= x.u4 >> 32;
    x.u4 <<=32;
    x.u4 ^= x.u3 >> 32;
    x.u3 <<=32;
    x.u3 ^= x.u2 >> 32;
    x.u2 <<=32;
    x.u2 ^= x.u1 >> 32;
    x.u1 <<=32;
    x.u1 ^= x.u0 >> 32;
    x.u0 <<=32;
    return x;
}

int512 shift_right_512(int512 x){

    x.u0 >>= 1;
    x.u0 ^= (x.u1 << 63);
    x.u1 >>=1;
    x.u1 ^= (x.u2 << 63);
    x.u2 >>=1;
    x.u2 ^= (x.u3 << 63);
    x.u3 >>=1;
    x.u3 ^= (x.u4 << 63);
    x.u4 >>=1;
    x.u4 ^= (x.u5 << 63);
    x.u5 >>=1;
    x.u5 ^= (x.u6 << 63);
    x.u6 >>=1;
    x.u6 ^= (x.u7 << 63);
    x.u7 >>=1;
    return x;
}
