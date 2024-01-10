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

    Fp x = {{6711165,900000000000,55,0}};
    int256 e = {0x30644e72e131a029,0xb85045b68181585d,0x97816a916871ca8d,0x3c208c16d87cfd45}; // P - 2
    Fp y = Fp_exp(x,e);

    print_Fp(Fp_mul(x,y));
    
}

void test_Fp_Inv(){

    Fp x = {{0,0,0,2}};

    Fp y = Fp_inv(x);
    print_Fp(y);
    printf("\n");
    print_Fp(Fp_mul(x,y));
    
}

void test_Fp_ext_Inv(){

    Fp x = {{22223,67,75,53}};
    Fp y = {{7656,95,15600,987}};

    Fp2 a;

    a.x0 = x;
    a.x1 = y;

    Fp2 a_inv = Fp2_inv(a);

    
    print_Fp2(a);
    printf("\n");
    print_Fp2(Fp2_mul(a,a_inv));printf("\n");printf("\n");

    Fp6 jsp;
    jsp.x0 = a;
    jsp.x1 = a_inv;
    jsp.x2 = a;

    print_Fp6(jsp);printf("\n");

    Fp6 jsp_inv = Fp6_inv(jsp);

    print_Fp6( Fp6_mul(jsp, jsp_inv));

    Fp12 jstjrp;
    jstjrp.x0 = jsp_inv;
    jstjrp.x1 = jsp_inv;
    Fp12 jstjrp_inv = Fp12_inv(jstjrp);

    printf("\n");printf("\n");printf("\n");
    print_Fp12(jstjrp);
    printf("\n");printf("\n");printf("\n");
    print_Fp12(jstjrp_inv);

    printf("\n");printf("\n");printf("\n");
    print_Fp12(Fp12_mul(jstjrp,jstjrp_inv));
    
}

void test_Euclid(){

    int256 a = {0,0,0,58765856};
    int256 b = {0,0,0,56};

    QR qr = euclidean_div_256(a,b);
    print_256(qr.quotient);
    printf(" * ");
    print_256(b);
    printf(" + ");
    print_256(qr.rest);
    printf(" = ");
    print_256(a);

    printf("\n\n");


    int256 a2 = {0,6979,654,58765856};
    int256 b2 = {0,0,0,47};

    QR qr2 = euclidean_div_256(a2,b2);
    print_256(qr2.quotient);
    printf(" * ");
    print_256(b2);
    printf(" + ");
    print_256(qr2.rest);
    printf(" = ");
    print_256(a2);
    printf(" = ");

    int512 a3 = mul_from_256(qr2.quotient , b);
    int256 a4 = {a3.u3, a3.u2 ,a3.u1 ,a3.u0};
    a4 = add_256(a4, qr2.rest);
    print_256(a4);
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

    //test_Euclid();
    //test_Fp_exp();
    //test_Fp_Inv();
    //test_Fp_ext();
    test_Fp_ext_Inv();

    return 0;
}