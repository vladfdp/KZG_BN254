#include <stdio.h>
#include <stdlib.h>
#include "Fp.h"
#include "Fp2.h"
#include "int256.h"
#include "int512.h"


Fp2 Fp2_add(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x0 = Fp_add(a.x0,b.x0);
	c.x1 = Fp_add(a.x1,b.x1);
	return c;
}

Fp2 Fp2_mul(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x0 = Fp_sub(Fp_mul(a.x0, b.x0), Fp_mul(a.x1,b.x1));
	c.x1 = Fp_add(Fp_mul(a.x0,b.x1),Fp_mul(b.x0,a.x1));
	return c;
}

Fp2 Fp2_sub(Fp2 a,Fp2 b)
{
	Fp2 c;
	c.x0 = Fp_sub(a.x0,b.x0);
	c.x1 = Fp_sub(a.x1,b.x1);
	return c;
}

void print_Fp2 (Fp2 a)
{
	print_Fp(a.x0);
	printf("+");
	print_Fp(a.x1);
	printf("u");
}
