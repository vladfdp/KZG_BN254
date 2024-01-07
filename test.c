#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"






int main(){


    uint64_t f = 0xFFFFFFFFFFFFFFFF;
    Fp A = {{0,0,0x706,0x0f9e24e6ffdbd05b}};
    int256 e = {0,0,0x706,0x0f9e24e6ffdbd05d};
    Fp B = Fp_exp(A,e);
    Fp C = Fp_mul(A, A);


    printf("\n\n");
    print_Fp(A);
    print_Fp(B);
    print_Fp(C);

    printf("\n\n");

    int512 a = {0,0,0,0,0,1,0,0};
    int256 p = {0,0,0x706,0x0f9e24e6ffdbd05d};
    print_256(modulo(a,p));

    // printf("\n\n");

    // int256 x = {((uint64_t)1<<33),2,3,4};
    // int256 y = {34,0,0,0};

    // int512 z = mul_from_256(x,y);

    // print_256(x);
    // printf(" * ");
    // print_256(y);
    // printf("\n = ");
    // print_512(z);



    

   
    return 0;
}