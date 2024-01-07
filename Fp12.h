#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "Fp6.h"
#include "int256.h"
#include "int512.h"

#ifndef FP12_H
#define FP12_H


typedef struct Fp12
{
	Fp6 x0;
	Fp6 x1;
	
}Fp12; // Fp12 = Fp6[w]/(w^2-v)

Fp12 Fp12_add(Fp12 a,Fp12 b);

Fp12 Fp12_sub(Fp12 a,Fp12 b);

Fp12 Fp12_mul(Fp12 a,Fp12 b);

void print_Fp12(Fp12 a);


#endif