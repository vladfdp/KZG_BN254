#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
#include "Fr.h"
#include "Poly.h"
#include "EC.h"
  


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

    Fp6 b;
    b.x0 = a;
    b.x1 = a_inv;
    b.x2 = a;

    print_Fp6(b);printf("\n");

    Fp6 b_inv = Fp6_inv(b);

    print_Fp6( Fp6_mul(b, b_inv));

    Fp12 c;
    c.x0 = b_inv;
    c.x1 = b_inv;
    Fp12 c_inv = Fp12_inv(c);

    printf("\n");printf("\n");printf("\n");
    print_Fp12(c);
    printf("\n");printf("\n");printf("\n");
    print_Fp12(c_inv);

    printf("\n");printf("\n");printf("\n");
    Fp12 one = Fp12_mul(c,c_inv);
    print_Fp12(one);printf("\n");
    printf("%d",Fp12_equal(one, Fp12_one()));
    
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

void test_poly(){

    Poly poly = Poly_init(2);


    poly.coeffs[2] = Fr_from_int(6);
    poly.coeffs[1] = Fr_from_int(1);
    poly.coeffs[0] = Fr_from_int(3);

    Fr x = Fr_from_int(5);

    print_Poly(poly);
    print_Fr(Poly_eval(poly, x)); printf("\n");
    free_Poly(poly);

    Poly poly2 = Poly_init(7);

    poly2.coeffs[7] = Fr_from_int(1);
    poly2.coeffs[6] = Fr_from_int(2);
    poly2.coeffs[5] = Fr_from_int(178);
    poly2.coeffs[4] = Fr_from_int(32);

    poly2.coeffs[2] = Fr_from_int(6);
    poly2.coeffs[1] = Fr_from_int(1);
    poly2.coeffs[0] = Fr_from_int(356);

    Fr y = Fr_from_int(57);

    print_Poly(poly2);
    print_Fr(Poly_eval(poly2, y)); printf("\n");
    free_Poly(poly2);

    printf("\n");
    Poly van_poly = vanish_Poly(Fr_from_int(12654734));
    print_Poly(van_poly);printf("\n");
    print_Fr(Poly_eval(van_poly, Fr_from_int(12654734)));
}

void test_poly_euclid_div(){
    Poly f = Poly_init(9);

    f.coeffs[9] = Fr_from_int(6);
    f.coeffs[8] = Fr_from_int(13);
    f.coeffs[7] = Fr_from_int(1073);
    f.coeffs[6] = Fr_from_int(376);
    f.coeffs[5] = Fr_from_int(566);
    f.coeffs[4] = Fr_from_int(132);
    f.coeffs[3] = Fr_from_int(12);
    f.coeffs[2] = Fr_from_int(2155);
    f.coeffs[1] = Fr_from_int(359);
    f.coeffs[0] = Fr_from_int(1068);

    Poly g = Poly_init(2);

    g.coeffs[2] = Fr_from_int(6);
    g.coeffs[1] = Fr_from_int(1);
    g.coeffs[0] = Fr_from_int(3);

    Poly q = euclidean_div_Poly(f, g);
    printf("\n\n\n");
    print_Poly(q);
    printf("\n\n\n");
    print_Poly(g);
    printf("\n\n\n");
    print_Poly(f);
}

void test_Fr(){
    Fr x = {{6711165,900000000000,55,0}};
    int256 e = {0x30644E72E131A029,0xB85045B68181585D,0x2833E84879B97091,0x43E1F593EFFFFFFF}; // P - 2
    Fr y = Fr_exp(x,e);
    Fr z = Fr_inv(x);

    print_Fr(Fr_mul(x,y));printf("\n");
    print_Fr(Fr_mul(x,z));
}

void test_setup(){
    FILE *srs_g1;
    FILE *srs_g2;

   if ((srs_g1 = fopen("SRS_G1.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }

   for(int i = 0; i < 10; i++)
    {
        G1 srs;
        fread(&srs, sizeof(G1), 1, srs_g1); 
        printf("\n");
        print_Fp(srs.x);print_Fp(srs.y);
    }
   fclose(srs_g1); 

   if ((srs_g2 = fopen("SRS_G2.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }
    G2 srs2;
    fread(&srs2, sizeof(G2), 1, srs_g2); 
    printf("\n");
    print_Fp12(srs2.x);print_Fp12(srs2.y);

}

int main(){

    //test_Euclid();
    //test_Fp_exp();
    //test_Fp_Inv();
    //test_Fp_ext();
    //test_Fp_ext_Inv();
    //test_Fr();
    //test_poly();
    //test_poly_euclid_div();
    test_setup();

    return 0;
}