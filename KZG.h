#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fr.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Poly.h"
#include "EC.h"

int verify(g1 commit, g1 proof, Fr index, Fr eval);

g1 commit(Poly poly);

g1 create_witness(Poly poly, Fr index, Fr eval);

Fp12 e_GH();


#ifdef __cplusplus
}
#endif