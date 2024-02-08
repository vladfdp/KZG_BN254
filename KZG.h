#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fr.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Poly.h"
#include "EC.h"

const Fp12 e_gh = {};

int verify(G1 commit, G1 proof, Fr index, Fr eval);

G1 commit(Poly poly);

G1 create_proof_at_point(Poly poly, Fr index, Fr eval);