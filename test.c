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
#include "Pairing.h"
  


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

   for(int i = 0; i < 100; i++)
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
    print_Fp6(srs2.x);print_Fp12(srs2.y);

}

void test_EC_gen(){

    Fp x = {0x187CC1E6F77C59DD,0x29AC8214D5733697,0xB33601F06D087C26,0xC1D8F343FA92FFC2};
    Fp y = {0x197C3E3702A874C3,0x424634A83761F37A,0xD8E8E8E4BE86082B,0xC8D9C9E6FE14275E};

    Fp x2 = Fp_mul(x,x);
    Fp x3 = Fp_mul(x2, x);
    Fp x3pb = Fp_add(x3, Fp_from_int(3));

    Fp y2 = Fp_mul(y,y);

    printf("\n");
    print_Fp(Fp_sub(y2,x3pb));
    printf("\n");printf("\n");


    Fp12 x1 = Fp12_zero();
    Fp12 y1 = Fp12_zero();

    Fp x10 = {0x2351A862F99A2E05,0x202DB891D078A76E,0x4316B508B69C17DE,0x69B71BDCEEA9943F};
    Fp x11 = {0x1B09333D8FFAF56,0x702D0CDB0C731DC1,0xE806C87EAC937733,0xC82BD78D428F66CE};

    Fp y10 = {0x2C6977D27D199BA8,0xBB2A4FFC86E57425,0x04B88246B19977D4,0xC52C2436273F7DF1};
    Fp y11 = {0x2D5991DC9820B9CB,0xEAB5AA224869A316,0x859C7B603A8EFF71,0x6670A2DCA426B521};


    x1.x0.x0.x0 = x10;
    x1.x0.x0.x1 = x11;

    y1.x0.x0.x0 = y10;
    y1.x0.x0.x1 = y11;


    Fp12 y1sq = Fp12_mul(y1, y1);

    Fp12 x1sq = Fp12_mul(x1,x1);
    Fp12 x1cub = Fp12_mul(x1, x1sq);

    Fp12 three = Fp12_zero();
    three.x0.x0.x0 = Fp_from_int(3);

    Fp12 zeta = Fp12_zero();
    zeta.x0.x0.x0 = Fp_from_int(9);
    zeta.x0.x0.x1 = Fp_one();

    Fp12 x1cubpB = Fp12_add(x1cub, Fp12_div(three, zeta));

    print_Fp12(Fp12_sub(y1sq, x1cubpB));
    printf("\n\n");


    Fp12 omega = Fp12_zero();
    omega.x1 = Fp6_one();

    Fp12 omesq = Fp12_mul(omega, omega);
    Fp12 omecub = Fp12_mul(omesq, omega);

    Fp12 untx = Fp12_mul(omesq, x1);
    Fp12 unty = Fp12_mul(omecub, y1);

    // print_Fp12(omega);printf("\n");
    // print_Fp12(omesq);printf("\n");
    // print_Fp12(omecub);printf("\n\n");

    print_Fp12(Fp12_inv(omesq));printf("\n");
    print_Fp12(Fp12_inv(omecub));printf("\n");


    Fp12 untysq = Fp12_mul(unty, unty);
    Fp12 untxsq = Fp12_mul(untx, untx);
    Fp12 untxcub = Fp12_mul(untxsq, untx);
    Fp12 untxcubp3 = Fp12_add(untxcub, three);

    print_Fp12(Fp12_sub(untysq, untxcubp3));


    Fp6 H_x;
    Fp12 H_y;


    Fp x_a = {0x2351a862f99a2e05,0x202db891d078a76e,0x4316b508b69c17de,0x69b71bdceea9943f};
    Fp x_b = {0x1b09333d8ffaf56,0x702d0cdb0c731dc1,0xe806c87eac937733,0xc82bd78d428f66ce};

    Fp y_c = {0x2c6977d27d199ba8,0xbb2a4ffc86e57425,0x4b88246b19977d4,0xc52c2436273f7df1};
    Fp y_d = {0x2d5991dc9820b9cb,0xeab5aa224869a316,0x859c7b603a8eff71,0x6670a2dca426b521};


    H_x.x0 = Fp2_zero();
    H_x.x2 = Fp2_zero();
    H_x.x1.x0 = x_a;
    H_x.x1.x1 = x_b;

    H_y.x0 = Fp6_zero();
    H_y.x1.x0 = Fp2_zero();
    H_y.x1.x2 = Fp2_zero();

    H_y.x1.x1.x0 = y_c;
    H_y.x1.x1.x1 = y_d;

    Fp12 H_ysq = Fp12_mul(H_y, H_y);
    Fp6 H_xsq = Fp6_mul(H_x, H_x);
    Fp6 H_xcub = Fp6_mul(H_xsq, H_x);


    printf("\n\n\n");
    //print_Fp12(Fp12_sub(H_ysq, Fp6_to_Fp12(H_xcub)));

}

// 268FF4DCF71C97A2C4C5275F368914E0D7FAAEDF79B9414190409DBBE802D801

void test_G1()
{  
   G1 A = {{{0x1083588805634D3F,0x51C50FEF5D4A71C5,0x877415191FFD2C46,0x923028175C2F45D3}}, {{0x1604C841A2B0A4BC,0x6A6FBFBFC45B2A46,0xAD0F7EE20A1F99BC,0xB13154224160F996}}};
   G1 B = {{0x12E5C63E40D0A3E1,0x76D8AF88E5731746,0x4CF911570E142E6B,0x6CF5A1F1E272470C}, {{0x7060D04CA61EA2345,0xFEABA976434E792E,0x93FD8AB53A4FDB,0xC3957D8D1F39C96F}}};
   int256 a = {0,0,0,1100110010100};
   G1 C = G1_add (A, B);
   G1 D = G1_mul_by_int(A,a);
   print_G1(C);
   print_G1(D);
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
    //test_setup();
    test_G1();

    
    
    return 0;
}