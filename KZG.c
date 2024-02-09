#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Poly.h"
#include "EC.h"
#include "Pairing.h"
#include "TwistedG2.h"

Fp12 e_GH(){

    Fp12 e_GH;

    Fp a1 = {{0x92c34e7f72f7814,0x1f2fbd0e2171c4c5,0xa7f32bc136354647,0xf630991bd423cf7c}};
    Fp a2 = {{0x14a270fda0009f41,0xfccb4e08254201f,0x2111b72165ae7ab8,0xe2db3b2cca9615c8}};
    Fp a3 = {{0x2edb75a51bed610c,0xc4e3750728468f1c,0x1eb3c806bf86a085,0x99a301c592790044}};
    Fp a4 = {{0x2a5380bc8ef5c530,0x39e91cb5db0a9dff,0xc9119bf59d53a40d,0x57ee74ca3256b625}};
    Fp a5 = {{0x2cf73513b4ba255e,0x5383ea0b2ffe2747,0xd69fd9ccdbf1ba29,0xe4f86800212f6e74}};
    Fp a6 = {{0x8a1f665f8107c0d,0xbbee5d86ce2fea9d,0x17f7ea299eb1fb3f,0x7364f557898c2ca3}};
    Fp a7 = {{0x19470bf6b94966fd,0xe2d4ab74b83649b5,0xe546aea85b374e35,0x18f26e433995af2}};
    Fp a8 = {{0x22d9f96d0869e6d0,0x63af4ddd6c8f7240,0xe4e7ce5fd59acec9,0xfb7731e06bafe633}};
    Fp a9 = {{0x1582860262e32884,0x2bfcb0a6cd34b98c,0x3a6a3d6b2e5ae7c6,0xdc34c57023f01f1b}};
    Fp a10 = {{0x6288a3d5f08227e,0x7c75ca5c68821965,0xe7b0d476abc3c2a7,0x32c09c04b271253d}};
    Fp a11 = {{0x15e9ff8993eaf5e0,0x9ba417719c588ce5,0x8c1e00f9aa0e7388,0xd6046a6dea38e5a2}};
    Fp a12 = {{0xd758f0ff70cf5b8,0x8175762e662ba544,0xcc91bec6397eba36,0x8db6d068412b3ebc}};

    e_GH.x0.x0.x0 = a1;
    e_GH.x0.x0.x1 = a2;
    e_GH.x0.x1.x0 = a3;
    e_GH.x0.x1.x1 = a4;
    e_GH.x0.x2.x0 = a5;
    e_GH.x0.x2.x1 = a6;
    e_GH.x1.x0.x0 = a7;
    e_GH.x1.x0.x1 = a8;
    e_GH.x1.x1.x0 = a9;
    e_GH.x1.x1.x1 = a10;
    e_GH.x1.x2.x0 = a11;
    e_GH.x1.x2.x1 = a12;

    return e_GH;
}

int verify(G1 commit, G1 proof, Fr index, Fr eval){

    FILE *srs_g2;

    if ((srs_g2 = fopen("SRS_G2.bin","rb")) == NULL){       //on ouvre le SRS
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }

    G2 H;
    G2 alpha_H;
    fread(&H, sizeof(G2), 1, srs_g2);
    fread(&alpha_H, sizeof(G2), 1, srs_g2); 


    Fp12 e_gh = e_GH();

    G2 ind_H = G2_mul_by_int_twist(H, Fr_opp(index).num);
    G2 cofactor = G2_add( alpha_H , ind_H);                 // (alpha - index) * H

    Fp12 exp_eval = Fp12_exp(e_gh, eval.num);               // e(G,H)^eval
    Fp12 pairing = Tate_pairing(proof, cofactor);

    Fp12 lhs = Tate_pairing(commit, H);
    Fp12 rhs = Fp12_mul(pairing, exp_eval);

    return Fp12_equal(lhs, rhs);                            //on evalue e(commit, H) = e(proof, (alhpa - index)H) * e(G,H)^eval
}

G1 commit(Poly poly){

    FILE *srs_g1;

    if ((srs_g1 = fopen("SRS_G1.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");    //On ouvre le SRS

       exit(1);
    }

    G1 ans = G1_zero();
    G1 alpha_i_G;
    
    for (int i = 0; i < poly.degree + 1; i++)                   //on calcul poly(alpha) * G
    {
        fread(&alpha_i_G, sizeof(G1), 1, srs_g1);
        ans = G1_add(ans, G1_mul_by_int(alpha_i_G, poly.coeffs[i].num ));
    }
    return ans;
}

G1 create_witness(Poly poly, Fr index, Fr eval){

    poly.coeffs[0] = Fr_sub(poly.coeffs[0], eval);

    Poly van_poly = vanish_Poly(index);

    Poly quotient = euclidean_div_Poly(poly, van_poly);     //on calcule poly / (X - index)

    G1 proof = commit(quotient);                            //et on renvoie son commit

    free_Poly(quotient);

    return proof;
}

