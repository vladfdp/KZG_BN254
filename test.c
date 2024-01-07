#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
  


void test_Fp_exp(){

    Fp x = {{6711165,67675,5004865,6767655}};
    int256 e = {0x30644e72e131a029,0xb85045b68181585d,0x97816a916871ca8d,0x3c208c16d87cfd45}; // P - 2
    Fp y = Fp_exp(x,e);

    print_Fp(Fp_mul(x,y));
    
}

void test_Fp_ext(){

    Fp A1 = {{0,0,0,10}};
    Fp B1 = {{0,0,0,0}};
    Fp C1 = {{0,0,0,10}};
    Fp D1 = {{0,0,0,0}};
  
    Fp2 A2 = {A1, B1};
    Fp2 B2 = {C1, D1}; 
    Fp2 C2 = Fp2_add(A2,B2);
    Fp2 E2 = Fp2_sub(A2,B2);
    Fp2 F2 = Fp2_mul(A2,B2);


    print_Fp2(A2);printf("\n");
    print_Fp2(B2);printf("\n");
    print_Fp2(C2);printf("\n");
    print_Fp2(E2);printf("\n");
    print_Fp2(F2);printf("\n"); printf("\n");

    Fp6 A3 = {A2,B2,C2};
    Fp6 B3 = {C2,C2,A2};
    Fp6 C3 = Fp6_add(A3,B3);
    Fp6 D3 = Fp6_sub(A3,B3);
    Fp6 E3 = Fp6_mul(A3,B3);

    print_Fp6(A3);printf("\n");
    print_Fp6(B3);printf("\n");
    print_Fp6(C3);printf("\n");
    print_Fp6(D3);printf("\n");
    print_Fp6(E3);printf("\n"); printf("\n");




    Fp12 A4 = {A3, B3};
    Fp12 B4 = {C3, A3};
    Fp12 C4 = Fp12_add(A4,B4);
    Fp12 D4 = Fp12_mul(A4,B4);
    Fp12 E4 = Fp12_sub(A4,B4);

    print_Fp12(A4);printf("\n");
    print_Fp12(B4);printf("\n");
    print_Fp12(C4);printf("\n");
    print_Fp12(D4);printf("\n");
    print_Fp12(E4);printf("\n");

}
  

int main(){


    test_Fp_exp();

    uint64_t f = 0xFFFFFFFFFFFFFFFF;
return 0;
}