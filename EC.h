#ifdef __cplusplus
extern "C" {
#endif

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


typedef struct g1
{
	Fp x;
	Fp y;
} g1;

typedef struct g2
{
	Fp6 x;
	Fp12 y;
} g2;

g1 g1_zero();

g2 g2_zero();

int g1_equal(g1 P1,g1 P2);

g1 g1_add(g1 P1, g1 P2);

g1 g1_oppo(g1 P0);

int g2_equal(g2 P1,g2 P2);

g2 g2_add(g2 P1, g2 P2);

g2 g2_oppo(g2 P0);

int g2_is_on_curve(g2 P);

g1 g1_mul_by_int(g1 base, int256 exponent);

g2 g2_mul_by_int(g2 base, int256 exponent);

g2 g2_mul_by_int_twist(g2 base, int256 exponent);

void print_g1(g1 P);

void print_g2(g2 P);

g2 g2_frobenius(g2 A);





#endif

#ifdef __cplusplus
}
#endif