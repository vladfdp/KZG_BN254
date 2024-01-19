#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fr.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Poly.h"
int verify(G1 commit, G1 proof, Fr index, Fr eval){

    G2 cofactor = G2_add( SRS_G2[1] , G2_mul_scal(Fr_opp(index), SRS_G2[0]) ); // (alpha - index) * H
    Fp12 exp_eval = Fp12_exp(e_gh, eval.num); // e(G,H)^eval
    Fp12 pairing = EC_pairing(proof, cofactor);

    Fp12 lhs = EC_pairing(commit, H);
    Fp12 rhs = Fp12_mul(pairing, exp_eval);

    return Fp12_equal(lhs, rhs);
}

G1 commit(Poly poly){

    G1 ans = G1_zero();
    
    for (int i = 0; i < poly.degree + 1; i++)
    {
        ans = G1_add(ans, G1_mul( poly.coeffs[i], SRS_G1[i]));
    }
    return ans;
}

G1 create_proof_at_point(Poly poly, Fr index, Fr eval){

    poly.coeffs[0] = Fr_add(poly.coeffs[0], Fr_opp(eval));

    Poly van_poly = vanish_Poly(eval);

    Poly quotient = euclidean_div_Poly(poly, van_poly);

    return commit(quotient);
}