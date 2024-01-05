#include <stdint.h>
#include <stdio.h>
#include "int256.h"


int cmp_256(int256 a, int256 b){ // verifie si a est plus grand ou egal a b
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


int256 add_256(int256 a, int256 b){
    
    int256 ans = {a.u3 + b.u3,
    a.u2 + b.u2,
    a.u1 + b.u1,
    a.u0 + b.u0,
    };
    
    ans.u1 += (ans.u0 < a.u0) ? 1 : 0; //effectue la retenue, si c.u0 < a.u0 alors a.u0 + b.u0 overflow donc on ajoute 1 a c.u1
    ans.u2 += (ans.u1 < a.u1) || (ans.u1 < b.u1) ? 1 : 0;
    ans.u3 += (ans.u2 < a.u2) || (ans.u2 < b.u2) ? 1 : 0;

    return ans;  
}


int256 sub_256(int256 a, int256 b){       //on assume que a > b

    int256 ans = {a.u3 - b.u3,
    a.u2 - b.u2,
    a.u1 - b.u1,
    a.u0 - b.u0,
    };
    ans.u1 -= (ans.u0 > a.u0) ? 1 : 0; //effectue la retenue inverse
    ans.u2 -= (ans.u1 > a.u1) || (ans.u1 > b.u1) ? 1 : 0;
    ans.u3 -= (ans.u2 > a.u2) || (ans.u2 > b.u2) ? 1 : 0;

    return ans;

}


int64_t get_32_slice(int256 x, int i){
    switch (i)
    {
    case 0:
        return x.u0 & 
        break;
    
    default:
        break;
    }
}


int256 shift_right(int256 x){

    x.u0 >>= 1;
    x.u0 ^= (x.u1 & 1) << 63;
    x.u1 >>=1;
    x.u1 ^= (x.u2 & 1) << 63;
    x.u2 >>=1;
    x.u2 ^= (x.u3 & 1) << 63;
    x.u3 >>=1;
    return x;
}