#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Fp.h"
#include "int256.h"


const Fp P1 = {{10,10,10,10}};





int main(){

    uint64_t f = 0xFFFFFFFFFFFFFFFF;
    Fp A1 = {{0,0,0,24}};
    Fp B1 = {{10,10,10,1}};
    Fp C1 = Fp_add(A1,B1);

    int256 A = A1.num;
    int256 B = B1.num;
    int256 C = C1.num;

    printf("A = {%lu,%lu,%lu,%lu}\n\n",A.u3,A.u2,A.u1,A.u0);
    printf("B = {%lu,%lu,%lu,%lu}\n\n",B.u3,B.u2,B.u1,B.u0);
    printf("A+B = {%lu,%lu,%lu,%lu}\n\n",C.u3,C.u2,C.u1,C.u0);

    print_Fp(P1);


    // Fp A2 = {0,0,0,24};
    // Fp B2 = {10,10,10,11};
    // Fp C2 = Fp_add(A2,B2);


    // printf("A+B = {%lu,%lu,%lu,%lu}\n\n",C2.u3,C2.u2,C2.u1,C2.u0);



    // Fp A3 = {0,0,0,24};
    // Fp B3 = {10,10,10,9};
    // Fp C3 = Fp_add(A3,B3);


    // printf("A+B = {%lu,%lu,%lu,%lu}\n\n",C3.u3,C3.u2,C3.u1,C3.u0);

    return 0;
}