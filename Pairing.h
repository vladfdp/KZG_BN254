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

typedef struct EFp
{
	Fp x0;
	Fp x1;
} EFp;

typedef struct EFp12
{
	Fp12 x0;
	Fp12 x1;
} EFp12;

int EFp_is_equal(EFp P1,EFp P2);

EFp EFp_add(EFp P1, EFp P2);

EFp EFp_oppo(EFp P0);

int EFp12_is_equal(EFp12 P1,EFp12 P2);

EFp12 EFp12_add(EFp12 P1, EFp12 P2);

EFp12 EFp12_oppo(EFp12 P0);





#endif