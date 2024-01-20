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

typedef struct G1
{
	Fp x;
	Fp y;
} G1;

typedef struct G2
{
	Fp12 x;
	Fp12 y;
} G2;

int G1_equal(G1 P1,G1 P2);

G1 G1_add(G1 P1, G1 P2);

G1 G1_oppo(G1 P0);

int G2_equal(G2 P1,G2 P2);

G2 G2_add(G2 P1, G2 P2);

G2 G2_oppo(G2 P0);





#endif