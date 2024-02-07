#include <stdint.h>
#include <stdio.h>
#include "int256.h"
#include "int512.h"

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

int cmp_strict_256(int256 a, int256 b){ // verifie si a est strictement plus grand que b
    if (a.u3 == b.u3){
        if (a.u2 == b.u2){
            if (a.u1 == b.u1){
                return a.u0 > b.u0;
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
    
    (ans.u0 < a.u0) ? ans.u1++ : 0 ; //effectue la retenue, si c.u0 < a.u0 alors a.u0 + b.u0 overflow donc on ajoute 1 a ans.u1
    (ans.u1 < a.u1) || (ans.u1 < b.u1) ? ans.u2 ++ : 0;
    (ans.u2 < a.u2) || (ans.u2 < b.u2) ? ans.u3 ++ : 0;

    return ans;  
}


int256 sub_256(int256 a, int256 b){       //on assume que a >= b

    int256 ans = {a.u3 - b.u3,
    a.u2 - b.u2,
    a.u1 - b.u1,
    a.u0 - b.u0,
    };
    (ans.u0 > a.u0) ? ans.u1-- : 0; //effectue la retenue inverse
    (ans.u1 > a.u1) || ((ans.u1 == a.u1) && b.u1 )  ? ans.u2 -- : 0;
    (ans.u2 > a.u2) || ((ans.u2 == a.u2) && b.u2 )  ? ans.u3 -- : 0;

    return ans;

}


uint64_t get_32_slice(int256 x, int i){
    switch (i)
    {
    case 0:
        return x.u0 & 0x00000000FFFFFFFF;
        break;
    case 1:
        return x.u0 >> 32;
        break;
    case 2:
        return x.u1 & 0x00000000FFFFFFFF;
        break;
    case 3:
        return x.u1 >> 32;
        break;
    case 4:
        return x.u2 & 0x00000000FFFFFFFF;
        break;
    case 5:
        return x.u2 >> 32;
        break;
    case 6:
        return x.u3 & 0x00000000FFFFFFFF;
        break;
    case 7:
        return x.u3 >> 32;
        break;
    
    default:
    return 0;
        break;
    }
}


int256 modulo(int512 x, int256 mod){ //on considere que x < mod*2^256

    int512 mod_shifted = {
        mod.u3,
        mod.u2,
        mod.u1,
        mod.u0,
        0,0,0,0,
    };

    for (int i = 0; i < 256 + 1 ; i++)
    {
        if (cmp_512( x,mod_shifted)){
            x = sub_512(x, mod_shifted);
        }
        mod_shifted = shift_right_512(mod_shifted);
        
    }
    int256 ans = {x.u3,x.u2,x.u1,x.u0};
    return ans;

}


QR euclidean_div_256(int256 a ,int256 b){

    int256 quotient = zero_256();

    if (cmp_strict_256(b,a))
    {
        QR ans = {quotient,a};
        return ans;
    }

    int i = 0;
    
    while (cmp_256(a,b))
    {
        b = shift_left_256(b);
        i++;
    }
    b = shift_right_256(b);
    i--;




    while( i >= 0)
    {
        if (cmp_256(a,b)){
            a = sub_256(a, b);
            switch (i >> 6)
            {
            case 0:
                quotient.u0 ^= ((uint64_t)1<<i);
                break;
            case 1:
                quotient.u1 ^= ((uint64_t)1<<(i-64));
                break;
            case 2:
                quotient.u2 ^= ((uint64_t)1<<(i-128));
                break;
            case 3:
                quotient.u3 ^= ((uint64_t)1<<(i-192));
                break;
            
            default:
                break;
            }
        }
        b = shift_right_256(b);
        i--;
        
    }
    QR ans = {quotient,a};
    return ans;

}

int256 zero_256(){
    int256 zero = {0,0,0,0};
    return zero;
}

int256 shift_right_256(int256 x){

    x.u0 >>= 1;
    x.u0 ^= x.u1 << 63;
    x.u1 >>=1;
    x.u1 ^= x.u2 << 63;
    x.u2 >>=1;
    x.u2 ^= x.u3 << 63;
    x.u3 >>=1;
    return x;
}

int256 shift_left_256(int256 x){

    x.u3 <<= 1;
    x.u3 ^= (x.u2 >> 63);
    x.u2 <<= 1;
    x.u2 ^= (x.u1 >> 63);
    x.u1 <<= 1;
    x.u1 ^= (x.u0 >> 63);
    x.u0 <<= 1;
    return x;
}
void print_256(int256 x){
    //printf("{%lu,%lu,%lu,%lu}",x.u3,x.u2,x.u1,x.u0);

    printf("{%llx,%llx,%llx,%llx}",x.u3,x.u2,x.u1,x.u0);
}