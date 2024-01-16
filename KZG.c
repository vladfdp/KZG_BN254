#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fr.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"

int verify(G1 commit, G1 proof, Fr index, Fr eval){

    Fp12 exp_eval = Fp12_exp(e_gh, eval.num); // e(G,H)^eval
    G2 cofactor = G2_add( SRS_alpha_H , G2_mul_scal(Fr_opp(index),H) ); // (alpha - index) * H
    Fp12 pairing = EC_pairing(proof, cofactor);

    Fp12 lhs = EC_pairing(commit, H);
    Fp12 rhs = Fp12_mul(pairing, exp_eval);

    return Fp12_equal(lhs, rhs);
}

G1 commit(polynomial poly)