#ifndef PAIRING
#define PAIRING

#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"

Fp12 Tate_pairing(G1 P, G2 Q, int256 r);

Fp12 exp_par_un_mega_int(Fp12 base);

Fp Millerloop(G1 P, G1 Q, int256 r);

Fp Weil_pairing(G1 P, G1 Q, int256 r);

#endif