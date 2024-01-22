#include <stdio.h>
#include <stdlib.h>
#include "Fr.h"
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Poly.h"
#include "EC.h"

int verify(G1 commit, G1 proof, Fr index, Fr eval){

    FILE *srs_g2;

   if ((srs_g2 = fopen("SRS_G2.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }

    G2 H;
    G2 alpha_H;
    fread(&H, sizeof(G2), 1, srs_g2);
    fread(&alpha_H, sizeof(G2), 1, srs_g2); 


    G2 ind_H = G2_mul_scal(Fr_opp(index), H);
    G2 cofactor = G2_add( SRS_G2[1] , ind_H); // (alpha - index) * H

    Fp12 exp_eval = Fp12_exp(e_gh, eval.num); // e(G,H)^eval
    Fp12 pairing = EC_pairing(proof, cofactor);

    Fp12 lhs = EC_pairing(commit, H);
    Fp12 rhs = Fp12_mul(pairing, exp_eval);

    return Fp12_equal(lhs, rhs);
}

G1 commit(Poly poly){

    FILE *srs_g1;

    if ((srs_g1 = fopen("SRS_G1.bin","rb")) == NULL){
       printf("Missing SRS, run setup using 'make setup'");

       exit(1);
    }


    G1 ans = G1_zero();
    G1 alpha_i_G;
    
    for (int i = 0; i < poly.degree + 1; i++)
    {
        fread(&alpha_i_G, sizeof(G1), 1, srs_g1);
        ans = G1_add(ans, G1_mul_scal( poly.coeffs[i], alpha_i_G));
    }
    return ans;
}

G1 create_proof_at_point(Poly poly, Fr index, Fr eval){

    poly.coeffs[0] = Fr_add(poly.coeffs[0], Fr_opp(eval));

    Poly van_poly = vanish_Poly(eval);

    Poly quotient = euclidean_div_Poly(poly, van_poly);

    G1 proof = commit(quotient);

    free_Poly(quotient);

    return proof;
}