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
    Fp A1 = {{10,10,10,10}};
    Fp B1 = {{0,f,f,0}};
    Fp C1 = Fp_mul(A1,B1);

    print_Fp(A1);
    print_Fp(B1);
    print_Fp(C1);

    int512 A2 = {0,0,0,100,180,180,180,81};
    int512 B2 = {0,0,0,80,80,80,80,0};
    int512 C2 = sub_512(A2,B2);
    printf("\n");
    print_512(C2);

    

   
    return 0;
}