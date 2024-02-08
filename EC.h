#ifndef EC
#define EC

#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "Fp12.h"
#include "Fr.h"
#include "int256.h"
#include "int512.h"

typedef struct G1
{
	Fp x;
	Fp y;
} G1;

typedef struct G2
{
	Fp6 x;
	Fp12 y;
} G2;

G1 G1_zero();

G2 G2_zero();

int G1_equal(G1 P1,G1 P2);

G1 G1_add(G1 P1, G1 P2);

G1 G1_oppo(G1 P0);

int G2_equal(G2 P1,G2 P2);

G2 G2_add(G2 P1, G2 P2);

G2 G2_oppo(G2 P0);

int G2_is_on_curve(G2 P);

G1 G1_mul_by_int(G1 base, int256 exponent);

G2 G2_mul_by_int(G2 base, int256 exponent);

G2 G2_mul_by_int_twist(G2 base, int256 exponent);

void print_G1(G1 P);

void print_G2(G2 P);

G2 G2_frobenius(G2 A);





#endif