#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "int256.h"
#include "int512.h"

#ifndef FP6_H
#define FP6_H


typedef struct Fp6
{
	Fp2 x2;
	Fp2 x1;
	Fp2 x0;
}Fp6;

Fp6 Fp6_add(Fp6 a,Fp6 b);

Fp6 Fp6_sub(Fp6 a,Fp6 b);

Fp6 Fp6_mul(Fp6 a,Fp6 b);

#endif