#ifdef __cplusplus
extern "C" {
#endif

#ifndef TWISTEDg2_H
#define TWISTEDg2_H

#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Fr.h"
#include "int256.h"
#include "int512.h"
#include "EC.h"

typedef struct TwistedG2
{
	Fp2 x;
	Fp2 y;
} TwistedG2;



TwistedG2 g2_twist(g2 P);

g2 g2_untwist(TwistedG2 P);

TwistedG2 TwistedG2_zero();

TwistedG2 TwistedG2_opp(TwistedG2 P0);

int TwistedG2_equal(TwistedG2 P1, TwistedG2 P2);

TwistedG2 TwistedG2_add(TwistedG2 P1, TwistedG2 P2);

TwistedG2 TwistedG2_mul_by_int(TwistedG2 base, int256 exponent);

#endif

#ifdef __cplusplus
}
#endif