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


#endif