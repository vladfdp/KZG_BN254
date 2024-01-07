#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "int256.h"
#include "int512.h"

#ifndef FP2_H
#define FP2_H

typedef struct Fp2
{
	Fp x0;
	Fp x1;
	
}Fp2;  // Fp2 = Fp[u]/(u^2+1)

Fp2 Fp2_add(Fp2 a,Fp2 b);

Fp2 Fp2_sub(Fp2 a,Fp2 b);

Fp2 Fp2_mul(Fp2 a,Fp2 b); 

void print_Fp2(Fp2 a);

#endif