#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "int320.h"
#include "int256.h"
#include "int512.h"


int cmp_320(int320 a, int320 b){ // verifie si a est plus grand ou egal a b
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

int cmp_strict_320(int320 a, int320 b){ // verifie si a est strictement plus grand que b
    if (a.u4 == b.u4){
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
    return a.u4 > b.u4;
}

int320 add_320(int320 a, int320 b){ //l'operation est fait modulo 2^320 //TODO: fix this
    
    int320 ans = {a.u4 + b.u4,
    a.u3 + b.u3,
    a.u2 + b.u2,
    a.u1 + b.u1,
    a.u0 + b.u0,
    };
    
    (ans.u0 < a.u0) ? ans.u1++ : 0 ; //effectue la retenue, si c.u0 < a.u0 alors a.u0 + b.u0 overflow donc on ajoute 1 a ans.u1
    (ans.u1 < a.u1) || (ans.u1 < b.u1) ? ans.u2 ++ : 0;
    (ans.u2 < a.u2) || (ans.u2 < b.u2) ? ans.u3 ++ : 0;
    (ans.u3 < a.u3) || (ans.u3 < b.u3) ? ans.u4 ++ : 0;

    return ans;  
}



int320 sub_320(int320 a, int320 b){ //l'operation est fait modulo 2^320

    int320 ans = {a.u4 - b.u4,
    a.u3 - b.u3,
    a.u2 - b.u2,
    a.u1 - b.u1,
    a.u0 - b.u0,
    };
    (ans.u0 > a.u0) ? ans.u1-- : 0; //effectue la retenue inverse
    (ans.u1 > a.u1) || ((ans.u1 == a.u1) && b.u1 )  ? ans.u2 -- : 0;
    (ans.u2 > a.u2) || ((ans.u2 == a.u2) && b.u2 )  ? ans.u3 -- : 0;
    (ans.u3 > a.u3) || ((ans.u3 == a.u3) && b.u3 )  ? ans.u4 -- : 0;

    return ans;

}




int320 zero_320(){
    int320 zero = {0,0,0,0,0};
    return zero;
}

int320 shift_right_320(int320 x){

    x.u0 >>= 1;
    x.u0 ^= x.u1 << 63;     // on met le dernier bit de u1 a la place du premier bit de u0 et ainsi de suite
    x.u1 >>=1;
    x.u1 ^= x.u2 << 63;
    x.u2 >>=1;
    x.u2 ^= x.u3 << 63;
    x.u3 >>=1;
    x.u3 ^= x.u4 << 63;
    x.u4 >>=1;
    return x;
}

int320 shift_left_320(int320 x){

    x.u4 <<= 1;
    x.u4 ^= (x.u3 >> 63);
    x.u3 <<= 1;
    x.u3 ^= (x.u2 >> 63);
    x.u2 <<= 1;
    x.u2 ^= (x.u1 >> 63);
    x.u1 <<= 1;
    x.u1 ^= (x.u0 >> 63);
    x.u0 <<= 1;
    return x;
}
void print_320(int320 x){
    //printf("{%lu,%lu,%lu,%lu}",x.u3,x.u2,x.u1,x.u0);

    printf("{0x%llx,0x%llx,0x%llx,0x%llx,0x%llx}",x.u4,x.u3,x.u2,x.u1,x.u0);
}

int320 mul_by_32_320( int256 x, uint64_t slice){ //multiplie un entier de 256 bit par un de 32

    
    int320 even = {0,
    (x.u3 & 0x00000000FFFFFFFF) * slice,   //on separe les slices pair et impair de a pour eviter tout chevauchement
    (x.u2 & 0x00000000FFFFFFFF) * slice,
    (x.u1 & 0x00000000FFFFFFFF) * slice,
    (x.u0 & 0x00000000FFFFFFFF) * slice,   
    };



    int320 odd = {0,
    (x.u3 >> 32) * slice,
    (x.u2 >> 32) * slice,
    (x.u1 >> 32) * slice,
    (x.u0 >> 32) * slice,   
    };

    return add_320(even , shift_left_by_32_320(odd));  //on additionne le resultat sans oublier le shift

}

int320 mul_by_64_320( int256 x, uint64_t slice){ //multiplie un entier de 256 bit par un de 64

    
    int320 even = mul_by_32_320(x, (slice & 0x00000000FFFFFFFF));
    int320 odd = mul_by_32_320(x, (slice >> 32));

    return add_320(even , shift_left_by_32_320(odd));  //on additionne le resultat sans oublier le shift

}

int320 shift_left_320_by_n(int320 x, int n){
    for (int i = 0; i < n; i++)
    {
        x = shift_left_320(x);
    }
    return x;
}

int320 shift_left_by_32_320(int320 x){

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

int320 shift_right_by_32_320(int320 x){

    x.u0 >>= 32;
    x.u0 ^= x.u1 << 32;
    x.u1 >>=32;
    x.u1 ^= x.u2 << 32;
    x.u2 >>=32;
    x.u2 ^= x.u3 << 32;
    x.u3 >>=32;
    x.u3 ^= x.u4 << 32;
    x.u4 >>=32;
    return x;
}



int256 modulo_320(int320 x, int256 mod){ //on considere que x < mod*2^320

    int320 mod_shifted = { //mod*2^64
        mod.u3,
        mod.u2,
        mod.u1,
        mod.u0,
        0,
    };
    

    for (int i = 0; i < 64 + 1 ; i++)      //on shift a droite mod_shifted et on le soustrait a x quand c'est possible
    {
        if (cmp_320( x,mod_shifted)){
            x = sub_320(x, mod_shifted);
        }
        mod_shifted = shift_right_320(mod_shifted);
        //print_320(mod_shifted);printf("\n");
        
    }
    //print_320(x);printf("\n");
    int256 ans = {x.u3,x.u2,x.u1,x.u0};
    return ans;

}

int256 modulo_33(int320 x, int320 mod_shifted){

    
    for (int i = 0; i < 33 + 1 ; i++)      //on shift a droite mod_shifted et on le soustrait a x quand c'est possible
    {
        //print_320(x);printf("\n-\n");print_320(mod_shifted);
        if (cmp_320( x,mod_shifted)){
        
            x = sub_320(x, mod_shifted);
        }
        mod_shifted = shift_right_320(mod_shifted);
        
    }
    //print_320(x);printf("\n");
    int256 ans = {x.u3,x.u2,x.u1,x.u0};
    return ans;
}