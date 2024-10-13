
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <gmp.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int320.h"
#include "int512.h"
#include "Fr.h"
#include "Poly.h"
#include "EC.h"
#include "Pairing.h"
#include "TwistedG2.h"
#include "KZG.h"
#include <time.h>

const int256 r = {0x30644E72E131A029,0xB85045B68181585D,0x2833E84879B97091,0x43E1F593F0000001};


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

    print_Fr(y);printf("\n");
    print_Fr(Fr_mul(x,y));printf("\n");
    print_Fr(Fr_mul(x,z));
}

void test_setup(){
    FILE *srs_g1;
    FILE *srs_g2;

   if ((srs_g1 = fopen("SRS_g1.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }

   for(int i = 0; i < 100; i++)
    {
        g1 srs;
        fread(&srs, sizeof(g1), 1, srs_g1); 
        printf("\n");
        print_Fp(srs.x);print_Fp(srs.y);
    }
   fclose(srs_g1); 

   if ((srs_g2 = fopen("SRS_g2.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }
    g2 srs2;
    fread(&srs2, sizeof(g2), 1, srs_g2); 
    printf("\n");
    print_Fp6(srs2.x);print_Fp12(srs2.y);
    fclose(srs_g2); 

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

void test_g1()
{  
   g1 A = {{{0x1083588805634D3F,0x51C50FEF5D4A71C5,0x877415191FFD2C46,0x923028175C2F45D3}}, {{0x1604C841A2B0A4BC,0x6A6FBFBFC45B2A46,0xAD0F7EE20A1F99BC,0xB13154224160F996}}};
   g1 B = {{{0x12E5C63E40D0A3E1,0x76D8AF88E5731746,0x4CF911570E142E6B,0x6CF5A1F1E272470C}}, {{0x7060D04CA61EA23,0x45FEABA976434E79,0x2E93FD8AB53A4FDB,0xC3957D8D1F39C96F}}};
   int256 a = {0,0,0,6548};
   g1 C = g1_add (A, B);
   g1 D = g1_mul_by_int(A,a);
   g1 E = g1_mul_by_int(A,r);
   print_g1(C);
   print_g1(D);
   print_g1(E);               
}

void test_g2()
{
    int256 a = {0,0,0,6548};
    
    Fp A1 = {{0x2CFC7B2345E6401B,0x2DF4923F8058718B,0xDC845E570A1AE9B1,0x3D97853E6C2B269A}};
    Fp A2 = {{0x22FA50A8B9951CDC,0x8E56E8C770EA498F,0x225F22168BD7A679,0x3E79F935033EAB3C}};
    Fp A3 = {{0x1BCD7A83D05A4D3A,0x42DD04CAC74CCE26,0x10D93BD12665F7BA,0x0877ECC24C99D7A4}};
    Fp A4 = {{0x143A32995F90A654,0x200AB4F5024C410D,0xC142282BA5475705,0x3C0B53E2EE2F6CF0}};

    Fp A5 = {{0x1650A85142F8CEE5,0xE1D8B4B4AE11EEEF,0xB4406E46024046C5,0x4D88F3B4B14D549E}};
    Fp A6 = {{0x2D48C1D0A657BB  ,0x9EFB5DD8AD575255,0x5362E03A1F55A30A,0x231406A465C755CF}};
    Fp A7 = {{0x141B8C7873B0A503,0x839FC1EA94EE725B,0xA30D73F6BE08A9E7,0xC56AEE0FCB56256F}};
    Fp A8 = {{0x20E75024288235A5,0x0B21481D4D7D2F8B,0xDA0FE1CA51650623,0x405F651A8C6C1EB8}};

    
    Fp2 B1 = {A1,A2};
    Fp2 B2 = {A3,A4};
    Fp2 B3 = {A5,A6};
    Fp2 B4 = {A7,A8};
    
    TwistedG2 C = {B1, B2};
    TwistedG2 D = {B3, B4};
    
    g2 P1 = g2_untwist(C);
    g2 Q = g2_untwist(D);

    print_g2(P1);printf("\n \n");
    print_g2(Q);printf("\n \n");

    g2 R = g2_add(P1,Q);
    print_g2(R);printf("\n \n");
    
    g2 R2 = g2_mul_by_int(P1,a);
    print_g2(R2);printf("\n \n");

    g2 H = g2_frobenius(R);
    g2 I = g2_mul_by_int(R,P);
    int i = g2_equal(H,I);
    printf("%d \n \n", i);

    Fp C1 = {{0x296A6F157EC84CF2,0x99D22CAB1377ACA8,0xB936AC1F2F726BD7,0x4D8ABCE3F5F89068}};
    Fp C2 = {{0x160F7D3E620A1007,0xB39641ED1D294460,0x21EE4B88782E12D8,0x5C1521DD3483B52F}};
    Fp C3 = {{0x182898BEBA3CDACD,0x20030F41DD3D276A,0x6DFA6068D99D29B9,0x74A8E6D3C0086E9A}};
    Fp C4 = {{0x1C75D5282EF3D1CA,0x225F3B37E38CF6A1,0x80721D5E3BF5A373,0xBCD40F5B0010581A}};
    
    Fp C5 = {{0xBF20BD5CA4914BB ,0xEC563EC25DB01045,0x052010E91C4F3B8E,0xD83A0975E4F045A3}};
    Fp C6 = {{0xD87F9AD9BB68000 ,0x144DBA44C32E9F73,0xB152FA1EAA969C80,0xF3C1AB0EF2F24EC2}};
    Fp C7 = {{0x26BAB2D581F7E3A5,0x5CA4ACA8CB5DB8D5,0x4193BD9A06302B10,0xE729263093E710AB}};
    Fp C8 = {{0x1A769663CD216DCE,0x4E50CC54B1A990CA,0x1CAF86CADA5B59C2,0x28DC3BC379FFF0B4}};
    

    Fp2 E1 = {C1,C2};
    Fp2 E2 = {C3,C4};
    Fp2 E3 = {C5,C6};
    Fp2 E4 = {C7,C8};

    TwistedG2 E = {E1, E2};
    TwistedG2 F = {E3, E4};

    g2 X = g2_untwist(E);
    g2 Y = g2_untwist(F);

    print_g2(X);printf("\n \n");
    print_g2(Y);printf("\n \n");


}

void test_pairing()
{
    int256 a = {0,0,0,6548};
    
    Fp A1 = {{0x2CFC7B2345E6401B,0x2DF4923F8058718B,0xDC845E570A1AE9B1,0x3D97853E6C2B269A}};
    Fp A2 = {{0x22FA50A8B9951CDC,0x8E56E8C770EA498F,0x225F22168BD7A679,0x3E79F935033EAB3C}};
    Fp A3 = {{0x1BCD7A83D05A4D3A,0x42DD04CAC74CCE26,0x10D93BD12665F7BA,0x0877ECC24C99D7A4}};
    Fp A4 = {{0x143A32995F90A654,0x200AB4F5024C410D,0xC142282BA5475705,0x3C0B53E2EE2F6CF0}};

    Fp A5 = {{0x1650A85142F8CEE5,0xE1D8B4B4AE11EEEF,0xB4406E46024046C5,0x4D88F3B4B14D549E}};
    Fp A6 = {{0x2D48C1D0A657BB  ,0x9EFB5DD8AD575255,0x5362E03A1F55A30A,0x231406A465C755CF}};
    Fp A7 = {{0x141B8C7873B0A503,0x839FC1EA94EE725B,0xA30D73F6BE08A9E7,0xC56AEE0FCB56256F}};
    Fp A8 = {{0x20E75024288235A5,0x0B21481D4D7D2F8B,0xDA0FE1CA51650623,0x405F651A8C6C1EB8}};
    
    Fp2 B1 = {A1,A2};
    Fp2 B2 = {A3,A4};
    Fp2 B3 = {A5,A6};
    Fp2 B4 = {A7,A8};
    
    TwistedG2 C = {B1, B2};
    TwistedG2 D = {B3, B4};
    
    g2 P = g2_untwist(C);
    g2 Q = g2_untwist(D);

    g2 PplusQ = g2_add(P,Q);

    Fp G_x = {0x187CC1E6F77C59DD,0x29AC8214D5733697,0xB33601F06D087C26,0xC1D8F343FA92FFC2};
    Fp G_y = {0x197C3E3702A874C3,0x424634A83761F37A,0xD8E8E8E4BE86082B,0xC8D9C9E6FE14275E};

    g1 A = {G_x, G_y};
   
   // g1 AplusB = g1_add (A, B);

   Fp12 K = Tate_pairing(A,PplusQ);
   Fp12 K2 = Fp12_mul(Tate_pairing(A,P),Tate_pairing(A,Q));

   print_Fp12(K) ;printf("\n \n");
   print_Fp12(K2);printf("\n \n");


   Fp12 F = Tate_pairing(A,g2_mul_by_int(P,a));
   Fp12 F2 = Tate_pairing(g1_mul_by_int(A,a),P);

   print_Fp12(F) ;printf("\n \n");
   print_Fp12(F2);printf("\n \n");


}

// void calculdelexposant()
// {
//     unsigned long int k = 12;
//     mpz_t p,y,z,w;
//     mpz_init(p);
//     mpz_init(y);
//     mpz_init(z);
//     mpz_init(w);
//     mpz_set_str(p, "30644e72e131a029b85045b68181585d97816a916871ca8d3c208c16d87cfd47", 16);
//     mpz_set_str(y, "30644E72E131A029B85045B68181585D2833E84879B9709143E1F593F0000001", 16);
//     mpz_pow_ui(z,p,k); mpz_out_str(stdout,2,z); printf("\n"); printf("\n");
//     mpz_sub_ui(z,z,1); mpz_out_str(stdout,2,z); printf("\n"); printf("\n");
//     mpz_cdiv_r(w,z,y);
//     mpz_cdiv_q(z,z,y);
//     mpz_out_str(stdout,2,z); printf("\n"); printf("\n");
//     mpz_out_str(stdout,16,w); printf("\n");
// }

void test_frobenius(){

    FILE *srs_g2;


   if ((srs_g2 = fopen("SRS_g2.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }
    g2 H;
    fread(&H, sizeof(g2), 1, srs_g2); 
    printf("\n");
    g2 pH = g2_mul_by_int(H, P);
    g2 froH = g2_frobenius(H);

    printf("\n%d",g2_equal(pH,froH));
    

    fclose(srs_g2);


    Fp A5 = {{0x1650A85142F8CEE5,0xE1D8B4B4AE11EEEF,0xB4406E46024046C5,0x4D88F3B4B14D549E}};
    Fp A6 = {{0x2D48C1D0A657BB  ,0x9EFB5DD8AD575255,0x5362E03A1F55A30A,0x231406A465C755CF}};
    Fp A7 = {{0x141B8C7873B0A503,0x839FC1EA94EE725B,0xA30D73F6BE08A9E7,0xC56AEE0FCB56256F}};
    Fp A8 = {{0x20E75024288235A5,0x0B21481D4D7D2F8B,0xDA0FE1CA51650623,0x405F651A8C6C1EB8}};
    
    Fp2 B3 = {A5,A6};
    Fp2 B4 = {A7,A8};
    
    TwistedG2 D = {B3, B4};
    
    g2 Q = g2_untwist(D);

    printf("\n");
    g2 pQ = g2_mul_by_int(Q, P);
    g2 froQ = g2_frobenius(Q);

    printf("\n%d",g2_equal(pQ,froQ));

}

void test_TwistedG2(){


    FILE *srs_g2;


   if ((srs_g2 = fopen("SRS_g2.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }
    g2 H;
    fread(&H, sizeof(g2), 1, srs_g2);

    Fr lambda = Fr_from_4_int(765,657543,109763,1111);
    g2 lamH = g2_mul_by_int(H, lambda.num);
    
    TwistedG2 tH = g2_twist(H);
    TwistedG2 lamTH = TwistedG2_mul_by_int(tH, lambda.num);

    g2 lamH2 = g2_untwist(lamTH);


    // Fp A1 = {{0x2CFC7B2345E6401B,0x2DF4923F8058718B,0xDC845E570A1AE9B1,0x3D97853E6C2B269A}};
    // Fp A2 = {{0x22FA50A8B9951CDC,0x8E56E8C770EA498F,0x225F22168BD7A679,0x3E79F935033EAB3C}};
    // Fp A3 = {{0x1BCD7A83D05A4D3A,0x42DD04CAC74CCE26,0x10D93BD12665F7BA,0x0877ECC24C99D7A4}};
    // Fp A4 = {{0x143A32995F90A654,0x200AB4F5024C410D,0xC142282BA5475705,0x3C0B53E2EE2F6CF0}};
    
    // Fp2 B1 = {A1,A2};
    // Fp2 B2 = {A3,A4};
    
    // TwistedG2 C = {B1, B2};
    
    // g2 P = g2_untwist(C);

    // TwistedG2 C2 = g2_twist(P);
    
    // printf("\n\n%d\n\n",TwistedG2_equal(C,C2));

    printf("pls be 1: %d",g2_equal(lamH, lamH2));
    


    fclose(srs_g2); 
}

void test_final_exp(){
    Fp12 x = Fp12_zero();
    x.x0.x0.x0 = Fp_from_int(7597);
    //x.x1.x2.x1 = Fp_from_int(6);

    x = Fp12_exp(x, R);

    
    printf("\n\n\n");

    print_Fp12(final_exp(x));printf("\n\n\n");
}

void get_e_GH(){
    FILE *srs_g1;


   if ((srs_g1 = fopen("SRS_g1.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }
    g1 G;
    fread(&G, sizeof(g1), 1, srs_g1);

    FILE *srs_g2;


   if ((srs_g2 = fopen("SRS_g2.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }
    g2 H;
    fread(&H, sizeof(g2), 1, srs_g2);

    Fp12 e = Tate_pairing(G, H);
    Fp12 e2 = e_GH();
    printf("%d",Fp12_equal(e,e2));
}

void test_test(){

    clock_t start, end;

    double mul_time = 0;
    double daa_mul_time = 0;
    double mq_mul_time = 0;
    double mq2_mul_time = 0;
    double mq3_mul_time = 0;

    int sample_size = 10000;

    for (int i = 0; i < sample_size; i++)
    {
        Fr A = get_rand_Fr();
        Fr B = get_rand_Fr();

        start = clock();
        Fr C = Fr_mul_original(A,B);
        end = clock();
        mul_time += ((double) (end - start))/CLOCKS_PER_SEC;


        start = clock();
        Fr C2 = Fr_mul_daa(A,B);
        end = clock();
        daa_mul_time += ((double) (end - start))/CLOCKS_PER_SEC;

        start = clock();
        Fr C3 = Fr_mul_mq(A,B);
        end = clock();
        mq_mul_time += ((double) (end - start))/CLOCKS_PER_SEC;

        start = clock();
        Fr C4 = Fr_mul_mq2(A,B);
        end = clock();
        mq2_mul_time += ((double) (end - start))/CLOCKS_PER_SEC;

        start = clock();
        Fr C5 = Fr_mul(A,B);
        end = clock();
        mq3_mul_time += ((double) (end - start))/CLOCKS_PER_SEC;


        if (!Fr_equal(C, C2))
        {
            printf("erreur\n");
        }
        if (!Fr_equal(C, C3))
        {
            printf("erreur\n");
        }
        if (!Fr_equal(C, C5))
        {
            printf("erreur\n");
        }
    }
    printf("\nTemps de multiplication moyen: %f microsecond \n", mul_time/sample_size * 1000000);
    printf("Temps de multiplication moyen avec double-and-add: %f microsecond \n", daa_mul_time/sample_size * 1000000);
    printf("Temps de multiplication moyen avec mq: %f microsecond \n", mq_mul_time/sample_size * 1000000);
    printf("Temps de multiplication moyen avec mq2: %f microsecond \n", mq2_mul_time/sample_size * 1000000);
    printf("Temps de multiplication moyen avec mq3: %f microsecond \n", mq3_mul_time/sample_size * 1000000);

    Fr rand = get_rand_Fr();
    Fr rand2 = Fr_from_4_int(0x100000000,0,0,0);//get_rand_Fr();
    print_Fr(rand);
    printf("%u",cmp_256(rand.num, R));

    printf("\n\n\nmult = ");
    print_Fr(Fr_mul_original(rand,rand));
    printf("\nmult daa = ");
    print_Fr(Fr_mul_daa(rand,rand));
    printf("\nmult mq = ");
    print_Fr(Fr_mul_mq(rand,rand));
    printf("\nmult mq2 = ");
    print_Fr(Fr_mul_mq2(rand,rand));
    printf("\nmult mq3 = ");
    print_Fr(Fr_mul(rand,rand));

    printf("\n\n\n");
    
    int512 tp256 = {0,0,0,1,0,0,0,0};
    int512 tp288 = {0,0,0,0x100000000,0,0,0,0};
    int512 tp320 = {0,0,1,0,0,0,0,0};
    int512 tp352 = {0,0,0x100000000,0,0,0,0,0};
    int512 tp384 = {0,1,0,0,0,0,0,0};
    int512 tp416 = {0,0x100000000,0,0,0,0,0,0};
    int512 tp448 = {1,0,0,0,0,0,0,0};
    int512 tp480 = {0x100000000,0,0,0,0,0,0,0};

    
    print_256(modulo(tp256, P)); printf("\n");
    print_256(modulo(tp288, P)); printf("\n");
    print_256(modulo(tp320, P)); printf("\n");
    print_256(modulo(tp352, P)); printf("\n");    
    print_256(modulo(tp384, P)); printf("\n");
    print_256(modulo(tp416, P)); printf("\n");
    print_256(modulo(tp448, P)); printf("\n");
    print_256(modulo(tp480, P)); printf("\n");  
      
}

int main(){
   
    //test_Euclid();
    test_Fp_exp();
    //test_Fp_Inv();
    //test_Fp_ext();    
    //test_Fp_ext_Inv();
    //test_Fr();
    //test_poly();
    //test_poly_euclid_div();
    //test_setup();
    //test_g1();
    //test_g2();
    //test_frobenius();
    //test_final_exp();

    //test_pairing();
    //test_test();

    //test_TwistedG2();
    //get_e_GH();

    return 0;
}

